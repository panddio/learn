/* ************************************************************************
 *       Filename:  sigpromask.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 17时22分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>



int main(int argc, char *argv[])
{
	sigset_t set;
	int i = 0;

	sigemptyset(&set);
	sigaddset(&set,SIGINT);

	while(1)
	{
		sigprocmask(SIG_BLOCK, &set, NULL);

		for(i=0;i<5;i++)
		{
			printf("SIGINT signal is blocked\n");
			sleep(1);
		}

		sigprocmask(SIG_UNBLOCK, &set, NULL);

		for(i=0;i<5;i++)
		{
			printf("SIGINT signal unblocked\n");
			sleep(1);
		}
	}
	return 0;
}


