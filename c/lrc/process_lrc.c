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
#include "link.h"
#include "file.h"

int src_segment(char *lrc_src, char *plines[], char *str)
{
	int i = 0;

	plines[0] = strtok(lrc_src, str);

	while(plines[i++] != NULL)
	{
		plines[i] = strtok(NULL, str);
	}
	//printf("i=%d\n",i);
	return (i-1);
}

int line_segment(char *pline, char *pbuf[], char *str)
{
	int i = 0;

	pbuf[0] = strtok(pline, str);

	while(pbuf[i++] != NULL)
	{
		pbuf[i] = strtok(NULL, str);
		//printf("%s\n",pbuf[i]);
	}
	//printf("i=%d\n",i);

	return (i-1);
}

LRC *build_link(char *plines[], char *pheader[], int lines)
{
	int i, j;
	int part = 0;
	LRC lyric, *lrc_head = NULL;

	for(i=0;plines[i] != NULL && i<lines;i++)
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
			char *trash = NULL;
			//char msg[100]; sscanf 按给定格式输出内容放到一个足够大的空间
			//sscanf(plines[i],"%*[^:]%*1s%[^]]",msg[0]);
			trash = strtok(plines[i],":]");
			if(trash != NULL) pheader[i] = strtok(NULL,":]");
		}
		else
		{
			char *pbuf[10] = {NULL};
			char tbuf[10]  = {0};
			int min = 0, sec = 0, msec = 0;
			//float sec;

			part = line_segment(plines[i],pbuf, "]"); //切割一行

			for(j=0;j<part-1;j++)
			{
				if(pbuf[part-1][0] != '[')
				{
					sscanf(pbuf[j],"[%2d:%2d.%2d",&min,&sec,&msec);
					//printf("%2d:%2d.%2d\n",min,sec,msec);

					lyric.time = (min * 60 + sec)*1000 + msec*10; //毫秒
					lyric.psrc = pbuf[part-1];
					lrc_head = insert_link(lrc_head,lyric);
					//printf("%4d  %s\n",lyric.time, lyric.psrc);
				}
			}
		}
	#endif
	}
	return lrc_head;
}

void show_lyric(LRC *pnode, int longest)
{
	char *empty = " ";
	char *pbuf[12];
	int i = 0, offset = 0;
	LRC  *pb = NULL, *pf = NULL;

	pb = pnode;
	pf = pnode->next;

	for(i=4;i>=0;i--)
	{
		if(pb != NULL)
		{
			pbuf[i] = pb->psrc;
			pb = pb->prev;
		}
		else
		{
			pbuf[i] = empty;
		}
	}

	for(i=5;i<12;i++)
	{
		if(pf != NULL)
		{
			pbuf[i] = pf->psrc;
			pf = pf->next;
		}
		else
		{
			pbuf[i] = empty;
		}
	}

	for(i = 0;i < 12;i++) //
	{
		cusor_moveto(60, 17+i); //光标移到 第4+i行，第20列
		printf("%-36s",empty);  //清除上次的显示
		fflush(stdout);
	}

	for(i = 0;i < 12;i++)
	{
		offset = get_showoffset(pbuf[i],longest);
		cusor_moveto(60+offset, 17+i); //光标移到 第10+i行，第50列

		set_fg_color(COLOR_WHITE);
		if(i == 4)
		{
			set_fg_color(COLOR_MAGENTA);
		}
		printf("%-36s",pbuf[i]);

	}
	//cusor_moveto(9, 33);
	fflush(stdout);
}

int get_maxtime(LRC *head)
{
	int maxtime = 0;
	LRC *pb = head;

	while(pb->next != NULL) pb = pb->next;

	maxtime = pb->time;

	return (maxtime + 12 * 1000); //ms
}

int get_timelag(LRC *head)
{
	int maxtime = 0;
	LRC *pb = head;

	while(pb->next != NULL) pb = pb->next;

	maxtime = pb->time;

	return (maxtime + 12 * 1000)/60; //ms
}
