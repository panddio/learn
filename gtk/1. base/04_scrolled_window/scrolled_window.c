 #include <gtk/gtk.h> 

// 回调函数
void destroy( GtkWidget *widget, gpointer data ) 
{ 
    gtk_main_quit(); 
} 
 
int main( int   argc, char *argv[] ) 
{
    gtk_init (&argc, &argv); 
     
    // 创建顶层窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// 设置窗口的标题
	gtk_window_set_title(GTK_WINDOW(window), "GtkScrolledWindow");
	// 设置窗口在显示器中的位置为居中
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 
    gtk_widget_set_size_request(window, 300, 200); // 设置窗口的最小大小
     
    /* 创建一个新的滚动窗口。
	 * 第一个参数是水平方向的调整对象，第二个参数是垂直方向的调整对象。它们总是设置为NULL。
	 */
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL); 
    gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 10); 
	gtk_container_add(GTK_CONTAINER(window), scrolled_window); // 滚动窗口放入窗口
     
    /* 滚动条的出现方式可以是 GTK_POLICY_AUTOMATIC 或GTK_POLICY_ALWAYS。 
     * GTK_POLICY_AUTOMATIC：将自动决定是否需要出现滚动条 
     * GTK_POLICY_AUTOMATIC：将自动决定是否需要出现滚动条 
     * 第一个是设置水平滚动条，第二个是垂直滚动条 
	 */ 
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), 
                     GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 
	
	// 标签
	GtkWidget *label = gtk_label_new("This is an example of a line-wrapped label. It "\
	   "should not be taking up the entire "\
       "width allocated to it, but automatically "\
       "wraps the words to fit.  "\
       "The time has come, for all good men, to come to "\
       "the aid of their party. "\
       "The sixth sheik's six sheep's sick.\n"\
       "     It supports multiple paragraphs correctly, "\
       "and correctly adds "\
       "many extra  spaces."\
	   "This is an example of a line-wrapped label. It "\
	   "should not be taking up the entire "\
       "width allocated to it, but automatically "\
       "wraps the words to fit.  "\
       "The time has come, for all good men, to come to "\
       "the aid of their party. "\
       "The sixth sheik's six sheep's sick.\n"\
       "     It supports multiple paragraphs correctly, "\
       "and correctly adds "\
       "many extra  spaces."); 
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE); 	// label 自动换行
	
    // 将标签组装到滚动窗口中 
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), label); 
  
    gtk_widget_show_all(window); 
     
    gtk_main(); 
     
    return 0; 
}