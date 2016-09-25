/* ************************************************************************
 *       Filename:  pause.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 15时38分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>


int main(int argc, char *argv[])
{
	sleep(3);
	printf("pause\n");
	pause();
	return 0;
}


