/* ************************************************************************
 *       Filename:  signal.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 15时10分06秒
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
	pid_t pid;

	pid = fork();

	if(pid < 0) perror("");
	else if(pid == 0)
	{
		int i;

		for(i=0;i<10;i++)
		{
			printf("in son prpcess\n");
			sleep(1);
		}
	}
	else
	{
		sleep(3);
		kill(pid,2);

		printf("kill pid\n");
	}
	return 0;
}


