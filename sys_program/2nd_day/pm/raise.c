/* ************************************************************************
 *       Filename:  raise.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 15时28分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	sleep(3);
	printf("raise\n");
	raise(2);
	return 0;
}


