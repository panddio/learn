/* ************************************************************************
 *       Filename:  picture_browse.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月11日 14时21分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <gtk/gtk.h>
#include "scan_dir.h"
#include "image.h"

gboolean pause_flag = TRUE;
guint timer;	// 定时器id
gdouble upstep;
char buf[6];

typedef struct _Window
{
	GtkWidget *main_window;
	GtkWidget *table;
	GtkWidget *image;
	GtkWidget *button_previous;
	GtkWidget *button_next;
	GtkWidget *button_pause;
	GtkWidget *progress;
}WINDOW;

void itoc(int number, char buf[])
{

	buf[0] = number/1000;
	buf[1] = number%1000/100;
	buf[2] = number%100/10;
	buf[3] = '%';
	buf[4] = '\0';
	buf[5] = number%10;	
	
	if(buf[5] > 5)
	{
		buf[2] += 1;
		if(buf[2] >= 10)
		{
			buf[2] = 0;
			buf[1] += 1;
			
			if(buf[1] >= 10)
			{
				buf[1] = 0;
				
				if(buf[0] > 0) buf[0] = 1;
				else buf[0] += 1;
			}
		}
	}
	
	if (buf[0] == 0) buf[0] = ' ';
	else  buf[0] +=48;
	buf[1] += 48;
	buf[2] += 48;
}

// 定时器的回调函数
static void timer_callback(gpointer data)
{
	WINDOW *p_temp = (WINDOW *)data;
	//upstep = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(p_temp->progress));	
	gs_index++;	
	upstep += (gdouble)(1.0/(gs_bmp_total));	
	if(gs_index >= gs_bmp_total)
	{
		gs_index = 0;
		upstep = (gdouble)(1.0/(gs_bmp_total));;
	}
	
	printf("gs_index = %d\n", gs_index);
	load_image(p_temp->image, gs_bmp_name[gs_index], 500, 450);	
	
	// 设置进度条的新值 
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(p_temp->progress), upstep); 
	
	itoc((int)(upstep*1000),buf);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(p_temp->progress), buf);
}
// 按钮的回调函数
void deal_switch_image(GtkWidget *button, gpointer data)
{
	WINDOW *p_temp = (WINDOW *)data;

	//gdouble upstep = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(p_temp->progress)); 
	
	//创建图片控件(这里加这行会出现只能播放一张图片的错误)
	//p_temp->image = gtk_image_new_from_pixbuf(NULL); 
	
	if(button == p_temp->button_previous)// 上一张
	{		
		gs_index--;
		upstep -= (gdouble)(1.0/(gs_bmp_total));
		if(gs_index < 0)
		{	
			gs_index = gs_bmp_total - 1;
			upstep = 1;
		}
		printf("gs_index = %d\n", gs_index);
		printf("p_temp->button_previous\n");
		load_image(p_temp->image, gs_bmp_name[gs_index], 500, 450);

	}
	else if(button == p_temp->button_next ) // 下一张
	{	
		gs_index++;	
		upstep += (gdouble)(1.0/(gs_bmp_total));
		
		if(gs_index >= gs_bmp_total)
		{
			gs_index = 0;
			upstep = (gdouble)(1.0/(gs_bmp_total));
		}
		printf("gs_index = %d\n", gs_index);
		printf("p_temp->button_next\n");
		load_image(p_temp->image, gs_bmp_name[gs_index], 500, 450);
	}
	else if(button == p_temp->button_pause ) 
	{
		printf("p_temp->button_pause\n");
		
		if(pause_flag)  // 自动播放
		{
			pause_flag = FALSE;
			
			gtk_widget_set_sensitive(p_temp->button_next, FALSE);
			gtk_widget_set_sensitive(p_temp->button_previous, FALSE);
			
			GtkWidget *image = gtk_image_new_from_file("./skin/pause.bmp"); // 图像控件
			gtk_button_set_image(GTK_BUTTON(p_temp->button_pause), image);
			
			//创建定时器
			timer = g_timeout_add(1000, (GSourceFunc)timer_callback, (gpointer)data);
		}
		else
		{
			pause_flag = TRUE;
			
			gtk_widget_set_sensitive(p_temp->button_next, TRUE);
			gtk_widget_set_sensitive(p_temp->button_previous, TRUE);
			
			GtkWidget *image = gtk_image_new_from_file("./skin/play.bmp"); // 图像控件
			gtk_button_set_image(GTK_BUTTON(p_temp->button_pause), image);
			
			//移除定时器
			g_source_remove(timer);		
		}
		
	}
	
	printf("%f\n",(float)upstep);
 
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(p_temp->progress), upstep); //设置进度条的新值
	
	itoc((int)(upstep*1000),buf);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(p_temp->progress), buf);
	
	//gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->image, 1, 6, 1, 6);	// 把图片控件加入布局
	//gtk_widget_show_all(p_temp->main_window);
}

void show_window(gpointer data)
{
	WINDOW *p_temp = (WINDOW *)data;
	upstep = (gdouble)(1.0/(gs_bmp_total));
	// 主窗口
	p_temp->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);		 	// 创建主窗口
	gtk_window_set_title(GTK_WINDOW(p_temp->main_window), "picture_browse");	 	// 设置窗口标题
	gtk_window_set_position(GTK_WINDOW(p_temp->main_window), GTK_WIN_POS_CENTER); // 设置窗口在显示器中的位置为居中
	gtk_widget_set_size_request(p_temp->main_window, 800, 480);		 	// 设置窗口的最小大小
	gtk_window_set_resizable(GTK_WINDOW(p_temp->main_window), FALSE); 	// 固定窗口的大小
	g_signal_connect(p_temp->main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
	
	// 表格布局
	p_temp->table = gtk_table_new(7, 7, TRUE);	// 表格布局容器 7行 7列
	gtk_container_add(GTK_CONTAINER(p_temp->main_window), p_temp->table); // 容器加入窗口
	
	// 图片控件
	//gs_index = 1;
	p_temp->image = gtk_image_new_from_pixbuf(NULL);		// 创建图片控件
	load_image(p_temp->image, gs_bmp_name[gs_index], 500, 450);
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->image, 1, 6, 1, 6);	// 把图片控件加入布局
	
	// 进度条
	GtkWidget *table = gtk_table_new(5, 7, TRUE);  // 表格布局容器，用来存放进度条，限制进度条的宽度
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), table, 0, 7, 0, 1);// 把进度条控件加入布局
	
	p_temp->progress = gtk_progress_bar_new();
	gtk_table_attach_defaults(GTK_TABLE(table), p_temp->progress, 1, 6, 3, 4);// 把进度条控件加入布局
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(p_temp->progress), upstep); //设置开始进度为零
	itoc((int)(upstep*1000),buf);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(p_temp->progress), buf);
	//gtk_progress_bar_set_bar_style (p_temp->progress,GTK_PROGRESS_CONTINUOUS);

	// 按钮
#if 1
	p_temp->button_previous = create_button_from_file("./skin/previous.bmp", 70, 60);
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->button_previous, 1, 2, 6, 7);
	g_signal_connect(p_temp->button_previous, "clicked", G_CALLBACK(deal_switch_image), p_temp);
	
	p_temp->button_next = create_button_from_file("./skin/next.bmp", 70, 60);
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->button_next, 5, 6, 6, 7);
	g_signal_connect(p_temp->button_next, "clicked", G_CALLBACK(deal_switch_image), p_temp);
	
	p_temp->button_pause = create_button_from_file("./skin/play.bmp", 70, 60);
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->button_pause, 3, 4, 6, 7);
	g_signal_connect(p_temp->button_pause, "clicked", G_CALLBACK(deal_switch_image), p_temp);
#endif
	chang_background(p_temp->main_window, 800, 480, "./skin/background.bmp");	// 设置窗口背景图
	gtk_widget_show_all(p_temp->main_window);
}

int main(int argc, char* argv[])
{
	WINDOW window;
	
	gtk_init(&argc, &argv);	
	
	get_bmp_name(IMAGE_DIR);
	order_bmp_name();
	//bmp_name_print();//for test
	show_window(&window);
	
	gtk_main();
	return 0;
}

