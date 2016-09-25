#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>
#include "common.h"
#include "mplayer_control.h"
#include "mplayer_pthread.h"
#include "mplayer_ui.h"
#include "gtk_callback.h"


// 鼠标移动事件(点击鼠标任何键)的处理函数
gboolean motion_event_callback(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
	// 获得移动鼠标的坐标值
	gint x = event->x;
	gint seek_sec = 0;
	char cmd[32] = "seek ";
	char buf[8] = {0};
	MPLAYER *pm = (MPLAYER*)data;

	if(pm->playflag == playing) pm->playflag = stop;

	seek_sec = x * song.end_time/400;          //毫秒
	seek_sec = (seek_sec - song.cur_time)/1000;//秒
	
	printf("seek_sec = %d\n",seek_sec);
	
	gcvt(seek_sec,5,buf);
	strcat(cmd, buf);
	strcat(cmd,"\n");
	printf("cmd = %s\n",cmd);
	send_cmd(cmd,pm);

	pm->playflag == playing;
	//gint j = event->y;
	//printf("motion_x = %d, motion_y = %d\n", i, j);
	return TRUE;
}

void search_entry_callback(GtkWidget *widget, gpointer entry)
{	
	MPLAYER *pm = (MPLAYER*)entry;
	const gchar *text;
	int i = 0;
	char *p = NULL;
	
	text = (gchar *)gtk_entry_get_text(GTK_ENTRY(pm->ui.hbox_left.entry_search));
	//printf("Entry contents: %s\n",text);

	for(i=0; i<song.count; i++)
	{
		if((p=strstr(song.psong_list[i],text)) != NULL)
		{
			printf("entry >> song_name = %s\n",song.psong_list[i]);
			
			sungtk_clist_set_row_color(musiclist, i, "green");
			
			song.search[i] = 1;
			song.search_flag = 1;
			p = NULL;
		}
	}
}

void keys_board_callback(GtkWidget *widget, GdkEventKey  *event, gpointer data)
{

	printf("Entry keys_board_callback!!!!\n");
	if(event->keyval == 65288) //backspace
	{
		MPLAYER *pm = (MPLAYER*)data;
		const gchar *text;
		char *p = NULL;
		int i = 0;

		text = (gchar *)gtk_entry_get_text(GTK_ENTRY(pm->ui.hbox_left.entry_search));
		//printf("Entry contents: %s\n",text);

		if(text != NULL)
		{
			for(i=0; i<song.count; i++)
			{
				if((p=strstr(song.psong_list[i],text)) != NULL)
				{
					printf("entry >> song_name = %s\n",song.psong_list[i]);
					
					//gdk_threads_enter();
					sungtk_clist_set_row_color(musiclist, i, "green");
					//gdk_threads_leave();
					
					song.search[i] = 1;
					song.search_flag = 1;
					p = NULL;
				}
			}
		}
	}
}

void playmode_button_callback(GtkButton *button, gpointer data)
{
	MPLAYER *pm = (MPLAYER*)data;

	switch(pm->playmode)
	{
		case list_loop:
		{
			pm->playmode = sequence;
			sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_playmode), "./image/style/playmode_sequence.png",20,20);
			break;
		}
		
		case sequence:
		{
			pm->playmode = loop;
			sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_playmode), "./image/style/playmode_loop.png",20,20);
			break;
		}
		
		case loop:
		{
			pm->playmode = randm;
			sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_playmode), "./image/style/playmode_random.png",20,20);
			break;
		}
		
		case randm:
		{
			pm->playmode = list_loop;
			sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_playmode), "./image/style/playmode_list_loop.png",20,20);
			break;
		}
	}
}

