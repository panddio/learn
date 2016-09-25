/* ************************************************************************
 *       Filename:  interface.c
 *    Description:
 *        Version:  1.0
 *        Created:  2015年08月03日 星期一 03時39分07秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (),
 *        Company:
 * ************************************************************************/
#include "common.h"
#include "console.h"
#include "file.h"
#include "interface.h"

const char *logo[6] = {"．．＿＿＿＿．╭╮╭╮．＿＿＿＿",
					   "．．＿．．．╭－┴┴－★╮．．．",
					   "．．＿．．．│◎　　︵│＿．．．",
					   "．．．． ※※※╰○－－○╯※※※．",
					   "．．．．．．★ 欢迎光临 ★．．．",
					   "．．．．．．★ 无限透明 ★．．．",
					  };

const char *wave1[7]	= { "．．．．．．．．．★︵＿＿＿︵★．．．．．．．．",
							"．．．．．．．．．／●　　　●＼．．．．．．．．",
							"．．．．．．．．．︴≡　﹏　≡  ︴．．．．．．．．",
							"．．．．．．．．．＼＿＿＿＿ ／．．．．．．．．．",
							"．．．．．╭╧╮ ╭╧╮ ╭╧╮  ╭╧╮ ╭╧╮  ╭╧╮  ╭╧╮ ．．．",
							"．．．．．│我 |來  │幫  │你  │灌  水│  │哩．．．．",
							"．．．．．╘∞╛╘∞╛ ╘∞╛ ╘∞╛ ╘∞╛ ╘∞╛  ╘∞╛．．．",
					  };


void show_interface()
{
	int i = 0;

	system("clear");
	set_fg_color(COLOR_GREEN);
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·");
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·");
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·\n");
	//fflush(stdout);

	for(i=0;i<33;i++)
	{
		cusor_moveto(110, i+2); //
		printf("‖");
	}
	cusor_moveto(0, 34); //
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·");
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·");
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·\n");

	set_fg_color(COLOR_WHITE);

	show_musicbar();
	show_pattern(logo, 6, 2, 1);
	//show_pattern(wave, 7, 2, 58);
}

void show_musicbar()
{
	int i = 0;

	cusor_moveto(0, 9);
	set_fg_color(COLOR_GREEN);

	printf("·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═");
	printf("·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═");
	printf("·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·\n");

	printf("·       >>  歌曲清单  <<      ·\n");

	printf("·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═");
	printf("·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═");
	printf("·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·\n");

	for(i=0;i<20;i++)
	{
		cusor_moveto(31, 12+i);
		printf("‖         ");
	}

	for(i=2;i<9;i++)
	{
		cusor_moveto(31, i);
		printf("|");
	}

	cusor_moveto(0, 32);
	printf("·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·\n");
	printf("·                             ·\n");

	set_fg_color(COLOR_RED);
	cusor_moveto(3, 33);
	printf("搜索：");
#if 0
	printf("■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■\n");
	printf("☆        >>  歌曲清单  <<     ★\n");
	printf("■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■\n");

	for(i=0;i<20;i++)
	{
		printf("                              □\n");
		printf("                              ■\n");
	}
	printf("■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■\n");
	printf("· 搜索：                      ·\n");
x
	for(i=32;i<110;i ++)
	{
		cusor_moveto(i, 9);
		printf("-");
		//printf("☆★");
	}
#endif
	fflush(stdout);
	set_fg_color(COLOR_WHITE);
	cusor_hide(); //隐藏光标
	//cusor_moveto(9, 33);
}

void show_pattern(const char *src[], int lines, int SROW, int COL)
{
	int i;

	for(i=0;i<lines;i++)
	{
		cusor_moveto(COL, SROW + i);
		printf("%s",src[i]);
	}
	fflush(stdout);
}

void show_musiclist(char *plist[])
{
	int i = 0;

	set_fg_color(COLOR_BLUE);
	for(i=0;plist[i] != NULL && i<20;i++)
	{
		cusor_moveto(0, 12+i);
		printf("%d. %s",i+1,plist[i]);
	}

	set_fg_color(COLOR_GREEN);
	for(i=0;i<20;i++)
	{
		cusor_moveto(31, 12+i);	//为了防止歌名覆盖了原来的界面
		printf("‖         ");
	}
	fflush(stdout);
	set_fg_color(COLOR_WHITE);
}

void show_lrcheader(char *pheader[])
{
	cusor_moveto(40, 3); //
	printf("歌名：%s\n",pheader[0]);
	cusor_moveto(40, 4); //
	printf("演唱：%s\n",pheader[1]);
	cusor_moveto(40, 5); //
	printf("作者：%s\n",pheader[2]);
	cusor_moveto(41, 14); //
	printf("○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○");//
}
/*************************************************************************
*  函数名称：show_progressbar
*  功能说明：显示进度条
*  参数说明：time     歌曲从播放到当前的时间
*          timelag  进度条前进的时间间隔
*  函数返回：无
*************************************************************************/
char move = 1;
void show_progressbar(int time, int timelag)
{
	char *p = " ";
	if(time/(timelag * move) > 0 && move <= 61)
	{
		cusor_moveto(40+move, 14); //
		set_fg_color(COLOR_MAGENTA);
		printf("●");
		move++;
	}

	if(time%2 == 0)
	{
		set_fg_color(COLOR_GREEN);
	}
	else if(time%3 == 0)
	{
		set_fg_color(COLOR_RED);
	}
	else if(time%5 == 0)
	{
		set_fg_color(COLOR_CYAN);
	}
	else
	{
		set_fg_color(COLOR_YELLOW);
	}

	cusor_moveto(40+move, 14); //
	printf("●");
	set_fg_color(COLOR_WHITE);

	fflush(stdout);
}
/*************************************************************************
*  函数名称：show_time
*  功能说明：显示进度条
*  参数说明：time     歌曲从播放到当前的时间
*  函数返回：无
*************************************************************************/


void show_time(int time, int maxtime)
{
	int min = 0,sec = 0,time_left = 0;

	time_left = maxtime - time;

	if(time_left < 0) time_left = 0;

	min = time_left/1000/60; //单位：秒
	sec = time_left/1000%60;


	if(time_left%1000 > 500)
	{
		 sec += 1;
	}
	//cusor_moveto(55, 6); //
	//printf("%02d:%02d\n",min,sec);

	cusor_moveto(40, 6); //
	printf("时间：%02d:%02d\n",min,sec);

}
