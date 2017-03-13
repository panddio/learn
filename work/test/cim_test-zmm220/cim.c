#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <asm/mman.h>
#include <sys/mman.h>
#include <string.h>

#include "cim.h"
#include "arca.h"


#define CIM0308DEV  	"/dev/cim0"
#define CIM367DEV      "/dev/cim1"

#define    GC0308   1
#define    MT367    2


/*
 * IOCTL_XXX commands
 */
#define IOCTL_READ_REG      0 /* read sensor registers */
#define IOCTL_WRITE_REG     1 /* write sensor registers */
#define IOCTL_READ_EEPROM   2 /* read  sensor eeprom */
#define IOCTL_WRITE_EEPROM  3 /* write sensor eeprom */
#define IOCTL_SET_IMG_FORMAT	8	//arg type:enum imgformat
#define IOCTL_SET_TIMING_PARAM	9	// arg type: timing_param_t *
#define IOCTL_SET_IMG_PARAM	10	// arg type: img_param_t *
#define IOCTL_CIM_READ_REG	211	


static int cim0308_fd=-1;
static int cim367_fd=-1;


int set_timing_param(int id,TIMING_PARAM *timing)
{
	printf(" %s  %d \n",__func__,__LINE__);
	switch(id)
	{
	case GC0308:	
		if (ioctl(cim0308_fd, IOCTL_SET_TIMING_PARAM, (unsigned long)timing) < 0){
			printf("set_timing_param failed!\n");
			return 0;
		}
		break;
		
	case MT367:		
		if (ioctl(cim367_fd, IOCTL_SET_TIMING_PARAM, (unsigned long)timing) < 0){
			printf("set_timing_param failed!\n");
			return 0;
		}
		break;
	default:
		return 0;
	}
	
	return 1;
	
}

int set_img_format(int fd, img_format_t format)
{
	if (ioctl(fd, IOCTL_SET_IMG_FORMAT, &format) < 0) {
		printf("set_img_format failed!\n");
		return 0;
	}
	return 1;
}

int set_img_param(int fd,IMG_PARAM *img)
{
	printf(" %s  %d \n",__func__,__LINE__);
	if (ioctl(fd, IOCTL_SET_IMG_PARAM, (unsigned long)img) < 0) {
		printf("set_img_param failed!\n");
		return 0;
	}
	return 1;
}

int cim_open(int id,int width, int height, int bpp)
{
	IMG_PARAM param;
	printf(" %s  %d \n",__func__,__LINE__);
	switch(id)
	{
		case GC0308:
		{
			if(cim0308_fd>0) cim_close(GC0308);
			cim0308_fd = open(CIM0308DEV, O_RDWR);
			if(cim0308_fd < 0)
			{
				printf("Error opening %s \n",CIM0308DEV);
				return -1;
			}
			printf("open %s  success \n",CIM0308DEV);

			if (set_img_format(cim0308_fd, RGB565) == 0)
				return -1;

			param.width = width;
			param.height = height;
			param.bpp = bpp;
			
			if (set_img_param(cim0308_fd,&param) == 0)
				return -1;

			return cim0308_fd;
		}
		case MT367:
		{
			if(cim367_fd>0) cim_close(MT367);
			cim367_fd = open(CIM367DEV, O_RDWR);
			if(cim367_fd < 0)
			{
				printf("Error opening %s \n",CIM367DEV);
				return -1;
			}

			if (set_img_format(cim367_fd, YUV422_SEP) == 0)
				return -1;

			param.width = width;
			param.height = height;
			param.bpp = bpp;

			if (set_img_param(cim367_fd,&param) == 0)
				return -1;
			
			return cim367_fd;
		}
			
	}
	return -1;
}


/* Read a frame of image */
int cim_read(unsigned char id,unsigned char *buf, int frame_size)
{		
	switch(id)
	{
		case GC0308:
			return read(cim0308_fd, buf, frame_size);
		case MT367:
			return read(cim367_fd, buf, frame_size);
		default:
			return 0;
	}
}


void cim_close(int id)
{
	switch(id)
	{
		case GC0308:
			close(cim0308_fd);
			cim0308_fd = -1;
		 break;
		case MT367:
			close(cim367_fd);
			cim367_fd = -1;
		break;
		default:
			break;
	}

}

void  *cim_mmap(int id, unsigned int size)
{
	caddr_t  mem;
	switch(id){
	case GC0308:
		if ((mem = mmap(0, size, PROT_READ | PROT_WRITE,
						  MAP_SHARED, cim0308_fd, 0)) == MAP_FAILED) {
			perror(__func__);
			return NULL;
		}
		
		break;
		
	case MT367:
		if ((mem = mmap(0, size, PROT_READ | PROT_WRITE,
						  MAP_SHARED, cim367_fd, 0)) == MAP_FAILED) {
			perror(__func__);
			return NULL;
		}
		
		break;
		
	default:
			return NULL;
	 }
	
	return (mem);
}


