/* ************************************************************************
 *       Filename:  operation.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月27日 星期一 11時04分01秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "fun.h"

char *cmp[] = { "add", "sub", "mul", "div"};
int (*fp[])(int a,int b) = { add, sub, mul, div};

void main()
{
	int i = 0;
	int a = 0,b = 0, res = 0;
	char buf[10] = {0};

	printf("请输入计算指令，例如：\n");
	printf("add 15 25 //计算15+25的值，并返回结果\n");
	printf("sub 15 25 //计算15-25的值，并返回结果\n");
	printf("mul 15 25 //计算15*25的值，并返回结果\n");
	printf("div 15 25 //计算15/25的值，并返回结果\n");
	scanf("%s %d %d",buf,&a,&b);
	
	while(1)
	{
		for(i=0;i<sizeof(fp)/sizeof(fp[0]);i++)
		{
			if(strcmp(buf,cmp[i])==0)
			{
				res = fp[i](a,b);
				printf("计算结果为：%d\n",res);
			}
		}
	}
}


