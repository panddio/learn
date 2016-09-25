/* ************************************************************************
 *       Filename:  image.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月11日 14时47分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <gtk/gtk.h>

// 给创建好的image重新设计一张图片
void load_image(GtkWidget *image, const char *file_path, const int w, const int h )
{
	gtk_image_clear( GTK_IMAGE(image) );        // 清除图像
	GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(file_path, NULL);	// 创建图片资源
	GdkPixbuf *dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR); // 指定大小
	gtk_image_set_from_pixbuf(GTK_IMAGE(image), dest_pixbuf); // 图片控件重新设置一张图片(pixbuf)
	g_object_unref(src_pixbuf);		// 释放资源
	g_object_unref(dest_pixbuf);	// 释放资源
}

// 根据图片路径创建一个新按钮，同时指定图片大小
GtkWidget *create_button_from_file(const char *file_path, const int w, const int h)
{
	GtkWidget *temp_image = gtk_image_new_from_pixbuf(NULL);
	load_image(temp_image, file_path, w, h);
	
	GtkWidget *button = gtk_button_new(); 					// 先创建空按钮
	gtk_button_set_image(GTK_BUTTON(button), temp_image);	// 给按钮设置图标
	gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);	// 按钮背景色透明
	
	return button;
}

/* 功能：  设置背景图
 * widget: 主窗口
 * w, h:   图片的大小
 * path：  图片路径
 */
void chang_background(GtkWidget *widget, int w, int h, const gchar *path)
{
	gtk_widget_set_app_paintable(widget, TRUE);		//允许窗口可以绘图
    gtk_widget_realize(widget);	
	
	/* 更改背景图时，图片会重叠
	 * 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。
	 */
	gtk_widget_queue_draw(widget);
	
    GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL);	// 创建图片资源对象
    // w, h是指定图片的宽度和高度
    GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);

	GdkPixmap *pixmap = NULL;
	
	/* 创建pixmap图像; 
	 * NULL：不需要蒙版; 
	 * 123： 0~255，透明到不透明
	 */
    gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 50);
    // 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASLE
	gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);
    
	// 释放资源
	g_object_unref(src_pixbuf);
    g_object_unref(dst_pixbuf);
    g_object_unref(pixmap);
}

