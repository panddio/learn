/* ************************************************************************
 *       Filename:  sighandler.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 15时48分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

typedef void (* sighandler_t)(int);

void fun1(int signum)
{
	printf("fun1 signal = %d\n",signum);
}

void fun2(int signum)
{
	printf("fun2 signal = %d\n",signum);
}
int main(int argc, char *argv[])
{
	sighandler_t p = NULL;

	p = signal(2,fun1);

	if(p == NULL)
		printf("fun1\n");

	p = signal(2,fun2);

	if(p == fun1)
		printf("fun2\n");

	pause();
	return 0;
}


