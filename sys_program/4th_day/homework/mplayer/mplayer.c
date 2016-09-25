/* ************************************************************************
 *       Filename:  mplayer.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月18日 12时25分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include "interface.h"

void *fun(void *arg)
{
	int i = (int)arg;

	printf("pid = %d\n",i);

	sleep(6);
	kill((int)arg,2);
}

int main(int argc, char* argv[])
{
	WINDOW window;	
	pid_t pid;
	pthread_t pth;
	
	mkfifo("cmd_fifo",0777);
	fd = open("cmd_fifo",O_RDWR);	
		
	pid = fork();
	
	if(pid < 0)
	{
		perror("");
		exit(-1);
	}
	else if(pid == 0) //
	{
		printf("start mplayer now!\n");	
		//write(fd, "pause\n", strlen("pause\n")); //
		//启动mplayer
		execlp("mplayer",
		       "mplayer",
			   "-slave", "-quiet","-idle",
			   "-input", "file=./cmd_fifo",
			   "./media/sad_or_happy.mp3", NULL);
	}
	else
	{	
		//pthread_create(&pth,NULL,fun,(void *)pid); //创建一个新进程
		
		write(fd, "pause\n", strlen("pause\n")); //
		gtk_init(&argc, &argv);		
		show_window(&window);	
		gtk_main();				
	}
	
	return 0;
}
