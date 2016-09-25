/* ************************************************************************
 *       Filename:  gtk_calculator.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月10日 19时59分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <gtk/gtk.h>


int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"GTK entry");

	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);//设置窗口的位置
	gtk_widget_set_size_request(window, 500, 300);	               //设置窗口的大小	
	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);            //设置窗口是否可以改变大小

	GtkWidget *entry = gtk_entry_new();                //创建行编辑	
	gtk_entry_set_max_length(GTK_ENTRY(entry), 100);   //设置行编辑显示最大字符的长度
	gtk_entry_set_text(GTK_ENTRY(entry), "1+2=3");     //设置显示内容
	gtk_entry_set_editable(GTK_EDITABLE(entry),FALSE); //设置行编辑不予许编辑，只能显示
	
	