#include <gtk/gtk.h>
#include <stdlib.h> 
#include <string.h>

guint timer;	// 定时器id

/* 功能: 		设置控件字体大小
 * widget: 		需要改变字体的控件
 * size: 		字体大小
 * is_button: 	TRUE代表控件为按钮，FALSE为其它控件
 */
void set_widget_font_size(GtkWidget *widget, int size, int is_button)
{
	GtkWidget *labelChild;  
	PangoFontDescription *font;  
	gint fontSize = size;  
  
	font = pango_font_description_from_string("Sans");//"Sans"字体名   
	pango_font_description_set_size(font, fontSize*PANGO_SCALE);//设置字体大小   
	
	if(is_button){
		labelChild = gtk_bin_get_child(GTK_BIN(widget));//取出GtkButton里的label  
	}else{
		labelChild = widget;
	}
	
	//设置label的字体，这样这个GtkButton上面显示的字体就变了
	gtk_widget_modify_font(GTK_WIDGET(labelChild), font);
	pango_font_description_free(font);
}

/* 功能:  定时器处理函数
 * label: 主要用于显示数字
 */
gboolean deal_time( GtkWidget* label ) 
{
	char buf[5] = "";
	static int num = 10;
	num--;
	sprintf(buf, "%d", num);
	gtk_label_set_text(GTK_LABEL(label), buf);
	
	if(0 == num){
		num = 11;
		//g_source_remove(timer); // 移除定时器 
	}
	
	return TRUE;
}

int main( int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	
	/////////////////主窗口操作
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "倒计时");
	gtk_container_set_border_width(GTK_CONTAINER(window), 0);
	//设置窗口默认大小，设置一个最小大小
	gtk_window_set_default_size(GTK_WINDOW(window), 320, 400);
	//设置窗口在显示器中的位置为居中。
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect( G_OBJECT(window), "destroy",
		G_CALLBACK(gtk_main_quit), NULL ); //按关闭按钮可以把程序中断
	
	// 倒计时显示区域
	GtkWidget *label = gtk_label_new("10");		// label的创建
	set_widget_font_size(label, 230, FALSE);	// 设置label的字体大小
	gtk_container_add(GTK_CONTAINER(window), label);
	
	// 定时器的创建
	timer = g_timeout_add(500, (GSourceFunc)deal_time, (gpointer)label);
	
	gtk_widget_show_all(window); // 显示所有部件
	
	gtk_main();
	
	return 0;
}