/* ************************************************************************
 *       Filename:  mytest.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月22日 星期三 10時28分13秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include "mylib.h"


int main(int argc, char *argv[])
{
	int a = 10, b = 20;
	int max_num,min_num;

	max_num = max(a,b);
	min_num = min(a,b);
	printf("max=%d\n",max_num);
	printf("min=%d\n",min_num);
	return 0;
}


