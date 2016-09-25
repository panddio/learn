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

#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_container_set_border_width(GTK_CONTAINER(window),15);

	GtkWidget *button = gtk_button_new_with_label("button");

	const char *str =  gtk_button_get_label(GTK_BUTTON(button));

	printf("str =  %s\n",str);

	gtk_container_add(GTK_CONTAINER(window),button);


	gtk_widget_show_all(window);

	gtk_main();

	return 0;

}


