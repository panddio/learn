/* ************************************************************************
 *       Filename:  expr.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月17日 19时28分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int fd[2];
	char cmd[128] = "";
	char buf[64] = "";
	
	if(pipe(fd) < 0)
	{
		perror("");
	}
		
	while(1)
	{	
		pid = vfork();
		
		if(pid < 0) perror("");
		
		else if(pid == 0)
		{
			int len = 0;
			printf("Please input a cmd: ");		
			fgets(cmd,sizeof(cmd),stdin);
			
			len = strlen(cmd);
						
			if(len > 1) 
				cmd[len-1] = '\0'; //把获取的字符后面的\n转化成 '\0'
			else  
				exit(0);
			
			dup2(fd[1], 1); //			
	
			execl("/bin/sh","sh","-c",cmd,NULL);
			//_exit(1);
		}
		else //
		{
			read(fd[0],buf,sizeof(buf));
			printf("%s",buf);
			//wait(NULL);
		}	
	}
	
	return 0;
}



