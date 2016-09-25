/* ************************************************************************
 *       Filename:  mplayer_process.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月23日 18时05分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "common.h"
#include "file.h"
#include "link.h"
#include "process_lrc.h"
#include "mplayer_control.h"
#include "mplayer_pthread.h"


SONG song;


void mplayer_init(MPLAYER *pm)
{
	FILE *fp = NULL;
	int i = 0, ret = 0;
	char buf[128];

	song.song_src = (char *)get_musiclist(&song.psong_list, &song.count);
	if(song.count > 0)
	{
		song.search = NULL;
		song.search = (char *)malloc(song.count + 1);
		if(song.search == NULL) perror("");	
		bzero(song.search, song.count+1);
	}
	
	pm->playflag  = playing;  //暂停
	pm->playmode  = list_loop;//列表顺序播放模式 
	pm->soundflag = beam;     //播音

	bzero(song.name, sizeof(song.name));
	fp = fopen(".song", "r");
	if(fp != NULL)
	{
		fread(buf, sizeof(buf), 1, fp);
		
		if(get_songname(song.name,buf) == 0)
		{
			printf("get_songname = %s\n",song.name);
			for(i = 0;i < song.count; i++)
			{
				if(strcmp(song.name,song.psong_list[i]) == 0)
				{
					song.now = i;
					song.old = i;				
					break;
				}
			}
			if(i == song.count) 
			{
				song.now = 0;   
				song.old = 0;
				strcpy(song.name, song.psong_list[0]);
			}
		}
	}
	else
	{
		song.now = 6;  
		song.old = 6;
		strcpy(song.name, song.psong_list[6]);
	}
	song.keyflag = init;
	song.endflag = FALSE;
	
	//?
	ret = pipe(pm->fd);   
	if(ret < 0) perror("pipe");

	unlink("./.cmd_fifo");      //
	mkfifo("./.cmd_fifo",0666); //
	pm->fd_pipe = open("./.cmd_fifo", O_RDWR);	
	//write(pm->fd_pipe, "pause\n", strlen("pause\n"));//
	
	//??
	sem_init(&song.sem_keyflag, 0, 1);
	sem_init(&song.sem_setsong, 0, 1);

	//?
	pthread_mutex_init(&pm->mutex, NULL);
}

int mplayer_process(MPLAYER *pm)
{		
	pm->pid = fork();//
	
	if(pm->pid < 0)
	{
		perror("fork:");
		return(-1);
	}	
	
	if(pm->pid == 0)
	{
		//char buf[256] = "./music/";
		//printf("in son process  >> song_name = %s\n",song.name);
		//strcat(buf,song.name);		
		 
		if( dup2(pm->fd[1], 1) < 0) perror("dup2");//??

		printf("start mplayer now!\n");
		
		//启动mplayer		
		execlp("mplayer",		      
		       "mplayer",			  
	           "-slave", "-quiet","-idle",			  
		       "-input", "file=./.cmd_fifo",			   
		       "./music/login.wav", NULL);
		exit(0);		
	}

	return 0;
}

void gtk_thread_init(void)
{
	if( FALSE == g_thread_supported() )	
	{  
		g_thread_init(NULL);
	}
	gdk_threads_init();
}

void *pthread_show_lrc(void *agr)
{
	MPLAYER *pm = (MPLAYER *)agr;
	LRC *pb = NULL;
	char buf[256];
	char lrc_path[]  = "./music/lyric/";
	
	while(1)
    {  	
		usleep(500*MS);

		if(pm->playflag == playing)
		{
			if(song.keyflag != quiet)
			{   	
				set_keyflag(quiet);
				free_link(song.lrc_head);
				
				bzero(buf,sizeof(buf));
				strcat(buf,lrc_path);
		    	strcat(buf,song.name);			
				get_lrcname(buf);			
				
				dispose_lrc(pm, buf);		
				playing_song(pm, song.now);
				
				song.cur_time = 0;
				song.end_time = 0;
				song.endflag  = FALSE;
			}
			
			if(song.pnode != NULL && song.cur_time >= song.pnode->time) //		
			{		
				pb = NULL;
				pb = (LRC *)search_link(song.pnode, song.pnode->time); //song.pnode???????
				mplayer_show_lyric(pm, pb);	
				
				if(pb != NULL) song.pnode = song.pnode->next;		
			}		
			
			if((song.rate/100.0) >= 0.99) //
			{			
				song.endflag = TRUE;				
				set_playing_song(pm, 1);
				set_keyflag(init);
				song.rate = 0;			
			}	

		}
	}
}

void *pthread_send_cmd(void *agr)
{
	MPLAYER *pm = (MPLAYER *)agr;
	char *cmd[]={ "get_percent_pos\n", "get_time_pos\n","get_time_length\n", "get_file_name\n", "get_meta_artist\n"};
	int i = 0;
	
	while(1)
	{		
		for(i=0; i < 5; i++)
		{
			if((pm->playflag == playing) && (song.endflag == FALSE))
			{
				send_cmd(cmd[i], pm);
				usleep(100*MS);
			}
		}		
	}
}

void *pthread_rcv_msg(void *agr)
{
	MPLAYER *pm = (MPLAYER *)agr;
	float temp = 0.0;
	char msg[256];
	char *p = NULL, buf[16];
	
	while(1)
	{	
		usleep(80*MS);
		
		if(pm->playflag == playing)
		{
			bzero(msg,sizeof(msg));	
			read(pm->fd[0], msg, sizeof(msg));	
			
			//printf(">>>>>pthread_rcv_msg  = %s\n",msg);
			if((p = strstr(msg, "ANS_PERCENT_POSITION=")) != NULL)
		    {
		   		sscanf(p,"ANS_PERCENT_POSITION=%f",&song.rate);
				gdk_threads_enter();	
				gtk_progress_bar_set_fraction(pm->ui.hbox_right.progress_bar, song.rate/100.0);
				gdk_threads_leave();			    }
			
			if((p = strstr(msg,"ANS_TIME_POSITION=")) != NULL) 
		    {
		  	    sscanf(msg,"ANS_TIME_POSITION=%f\n",&temp);

				bzero(buf,sizeof(buf));		
				sprintf(buf,"%02d:%02d", (int)temp/60, (int)temp%60);
				
				set_lable(pm->ui.hbox_right.label_cur_time, buf);				
				song.cur_time = (int)(temp * 1000); 
				//printf("music cur_time = %d ms\n",song.cur_time);
		    }   
		    
		    if((p = strstr(msg,"ANS_LENGTH=")) !=NULL) 
		    {
		    	sscanf(p,"ANS_LENGTH=%f",&temp);

				bzero(buf,sizeof(buf));	
				sprintf(buf,"%02d:%02d", (int)temp/60, (int)temp%60);

				set_lable(pm->ui.hbox_right.label_end_time, buf);			
				song.end_time = (int)(temp * 1000); 
				//printf("music end_time = %d ms\n",song.end_time);			
		    }

			#if 1
			if((p = strstr(msg, "ANS_FILENAME=")) != NULL)
			{
				char buf[128] = {0};
				
				sscanf(p,"ANS_FILENAME='%[^']",buf);
				
				set_lable(pm->ui.hbox_right.label_title1, buf);	
			}
			
			if((p = strstr(msg, "ANS_META_ARTIST=")) != NULL)
			{
				char buf[128]  = {0};
				char utf8[128] = {0};

				sscanf(p,"ANS_META_ARTIST='%[^']",buf);	
				gb2312_to_utf8(buf, utf8);
				set_lable(pm->ui.hbox_right.label_title2, utf8);
			}
			#endif
		}
	}
}

void create_pthread(MPLAYER *pm)
{		
	pthread_create(&pm->pth_sendcmd,NULL,pthread_send_cmd,(void *)pm);
	pthread_create(&pm->pth_rcvmsg, NULL,pthread_rcv_msg, (void *)pm);
	pthread_create(&pm->pth_showlrc,NULL,pthread_show_lrc,(void *)pm);

	pthread_detach(pm->pth_showlrc);
	pthread_detach(pm->pth_rcvmsg);
	pthread_detach(pm->pth_sendcmd);
}

