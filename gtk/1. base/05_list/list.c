#include <gtk/gtk.h>

// 用户点击"Add List"按钮时的回调函数
void button_add_clicked( GtkWidget *widget, gpointer data )
{
	char *a[2] = {"Mike",  "3 Oz"};
	gtk_clist_append( (GtkCList *)data, a );

	char *b[2] = { "Water",   "6 l" };
	gtk_clist_append( (GtkCList *)data, b );
}

//用户点击"Clear List"  按钮时的回调函数
void button_clear_clicked( GtkWidget *widget, gpointer data )
{
	/* 用gtk_clist_clear函数清除列表。比用
	 * gtk_clist_remove函数逐行清除要快
	 */
	gtk_clist_clear( (GtkCList *)data );
}

// 用户选中某一行时的回调函数
void selection_made( GtkWidget *clist, gint row, gint column,
					GdkEventButton *event, gpointer data )
{
	gtk_widget_queue_draw(clist);	// 人为更新列表，开发板有效
	
	gchar *text;
	
	/* 取得存储在被选中的行和列的单元格上的文本
	 * 当鼠标点击时，我们用text参数接收一个指针
	 */
	gtk_clist_get_text(GTK_CLIST(clist), row, column, &text);
	//打印一些关于选中了哪一行的信息
	g_print("第%d行，第%d列的内容为%s\n", row, column, text);
}

int main( int argc, gchar *argv[] )
{                                  
	gtk_init(&argc, &argv);					// 初始化
	
	// 主窗口
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	// 创建窗口
	gtk_widget_set_size_request(GTK_WIDGET(window), 300, 300);	// 设置最小大小
	gtk_window_set_title(GTK_WINDOW(window), "GtkCList Example");	// 设置标题
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE); 			// 固定窗口大小
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit),  NULL);
	
	// 表格布局容器
	GtkWidget *table = gtk_table_new(5, 2, TRUE);
	gtk_container_add(GTK_CONTAINER(window), table);

	/* 创建一个滚动窗口构件，将GtkCList组装到里面。
	 * 这样使得内容超出列表时，可以用滚动条浏览
	 * 第一个参数是水平方向的调整对象，第二个参数是垂直方向的调整对象。它们总是设置为NULL。
	 */
	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 2, 0, 4);// 把按钮加入布局
	
	// GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
					GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	

	gchar *titles[2] = { "Ingredients", "Amount" };
	// 创建GtkCList构件。本例中，我们使用了两列
	GtkWidget *clist = gtk_clist_new_with_titles(2, titles);
	// 将GtkCList构件添加到滚动窗口构件中
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); 
	
	/* 设置某列内容显示的对齐方式
	 * GTK_JUSTIFY_LEFT：  列中的文本左对齐。
	 * GTK_JUSTIFY_RIGHT： 列中的文本右对齐。
	 * GTK_JUSTIFY_CENTER：列中的文本居中对齐。
	 * GTK_JUSTIFY_FILL：  文本使用列中所有可用的空间
	 */
	gtk_clist_set_column_justification(GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
	 
	/* 很重要的一点，我们设置列宽，让文本能容纳在列中。
	 * 注意，列编号是从0开始的, 本例中是0和1
	 */
	gtk_clist_set_column_width(GTK_CLIST(clist), 0, 100);
	
	// 选择某一行时触发selection_made回调函数
	g_signal_connect(clist, "select-row", G_CALLBACK(selection_made), NULL);
	
	
	// 按钮的创建，并放进布局容器里
	GtkWidget *button_add = gtk_button_new_with_label("Add List");
	GtkWidget *button_clear = gtk_button_new_with_label("Clear List");
	gtk_table_attach_defaults(GTK_TABLE(table), button_add, 0, 1, 4, 5);// 把按钮加入布局
	gtk_table_attach_defaults(GTK_TABLE(table), button_clear, 1, 2, 4, 5);// 把按钮加入布局
	
	// 为按钮的点击设置回调函数
	g_signal_connect(button_add, "clicked", G_CALLBACK(button_add_clicked), (gpointer)clist);
	g_signal_connect(button_clear, "clicked", G_CALLBACK(button_clear_clicked), (gpointer)clist);
				
	/* 界面已经完全设置好了，下面可以显示窗口，
	 * 进入gtk_main主循环
	 */
	gtk_widget_show_all(window);
	
	gtk_main();

	return 0;
}