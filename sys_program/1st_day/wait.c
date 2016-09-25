/* ************************************************************************
 *       Filename:  wait.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月13日 17时03分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();

	if(pid < 0) perror("error\n");

	else if (pid == 0)
	{
		int i = 0;

		for(i = 0;i<5;i++)
		{
			printf("in son process");

			sleep(1);
		}

		exit(2); //退出时会刷新缓冲区
		//_exit(2);//退出时 不会 刷新缓冲区
		//return 2; //这里return 2 跟 exit(2) 效果一样
	}
	else
	{
		int status = 0;
		int i;

		//wait(&status);
		waitpid(-1,&status,0);

		if(WIFEXITED(status) != 0) //判断返回状态 ，存在status的低8位
		{
			printf("return = %d\n",WEXITSTATUS(status)); //取返回值，存在status的8~16位
		}
		for(i=0;i<5;i++)
		{
			printf("in father process\n");
			sleep(1);
		}
	}

	return 0;
}
