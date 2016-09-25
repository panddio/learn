/* ************************************************************************
 *       Filename:  myatoi.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月27日 星期一 02時24分00秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>

int myatoi(char *src)
{
	int i = 0;
	int len = 0, res = 0;
	len = strlen(src);

	for(i=0;i<len;i++)
	{
		res += pow(10,len-i-1) * (src[i]-48);
	}

	return res;
}

void main()
{
	char c[]="12345";
	
	printf("%d\n",myatoi(c));
}
