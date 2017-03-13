#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include "arca.h"
#include "sensor.h"
#include "cim.h"
#include "futil.h"
#include "mt9v136.h"
//#include "mt9v136old62.h"

#define 	IMAGESIZE		(640*480)
#define 	RGB565CUT		(640*480)
#define 	YUVSIZE			(640*480*2)
#define 	RGB24			(640*480)//(320*240*3)
#define 	YUVCUT			(640*240*3)

#define 	PIN 	(1*32+29) //(3*32+2)

#define 	TEST	1

#define    GC0308   1
#define    MT367    2

#if TEST
#define  LCD_DEV	"/dev/fb0"
static int lcd_fd = -1;
static unsigned int fb_width;
static unsigned int fb_height;
static unsigned int fb_depth;
static unsigned int screensize;
static unsigned char *fbmem;
#endif

extern void*fb_mmap(int fd, unsigned int screensize);


int init_camera_gc0308(int width,int height,int bpp)
{
	int ret=0;
	TIMING_PARAM t;
	ret=cim_open(GC0308,width, height, bpp);
	if(ret<0){
		printf(" cim open fail \n ");
		return -1;
	}
	ret = sensor_open_0308();
	if(ret < 0) {
		printf("Open sensor fail!!\n");
		return -1;
	}
	gc0308_init();

	t.mclk_freq = 24000000;
	t.pclk_active_direction = 1;
	t.hsync_active_level = 1;
	t.vsync_active_level = 1;
	
	ret = set_timing_param(GC0308,&t);
	if(ret == 0) {
		printf("set_timing_param fail!!\n");
		return -1;
	}
	printf("Set mclk to %dHz.\n", t.mclk_freq);

	sensor_close_0308();

	printf("GC0308 Init finish!\n");
	return 0;
}

int init_camera_mi367(int width,int height,int bpp)
{	
	int ret = -1;
	TIMING_PARAM t;
	ret=cim_open(MT367,width, height, 16);
	if(ret<0){
		printf("  %s  fail \n ",__func__);
		return -1;
	}	
	ret = sensor_open_mi367();
	if(ret < 0) {
		printf("Open sensor fail!!\n");
		return -1;
	}

	InitMT9V136(width,height,mt9v117regs1);
	InitMT9V136(width,height,wieght_table);

	t.mclk_freq = 48000000;
	t.pclk_active_direction = 0;
	t.hsync_active_level = 1;
	t.vsync_active_level = 0;
	
	set_timing_param(MT367,&t);
	if(ret == 0) {
		printf("set_timing_param fail!!\n");
		return -1;
	}
	printf("Set mclk to %dHz.\n", t.mclk_freq);

	sensor_close_mi367();

	printf("MI367 Init finish!\n");
	
	return 0;
}


int initcamera(unsigned char sensor,int width,int height,int bpp)
{
	int ret = -1 ;
	switch(sensor)
	{
		case GC0308:
			ret = init_camera_gc0308(width,height,bpp);
			
		break;
		
		case  MT367:
			ret = init_camera_mi367(width,height,bpp);
			
		break;
		
	   default:
			printf(" NOT SUPPORT SENSOR \n");
			ret = -1;
		break;
	}
	
	return ret;
}

void close_camera(int id)
{
	cim_close(id);
}

int saveImage(int quality,int width,int height,const char *path, unsigned char *yuv422buf)
{
	int i;
	unsigned char *pframebuf;
	unsigned char *yuv_data[3];
#if TEST
	pframebuf = (unsigned char *)yuv422buf;
	yuv_data[0] = pframebuf;
	yuv_data[2] = pframebuf + width*height;
	yuv_data[1] = pframebuf + width*height*3/2;
	write_JPEG_file(path,quality,width,height,yuv_data);
#endif
	return 0;
}

int grab_image(unsigned int id,int width,int height,unsigned char *buf)
{
	return cim_read(id,buf, width * height * 2);
}


#if TEST
int openlcd(void)
{
	lcd_fd = fb_open(LCD_DEV);
	if(lcd_fd<0)
	{
		printf("open /dev/fb0 fail!!\n");
		return -1;
	}
	printf("openlcd ok lcd_fd =%d\n",lcd_fd);
	fb_stat(lcd_fd,&fb_width,&fb_height,&fb_depth);
	printf("fb: w = %d h = %d depth = %d\n", fb_width, fb_height, fb_depth);
	screensize = fb_width * fb_height *fb_depth/8;
	fbmem = fb_mmap(lcd_fd,screensize);
	if (!fbmem)
	{
		printf("fb_mmap failed!\n");
		return -1;
	}
	return 0;
}

