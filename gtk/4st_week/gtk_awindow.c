/* ************************************************************************
 *       Filename:  gtk_awimdow.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月10日 09时35分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	//设置窗口标题
	gtk_window_set_title(GTK_WINDOW(window),"Hello GTK");
	
	//设置窗口的位置
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

	//设置窗口的大小
	gtk_widget_set_size_request(window, 400, 300);
	
	//设置窗口是否可以改变大小
	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);

	gtk_widget_show_all(window);
	//隐藏窗口


	gtk_main();

	return 0;
}



