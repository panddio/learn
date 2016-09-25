/* ************************************************************************
 *       Filename:  gpio_buttons.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月21日 14时16分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "s5pv210-gpio.h"

static open_dev(const char *devname)
{
	int fd;

	fd = open(devname,O_RDWR);

	if(fd < 0)
	{
		perror("open_dev");
		_exit(-1);
	}
	return fd;
}
int main(int argc,char *argv[])
{
	int fd_row = 0;
	int fd_col = 0;
	int key_ret = 0, key_tmp = 0;
	fd_row = open_dev("/dev/gpH3");
	ioctl(fd_row,GPIO_SET_PIN_OUT,0x0);
	ioctl(fd_row,GPIO_CLR_PIN,0x0);

	fd_col = open_dev("/dev/gpH2");
	ioctl(fd_col,GPIO_SET_PIN_IN,0x3);
	ioctl(fd_col,GPIO_SET_PIN_IN,0x4);
	ioctl(fd_col,GPIO_SET_PIN_IN,0x5);
	ioctl(fd_col,GPIO_SET_PIN_IN,0x6);
	ioctl(fd_col,GPIO_SET_PIN_IN,0x7);

	ioctl(fd_col,GPIO_SET_PULL_UP,0x3);
	ioctl(fd_col,GPIO_SET_PULL_UP,0x4);
	ioctl(fd_col,GPIO_SET_PULL_UP,0x5);
	ioctl(fd_col,GPIO_SET_PULL_UP,0x6);
	ioctl(fd_col,GPIO_SET_PULL_UP,0x7);

	while(1)
	{
		read(fd_col, &key_tmp, sizeof(key_tmp));
		key_tmp &= 0xf8;

		if(key_tmp != 0xf8)
		{
			switch(key_tmp)
			{
				case 0xf0:
					key_ret = 2;
					printf("key2 pressed\n");
					break;
				case 0xe8:
					key_ret = 3;
					printf("key3 pressed\n");
					break;
				case 0xd8:
					key_ret = 4;
					printf("key4 pressed\n");
					break;
				case 0xb8:
					key_ret = 5;
					printf("key5 pressed\n");
					break;
				case 0x78:
					key_ret = 6;
					printf("key6 pressed\n");
					break;
			}

			do
			{
				read(fd_col, &key_tmp, sizeof(key_tmp));
				key_tmp &= 0xf8;
			}while(key_tmp != 0xf8);
		}
		else
		{
			printf("Err: key_ret = %d\n",key_tmp);
		}
	}

	return 0;
}
