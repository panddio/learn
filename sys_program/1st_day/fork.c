/* ************************************************************************
 *       Filename:  fork.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月13日 15时34分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int gnum = 0;

int main(int argc, char *argv[])
{
	int num = 0;
	pid_t pid;

	pid = fork();

	if(pid < 0)  perror("error");

	else if(pid == 0)
	{
		while(1)
		{
			printf("gnum = %d   num = %d\n",gnum,num);
			printf("in son process\n");
			sleep(1);
		}
	}
	else
	{
		while(1)
		{
			gnum++;
			num++;

			printf("in father process\n");
			sleep(1);
		}
	}
	return 0;
}
