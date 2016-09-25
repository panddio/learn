#ifndef __GTK_CALLBACK_H__
#define __GTK_CALLBACK_H__

extern gboolean motion_event_callback(GtkWidget *widget, GdkEventMotion *event, gpointer data);
extern void search_entry_callback(GtkWidget *widget, gpointer entry);
extern void keys_board_callback(GtkWidget *widget, GdkEventKey  *event, gpointer data);
extern void playmode_button_callback(GtkButton *button, gpointer data);
extern void musiclist_buttons_callback(GtkButton *button, gpointer data);
extern void music_buttons_callback(GtkButton *button, gpointer data);
extern gboolean callback_list_release(GtkWidget *widget, GdkEventButton *event, gpointer data);
#endif