#include <stdio.h>
#include <string.h>
#include "msg.h"

void show_number(const char *src)
{
	printf("from: %s\n",src+3);
}

void show_time( char *src1,char *src2)
{
	int i = 0;
	char *pbuf[3] = {NULL};
	char *p = NULL;
	int time[3];
	
	pbuf[0] = strtok(src1,"/");
	
	while(pbuf[i++] != NULL)
	{
		pbuf[i] = strtok(NULL,"/");
	} 	
	
	if(atoi(pbuf[0])>15)
	{
		time[0] = 1900+ atoi(pbuf[0]);
	}
	else
	{
		time[0] = 2000+ atoi(pbuf[0]);
	}
	time[1] = atoi(pbuf[1]);
	time[2] = atoi(pbuf[2]);
	
	printf("date: %d年%d月%d日  ",time[0],time[1],time[2]);
	p = strchr(src2,'+');
	*p = '\0';
	printf("%s\n",src2);
}

void show_content(const char *src)
{
	printf("content: %s\n",src);
}

void show_message(char **src)
{
	show_number(src[1]);
	show_time(src[2],src[3]);
	show_content(src[4]);
}

int msg_deal(char *msg_src, char *msg_done[],char *str)
{
	int i = 0;
	
	msg_done[0] = strtok(msg_src,str);
	
	while(msg_done[i++] != NULL)
	{
		msg_done[i] = strtok(NULL,str);
	} 
	
	return i;
}
