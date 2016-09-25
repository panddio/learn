/* ************************************************************************
 *       Filename:  gps.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月28日 星期二 07時11分10秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/



#include <stdio.h>
#include <string.h>

typedef struct gpsinfo
{
	char id[10];
	char time[16];
	char sta;
	char lat[12];
	char ns;
	char lon[12];
	char ew;
	char vel;
	char azi[8];
	char utct[10];
	char mag[6];
	char dir;
	int crc;
}GPS;

typedef struct date
{
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
}DATE;

void show_time(char *pinfo[])
{
	DATE time;
	
//	printf("%s\n",pinfo);
	sscanf(pinfo[1],"%2d%2d%2d",&time.hour,&time.min,&time.sec);
	time.hour += 8;
	printf("时间：%02d:%02d:%02d\n",time.hour,time.min,time.sec);

	sscanf(pinfo[9],"%2d%2d%2d",&time.day,&time.mon,&time.year);
	printf("日期：%02d年%02d月%01d日\n",time.year,time.mon,time.day);
}

void show_latitude(char *pinfo[])
{
	int du = 0;
	char fen[10];

	sscanf(pinfo[3],"%2d%s",&du,fen);

	printf("纬度：%s纬 %3d度 %s分\n",pinfo[4],du,fen);
}
void show_longitude(char *pinfo[])
{
	int du = 0;
	char fen[10];

	sscanf(pinfo[5],"%3d%s",&du,fen);

	printf("经度：%s经 %3d度 %s分\n",pinfo[6],du,fen);
}
char get_status(char *pinfo[])
{
	char state;

	sscanf(pinfo[2],"%1c",&state);
	//printf("state = %c\n",state);

	return state;
}
int sep_gpsinfo(char *pinfo[],char info[],char *pch)
{
	int i = 0;
	
	pinfo[0] = strtok(info,pch);
	
	while(pinfo[i++] != NULL)
	{
		pinfo[i] = strtok(NULL,pch);
	}
	
	return i;
}

void main()
{
	char *pinfo[13] = {NULL};
	char info[128]="$GPRMC,024813.640,A,3158.4608,N,11848.3737,E,\
					10.05,324.27,150706, , ,A*50";
	char state;

	sep_gpsinfo(pinfo,info,",");

	state = get_status(pinfo);

	if(state == 'A')
	{
		show_time(pinfo);
		show_latitude(pinfo);
		show_longitude(pinfo);
	}
	
}	

	
