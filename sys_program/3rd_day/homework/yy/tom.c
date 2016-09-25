/* ************************************************************************
 *       Filename:  jerry.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月17日 16时57分02秒
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
	int ret,fr,fw;
	char tom[] = "Tom: ";
	pid_t pid;
	
	//remove(".rfifo");
	//remove(".wfifo");
	mkfifo(".rfifo",0777);
	mkfifo(".wfifo",0777);
	
	printf("Hello, I am %s\n",tom);	

	fr = open(".rfifo",O_RDONLY);
	if(fr < 0) perror("");
	fw = open(".wfifo",O_WRONLY);

	pid = fork();

	if(pid < 0) perror("");

	else if(pid == 0) //子进程
	{
		int len = 0;
		char buf[128] = "";
		while(1)
		{				
			printf("%s",tom);
			fflush(stdout);

			fgets(buf,sizeof(buf),stdin);
			len = strlen(buf);

			if(len > 1)
			{
				char msg[128] = "";
				
				strcat(msg,tom);
				strcat(msg,buf);
				write(fw, msg, strlen(tom)+len - 1);
			}
		}
	}
	else
	{
		char msg[128] = "";

		while(1)
		{
			memset(msg,0,sizeof(msg));
			read(fr, msg, sizeof(msg)); //FIFO里没数据read会阻塞，如果通信写进程先退出，read将不阻塞，read返回值为0
			
			if(msg[0] == 0)
			{
				kill(pid,1);
				exit(0);
			}
			
			printf("\r%s\n",msg);
			printf("%s",tom);
			fflush(stdout);
		}
	
	}

	return 0;
}



