/* ************************************************************************
 *       Filename:  fifo.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月17日 14时26分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int ret, fd;
	char buf[100] = "hello world";

	ret = mkfifo("./myfifo",0777);

	if(ret < 0)  perror("");

	printf("creat myfifo\n");
	fd = open ("./myfifo",O_WRONLY | O_NONBLOCK);
	printf("open success!  fd = %d\n",fd);

	while(1)
	{
		write(fd,buf,strlen(buf));
		printf("write\n");
		sleep(1);
	}
	return 0;
}
