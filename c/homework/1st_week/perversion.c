/* ************************************************************************
 *       Filename:  perversion.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月17日 星期五 06時34分20秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  王秋伟
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
#include <malloc.h>
#include <math.h>

#if 0
int main(int argc, char *argv[])
{
	int count = 0;
	int number = 0;
	int *buf = NULL;
	char i;

	printf("Please input a integer number:\n");
	scanf("%d",&number);

	count = printf("%d\n",number) - 1;
	//printf("count = %d\n",count);
	buf = (int *)malloc((sizeof(int) * count));

	perversion(number, buf, count);

	for(i=0;i<count;i++)
	{
		printf("%d",buf[i]);
	}
	putchar('\n');
	return 0;
}

void perversion(int number, int *buf, int count)
{
	int i;
	int divisor;

	for(i=count-1;i>=0;i--)
	{
		divisor = (int)pow(10,i);
		buf[i]  = number/divisor;
		number %= divisor;
	}
}
#else

void perversion(int number, char *buf, int count)
{
	int i;
	int divisor;

	for(i=count-1;i>=0;i--)
	{
		divisor = (int)pow(10,i);
		buf[i]  = number/divisor;
		number %= divisor;
	}
}

int main(int argc, char *argv[])
{
	int count = 0;
	int number = 0;
    char *buf = NULL;
	char i;

	printf("Please input a integer number:\n");
	scanf("%d",&number);

	#if 0 //三种方法计算 count 的值
 	count = printf("%d\n",number) - 1;
	#elif 1
	while((number/pow(10,count))>=1)
	{
		count++;
	}
	#else
	count =(int)log10(number) + 1;
	#endif

	//printf("count = %d\n",count);
	buf = (char *)malloc((sizeof(char) * count));

	if(count>1)
	{
		perversion(number, buf, count);
		for(i=0;i<count;i++)
		{
			printf("%d",buf[i]);
		}
		putchar('\n');
	}
	else
	{
		printf("%d\n",number);
	}

	free(buf);
	return 0;
}
#endif
