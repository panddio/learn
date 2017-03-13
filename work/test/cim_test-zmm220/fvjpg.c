/*
 * $Id: fv.c
 * $Desp: draw jpeg to framebuffer
 * $Author: rockins
 * $Date: Wed Jan  3 20:15:49 CST 2007
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
//#include <jpeglib.h>
//#include <jerror.h>
#include <string.h>

#define	FB_DEV	"/dev/fb0"

/***************** function declaration ******************/
void            usage(char *msg);
unsigned short  RGB888toRGB565(unsigned char red,
							   unsigned char green, unsigned char blue);
int             fb_open(char *fb_device);
int             fb_close(int fd);
int             fb_stat(int fd, int *width, int *height, int *depth);
void           *fb_mmap(int fd, unsigned int screensize);
int             fb_munmap(void *start, size_t length);
int             fb_pixel(void *fbmem, int width, int height,
						 int x, int y, unsigned short color);
#define TRUE	1
/************ function implementation ********************/
//int main(int argc, char **argv)

	/*
	 * declaration for jpeg decompression
	 */
	static struct jpeg_decompress_struct cinfo;
	static struct jpeg_error_mgr jerr;
	static FILE           *infile,*fp;
	static unsigned char  *buffer;

	/*
	 * declaration for framebuffer device
	 */
	static int             fbdev;
	static char           *fb_device;
	static unsigned char  *fbmem;
	static unsigned int    screensize;
	static unsigned int    fb_width;
	static unsigned int    fb_height;
	static unsigned int    fb_depth;
	static unsigned int    x;
	static unsigned int    y;
	static int flag=0;

void openDev(void)
{
	#if 0
	if ((fp = fopen("/mnt/sdcard/main", "rb")) != NULL) {
		printf("sdcard ok\n");
		fclose(fp);
		//return 1;
		flag=1;
	}
	#endif
#if 0
        /*
         * open input jpeg file
         */
        if(!flag)
        {
        //      if ((infile = fopen(argv[1], "rb")) == NULL) {
                if ((infile = fopen(path, "rb")) == NULL) {
                        printf("can't open jpg file\n");
                //      exit(-1);
                        return -1;
                }
        }
        else
        {
                if ((infile = fopen("warning2.jpg", "rb")) == NULL) {
                        printf("can't open jpg file\n");
                        exit(-1);
                }
        }
#endif

	/*
	 * open framebuffer device
	 */
	if ((fb_device = getenv("FRAMEBUFFER")) == NULL)
	{
		fb_device = FB_DEV;
		printf("fb_device=/dev/fb0\n");
	}

	printf("fd_device:%s\n",fb_device);

	fbdev = fb_open(fb_device);

	/*
	 * get status of framebuffer device
	 */
	fb_stat(fbdev, &fb_width, &fb_height, &fb_depth);

	/*
	 * map framebuffer device to shared memory
	 */
	screensize = fb_width * fb_height * fb_depth / 8;
	fbmem = fb_mmap(fbdev, screensize);
	printf("open framebuffer ok\n");

}

#if 0
int showimage(char *path)
{

                if ((infile = fopen(path, "rb")) == NULL) {
                        printf("can't open jpg file\n");
                //      exit(-1);
                        return -1;
                }
	/*
	 * init jpeg decompress object error handler
	 */
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	/*
	 * bind jpeg decompress object to infile
	 */
	jpeg_stdio_src(&cinfo, infile);


	/*
	 * read jpeg header
	 */
	jpeg_read_header(&cinfo, TRUE);

	/*
	 * decompress process.
	 * note: after jpeg_start_decompress() is called
	 * the dimension infomation will be known,
	 * so allocate memory buffer for scanline immediately
	 */
	jpeg_start_decompress(&cinfo);
	if ((cinfo.output_width > fb_width) ||
		(cinfo.output_height > fb_height)) {
		printf("fb_width=%d\n",fb_width);
		printf("fb_height=%d\n",fb_height);
		printf("too large JPEG file,cannot display\n");
		return (-1);
	}

	buffer = (unsigned char *) malloc(cinfo.output_width *
									  cinfo.output_components);
	y = 0;
//	printf("fb_depth %d\n",fb_depth);
	while (cinfo.output_scanline < cinfo.output_height) 
	{
		jpeg_read_scanlines(&cinfo, &buffer, 1);

		if (fb_depth == 16) 
		{
			unsigned short  color;
			for (x = 0; x < cinfo.output_width; x++) 
			{
				color = RGB888toRGB565(buffer[x * 3], buffer[x * 3 + 1], buffer[x * 3 + 2]);
				fb_pixel(fbmem, fb_width, fb_height, x, y, color);
			}
		} 
		else if (fb_depth == 24) 
		{
			memcpy((unsigned char *) fbmem + y * fb_width * 3, buffer, cinfo.output_width * cinfo.output_components);
		}
		y++;					// next scanline
	}
	/*
	 * finish decompress, destroy decompress object
	 */
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	fclose(infile);

}
#endif
void showimg(unsigned char *buf,int x, int y, int w, int h)
{
//	printf("show img ...\n");
	int i;
	for(i=0;i<h;i++)
		memcpy((unsigned char *) fbmem + ((y+i)*fb_width+x)*2 , buf+i*w*2, w*2);
}

