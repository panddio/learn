/* ************************************************************************
 *       Filename:  login.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月10日 14时27分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <gtk/gtk.h>

#define PSW  "123456"

char psw[50] = "";

/* 功能：  设置背景图
 * widget: 主窗口
 * w, h:   图片的大小
 * path：  图片路径
 */
static void chang_background(GtkWidget *widget, int w, int h, const gchar *path)
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

void entry_callback(GtkWidget *widget, gpointer entry)
{
	const gchar *entry_text;

	entry_text = (gchar *)gtk_entry_get_text(GTK_ENTRY(entry));
	printf("Entry contents: %s\n",entry_text);
	
	if(strcmp(entry_text, PSW) == 0)
	{
		printf("Entry password right!\n");
	}
	else
	{
		char empty[] = "";
		gtk_entry_set_text(GTK_ENTRY(entry), empty);//设置显示内容
		
		printf("Entry password wrong!\n");
	}
}
void num_callback(GtkButton *button, gpointer entry)
{
	const char *button_label = gtk_button_get_label(button);
	
	gtk_entry_append_text(GTK_ENTRY(entry), button_label);
	
	//strcat(psw,button_label);
	//gtk_entry_set_text(GTK_ENTRY(entry), psw);//设置显示内容
}

void button_callback(GtkButton *button, gpointer entry)
{
	const char *button_label = gtk_button_get_label(button);
	
	gint len = GTK_ENTRY(entry)->text_length;
	
	if(strcmp(button_label,"<-") == 0)
	{
		gtk_editable_delete_text(GTK_EDITABLE(entry), len-1,len);
	}
	else if(strcmp(button_label,"sure") == 0)
	{
		const char *databuf = gtk_entry_get_text(GTK_ENTRY(entry));
		
		if(strcmp(databuf,PSW) == 0)
		{
			printf("Entry password right!\n");
		}
		else
		{
			char empty[] = "";
			gtk_entry_set_text(GTK_ENTRY(entry), empty);//设置显示内容
			
			printf("Entry password wrong!\n");
		}
	}
}
int main(int argc, char *argv[])
{
	int i, j, num = 0;


	
	gtk_init(&argc,&argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"GTK entry");

	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);//设置窗口的位置
	gtk_widget_set_size_request(window, 500, 300);	               //设置窗口的大小	
	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);            //设置窗口是否可以改变大小

	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);	
	
	GtkWidget *table = gtk_table_new(4,6,TRUE); //创建一个三行六列的表格容器

	GtkWidget *entry = gtk_entry_new();                    //创建行编辑	
	gtk_entry_set_max_length(GTK_ENTRY(entry), 100);       //设置行编辑显示最大字符的长度
	//gtk_entry_set_text(GTK_ENTRY(entry), "hello world"); //设置显示内容
	gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);     //密码模式
	
	//创建一个标签
	GtkWidget *label = gtk_label_new("password: ");
	gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,0,1);
	gtk_table_attach_defaults(GTK_TABLE(table),entry,1,6,0,1); //
	for(i=2;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			char pnum[3] = "";
			sprintf(pnum,"%d",num);
			GtkWidget *button = gtk_button_new_with_label(pnum);
			num++;
			gtk_widget_set_size_request(button, 60, 35); 
			gtk_table_attach_defaults(GTK_TABLE(table),button,j,j+1,i,i+1);			 
			g_signal_connect(button, "pressed", G_CALLBACK(num_callback), entry); 
		}
	}
