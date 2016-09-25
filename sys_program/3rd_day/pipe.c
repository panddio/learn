/* ************************************************************************
 *       Filename:  pipe.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月17日 10时18分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int fd[2];
	char buf[100] = "Hello world";
	pid_t pid;

	if(pipe(fd) < 0)
	{
		perror("");
	}
	printf("fd[0] = %d  fd[1] = %d\n",fd[0],fd[1]);

	pid = fork();

	if(pid <0 )
	{
		perror("");
	}
	else if(pid == 0)
	{
		write(fd[1],buf,strlen(buf));
		exit(1);
	}
	else
	{
		wait(NULL);

		memset(buf,0,sizeof(buf));
		read(fd[0],buf,sizeof(buf));

		printf("buf = %s\n",buf);
	}
	return 0;
}