void closeDev(void)
{

	/*
	 * release memory buffer
	 */
	free(buffer);

	/*
	 * close jpeg inputing file
	 */
//	fclose(infile);

	/*
	 * unmap framebuffer's shared memory
	 */
	fb_munmap(fbmem, screensize);

	/*
	 * close framebuffer device
	 */
	fb_close(fbdev);
//	return (0);
}

void
usage(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	printf("Usage: fv some-jpeg-file.jpg\n");
}

/*
 * convert 24bit RGB888 to 16bit RGB565 color format
 */
unsigned short
RGB888toRGB565(unsigned char red,unsigned char green, unsigned char blue)
{
	unsigned short  B = (blue >> 3) & 0x001F;
	unsigned short  G = ((green >> 2) << 5) & 0x07E0;
	unsigned short  R = ((red >> 3) << 11) & 0xF800;

	return (unsigned short) (R | G | B);
}

void RGB565toRGB888(unsigned short rgb565, unsigned char *rgb)
{
	rgb[0] = (rgb565&0xF800)>>11;
	rgb[1] = (rgb565&0x0E70)>>5;
	rgb[2] = (rgb565&0x001F);
	
	return;
}
/*
 * open framebuffer device.
 * return positive file descriptor if success,
 * else return -1.
 */
int
fb_open(char *fb_device)
{
	int             fd;

	if ((fd = open(fb_device, O_RDWR)) < 0) {
		perror(__func__);
		return (-1);
	}
	return (fd);
}

/*
 * get framebuffer's width,height,and depth.
 * return 0 if success, else return -1.
 */
int
fb_stat(int fd, int *width, int *height, int *depth)
{
	struct fb_fix_screeninfo fb_finfo;
	struct fb_var_screeninfo fb_vinfo;

	if (ioctl(fd, FBIOGET_FSCREENINFO, &fb_finfo)) {
		perror(__func__);
		return (-1);
	}

	if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_vinfo)) {
		perror(__func__);
		return (-1);
	}

	*width = fb_vinfo.xres;
	*height = fb_vinfo.yres;
	*depth = fb_vinfo.bits_per_pixel;

	return (0);
}

/*
 * map shared memory to framebuffer device.
 * return maped memory if success,
 * else return -1, as mmap dose.
 */
void           *
fb_mmap(int fd, unsigned int screensize)
{
	caddr_t         fbmem;

	if ((fbmem = mmap(0, screensize, PROT_READ | PROT_WRITE,
					  MAP_SHARED, fd, 0)) == MAP_FAILED) {
		perror(__func__);
		return NULL;
	}

	return (fbmem);
}

/*
 * unmap map memory for framebuffer device.
 */
int
fb_munmap(void *start, size_t length)
{
	return (munmap(start, length));
}

/*
 * close framebuffer device
 */
int
fb_close(int fd)
{
	return (close(fd));
}

/*
 * display a pixel on the framebuffer device.
 * fbmem is the starting memory of framebuffer,
 * width and height are dimension of framebuffer,
 * x and y are the coordinates to display,
 * color is the pixel's color value.
 * return 0 if success, otherwise return -1.
 */
int
fb_pixel(void *fbmem, int width, int height,
		 int x, int y, unsigned short color)
{
	if ((x > width) || (y > height))
		return (-1);

	unsigned short *dst = ((unsigned short *) fbmem + y * width + x);

	*dst = color;
	return (0);
}

//modify by seven 2011-06-11
#if 1
int fb_pixelAsRow(void *fbmem, int width, int height,
                 int x, int y, unsigned short *rowbuf, int bufsize)
{
        if ((x > width) || (y > height))
                return (-1);

        unsigned short *dst = ((unsigned short *) fbmem + y * width + x);

	memcpy(dst, rowbuf, bufsize);

        return (0);
}
#endif


/*
int main(int argc, char **argv)
{
	char name[50];
	int i;

	for(i=0;i<10;i++)
	{
		sprintf(name,"image%d.jpg",i);
		showimage(name);
	}
	return 0;
}
*/