void musiclist_buttons_callback(GtkButton *button, gpointer data)
{
	MPLAYER *pm = (MPLAYER*)data;

	if(button == pm->ui.hbox_left.bmusic_list)
	{
		//int i = 0;
		//for(i=0;song.psong_list[i] != NULL && i< song.count;i++)
		//{
			//sungtk_clist_append(musiclist, song.psong_list[i]);
			//printf("%s\n",ps->psong_list[i]);
		//}
		
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_left.bmusic_list),     FALSE);
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_left.bmusic_collect),  TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_left.bmusic_recently), TRUE);
	}
	
	else if(button == pm->ui.hbox_left.bmusic_collect)
	{
		//gtk_clist_clear();
		
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_left.bmusic_list),     TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_left.bmusic_collect),  FALSE);
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_left.bmusic_recently), TRUE);
	}
	
	else if(button == pm->ui.hbox_left.bmusic_recently)
	{
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_left.bmusic_list),     TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_left.bmusic_collect),  TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_left.bmusic_recently), FALSE);
	}
}


void music_buttons_callback(GtkButton *button, gpointer data)
{
	MPLAYER *pm = (MPLAYER*)data;


	if(button == pm->ui.hbox_right.button_pause)
	{
		if(pm->playflag == playing)// 正在播放，则暂停
		{  
			//printf("pause\n");
			pm->playflag = stop;
			
			send_cmd("pause\n", pm);	
			
			gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_right.button_backward), FALSE);
			gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_right.button_forward), FALSE);			
			sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_pause), "./image/style/play.png",70,70);			
		}
		else //否则，开启播放
		{ 
			//printf("playing\n");
			pm->playflag = playing;
			
			send_cmd("pause\n", pm);	
			gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_right.button_backward), TRUE);
			gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_right.button_forward), TRUE);					
			sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_pause), "./image/style/pause.png",70,70);				
		}
	}

	else if(button == pm->ui.hbox_right.button_forward)
	{
		//printf("button_forward\n");
		send_cmd("seek 10\n", pm);	
	}
	
	else if(button == pm->ui.hbox_right.button_backward)
	{
		//printf("button_backward\n");
		send_cmd("seek -10\n", pm);
	}

	else if(button == pm->ui.hbox_right.button_next)
	{
		//printf("button_next\n");
		set_keyflag(next);
		set_playing_song(pm, 1);
		
		#if 0
		song.old= song.now;
		song.now++;
		if(song.now >= song.count)
		{
			song.now = 0;
		}
		#endif
		//set_songname(song.now);
		//strcpy(song.name, song.psong_list[song.now]);
		//playing_song(pm, song.now);
	}
	
	else if(button == pm->ui.hbox_right.button_back)
	{
		//printf("button_back\n");	
		set_keyflag(back);
		set_playing_song(pm, -1);
		#if 0
		song.old= song.now;
		song.now--;
		if(song.now < 0)
		{
			song.now = song.count - 1;
		}
		#endif
		
		//set_songname(song.now);
		//playing_song(pm, song.now);
	}

	else if(button == pm->ui.hbox_right.button_volume)
	{
		if(pm->soundflag == beam)//判断如果不是静音状态 则设置成静音状态
		{
			//printf("mute\n");
			pm->soundflag = mute;
			
			send_cmd("mute 1\n", pm);
			sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_volume), "./image/style/mute.png",50,50);			
		}
		else
		{
			//printf("beam\n");
			pm->soundflag = beam;
			send_cmd("mute 0\n", pm);
			sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_volume), "./image/style/beam.png",50,50);			
		}
	}
}


gboolean callback_list_release(GtkWidget *widget, GdkEventButton *event, gpointer data)  
{  
	int i;
    int row = (int)data; 	
    printf("row = %d\n", row);  

	printf(">>list 111---song.old = %d\n",song.old);
	song.old = song.now;
	song.now = row;

	printf(">>list 222---song.old = %d\n",song.old);

	if(song.search_flag == 1)
	{
		song.search_flag = 0;

		for(i=0;i< song.count;i++)
		{
			if(song.search[i] == 1)
			{
				song.search[i] = 0;

				//gdk_threads_enter();
				sungtk_clist_set_row_color(musiclist, i, "black");
				//gdk_threads_leave();
			}
		}
	}

	set_keyflag(clist);
	set_songname(song.now);
#if 0
    const char *text = sungtk_clist_get_row_data(musiclist, row);  
    printf("text = %s\n", text);  

	song.now = row;
	printf("new = %d\n",song.now);
	strcpy(song.name,text);
	printf("song_name= %s\n",song.name);
#endif
    return TRUE;  
} 
