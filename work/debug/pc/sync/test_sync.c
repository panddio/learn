/* ************************************************************************
 *       Filename:  test_sync.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年11月11日 10时58分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>  
#include <stdlib.h>	
#include <string.h> 
#include <fcntl.h>  
#include <unistd.h>	
#include <sys/stat.h>  
#include <signal.h>	


int flag = 0;

void sync_handler(int signo)
{
	if(signo == SIGIO){
		printf("receive successful!!!\n");
		flag++;
	}
}

#if 0
int main(int argc, char *argv[])
{
	int fd, oflags;

	fd = open("/dev/sync", O_RDWR, 766);

	if(fd < 0){
		printf("cannot' open /dev/sync\n");
		return -1;
	}

	signal(SIGIO, sync_handler);
	fcntl(fd, F_SETOWN, getpid());
	oflags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, oflags | FASYNC);

	while(1){
		if(flag > 5)
			break;
		usleep(600*1000);
	}

	close(fd);
	return 0;
}
#else
   
int main()   
{   
     struct sigaction action;  
     int async_fd; 
  
     memset(&action, 0, sizeof(action));   
     //信号处理函数
     action.sa_handler = sync_handler;   
     action.sa_flags = 0;       
     //注册信号类型
     sigaction(SIGIO, &action, NULL);   

     async_fd = open("/dev/sync", O_RDONLY);   
     if(async_fd < 0)
     {
          printf("can not open /dev/sync \n");
          return -1;
     }

     //告诉驱动当前进程的PID
     fcntl(async_fd, F_SETOWN, getpid());   
     //设置驱动的FASYNC属性，支持异步通知
     fcntl(async_fd, F_SETFL, fcntl(async_fd, F_GETFL) | FASYNC);   
  
     printf("waiting for receive...\n");

     while(1){
		 if(flag > 5) break;
		 usleep(600*1000); 
	 }
            
     close(async_fd);  
 
     return 0;   
}
#endif