#if 0		
	GtkWidget *button0 = gtk_button_new_with_label("0");
	GtkWidget *button1 = gtk_button_new_with_label("1");		
	GtkWidget *button2 = gtk_button_new_with_label("2");
	GtkWidget *button3 = gtk_button_new_with_label("3");
	GtkWidget *button4 = gtk_button_new_with_label("4");
	GtkWidget *button5 = gtk_button_new_with_label("5");
	GtkWidget *button6 = gtk_button_new_with_label("6");
	GtkWidget *button7 = gtk_button_new_with_label("7");
	GtkWidget *button8 = gtk_button_new_with_label("8");
	GtkWidget *button9 = gtk_button_new_with_label("9");
	
	GtkWidget *sure   = gtk_button_new_with_label("sure");
	GtkWidget *delete = gtk_button_new_with_label("<-");
	
	gtk_table_attach_defaults(GTK_TABLE(table),button0,0,1,2,3);
	gtk_table_attach_defaults(GTK_TABLE(table),button1,1,2,2,3);
	gtk_table_attach_defaults(GTK_TABLE(table),button2,2,3,2,3);
	gtk_table_attach_defaults(GTK_TABLE(table),button3,3,4,2,3);
	gtk_table_attach_defaults(GTK_TABLE(table),button4,4,5,2,3);
	gtk_table_attach_defaults(GTK_TABLE(table),delete, 5,6,2,3);
	
	gtk_table_attach_defaults(GTK_TABLE(table),button5,0,1,3,4);
	gtk_table_attach_defaults(GTK_TABLE(table),button6,1,2,3,4);
	gtk_table_attach_defaults(GTK_TABLE(table),button7,2,3,3,4);
	gtk_table_attach_defaults(GTK_TABLE(table),button8,3,4,3,4);
	gtk_table_attach_defaults(GTK_TABLE(table),button9,4,5,3,4);
	gtk_table_attach_defaults(GTK_TABLE(table),sure,5,6,3,4);


	//6.设置button的大小   	
	gtk_widget_set_size_request(button0,60, 35);  
	gtk_widget_set_size_request(button1,60, 35); 
	gtk_widget_set_size_request(button2,60, 35); 
	gtk_widget_set_size_request(button3,60, 35); 
	gtk_widget_set_size_request(button4,60, 35); 
	gtk_widget_set_size_request(button5,60, 35); 
	gtk_widget_set_size_request(button6,60, 35); 
	gtk_widget_set_size_request(button7,60, 35); 
	gtk_widget_set_size_request(button8,60, 35); 
	gtk_widget_set_size_request(button9,60, 35); 
	gtk_widget_set_size_request(sure,60, 30); 
	gtk_widget_set_size_request(delete,60, 30);  

	//7.注册信号函数，把entry传给回调函数deal_num()   
    g_signal_connect(button0, "pressed", G_CALLBACK(num_callback), entry);  
    g_signal_connect(button1, "pressed", G_CALLBACK(num_callback), entry);  
    g_signal_connect(button2, "pressed", G_CALLBACK(num_callback), entry);
    g_signal_connect(button3, "pressed", G_CALLBACK(num_callback), entry);  
    g_signal_connect(button4, "pressed", G_CALLBACK(num_callback), entry);  
    g_signal_connect(button5, "pressed", G_CALLBACK(num_callback), entry);  
    g_signal_connect(button6, "pressed", G_CALLBACK(num_callback), entry);  
    g_signal_connect(button7, "pressed", G_CALLBACK(num_callback), entry);  
    g_signal_connect(button8, "pressed", G_CALLBACK(num_callback), entry);  
    g_signal_connect(button9, "pressed", G_CALLBACK(num_callback), entry);
#endif 	
	GtkWidget *sure   = gtk_button_new_with_label("sure");
	GtkWidget *delete = gtk_button_new_with_label("<-");
	
	gtk_widget_set_size_request(sure,60, 30); 
	gtk_widget_set_size_request(delete,60, 30);  
	
	gtk_table_attach_defaults(GTK_TABLE(table),delete, 5,6,2,3);
	gtk_table_attach_defaults(GTK_TABLE(table),sure, 5,6,3,4);
	
    g_signal_connect(delete, "pressed", G_CALLBACK(button_callback), entry);  
    g_signal_connect(sure, "pressed", G_CALLBACK(button_callback), entry);
	g_signal_connect(entry, "activate",G_CALLBACK(entry_callback), entry);

	GtkWidget *fixed= gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(fixed),table,50,100);
	gtk_container_add(GTK_CONTAINER(window),fixed);
	
	chang_background(window, 500, 300, "image.jpg");	// 设置窗口背景图
	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}


