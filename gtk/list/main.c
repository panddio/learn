#include <gtk/gtk.h>  
#include"sungtk_interface.h"  
  
SunGtkCList *list = NULL;  
  
static gboolean callback_list_release(GtkWidget *widget, GdkEventButton *event, gpointer data)  
{  
    int row = (int)data;  
    printf("row===%d\n", row);  
      
    const char *text = sungtk_clist_get_row_data(list, row);  
    printf("text==%s==\n", text);  
    return TRUE;  
}  
  
int main(int argc, char *argv[])  
{  
    gtk_init(&argc, &argv);  
  
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
    gtk_window_set_title((GtkWindow *)window, "Hello");  
    gtk_widget_set_size_request(window, 400,300);  
      
    GtkWidget *table = gtk_table_new(5, 5, TRUE);  
    gtk_container_add(GTK_CONTAINER(window), table);  
  
    list = sungtk_clist_new();  
    sungtk_clist_set_row_height(list, 40);  
    sungtk_clist_set_col_width(list, 200);  
    sungtk_clist_set_text_size(list, 13);  
    sungtk_clist_set_select_row_signal(list, "button-release-event", callback_list_release);  
    gtk_table_attach_defaults(GTK_TABLE(table), list->fixed, 1, 4, 1, 5);  
      
    sungtk_clist_append(list, "aaaaaaaaaaa");  
    sungtk_clist_append(list, "bbbbbbbbbb");  
      
    sungtk_clist_set_row_color(list, 0, "red");  
      
	sungtk_background_set_picture(window,"./3.jpg",400, 300);	// 设置窗口背景图	
    gtk_widget_show_all(window);  
    gtk_main();  
    return 0;
}	