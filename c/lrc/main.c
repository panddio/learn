/* ************************************************************************
 *       Filename:  main.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月31日 星期五 05時36分37秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "common.h"
#include "process_lrc.h"
#include "start_mplayer.h"
#include "interface.h"
#include "file.h"
#include "link.h"


int main(int argc, char *argv[])
{
	char *lrc_src = NULL, **plines = NULL, *pheader[4] = {NULL};
	char *list_src = NULL, **plist = NULL;
	char playing = 0;    //播放标志，1 为正在播放
	int lines = 0, longestlength = 0, i = 0;
	int time = 0, maxtime = 0, timelag = 0;
	ulint lrc_length = 0;
	LRC *lrc_head = NULL, *pnode = NULL;
	struct timeval start_time,end_time;


	show_interface(); //
	list_src = get_musiclist(&plist);
	show_musiclist(plist);

	while(1)
	{
#if 1
		if(!playing)
		{

			mplayer_play("./music/喜欢你.mp3");
			lrc_src = read_src_file(&lrc_length, "lyric/喜欢你.lrc"); //读出歌词文件的内容到lrc_src指向的地址空间
			lines = check_lines(lrc_length, lrc_src);         //检测歌词有几行
			plines = (char **)malloc(lines*sizeof(char **));  //动态分配空间存储每行的首地址

			if(plines == NULL) goto out;                      //如果分配空间失败，退出程序

			src_segment(lrc_src, plines, "\r\n");	          //按行分割歌词

			lrc_head = build_link(plines, pheader, lines);    //按时间建立链表
			longestlength = get_longestlength(lrc_head);
			pnode = lrc_head;
			//print_link(lrc_head);
			show_lrcheader(pheader);

			maxtime = get_maxtime(lrc_head);
			timelag = maxtime/60;

			gettimeofday(&start_time,0);  //开始计时

			playing = 1; //
		}

		gettimeofday(&end_time,0);
		time = 1000000*(end_time.tv_sec - start_time.tv_sec) + end_time.tv_usec - start_time.tv_usec;
		time = (int)time/1000;  //除以1000则进行毫秒计时

		if(pnode != NULL && time >= pnode->time) //
		{
			show_lyric(pnode,longestlength);
			pnode = pnode->next;
		}

		show_progressbar(time,timelag);
		show_time(time, maxtime);

		if(pnode == NULL)
		{
			sleep(12);
			playing = 0;
			move = 1;    //在interface.c里定义，用于记录进度条的进度

			lrc_head = free_link(lrc_head);
			free(lrc_src);

		}
#endif
	}

	free(lrc_src);
	free_link(lrc_head);
	out:
	return 0;
}

