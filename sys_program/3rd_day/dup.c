/* ************************************************************************
 *       Filename:  dup.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月17日 11时10分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	int fd;
	int fd2;
	fd = open("a.txt",O_CREAT | O_RDWR,0777);

	close(1);

	fd2 = dup(fd);

	printf("fd2 = %d\n",fd2);
	return 0;
}


