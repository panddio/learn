/* ************************************************************************
 *       Filename:  gtk_hbox.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月10日 11时34分43秒
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

	g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit),NULL);

	//创建一个垂直容器
	GtkWidget *vbox = gtk_vbox_new(TRUE,10);

	//添加到window
	gtk_container_add(GTK_CONTAINER(window),vbox);

	GtkWidget *button1 = gtk_button_new_with_label("button1");
	//添加button1到hbox
	gtk_container_add(GTK_CONTAINER(vbox),button1);

	GtkWidget *button2 = gtk_button_new_with_label("button2");
	//添加button1到hbox
	gtk_container_add(GTK_CONTAINER(vbox),button2);

	GtkWidget *button3 = gtk_button_new_with_label("button3");
	//添加button1到hbox
	gtk_container_add(GTK_CONTAINER(vbox),button3);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}



