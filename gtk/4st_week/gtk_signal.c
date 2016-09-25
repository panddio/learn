/* ************************************************************************
 *       Filename:  gtk_signal.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月10日 10时52分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <gtk/gtk.h>

void button_callback(GtkButton *button, gpointer data)
{
	const char *str =  gtk_button_get_label(button);

	printf("str = %s    data = %s\n",str, (gchar *)data);
}
int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);


	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);

	GtkWidget *button = gtk_button_new_with_label("button");
	gtk_container_add(GTK_CONTAINER(window),button);


	g_signal_connect(button,"clicked",G_CALLBACK(button_callback),"hello_button");

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}