int closelcd(void)
{
	//fb_munmap(fbmem,screensize);
	fb_close(LCD_DEV);
	return 0;
}
#if 0
int fb_pixelAsRow(void *fbmem, int width_cut, int height_cut, int x, int y, unsigned int *rowbuf, int bufsize)
{
    	unsigned int *dst = ((unsigned int *) fbmem + y * width_cut + x);
	memcpy(dst, rowbuf, bufsize);
    	return (0);
}

int displayx(int width, int height,unsigned int width_cut,unsigned int height_cut,unsigned int *rgb888)
{
	unsigned int x,y,k=0;
	for(y = 0; y < height_cut; y++)
	{
		fb_pixelAsRow(fbmem,width_cut,height_cut,0,y,rgb888+y*width,width *4);
	}
}
#endif
#if 1


int displayx(int ox, int oy,unsigned int width_cut,unsigned int height_cut,unsigned short *rgb565cut)
{
	unsigned int x,y,k=0;
	for(y = 0; y < height_cut; y++)
	{
		fb_pixelAsRow(fbmem,fb_width,fb_height,0,y,rgb565cut+y*width_cut,width_cut *2);
	}
}

#endif


#endif

#if TEST
/****************************************************************************************

	flag =  0  save bmp  
	flag =  1  save jpeg
	flag =  2  display to lcd
	
*******************************************************************************************/
int sensor_0308_handle(int width, int higth, unsigned char *yuv422buf,unsigned short *rgb565,int flag)
{
	grab_image(GC0308,width,higth,(unsigned char *)rgb565);
}

/****
	flag =  0  save bmp  
	flag =  1  save jpeg
	flag =  2  display to lcd
****/

int sensor_367_handle(int width, int higth, unsigned char *yuv422buf,unsigned short *rgb565,int flag)
{
	if(grab_image(MT367,width,higth,yuv422buf)>0)
		yuv422rgb565(yuv422buf,rgb565,width,higth);		
}

#define USEGV0308	1
#define USEMI367	0
#define ROTATE		1
int main(int argc,char *argv[])
{
	int ret;
	int width_out, height_out;
	unsigned short *rgb565_0308buf = NULL;
	unsigned char *yuv422_367buf   =NULL;
	unsigned short *rgb565_out=NULL;
	unsigned short *rgb565_367buf=NULL;

	openlcd();	

	int flag=2;

#if USEGV0308
	ret = init_camera_gc0308(640,480,16);
	if (ret) {
		printf("init_camera_gc0308 failed!\n");
		return -1;
	}

	//rgb565_0308buf = cim_mmap(GC0308,640*480*2);
	rgb565_0308buf = malloc(640*480*2);
	if (!rgb565_0308buf) {
		printf("cim_mmap 0308 failed!\n");
		return -1;
	}
#endif

#if USEMI367
	ret = init_camera_mi367(640,480,16);
	if (ret) {
		printf("init_camera_mi367!\n");
		return -1;
	}

	//yuv422_367buf = cim_mmap(MT367,640*480*2);
	yuv422_367buf = malloc(640*480*2);
	if (!yuv422_367buf) {
		printf("cim_mmap 367 buf  failed!\n");
		return -1;
	}

	rgb565_367buf = (unsigned short *)malloc(RGB565CUT);
	if (!rgb565_367buf) {
		printf("malloc failed %s %d\n", __func__, __LINE__);
		return -1;
	}
#endif

#if ROTATE
	rgb565_out = (unsigned short *)malloc(2 * RGB565CUT);
	if (!rgb565_out) {
		printf("malloc failed %s %d\n", __func__, __LINE__);
		return -1;
	}
#endif

	while(1)
	{
#if USEGV0308
		sensor_0308_handle(640,480,NULL,rgb565_0308buf,flag);
#endif
#if USEMI367
		sensor_367_handle(640,480,yuv422_367buf,rgb565_367buf,flag);
#endif
#if ROTATE
		rgb565_rotate90(rgb565_0308buf, 640, 480, rgb565_out, &width_out, &height_out);
		displayx(0, 0, width_out, height_out, rgb565_out);
#else
		displayx(0, 0, 640, 480, rgb565_0308buf);
#endif
	}
#if USEGV0308
	close_camera(GC0308);
#endif
#if USEMI367
	close_camera(MT367);
#endif
	closelcd();
	if (rgb565_out)
		free(rgb565_out);
	if (rgb565_367buf)
		free(rgb565_367buf);
	return 0;
}

#endif  //endif test
