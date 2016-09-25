/* ************************************************************************
 *       Filename:  systemcall.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月13日 10时16分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#if 1
int main(int argc, char *argv[])
{
	int fd, ft, ret;
	char *pbuf = NULL, ch;
	unsigned long filelen = 0;

	fd = open(argv[1],O_RDWR);

	if(fd < 0) 
	{
		perror("error:\n");
		return -1;
	}

	while(read(fd,&ch,sizeof(ch)) == 1) filelen++;
	
	pbuf = (char *)malloc(filelen);
	if(pbuf == NULL) 
	{
		printf("Err:failed to malloc!\n");
		return -1;
	}

	close(fd);
	fd = open(argv[1],O_RDWR);
	ret = read(fd,pbuf,filelen);
	
	ft = open(argv[2],O_RDWR | O_CREAT,0777);
	write(ft,pbuf,filelen);

	printf("filelen = %lu\n",filelen);
	printf("ret     = %d\n",ret);

	close(fd);
	close(ft);
	free(pbuf);
	return 0;
}
#endif