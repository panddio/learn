/* ************************************************************************
 *       Filename:  interface.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月18日 20时42分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <string.h>
#include "interface.h"
#include "image.h"

int fd; //保存管道文件描述符
int playing = FALSE;

// 按钮的回调函数
void deal_switch_image(GtkWidget *button, gpointer data)
{
	WINDOW *p_temp = (WINDOW *)data;
		
	if(button == p_temp->button_previous)   // 快退
	{		
		write(fd, "seek -10\n", strlen("seek -10\n"));
	}
	else if(button == p_temp->button_next ) // 快进
	{	
		write(fd, "seek -10\n", strlen("seek 10\n"));
	}
	else if(button == p_temp->button_pause ) // 赞同或播放
	{
		printf("p_temp->button_pause\n");
		
		if(playing)  // 正在播放，则暂停
		{
			write(fd, "pause\n", strlen("pause\n"));
			playing = FALSE;
					
			GtkWidget *image = gtk_image_new_from_file("./skin/pause.bmp"); // 图像控件
			gtk_button_set_image(GTK_BUTTON(p_temp->button_pause), image);
			
		}
		else //否则，开启播放
		{
			write(fd, "pause\n", strlen("pause\n"));
			playing = TRUE;
					
			GtkWidget *image = gtk_image_new_from_file("./skin/play.bmp"); // 图像控件
			gtk_button_set_image(GTK_BUTTON(p_temp->button_pause), image);
					
		}
		
	}
	
}

void show_window(gpointer data)
{
	WINDOW *p_temp = (WINDOW *)data;
	
	// 主窗口
	p_temp->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);		 	// 创建主窗口
	gtk_window_set_title(GTK_WINDOW(p_temp->main_window), "picture_browse");	 	// 设置窗口标题
	gtk_window_set_position(GTK_WINDOW(p_temp->main_window), GTK_WIN_POS_CENTER); // 设置窗口在显示器中的位置为居中
	gtk_widget_set_size_request(p_temp->main_window, 500, 250);		 	// 设置窗口的最小大小
	gtk_window_set_resizable(GTK_WINDOW(p_temp->main_window), FALSE); 	// 固定窗口的大小
	g_signal_connect(p_temp->main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
	
	// 表格布局
	p_temp->table = gtk_table_new(5, 7, TRUE);	// 表格布局容器 5行 7列
	gtk_container_add(GTK_CONTAINER(p_temp->main_window), p_temp->table); // 容器加入窗口

	// 按钮
#if 1
	p_temp->button_previous = create_button_from_file("./skin/previous.bmp", 70, 60);
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->button_previous, 1, 2, 2, 3);
	g_signal_connect(p_temp->button_previous, "clicked", G_CALLBACK(deal_switch_image), p_temp);
	
	p_temp->button_next = create_button_from_file("./skin/next.bmp", 70, 60);
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->button_next, 5, 6, 2, 3);
	g_signal_connect(p_temp->button_next, "clicked", G_CALLBACK(deal_switch_image), p_temp);
	
	p_temp->button_pause = create_button_from_file("./skin/play.bmp", 70, 60);
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->button_pause, 3, 4, 2, 3);
	g_signal_connect(p_temp->button_pause, "clicked", G_CALLBACK(deal_switch_image), p_temp);
#endif
	chang_background(p_temp->main_window, 500, 250, "./skin/background.bmp");	// 设置窗口背景图
	gtk_widget_show_all(p_temp->main_window);
}
