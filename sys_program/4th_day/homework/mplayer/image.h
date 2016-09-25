/* ************************************************************************
 *       Filename:  image.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月11日 14时47分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#ifndef __IMAGE_H__
#define __IMAGE_H__

void load_image(GtkWidget *image, const char *file_path, const int w, const int h );
GtkWidget *create_button_from_file(const char *file_path, const int w, const int h);
void chang_background(GtkWidget *widget, int w, int h, const gchar *path);

#endif
