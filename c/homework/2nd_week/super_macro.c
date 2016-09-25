/* ************************************************************************
 *       Filename:  super_macro.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月22日 星期三 06時51分27秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>

#define SUPER(x,op,y)  (op=='+'?(x)+(y):op=='-'?(x)-(y):op=='*'?(x)*(y):op=='/'?(x)/(y):op=='%'?(x)%(y):0)
int main(int argc, char *argv[])
{
	int m=25,k=4;

	printf("m=%d,k=%d\n",m,k);
	printf("m+k=%d\n",SUPER(m,'+',k));
	printf("m-k=%d\n",SUPER(m,'-',k));
	printf("m*k=%d\n",SUPER(m,'*',k));
	printf("m/k=%d\n",SUPER(m,'/',k));
	printf("m%k=%d\n",SUPER(m,'%',k));
	return 0;
}


