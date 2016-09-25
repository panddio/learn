/* ************************************************************************
 *       Filename:  guess_number.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月20日 星期一 07時04分30秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  王秋伟
 *        Company:  
 * ************************************************************************/
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define uint unsigned int

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

void get_charnumber(int number,int n,char *buf)
{
	char i;
	int temp = 0;
	int divisor;

	temp = number%(int)pow(10,n);

	if(temp < 1000)
	{
		buf[n-1] = 0+48;
		for(i=n-2;i>=0;i--)
		{
			divisor =(int)pow(10,i);
			buf[i] = temp/divisor+48;
			temp %=divisor;
		}
	}
	else
	{
		for(i=n-1;i>=0;i--)
		{
			divisor =(int)pow(10,i);
			buf[i] = temp/divisor+48;
			temp %=divisor;
		}
	}
}

void start_game(char *src,int n)
{
	char *buf;
	char ch,i;
	int count=0;
	int right=0;

	printf(">>>请选择难度级别:\n");
    printf("1--简单，10次机会\n");
	printf("2--中度， 7次机会\n");
	printf("3--困难， 5次机会\n");

	do
	{
		ch = mygetch();
	}while(ch != '1' && ch != '2' && ch != '3');

	switch(ch)
	{
		case '1': count = 10; break;
		case '2': count =  7; break;
		case '3': count =  5; break;
	}

	buf = (char *)malloc(sizeof(char)*n);
	printf("请输入一个四位数字：");
	scanf("%s",buf);
	printf("%s\n",buf);
	//printf("%s\n",src);
	do
	{
		right = 0;

		for(i=0;i<n;i++)
		{
			if(buf[i] == src[i])
			{
				printf("第%d位数字正确\n",i+1);
				right++;
			}
			else if(buf[i] < src[i])
			{
				printf("第%d位数字小于正确数字\n",i+1);
			}
			else
			{
				printf("第%d位数字大于正确数字\n",i+1);
			}
		}

		if(right == n)
		{
			printf("你输入的数字全部正确，游戏成功\n");
			goto leave;
		}

		count--;
		if(count>0)
		{
			printf("你还有%d次机会，请再输入一个四位数:",count);
			scanf("%s",buf);
		}
		else
		{
			printf("在规定次数没能猜中数字，游戏失败\n");
		}
	}while(count>0);

leave:
	getchar();
	free(buf);
}

void show_rule()
{
	printf("---------------------------\n");
	printf("         猜字游戏规则      \n");
	printf("1、系统会产生一个四位随机数\n");
	printf("2、选择合适难度级别进行游戏\n");
	printf("3、输入你认为正确的四位数字\n");
	printf("4、系统根据输入数据给你提示\n");
	printf("5、规定的次数内猜对游戏成功\n");
	printf("---------------------------\n");
}

int main()
{
	int num,oldnum;
	char ch = 0;
	char *buf = NULL;


	buf = (char *)malloc(sizeof(char)*4);
//	get_charnumber(num,4,buf);
//	printf("%s\n",buf);

	while(1)
	{
		do
		{
		//	sleep(1);
			oldnum = num;
			srand((uint)time(NULL));
			num = rand();
		}while(num < 1000);

		get_charnumber(num,4,buf);

		printf(">>>>>欢迎进行猜字游戏<<<<<\n");
		printf("-----按1  进入游戏\n");
		printf("-----按2  查看规则\n");
		printf("-----按0  退出游戏\n");

		ch = mygetch();

		switch(ch)
		{
			case '1':
					{
						start_game(buf,4);
						break;
					}
			case '2':
					{
						show_rule();
						break;
					}
			case '0': goto exit;

		}
	}

exit:
	free(buf);
	return 0;
}
