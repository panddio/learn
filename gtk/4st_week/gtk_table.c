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

	GtkWidget *table = gtk_table_new(2,3,TRUE);

	GtkWidget *button1 = gtk_button_new_with_label("button1");
	
	GtkWidget *button2 = gtk_button_new_with_label("button2");
	GtkWidget *button3 = gtk_button_new_with_label("button3");
	GtkWidget *button4 = gtk_button_new_with_label("button4");
	GtkWidget *button5 = gtk_button_new_with_label("button5");
	GtkWidget *button6 = gtk_button_new_with_label("button6");

	gtk_table_attach_defaults(GTK_TABLE(table),button1,0,1,0,1);
	gtk_table_attach_defaults(GTK_TABLE(table),button2,1,2,0,1);
	gtk_table_attach_defaults(GTK_TABLE(table),button3,2,3,0,1);
	gtk_table_attach_defaults(GTK_TABLE(table),button4,0,1,1,2);
	gtk_table_attach_defaults(GTK_TABLE(table),button5,1,2,1,2);
	gtk_table_attach_defaults(GTK_TABLE(table),button6,2,3,1,2);
	
	gtk_container_add(GTK_CONTAINER(window),table);
	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}




