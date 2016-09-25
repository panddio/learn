/* ************************************************************************
 *       Filename:  test_typewriting.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月22日 星期三 11時59分14秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  王秋伟 
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
void get_string(char *buf, int n, int mode)
{
	char i,ch;
	
	i = 0;
	srand((uint)time(NULL));
	do
	{
		ch = (char)rand()%128;

		if((mode & 0x01 && ch >= 'a' && ch <= 'z')
	     ||(mode & 0x02 && ch >= 'A' && ch <= 'Z'))
		{
			buf[i] = ch;
			printf("%c",ch);
			i++;
		}
	
	}while(i<n);
	putchar('\n');
}
void typewriting(char *src,int num)
{
	char i,ch;
	int count = 0;
	int start_time,end_time;

	putchar('\n');

	for(i=0;i<num;i++)
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
			if(ch == 27)//判断是不是按下Esc键 
			{
				putchar('\n');
				exit(0);
			}
			putchar('_');
		}
	}
	end_time = time(NULL);
	printf("\n输出完成！\n用时 %ds\n",end_time-start_time);
	printf("正确率%.2f%\n",count/(num+0.0)*100);
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
int main()
{
	char src[LENGHT];
	int mode;
	//show_rule();
	//mygetch();
	system("clear");

	while(1)
	{
		show_rule();
		mygetch();
	   
		printf(">>>>请选择打字测试模式，输入：1 | 2 | 3\n");
		printf("1---全小写字符串\n");
		printf("2---全大写字符串\n");
		printf("3---大小写字符串\n");
		//scanf("%d",&mode);
		do
		{
			mode  = mygetch();
		}while(mode != '1' && mode != '2' && mode !='3');

		get_string(src,LENGHT,mode-48);

		typewriting(src,LENGHT);

	}

	return 0;
}

