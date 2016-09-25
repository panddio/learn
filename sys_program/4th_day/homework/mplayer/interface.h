/* ************************************************************************
 *       Filename:  interface.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月18日 20时42分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <gtk/gtk.h>

typedef struct _Window
{
	GtkWidget *main_window;
	GtkWidget *table;
	GtkWidget *image;
	GtkWidget *button_previous;
	GtkWidget *button_next;
	GtkWidget *button_pause;
	//GtkWidget *progress;
}WINDOW;

extern int fd;
extern int playing;


void show_window(gpointer data);

#endif
