#include <gtk/gtk.h>	// 头文件

// 鼠标点击事件处理函数
gboolean deal_mouse_press(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	switch(event->button){	// 判断鼠标点击的类型
        case 1:
            printf("Left Button!!\n");
            break;
        case 2:
            printf("Middle Button!!\n");
            break;
        case 3:
            printf("Right Button!!\n");
            break;
        default:
            printf("Unknown Button!!\n");
	}
	
	if(event->type == GDK_2BUTTON_PRESS){
		printf("double click\n");
	}
	
	// 获得点击的坐标值，距离窗口左顶点
	gint i = event->x;
	gint j = event->y;
	printf("press_x = %d, press_y = %d\n", i, j);
	
	return TRUE;
}

// 鼠标移动事件(点击鼠标任何键)的处理函数
gboolean deal_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
	// 获得移动鼠标的坐标值，距离窗口左顶点
	gint i = event->x;
	gint j = event->y;
	printf("motion_x = %d, motion_y = %d\n", i, j);
	
	return TRUE;
}

int main( int argc,char *argv[] )
{
	gtk_init(&argc, &argv);		// 初始化
	
	// 创建顶层窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// 设置窗口的标题
	gtk_window_set_title(GTK_WINDOW(window), "mouse_event");
	// 设置窗口在显示器中的位置为居中
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	// 设置窗口的最小大小
	gtk_widget_set_size_request(window, 400, 300);
	// "destroy" 和 gtk_main_quit 连接
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	// 窗口接收鼠标事件
	// GDK_BUTTON_PRESS_MASK：鼠标点击事件
	// GDK_BUTTON_MOTION_MASK：按住鼠标移动事件
	gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_MOTION_MASK);
	
	// "button-press-event" 与 deal_mouse_event 连接，鼠标点击事件
	g_signal_connect(window, "button-press-event", G_CALLBACK(deal_mouse_press), NULL);
	// "motion-notify-event" 与 deal_motion_notify_event 连接，按住鼠标移动事件
	g_signal_connect(window, "motion-notify-event", G_CALLBACK(deal_motion_notify_event), NULL);
	
    gtk_widget_show_all(window);	// 显示窗口全部控件
	
    gtk_main();		// 主事件循环
	
    return 0;
}