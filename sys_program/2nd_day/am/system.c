/* ************************************************************************
 *       Filename:  system.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 19时09分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	pid_t pid;
	char cmd[128] = "";

	while(1)
	{
		//printf("Please input a cmd: ");
		//fgets(cmd,sizeof(cmd),stdin);
		//printf("%d\n",strlen(cmd));
		//cmd[strlen(cmd)-1] = '\0'; //把获取的字符后面的\n转化成 '\0'

		pid =  fork(); //创建子进程

		if(pid == 0) //子进程
		{
			int len = 0;
			printf("Please input a cmd: ");
			fgets(cmd,sizeof(cmd),stdin);

			len = strlen(cmd);
			//printf("%d\n",len);
			if(len > 1)
			{
				cmd[len-1] = '\0'; //把获取的字符后面的\n转化成 '\0'
			}
			else
			{
				exit(0);
			}

			//printf("in son process\n");
			execl("/bin/sh","sh","-c",cmd,NULL);
			exit(1);
		}
		wait(NULL);
	}

	return 0;
}
