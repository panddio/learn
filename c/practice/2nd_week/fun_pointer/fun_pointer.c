/* ************************************************************************
 *       Filename:  fun_pointer.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月24日 星期五 12時14分36秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
//#include <stdlib.h>
#include "fun.h"

char cmd[] = {'+','-','*','/'};
int (*fp[])(int a, int b) = {add, sub, mul, div};

void main()
{
	int a=0,b=0,res=0;
	char i,ch;

	while(1)
	{
		scanf("%d%c%d",&a,&ch,&b);

		for(i=0;i<sizeof(cmd)/sizeof(cmd[0]);i++)
		{
			if(ch==cmd[i])
			{
				res = fp[i](a,b);
				printf("%d%c%d=%d\n",a,ch,b,res);
			}
		}
	}
}


