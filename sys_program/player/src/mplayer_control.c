/* ************************************************************************
 *       Filename:  mplayer_display.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015å¹´08æœˆ24æ—¥ 10æ—¶05åˆ†08ç§’
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "common.h"
#include "file.h"
#include "mplayer_ui.h"
#include "mplayer_pthread.h"
#include "mplayer_control.h"




void send_cmd(char cmd[],MPLAYER *pm)
{
	int ret = 0;
	
	pthread_mutex_lock(&pm->mutex); //
	ret = write(pm->fd_pipe,cmd,strlen(cmd));
	if(ret != strlen(cmd))
	{
		perror("send cmd");
	}
	pthread_mutex_unlock(&pm->mutex);//
}

#if 1
void mplayer_show_musiclist(MPLAYER *pm, SONG *ps)
{
	int i;
	
	for(i=0;i < ps->count;i++)
	{
		sungtk_clist_append(musiclist, ps->psong_list[i]);
		printf("%s\n",ps->psong_list[i]);
	}
	gtk_widget_show_all(pm->ui.main_window);
}

#else
void mplayer_show_musiclist(MPLAYER *pm)
{
	int i;
	
	song.song_src = get_musiclist(&song.psong_list, &song.count);
	printf("song count = %d\n",song.count);
	
	for(i=0;song.psong_list[i] != NULL && i< song.count;i++)
	{
		sungtk_clist_append(musiclist, song.psong_list[i]);
		printf("%s\n",song.psong_list[i]);
	}
	gtk_widget_show_all(pm->ui.main_window);
}
#endif

void playing_song(MPLAYER *pm, int new_song)
{
	FILE *fp = NULL;
	int ret = 0;
	char buf[256] = "loadfile ./music/";
	char *pbuf = NULL;

	set_songname(new_song);
	printf(">>>song_name= %s<<<<<\n",song.name);
	
	fp = fopen(".song", "w");
	if(fp != NULL)
	{
		ret = fwrite(song.name, strlen(song.name),1,fp); //ä¿å­˜æ’­æ”¾çš„æ­Œæ›²åˆ°æ–‡ä»¶
		//if(ret != strlen(song.name)) perror("write song.name to file");
	}
	fclose(fp);
	
	pbuf = (char *)transfer_space(song.name);
	strcat(buf,pbuf);
	strcat(buf,"\n");

	//printf(">>>cmd = %s<<<<<\n",buf);
	if(pm->playflag == stop)
	{
		pm->playflag = playing;
			
		send_cmd("pause\n", pm);
		

		gdk_threads_enter();
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_right.button_backward), TRUE);
		gdk_threads_leave();
		
		gdk_threads_enter();
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_right.button_forward), TRUE);
		gdk_threads_leave();
		
		gdk_threads_enter();
		sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_pause), "./image/style/pause.png",70,70);		
		gdk_threads_leave();
	}
	
	clear_lrc_lable(pm);
	send_cmd(buf, pm);

	gdk_threads_enter();
	//printf(">>list 333---song.old = %d\n",song.old);
	sungtk_clist_set_row_color(musiclist, song.old, "black");
	gdk_threads_leave();

	gdk_threads_enter();
	sungtk_clist_set_row_color(musiclist, song.now, "DarkOliveGreen1");
	gdk_threads_leave();
	
	free(pbuf);
}

void set_playing_song(MPLAYER *pm, int step)
{
	
	switch(pm->playmode)
	{
		case list_loop: //ÁÐ±íÑ­»·²¥·Å
		{
			song.old = song.now;
			song.now += step;
			
			if(song.now >= song.count) song.now = 0; //
			else if(song.now < 0) song.now = song.count - 1;

			set_songname(song.now);
			break;
		}		
		case sequence:  //ÁÐ±íË³Ðò²¥·Å
		{
			char stop_flag = FALSE;
			
			song.old = song.now;
			song.now += step;	

			if(song.now >= song.count)
			{
				if(song.keyflag == back) song.now = 0;
				else
				{
					song.now = song.count - 1;
					stop_flag = TRUE;
				}
			}
			else if(song.now < 0)
			{
				if(song.keyflag == back) song.now = song.count - 1;
				else
				{	
					song.now = 0;
					stop_flag = TRUE;
				}
			}

			if(stop_flag != TRUE)
			{
				set_songname(song.now);
			}
			else
			{
				pm->playflag = stop;
				
				send_cmd("pause\n", pm);			
				
				gdk_threads_enter();
				gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_right.button_backward), FALSE);
				gdk_threads_leave();
				
				gdk_threads_enter();
				gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_right.button_forward), FALSE);
				gdk_threads_leave();
				
				gdk_threads_enter();
				sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_pause), "./image/style/play.png",70,70); 	
				gdk_threads_leave();

				clear_lrc_lable(pm);
			}
			if(song.keyflag == back || song.keyflag == next)
			{
				if(song.now >= song.count) song.now = 0; //	
				else if(song.now < 0)      song.now = song.count - 1;
				
				set_songname(song.now);
			}
			else
			{

				//set_songname(song.now);						
			}
			
			break;
		}
		case loop:  //µ¥ÇúÑ­»·
		{
			if(song.keyflag == back || song.keyflag == next)
			{
				song.old = song.now;
				song.now += step;
				
			    if(song.now >= song.count) song.now = 0;
				else if(song.now < 0)      song.now = song.count - 1;
				set_songname(song.now);	
			}			
			break;
		}	
		case randm:
		{
			srand((uint)time(NULL));

			do
			{
				step = rand() % song.count; //»ñµÃËæ»úÊý
			}while(step != song.now);

			song.old = song.now;
			song.now = step;
			set_songname(song.now);
			break;
		}
	}
}

void set_lable(GtkLabel *label, char *src)
{
	gdk_threads_enter();	
	gtk_label_set_text(label, src);		
	gdk_threads_leave();
}

void set_keyflag(KEY_STATUS status)
{
	sem_wait(&song.sem_keyflag);	
	song.keyflag = status;
	sem_post(&song.sem_keyflag);	
}

void set_songname(int song_num)
{
	sem_wait(&song.sem_setsong);
	//bzero(song.name, sizeof(song.name));
	strcpy(song.name, song.psong_list[song_num]);	
	sem_post(&song.sem_setsong);	
}


void set_lrc_lable(MPLAYER *pm, char *pbuf[])
{
	gdk_threads_enter();
	gtk_label_set_text(pm->ui.hbox_right.label_lrc1, pbuf[0]);	
	gdk_threads_leave();

	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc2, pbuf[1]);	
	gdk_threads_leave();	
	
	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc3, pbuf[2]);
	gdk_threads_leave();	

#if 0	
	gdk_threads_enter();		
	gtk_label_set_text(pm->ui.hbox_right.label_lrc4, pbuf[3]);
	gdk_threads_leave();	
	
	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc5, pbuf[4]);	
	gdk_threads_leave();		

	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc6, pbuf[5]);	
	gdk_threads_leave();	
	
	gdk_threads_enter();	//	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc7, pbuf[6]);	
	gdk_threads_leave();	//
#endif
}

void clear_lrc_lable(MPLAYER *pm)
{
	char buf[] = " ";

	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_title1, buf);
	gdk_threads_leave();

	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_title2, buf);
	gdk_threads_leave();


	gdk_threads_enter();
	gtk_label_set_text(pm->ui.hbox_right.label_lrc1, buf);	
	gdk_threads_leave();

	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc2, buf);	
	gdk_threads_leave();	
	
	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc3, buf);
	gdk_threads_leave();	

	
	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_cur_time, buf);
	gdk_threads_leave();

	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_end_time, buf);
	gdk_threads_leave();

#if 0	
	gdk_threads_enter();		
	gtk_label_set_text(pm->ui.hbox_right.label_lrc4, pbuf[3]);
	gdk_threads_leave();	
	
	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc5, pbuf[4]);	
	gdk_threads_leave();		

	gdk_threads_enter();	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc6, pbuf[5]);	
	gdk_threads_leave();	
	
	gdk_threads_enter();
	gtk_label_set_text(pm->ui.hbox_right.label_lrc7, pbuf[6]);	
	gdk_threads_leave();	
	
#endif
}

