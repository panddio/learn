/* ************************************************************************
 *       Filename:  entry.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月10日 14时28分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <gtk/gtk.h>


void entry_callback(GtkWidget *widget, gpointer entry)
{
	const gchar *entry_text;

	entry_text = (gchar *)gtk_entry_get_text(GTK_ENTRY(entry));
	printf("Entry contents: %s\n",entry_text);	
}

int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"GTK entry");

	GtkWidget *vbox1 = gtk_vbox_new(TRUE, 5); //创建一个垂直布局容器
	gtk_container_add(GTK_CONTAINER(window), vbox1);
	
	GtkWidget *hbox1 = gtk_hbox_new(TRUE, 0); //创建一个水平布局容器
	gtk_container_add(GTK_CONTAINER(vbox1), hbox1); //加入垂直布局里面
	
	GtkWidget *label = gtk_label_new("text: ");
	gtk_container_add(GTK_CONTAINER(hbox1), label); //加入垂直布局里面
	
	GtkWidget *entry = gtk_entry_new(); //创建行编辑	
	gtk_entry_set_max_length(GTK_ENTRY(entry), 100);//设置行编辑显示最大字符的长度
	//gtk_entry_set_text(GTK_ENTRY(entry), "hello world");//设置显示内容
	gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE); //密码模式
	gtk_container_add(GTK_CONTAINER(hbox1), entry); //加入水平布局里面

	g_signal_connect(entry, "activate",G_CALLBACK(entry_callback), entry);

	GtkWidget *vbox2 = gtk_vbox_new(TRUE, 5); //创建一个垂直布局容器
	gtk_container_add(GTK_CONTAINER(window), vbox2);
	
	GtkWidget *hbox2 = gtk_hbox_new(TRUE, 0); //创建一个水平布局容器
	

	GtkWidget *button1 = gtk_button_new_with_label("button 1");
	gtk_container_add(GTK_CONTAINER(hbox2), button1);

	GtkWidget *button2 = gtk_button_new_with_label("button 2");
	gtk_container_add(GTK_CONTAINER(hbox2), button2);
	gtk_container_add(GTK_CONTAINER(vbox2), hbox2);
	
	GtkWidget *button_close = gtk_button_new_with_label("close");	
	g_signal_connect(button_close,"clicked", G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_add(GTK_CONTAINER(vbox2), button_close);

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}


