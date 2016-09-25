/* ************************************************************************
 *       Filename:  sum.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月16日 星期四 02時11分45秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <string.h>
int sum(int a,int b)
{
	return a+b;
}

int abs(int n)
{
	return n>0?n:~n;
}

void Bubbing_Methed(char *p)
{
	int length = 0;
	length = strlen(p);
	printf("%d\n",length);

}
