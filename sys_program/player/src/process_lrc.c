/* ************************************************************************
 *       Filename:  process_lrc.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月31日 星期五 09時17分27秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "common.h"
#include "console.h"
#include "mplayer_control.h"
#include "mplayer_pthread.h"
#include "gb2312_ucs2.h"
#include "link.h"
#include "file.h"
#include "process_lrc.h"


uint src_segment(char *src, char *plines[], char *str)
{
	uint i = 0;
	
	plines[0] = strtok(src, str);
	
	while(plines[i++] != NULL)
	{
		plines[i] = strtok(NULL, str);
	} 
	//printf("i=%d\n",i);
	return (i-1);
}

uint line_segment(char *pline, char *pbuf[], char *str)
{
	uint i = 0;
	
	pbuf[0] = strtok(pline, str);
	
	while(pbuf[i++] != NULL)
	{
		pbuf[i] = strtok(NULL, str);
		//printf("%s\n",pbuf[i]);
	} 
	//printf("i=%d\n",i);	
	
	return (i-1);
}

LRC *build_link(MPLAYER *pm,char *plines[],int lines)
{
	int i, j;
	uint part = 0;
	LRC lyric, *lrc_head = NULL;
	
	for(i=0;plines[i] != NULL && i<lines; i++)
	{	

	#if 0
		char *pbuf[10] = {NULL};
		
		part = line_segment(plines[i],pbuf, "]"); //切割一行
			
		for(j=0;j<part;j++)
		{
			int min = 0,sec = 0, msec = 0;
			
			printf("%s\n",pbuf[j]);
		}
	#elif 1				
		if(i<4) //
		{	
			char *ptitle = NULL;
			//char msg[100]; sscanf ???????
			//sscanf(plines[i],"%*[^:]%*1s%[^]]",msg[0]); 
			ptitle = strtok(plines[i],":]");
			if(ptitle != NULL) ptitle = strtok(NULL,":]");

			if(ptitle != NULL)
			{
				//printf("##$@#$ %s***\n",ptitle);
				//mplayer_show_lyrtitle(pm, ptitle, i);
			}
			
			#if 0			
			char *trash = NULL;
			int len = 0;

			if(plines[i] != NULL)
			{
				trash = strtok(plines[i],":]");
				if(trash != NULL)
				{
					trash = strtok(NULL,":]");
					if(trash != NULL)
					{						
						//printf("$$$$$$$$$$$$$$$$$$$$$$$\n");
						len = strlen(trash);
						
						if(len == 0) song.lrc_title[i] = NULL;
						else
						{
							char utf8[96] = {0};
							
							song.lrc_title[i] = (char *)malloc(len + 1);
							
							bzero(song.lrc_title[i], len + 1);
							gb2312_to_utf8(trash, utf8);
							
							strcpy(song.lrc_title[i], utf8);
							printf("lrc_title[%d] = %s\n",i, song.lrc_title[i]);
						}
					}
					else
					{
						song.lrc_title[i] = NULL;
					}
				}
			}
			#endif
		}
		else
		{ 	
			char *pbuf[10] = {NULL};
			int min = 0, sec = 0, msec = 0;
			//float sec;
			
			part = line_segment(plines[i],pbuf, "]"); //切割一行	
			
			for(j=0;j<part-1;j++)
			{				
				if(pbuf[part-1][0] != '[')
				{
					char utf8[256] = {0};
					sscanf(pbuf[j],"[%2d:%2d.%2d",&min,&sec,&msec);
					//printf("%2d:%2d.%2d\n",min,sec,msec);
				
					lyric.time = (min * 60 + sec)*1000 + msec*10;
					
					gb2312_to_utf8(pbuf[part-1], utf8);
					strcpy(lyric.src, utf8);				
					lrc_head = insert_link(lrc_head,lyric);
					//printf("%4d  %s\n",lyric.time, lyric.src);					
				}
			}				
		}
	#endif
	}
	return lrc_head;
}

LRC *dispose_lrc(MPLAYER *pm,char *name)
{
	song.lrc_src  = NULL;
	song.lrc_head = NULL;
	
	song.lrc_src = (char *)read_src_file(&song.lrc_length, name);
	if(song.lrc_src != NULL)
	{	
		song.lrc_lines = src_segment(song.lrc_src, song.plines, "\r\n");
		song.lrc_head  = (LRC *)build_link(pm, song.plines, song.lrc_lines);	
		song.pnode = song.lrc_head;	
		//print_link(song.lrc_head); 
	}

	free(song.lrc_src);
	return song.lrc_head;
}

void show_lyric(LRC *pnode, int longest)
{
	char *empty = " ";
	char *pbuf[12];
	int i = 0, offset = 0;
	LRC  *pb = NULL, *pf = NULL;
	
	pb = pnode;
	pf = pnode->next;
	
	for(i=3;i>=0;i--)
	{
		if(pb != NULL)
		{
			pbuf[i] = pb->src;
			pb = pb->prev;
		}
		else
		{
			pbuf[i] = empty;
		}
	}
	
	for(i=4;i<12;i++)
	{
		if(pf != NULL)
		{
			pbuf[i] = pf->src;
			pf = pf->next;
		}
		else
		{
			pbuf[i] = empty;
		}
	}

	for(i = 0;i < 12;i++) //
	{
		cusor_moveto(55, 20+i); //光标移到 第4+i行，第20列		
		printf("%-40s",empty); //清除上次的显示
		fflush(stdout);
	}	

	for(i = 0;i < 12;i++)
	{
		offset = get_showoffset(pbuf[i],longest);
		cusor_moveto(55+offset, 20+i); //光标移到 第10+i行，第50列
		
		set_fg_color(COLOR_WHITE);
		if(i == 3)
		{
			set_fg_color(COLOR_MAGENTA);
		}
		printf("%-40s",pbuf[i]);
		fflush(stdout);
	}
	cusor_moveto(9, 36);
	//fflush(stdout);	
}

void mplayer_show_lyric(MPLAYER *pm, LRC *pnode)
{
	char *empty = " ";
	char *pbuf[3] = {NULL};
	int i = 0;
	LRC  *pb = NULL, *pf = NULL;
	
	pb = pnode;
	pf = pnode->next;
	//printf(">>%d ms --- %s\n",song.pnode->time, song.pnode->src);
	
	for(i=0;i>=0;i--)
	{
		if(pb != NULL)
		{
			pbuf[i] = pb->src;
			pb = pb->prev;
		}
		else
		{
			pbuf[i] = empty;
		}
	}
	
	for(i=1;i<3;i++)
	{
		if(pf != NULL)
		{
			pbuf[i] = pf->src;
			pf = pf->next;
		}
		else
		{
			pbuf[i] = empty;
		}
	}

	set_lrc_lable(pm, pbuf);

}

void mplayer_show_lyrtitle(MPLAYER *pm, char *ptitle, int i)
{
	//char *msg[] = { ": ", "?: ", ": "};
	char utf8[168];
	//char buf[168];

	
	if(i < 3)
	{	
		//bzero(buf, sizeof(buf));
		//strcat(buf, msg[i]);
		//strcat(buf, ptitle);
		bzero(utf8, sizeof(utf8));
		gb2312_to_utf8(ptitle, utf8);
		printf("##$@#$ %s***\n",utf8);
		
		switch(i)
		{
			case 0:
			{
				set_lable(pm->ui.hbox_right.label_title1, utf8);
				break;
			}
			case 2:
			{
				set_lable(pm->ui.hbox_right.label_title2, utf8);
				break;
			}
			case 3:
			{
				set_lable(pm->ui.hbox_right.label_title3, utf8);
				break;
			}
		}
	}
}

