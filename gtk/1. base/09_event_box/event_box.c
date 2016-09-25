/* 通过使用事件盒子，连接button-press-event信号到GtkLabel。
 * 当标签被双击时，标签中的文本会根据当前的状态改变。
 * 当单击事件发生时，什么都不会发生，尽管在本例中这个信号也被发出了。
 */
 #include <gtk/gtk.h>
 
static gboolean button_pressed(GtkWidget*, GdkEventButton*, GtkLabel*); // 函数的声明

int main( int argc, char *argv[] )
{
	gtk_init(&argc, &argv);
	
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	// 主窗口
	gtk_window_set_title(GTK_WINDOW(window), "Event Box");	    // 标题
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // 居中显示
	gtk_widget_set_size_request(window, 200, 50);				     // 最小大小
	g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL ); 
	
	GtkWidget *eventbox = gtk_event_box_new();				// 事件盒子的创建
	gtk_widget_set_events(eventbox, GDK_BUTTON_PRESS_MASK); // 捕获鼠标点击事件
	gtk_container_add( GTK_CONTAINER(window), eventbox );	// 事件盒子放入窗口
	
	GtkWidget *label = gtk_label_new("Double-Click Me!");	// label
	gtk_container_add( GTK_CONTAINER(eventbox), label );	// label放入事件盒子里
	
	g_signal_connect(eventbox, "button_press_event", 
						G_CALLBACK(button_pressed), (gpointer)label);
	
	gtk_widget_show_all(window);	// 显示所有控件
	
	gtk_main();
	
	return 0;
}
/* This is called every time a button-press event occurs on the GtkEventBox. */
static gboolean button_pressed( GtkWidget *eventbox, GdkEventButton *event, GtkLabel *label )
{
	if (event->type == GDK_2BUTTON_PRESS){
		const gchar *text = gtk_label_get_text(label);
		if( text[0] == 'D' ){
			gtk_label_set_text(label, "I Was Double-Clicked!");
		}else{
			gtk_label_set_text(label, "Double-Click Me Again!");
		}
	}
	
	return FALSE;
}