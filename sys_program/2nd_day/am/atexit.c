/* ************************************************************************
 *       Filename:  atexit.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 09时59分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void fun1(void)
{
	printf("in fun1 atexit\n");
}

void fun2(void)
{
	printf("in fun2 atexit\n");
}
void fun3(void)
{
	printf("in fun3 atexit\n");
}

int main(int argc, int *argvp[])
{
	atexit(fun1);
	atexit(fun2);
	atexit(fun3);

	sleep(3);
	return 0;
}


