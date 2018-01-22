/* ************************************************************************
 *       Filename:  test_timer.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月08日 10时43分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

void main()
{
	int fd = 0;
	int counter = 0;
	int old_counter = 0;

	fd = open("/dev/timer_drv",O_RDONLY);

	if(fd != -1)
	{
		while(1)
		{
			read(fd,&counter,sizeof(unsigned int));
			if(counter != old_counter)
			{
				old_counter = counter;
				printf("seconds open /dev/timer_dev: %d\n",counter);
			}
		}
	}
	else
	{
		printf("Device open failure!\n");
	}
}


