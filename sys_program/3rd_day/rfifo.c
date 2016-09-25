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
	char buf[100] = "";

	ret = mkfifo("./myfifo",0777);

	if(ret < 0)  perror("");

	printf("creat myfifo\n");
	fd = open ("./myfifo",O_RDONLY | O_NONBLOCK);
	printf("open success!  fd = %d\n",fd);

	while(1)
	{
		memset(buf,0,sizeof(buf));
		read(fd,buf,sizeof(buf));
		printf("read success! buf = %s\n",buf);
		sleep(1);
	}
	return 0;
}


