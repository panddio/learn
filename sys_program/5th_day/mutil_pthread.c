#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int fd[2];
	pid_t pid;
	pid_t pid_sec;
	char buf[7];
	pipe(fd);
	if((pid = fork())<0)
	{
		printf("fork error!");
		exit(1);
	}
	else if(pid == 0)
	{
		close(fd[0]);
		write(fd[1],"first1",7);
		close(fd[1]);
		exit(0);
	}
	else
	{
		wait(NULL);
		if((pid_sec = fork())<0)
		{
			printf("fork second error!");
			exit(1);
		}
		else if(pid_sec==0)
		{
			close(fd[0]);
			write(fd[1],"Child1",7);
			close(fd[1]);
			exit(0);
		}
		else
		{
			wait(0);
			close(fd[1]);
			read(fd[0],buf,7);
			printf("%s\n",buf);
			wait(0);
			close(fd[1]);
			read(fd[0],buf,7);
			close(fd[0]);
			printf("%s\n",buf);
			exit(0);
		}
	}
	return 0;
}
