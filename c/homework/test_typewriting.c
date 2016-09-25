/* ************************************************************************
 *       Filename:  test_typewriting.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月22日 星期三 11時59分14秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

//#include <windows.h>

#define uint unsigned int
#define LENGHT  40

char mygetch()
{
    struct termios oldt, newt;
    char ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

void show_rule()
{

	printf("\n---------------------\n");
	printf(" 1.按任键开始测试\n");
	printf(" 3.输入屏幕显示字符\n");
	printf(" 4.输入首字母后计时\n");
	printf(" 2.输入过程按Esc退出\n");
	printf(" 5.输入出错以 _ 表示\n");
	printf("----------------------\n");
}
void get_string(char *buf, int n)
{
	char i,ch;

	i = 0;
	srand((uint)time(NULL));
	do
	{
		ch = (char)rand()%128;

		if((ch >= 'a' && ch <= 'z')
	     ||(ch >= 'A' && ch <= 'Z'))
		{
			buf[i] = ch;
			i++;
		}
	}while(i<n);
}

int main()
{
	char i,ch;
	char src[LENGHT],buf[LENGHT];
	int start_time,end_time;
	int count = 0;

	//show_rule();
	//mygetch();
	system("clear");

	while(1)
	{
		show_rule();
		mygetch();

		get_string(src,LENGHT);
		//printf("%s\n",src);
		for(i=0;i<LENGHT;i++)
		{
			printf("%c",src[i]);
		}
		putchar('\n');

		for(i=0;i<LENGHT;i++)
		{
			ch = mygetch();
			if(i == 0)
			{
				start_time = time(NULL);
			}

			if(ch == src[i])
			{
				putchar(ch);
				count++;
			}
			else
			{
				if(ch == 27)
				{
					putchar('\n');
					exit(0);
				}
				putchar('_');
			}
		}
		end_time = time(NULL);
		printf("\n输出完成！\n用时 %ds\n",end_time-start_time);
		printf("正确率%.2f%\n",count/(LENGHT+0.0)*100);
		printf("按Esc键退出，按空格键继续\n");

		getch:
		ch = mygetch();

		switch(ch)
		{
			case ' ': system("clear"); break;
			case  27: exit(0);
			default: goto getch;
		}

	}

	return 0;
}

