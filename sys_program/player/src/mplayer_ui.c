/* ************************************************************************
 *       Filename:  gtk_button.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月10日 10时14分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "common.h"
#include "file.h"
#include "mplayer_pthread.h"
#include "gtk_callback.h"
#include "mplayer_ui.h"


//MPLAYER mplayer; 
SunGtkCList *musiclist = NULL;  
  
static void show_boot_animation(MPLAYER *pm)
{
	int i;
	char ch[2] = "a"; 
	char path[] = "./image/jpg/";	
	char jpg[] = ".JPG";
	char buf[64];

	for(i=0; i<18;i++)
	{
		bzero(buf, sizeof(buf));
		ch[0] += i;
		strcat(buf, path);
		strcat(buf, ch);
		strcat(buf, jpg);

		printf("jpg path = %s####\n",buf);
		sungtk_background_set_picture(pm->ui.main_window,buf,800, 480);
		gtk_widget_show_all(pm->ui.main_window);
		ch[0] = 'a';
		sleep(1);
	}
}

static int hbox_left_init(MPLAYER *pm, GtkBuilder *builder)
{
	pm->ui.hbox_left.bmusic_list     = GTK_BUTTON(gtk_builder_get_object(builder, "bmusic_list"));
	pm->ui.hbox_left.bmusic_collect  = GTK_BUTTON(gtk_builder_get_object(builder, "bmusic_collect"));
	pm->ui.hbox_left.bmusic_recently = GTK_BUTTON(gtk_builder_get_object(builder, "bmusic_recently"));

	gtk_widget_set_sensitive(GTK_WIDGET(pm->ui.hbox_left.bmusic_list), FALSE);
	g_signal_connect(pm->ui.hbox_left.bmusic_list,    "clicked", G_CALLBACK(musiclist_buttons_callback), pm);
	g_signal_connect(pm->ui.hbox_left.bmusic_collect, "clicked", G_CALLBACK(musiclist_buttons_callback), pm);
	g_signal_connect(pm->ui.hbox_left.bmusic_recently,"clicked", G_CALLBACK(musiclist_buttons_callback), pm);
	
	pm->ui.hbox_left.eventbox_musiclist  = (GtkEventBox *)(gtk_builder_get_object(builder, "eventbox_musiclist"));
	gtk_event_box_set_visible_window(pm->ui.hbox_left.eventbox_musiclist, FALSE); //???

	//
	pm->ui.hbox_left.button_search= GTK_BUTTON(gtk_builder_get_object(builder, "button_search"));
	sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_left.button_search), "./image/style/find.png",20,20);
	g_signal_connect(GTK_WIDGET(pm->ui.hbox_left.button_search), "clicked", G_CALLBACK(search_entry_callback), pm);
	
	pm->ui.hbox_left.table_search = GTK_TABLE(gtk_builder_get_object(builder, "table_search"));
	pm->ui.hbox_left.entry_search = GTK_ENTRY(gtk_entry_new());                         //б?		
	gtk_entry_set_max_length(GTK_ENTRY(pm->ui.hbox_left.entry_search), 30); //б????	
	gtk_table_attach_defaults(pm->ui.hbox_left.table_search,GTK_WIDGET(pm->ui.hbox_left.entry_search),0,1,0,1); //
	g_signal_connect(GTK_WIDGET(pm->ui.hbox_left.entry_search), "activate",G_CALLBACK(search_entry_callback), pm);
	
	pm->ui.hbox_left.table_musiclist = GTK_TABLE(gtk_builder_get_object(builder, "table_musiclist"));

	//б
	musiclist = sungtk_clist_new();  
    sungtk_clist_set_row_height(musiclist, 25);  
    sungtk_clist_set_col_width(musiclist, 200);  
    sungtk_clist_set_text_size(musiclist, 12);  
    sungtk_clist_set_select_row_signal(musiclist, "button-release-event", callback_list_release);  
    gtk_table_attach_defaults(pm->ui.hbox_left.table_musiclist, musiclist->fixed, 1, 4, 1, 5);  
      
    //sungtk_clist_append(musiclist, "aaaaaaaaaaa");  
    //sungtk_clist_append(musiclist, "bbbbbbbbbb");  
      
    //sungtk_clist_set_row_color(musiclist, 0, "red");

	return 0;
}

static int hbox_right_init(MPLAYER *pm, GtkBuilder *builder)
{
#if 1 
	pm->ui.hbox_right.button_pause   = GTK_BUTTON(gtk_builder_get_object(builder, "button_pause"));
	pm->ui.hbox_right.button_back    = GTK_BUTTON(gtk_builder_get_object(builder, "button_back"));
	pm->ui.hbox_right.button_next    = GTK_BUTTON(gtk_builder_get_object(builder, "button_next"));
	pm->ui.hbox_right.button_backward= GTK_BUTTON(gtk_builder_get_object(builder, "button_backward"));
	pm->ui.hbox_right.button_forward = GTK_BUTTON(gtk_builder_get_object(builder, "button_forward"));
	pm->ui.hbox_right.button_volume  = GTK_BUTTON(gtk_builder_get_object(builder, "button_volume"));
	pm->ui.hbox_right.button_playmode= GTK_BUTTON(gtk_builder_get_object(builder, "button_playmode"));
		
	sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_back),     "./image/style/back.png",70,70);	
	sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_pause),    "./image/style/pause.png",70,70);
	sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_next),     "./image/style/next.png",70,70);	
	sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_backward), "./image/style/backward.png",60,60);
	sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_forward),  "./image/style/forward.png",60,60);
	sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_volume),   "./image/style/beam.png",50,50);
	sungtk_button_inset_image(GTK_WIDGET(pm->ui.hbox_right.button_playmode), "./image/style/playmode_list_loop.png",20,20);
	
	g_signal_connect(pm->ui.hbox_right.button_pause,    "clicked", G_CALLBACK(music_buttons_callback), pm);
	g_signal_connect(pm->ui.hbox_right.button_back,     "clicked", G_CALLBACK(music_buttons_callback), pm);
	g_signal_connect(pm->ui.hbox_right.button_next,     "clicked", G_CALLBACK(music_buttons_callback), pm);
	g_signal_connect(pm->ui.hbox_right.button_backward, "clicked", G_CALLBACK(music_buttons_callback), pm);
	g_signal_connect(pm->ui.hbox_right.button_forward,  "clicked", G_CALLBACK(music_buttons_callback), pm);
	g_signal_connect(pm->ui.hbox_right.button_volume,   "clicked", G_CALLBACK(music_buttons_callback), pm);
	g_signal_connect(pm->ui.hbox_right.button_playmode, "clicked", G_CALLBACK(playmode_button_callback), pm);
#endif	

#if 1 //label
	pm->ui.hbox_right.label_title1 = GTK_LABEL(gtk_builder_get_object(builder, "label_title1"));
	pm->ui.hbox_right.label_title2 = GTK_LABEL(gtk_builder_get_object(builder, "label_title2"));
	pm->ui.hbox_right.label_title3 = GTK_LABEL(gtk_builder_get_object(builder, "label_title3"));
	
	pm->ui.hbox_right.label_lrc1 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc1"));
	pm->ui.hbox_right.label_lrc2 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc2"));
	pm->ui.hbox_right.label_lrc3 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc3"));
	pm->ui.hbox_right.label_lrc4 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc4"));
	pm->ui.hbox_right.label_lrc5 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc5"));
	pm->ui.hbox_right.label_lrc6 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc6"));
	pm->ui.hbox_right.label_lrc7 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc7"));	

	sungtk_widget_set_font_color(GTK_WIDGET(pm->ui.hbox_right.label_lrc2),"yellow", FALSE);
	//char pbuf[] = "heheheh";
	gtk_label_set_text(pm->ui.hbox_right.label_title1, "");	
	gtk_label_set_text(pm->ui.hbox_right.label_title2, "");	
	gtk_label_set_text(pm->ui.hbox_right.label_title3, "");
	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc1, "");
	gtk_label_set_text(pm->ui.hbox_right.label_lrc2, "");	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc3, "");	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc4, "");	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc5, "");	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc6, "");	
	gtk_label_set_text(pm->ui.hbox_right.label_lrc7, "");	

	//sungtk_widget_set_font_color(GTK_WIDGET(pm->ui.hbox_right.label_lrc4),"MedSpringGreen", FALSE);
		
	pm->ui.hbox_right.label_cur_time = GTK_LABEL(gtk_builder_get_object(builder, "label_cur_time"));
	pm->ui.hbox_right.label_end_time = GTK_LABEL(gtk_builder_get_object(builder, "label_end_time"));	
#endif	

	pm->ui.hbox_right.progress_bar    = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "progress_bar"));
	pm->ui.hbox_right.eventbox_bar    = (GtkEventBox *)(gtk_builder_get_object(builder, "eventbox_bar"));
	pm->ui.hbox_right.eventbox_volume = (GtkEventBox *)(gtk_builder_get_object(builder, "eventbox_volume"));
	gtk_event_box_set_visible_window(pm->ui.hbox_right.eventbox_bar,   FALSE);
	gtk_event_box_set_visible_window(pm->ui.hbox_right.eventbox_volume,FALSE);

	//???
	gtk_widget_add_events(GTK_WIDGET(pm->ui.hbox_right.eventbox_bar), GDK_BUTTON_MOTION_MASK);
	// "motion-notify-event"  motion_event_callback ????
	g_signal_connect(GTK_WIDGET(pm->ui.hbox_right.eventbox_bar), "motion-notify-event", G_CALLBACK(motion_event_callback), pm);


	pm->ui.hbox_right.image_logo = GTK_IMAGE(gtk_builder_get_object(builder, "image_logo"));
	sungtk_image_load_picture(GTK_WIDGET(pm->ui.hbox_right.image_logo), "./image/style/picture.png", 140, 140);	
	
	return 0;
}

void window_init(MPLAYER *pm)
{
	//创建GtkBuilder对象，GtkBuilder在<gtk/gtk.h>声明
	//读取Mplayer.glade文件的信息，保存在builder中 	
	GtkBuilder *builder = gtk_builder_new(); //创建GtkBuilder对象，GtkBuilder在<gtk/gtk.h>声明
	if(!gtk_builder_add_from_file(builder,"Mplayer.glade", NULL)) //读取Mplayer.glade文件的信息，保存在builder中   
	{  
		printf("connot Mplayer.glade file!");  
	} 
	 

	//获取窗口指针，注意"main_window"要和glade里面的标签名词匹配
	pm->ui.main_window = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
	
 	gtk_window_set_title(GTK_WINDOW(pm->ui.main_window), "Mplayer");	            // 设置窗口标题
	gtk_window_set_position(GTK_WINDOW(pm->ui.main_window), GTK_WIN_POS_CENTER);    // 设置窗口在显示器中的位置为居中
	gtk_widget_set_size_request(pm->ui.main_window, 800, 480);		 	             // 设置窗口的最小大小
	gtk_window_set_resizable(GTK_WINDOW(pm->ui.main_window), FALSE); 	            // 固定窗口的大小
	//gtk_window_set_decorated(GTK_WINDOW(pm->ui.main_window), FALSE); // 设置无边框
	g_signal_connect(pm->ui.main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
	

	//show_boot_animation(pm);
	sungtk_background_set_picture(pm->ui.main_window,"./image/background/11.jpg",800, 480);
	
	hbox_left_init(pm, builder);  //
	hbox_right_init(pm, builder); //
	
	gtk_widget_show_all(pm->ui.main_window);
}

void mplayer_ui_show(int argc, char *argv[], MPLAYER *pm)
{
	
	pm->playflag  = stop; //暂停
	pm->soundflag = beam; //播音
	
	gtk_init(&argc, &argv);
	window_init(pm);
	gtk_main();
}
