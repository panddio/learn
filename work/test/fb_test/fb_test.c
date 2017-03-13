/*************************************************************************
	> File Name: fb_test.c
	> Author: 
	> Mail: 
	> Created Time: Mon 30 May 2016 04:06:45 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#define RED_COLOR565     0x0f100
#define GREEN_COLOR565   0x007e0
#define BLUE_COLOR565    0x0001f

#define RED_COLOR888     0xff0000
#define GREEN_COLOR888   0x00ff00
#define BLUE_COLOR888    0x0000ff

int main()
{
    int fd = 0;
    int x = 0, y = 0;
    int div = 0;
    char *fbp = NULL;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    struct fb_cmap cmapinfo;
    long int screensize = 0;
    long int location = 0;

    //Open the file for reading and writing
    fd = open("/dev/fb0", O_RDWR);
    if(fd < 0) {
        printf("ERROR: cannot open framebuffer device. %d\n", fd);
        exit(1);
    }
    printf("The framebuffer device was opened successfully!\n");

    //Get fixed screen infomation
    if(ioctl(fd, FBIOGET_FSCREENINFO, &finfo)) { //
        printf("ERROR: cannot get fixed infomation!\n ");
        exit(2);
    }

    printf(finfo.id);
    printf("\ntype: 0x%x\n", finfo.type);
    printf("visual: %d\n", finfo.visual);
    printf("line_length: %d\n", finfo.line_length);
    printf("smem_start: 0x%x, smem_len: %d\n", finfo.smem_start, finfo.smem_len);
    printf("mmio_start: 0x%x, mmio_len: %d\n", finfo.mmio_start, finfo.mmio_len);

    // Get variable screen infomation
    if(ioctl(fd, FBIOGET_VSCREENINFO, &vinfo)) {
        printf("ERROR: cannot get variable infomation!\n");
        exit(3);
    }
    printf("%d x %d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);
    //Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel/8;

    //Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if((int)fbp == -1) {
        printf("ERROR: failed to map framebuffer device to memory!\n");
        exit(4);
    }

    printf("The framebuffer device was mapped to memory successfully!\n");

    //Figure out where in memory to put the pixel
#if 0
    int r, b, g;
    b = 0x10;  //blue:0000 0010
    g = 0x100; //green: 0000 0100
    r = 0x100; //red: 0000 0100
    //vinfo.xoffset = (240-160)/2;
    //vinfo.yoffset = (240-160)/2;

    for(y = 80; y < 160; y++) {
        for(x = 80; x < 160; x++) {
            location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                (y + vinfo.yoffset) * finfo.line_length;

        #if 0
            if(vinfo.bits_per_pixel == 32) {
                *(fbp + location) = b;
                *(fbp + location + 1) = g;
                *(fbp + location + 2) = r;
                *(fbp + location + 3) = 0;
            } else { //16bpp: r:g:b = 5:6:6
                unsigned short int t = r << 11 | g << 5 | b;
                *((unsigned short int *)(fbp + location)) = t;
            }
        #else
            /* 简单处理,假定是32位或者是16位 565模式*/
            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = 100;    // Some blue
                *(fbp + location + 1) = 15+(x-100)/2; // A little green
                *(fbp + location + 2) = 200-(y-100)/5;// A lot of red
                *(fbp + location + 3) = 0xff;         // No transparency
            } else { //assume 16bpp
                unsigned short b = 10;
                unsigned short g = (x-100)/6;
                unsigned short r = 31-(y-100)/16; // A lot of red
                unsigned short t = r << 11 | g << 5 | b;
                *((unsigned short *)(fbp + location)) = t;
            }
        #endif
        }
    }
#else

    switch(vinfo.bits_per_pixel) {
    case 16:
		div = vinfo.yres/3;
		for(y = 0; y < vinfo.yres; y++) {
			for(x = 0; x < vinfo.xres; x++) {
				location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
					(y + vinfo.yoffset) * finfo.line_length;

				switch(y/div) {
				case 0: //Red screen
					*((unsigned short *)(fbp + location)) = RED_COLOR565;
					break;
				case 1: //Green screen
					*((unsigned short *)(fbp + location)) = GREEN_COLOR565;
					break;
				case 2: //Blue screen
					*((unsigned short *)(fbp + location)) = BLUE_COLOR565;
					break;
				}
			}
		}
        break;
    case 32:
        div = vinfo.yres/3;
		for(y = 0; y < vinfo.yres; y++) {
			for(x = 0; x < vinfo.xres; x++) {
				location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
					(y + vinfo.yoffset) * finfo.line_length;

                switch(y/div) {
				case 0: //Red screen
					*((unsigned int *)(fbp + location)) = RED_COLOR888 - ((y%div)/(div/4) * 0x20 << 16);
					break;
				case 1: //Green screen
					*((unsigned int *)(fbp + location)) = GREEN_COLOR888 - ((y%div)/(div/4) * 0x20 << 8);
					break;
				case 2: //Blue screen
					*((unsigned int *)(fbp + location)) = BLUE_COLOR888 - ((y%div)/(div/4) * 0x20 << 0);
					break;
				}
            }
        }
        break;
    default:
        printf("WARNNING: bpp if not %d\n", vinfo.bits_per_pixel);
    }
#endif
    munmap(fbp, screensize);
    close(fd);
    return 0;
}

