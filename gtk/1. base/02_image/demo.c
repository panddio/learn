#include <gtk/gtk.h>

typedef struct _Window
{
	GtkWidget *main_window;
	GtkWidget *table;
	GtkWidget *image;
	GtkWidget *button_previous;
	GtkWidget *button_next;
}WINDOW;

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

// 按钮的回调函数
void deal_switch_image(GtkWidget *button, gpointer data)
{
	WINDOW *p_temp = (WINDOW *)data;
	
	if(button == p_temp->button_previous){		// 上一张
		printf("p_temp->button_previous\n");
	}else if(button == p_temp->button_next ){	// 下一张
		printf("p_temp->button_next\n");
	}
}

void window_demo(gpointer data)
{
	WINDOW *p_temp = (WINDOW *)data;
	
	// 主窗口
	p_temp->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);		 	// 创建主窗口
	gtk_window_set_title(GTK_WINDOW(p_temp->main_window), "image");	 	// 设置窗口标题
	gtk_window_set_position(GTK_WINDOW(p_temp->main_window), GTK_WIN_POS_CENTER); // 设置窗口在显示器中的位置为居中
	gtk_widget_set_size_request(p_temp->main_window, 800, 480);		 	// 设置窗口的最小大小
	gtk_window_set_resizable(GTK_WINDOW(p_temp->main_window), FALSE); 	// 固定窗口的大小
	g_signal_connect(p_temp->main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
	
	// 表格布局
	p_temp->table = gtk_table_new(7, 7, TRUE);	 					      // 表格布局容器
	gtk_container_add(GTK_CONTAINER(p_temp->main_window), p_temp->table); // 容器加入窗口
	
	// 图片控件
	p_temp->image = gtk_image_new_from_pixbuf(NULL);		// 创建图片控件
	load_image(p_temp->image, "./image/1.jpg", 500, 450);
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->image, 1, 6, 1, 6);	// 把图片控件加入布局

	
	// 按钮
	p_temp->button_previous = create_button_from_file("./image/previous.bmp", 80, 80);
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->button_previous, 1, 2, 6, 7);
	g_signal_connect(p_temp->button_previous, "clicked", G_CALLBACK(deal_switch_image), p_temp);
	
	p_temp->button_next = create_button_from_file("./image/next.bmp", 80, 80);
	gtk_table_attach_defaults(GTK_TABLE(p_temp->table), p_temp->button_next, 5, 6, 6, 7);
	g_signal_connect(p_temp->button_next, "clicked", G_CALLBACK(deal_switch_image), p_temp);
	
	gtk_widget_show_all(p_temp->main_window);
	
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);		// 初始化
	
	WINDOW window;
	window_demo(&window);

	gtk_main();			// 主事件循环

	return 0;
}