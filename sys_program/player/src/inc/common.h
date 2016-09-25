#ifndef __COMMON_H__
#define __COMMON_H__

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include "sungtk_interface.h"



#define  uint   unsigned int
#define  ulint  unsigned long int
#define  uchar  unsigned char


#define  FIFO   "cmd_fifo"
#define  MS     (1000)


typedef enum
{	
	sequence  = 0,  //列表顺序播放
	list_loop = 1,  //列表循环
	loop      = 2,  //单曲循环
	randm     = 3,  //随机播放
}PLAY_MODE;

typedef enum
{
	stop    = 0,
	playing = 1,
//	end     = 2,
}PLAY_STATUS;

typedef enum
{
	mute = 0, //静音
	beam = 1, //播音
}SOUND_STATUS;

typedef enum
{
	quiet = 0,
	init  = 1,
	back  = 2,
	next  = 3,
	clist = 4,
}KEY_STATUS;

typedef struct _lrc
{
	//float time;
	int time;
	char src[256];
	
	struct _lrc *prev;
	struct _lrc *next;
}LRC;

typedef struct _song
{
	char *song_src;
	char **psong_list;
	char *search;
	char search_flag;
	char name[168];

	char *lrc_src;	
	char *plines[128]; //指向 歌词的每一行
//	char *lrc_title[4];

	int lrc_lines;    //存放歌词的行数
	int now;          //指向当前播放的歌曲
	int old;
	int count;        //歌的数量	
	
	int   cur_time;  //歌曲播放当前时间
	int   end_time;  //歌曲播放结束时间
	int   endflag;   //歌曲播放结束标志
	float rate;      //歌曲播放进度

	ulint lrc_length;

	sem_t sem_setsong;
	sem_t sem_keyflag;
	
	LRC *lrc_head;
	LRC *pnode;
	
	KEY_STATUS keyflag;
}SONG;

typedef struct _hbox_left
{
	GtkButton *bmusic_list;
	GtkButton *bmusic_collect;
	GtkButton *bmusic_recently;

	GtkEntry  *entry_search;
	GtkButton *button_search;
	GtkTable  *table_search;
	GtkScrolledWindow *scrollbar_musiclist;
	GtkCList *music_clist;
	GtkTable *table_musiclist;
	GtkEventBox *eventbox_musiclist;
}HBOX_LEFT;

typedef struct _hbox_right
{
	GtkImage *image_logo;
	
	GtkButton *button_back;
	GtkButton *button_next;
	GtkButton *button_pause;
	GtkButton *button_backward;
	GtkButton *button_forward;
	GtkButton *button_playmode;
		
	GtkImage *image_back;
	GtkImage *image_next;
	GtkImage *image_pause;
	GtkImage *image_backward;
	GtkImage *image_forward;
	
	GtkLabel *label_title1;
	GtkLabel *label_title2;
	GtkLabel *label_title3;
	
	GtkLabel *label_lrc1;
	GtkLabel *label_lrc2;
	GtkLabel *label_lrc3;
	GtkLabel *label_lrc4;
	GtkLabel *label_lrc5;
	GtkLabel *label_lrc6;
	GtkLabel *label_lrc7;
	
	GtkLabel *label_cur_time;
	GtkLabel *label_end_time;
	
	GtkProgressBar *progress_bar;	
	GtkEventBox *eventbox_bar;

	GtkHScale *hscale_volume;
	GtkButton *button_volume;
	GtkEventBox *eventbox_volume;
}HBOX_RIGHT;

typedef struct _window
{
	GtkWidget *main_window;
	//GtkImage *image;
		
	HBOX_LEFT  hbox_left;
	HBOX_RIGHT hbox_right;
}WINDOW;

typedef struct _mplayer
{
	WINDOW ui;

//	char msg[128]; //接收mplayer信息
	int fd_pipe;   //命名管道
	int fd[2];     //无名管道
	pid_t pid;     //启动mplayer的子进程pid
	
	pthread_t pth_showlrc;
	pthread_t pth_rcvmsg;
	pthread_t pth_sendcmd;

	pthread_mutex_t mutex;
	
	PLAY_STATUS  playflag; //播放状态
	PLAY_MODE    playmode; //播放模式
	SOUND_STATUS soundflag;
//	SunGtkCList *musiclist;
}MPLAYER;
#endif
