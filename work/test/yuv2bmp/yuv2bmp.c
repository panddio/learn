/*************************************************************************
	> Filename: main.c
	>   Author: Qiuwei.wang
	>    Email: qiuwei.wang@ingenic.com / panddio@163.com
	> Datatime: Time: Tue 27 Sep 2016 11:09:02 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "bmp.h"
#include "srcBuf.h"

/*
 * Macro
 */

#define DEFAULT_WIDTH    640
#define DEFAULT_HEIGHT   480
#define DEFAULT_BPP      16


static const char short_options[] = "b:hx:y:";

static const struct option long_options[] = {
	{ "help",       0,      NULL,           'h' },
	{ "bpp",        1,      NULL,           'b' },
	{ "width",      1,      NULL,           'x' },
	{ "height",     1,      NULL,           'y' },
	{ 0, 0, 0, 0 }
};

/*
 * Functions
 */
static void usage(FILE *fp, int argc, char *argv[])
{
	fprintf(fp,
			 "\nUsage: %s [options]\n"
			 "Options:\n"
			 "-h | --help          Print this message\n"
			 "-b | --bpp           Set image bpp\n"
			 "-x | --width         Set image width\n"
			 "-y | --height        set image height\n"
			 "\n", argv[0]);
}

/*
 * Functions
 */

unsigned int yuv2rgb_pixel(int y, int u, int v)
{
	unsigned int rgb_24 = 0;
	unsigned char *pixel = (unsigned char *)&rgb_24;
	int r, g, b;

	r = y + (1.370705 * (v - 128));
	g = y - (0.698001 * (v - 128)) - (0.337633 * (u - 128));
	b = y + (1.732446 * (u - 128));

	if(r > 255) r = 255;
	if(g > 255) g = 255;
	if(b > 255) b = 255;

	if(r < 0) r = 0;
	if(g < 0) g = 0;
	if(b < 0) b = 0;

	/*
	 * BMP文件内部不压缩图片的格式是BGR
	 */
	pixel[0] = b;
	pixel[1] = g;
	pixel[2] = r;

	return rgb_24;
}

/*
 * YUV422 to RGB
 */
int yuv2rgb(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned height)
{
	unsigned int in = 0, out = 0;
	unsigned int pixel_16;
	unsigned char pixel_24[3];
	unsigned int rgb_24;
	unsigned int y0, u, y1, v;

	for(in = 0; in < width * height * 2; in +=4) {
		pixel_16 = yuv[in + 3] << 24 |
				   yuv[in + 2] << 16 |
				   yuv[in + 1] << 8  |
				   yuv[in + 0];
#if 0
		u  = (pixel_16 & 0x000000ff);
		y0 = (pixel_16 & 0x0000ff00) >> 8;
		v  = (pixel_16 & 0x00ff0000) >> 16;
		y1 = (pixel_16 & 0xff000000) >> 24;
#else
		y0 = (pixel_16 & 0x000000ff);
		v  = (pixel_16 & 0x0000ff00) >> 8;
		y1 = (pixel_16 & 0x00ff0000) >> 16;
		u  = (pixel_16 & 0xff000000) >> 24;
#endif

		rgb_24 = yuv2rgb_pixel(y0, u, v);

		pixel_24[0] = (rgb_24 & 0x000000ff);
		pixel_24[1] = (rgb_24 & 0x0000ff00) >> 8;
		pixel_24[2] = (rgb_24 & 0x00ff0000) >> 16;

		rgb[out++] = pixel_24[0];
		rgb[out++] = pixel_24[1];
		rgb[out++] = pixel_24[2];

		rgb_24 = yuv2rgb_pixel(y1, u, v);

		pixel_24[0] = (rgb_24 & 0x000000ff);
		pixel_24[1] = (rgb_24 & 0x0000ff00) >> 8;
		pixel_24[2] = (rgb_24 & 0x00ff0000) >> 16;

		rgb[out++] = pixel_24[0];
		rgb[out++] = pixel_24[1];
		rgb[out++] = pixel_24[2];
	}

	return 0;
}

int writBMPFile(char *filename, unsigned int width, unsigned int height,\
        int iBitCount, unsigned long rgbSize, unsigned char *rgbBuf)
{
    unsigned char *dstBuf = NULL;
    unsigned int i, j, size;

    printf("width = %d, height = %d, rgbSize = %ld\n", width, height, rgbSize);
    printf("sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) = 0x%0x\n", \
            (unsigned int)(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)));
    printf("sizeof(BITMAPFILEHEADER) = 0x%02x\n", \
            (unsigned int)sizeof(BITMAPFILEHEADER));
    printf("sizeof(BITMAPINFOHEADER) = 0x%02x\n", \
            (unsigned int)sizeof(BITMAPINFOHEADER));

	if(iBitCount == 24) {
		FILE *fp;
		long count = 0;

		BITMAPFILEHEADER bmpHeader;
		BITMAPINFO bmpInfo;

		if((fp = fopen(filename, "wb")) == NULL) {
			printf("Can not create BMP file: %s\n", filename);
			return -1;
		}

		bmpHeader.bfType = (WORD)(('M' << 8) | 'B');
		bmpHeader.bfSize = rgbSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		bmpHeader.bfReserved1 = 0;
		bmpHeader.bfReserved2 = 0;
		bmpHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmpInfo.bmiHeader.biWidth = width;
		bmpInfo.bmiHeader.biHeight = height;
		bmpInfo.bmiHeader.biPlanes = 1;
		bmpInfo.bmiHeader.biBitCount = iBitCount;
		bmpInfo.bmiHeader.biCompression = 0;
        bmpInfo.bmiHeader.biSizeImage = rgbSize;
		bmpInfo.bmiHeader.biXPelsPerMeter = 0;
		bmpInfo.bmiHeader.biYPelsPerMeter = 0;
		bmpInfo.bmiHeader.biClrUsed = 0;
		bmpInfo.bmiHeader.biClrImportant = 0;

		if((count = fwrite(&bmpHeader, 1, sizeof(BITMAPFILEHEADER), fp))
				!= sizeof(BITMAPFILEHEADER))
			printf("write BMP file header failed: count=%ld\n", count);

		if((count = fwrite(&(bmpInfo.bmiHeader), 1, sizeof(BITMAPINFOHEADER), fp))
				!= sizeof(BITMAPINFOHEADER))
			printf("write BMP file info failed: count=%ld\n", count);

        /* convert rgbbuf */
        dstBuf = (unsigned char *)malloc(rgbSize);
        if(!dstBuf) {
            printf("malloc dstBuf failed !!\n");
            return -1;
        }

        size = width * 3; // line size
        for(i = 0, j = height -1; i < height - 1; i++, j--)
            memcpy((dstBuf + (size * j)), (rgbBuf + (size * i)), size);

		if((count = fwrite(dstBuf, 1, rgbSize, fp)) != rgbSize)
			printf("write BMP file date failed: count=%ld\n", count);

        free(dstBuf);
		fclose(fp);
		return 0;
	} else {
        printf("Err: iBitCount != 24\n");
        return -1;
    }
}

int main(int argc, char *argv[])
{
	unsigned char *rgbBuf = NULL;
    unsigned long rgbSize;
	unsigned int bpp = DEFAULT_BPP;
	unsigned int width = DEFAULT_WIDTH;
	unsigned int height = DEFAULT_HEIGHT;

	while(1) {
		int oc;

		oc = getopt_long(argc, argv, \
						 short_options, long_options, \
						 NULL);
		if(-1 == oc)
			break;

		switch(oc) {
		case 0:
			break;

		case 'h':
			usage(stdout, argc, argv);
			exit(EXIT_SUCCESS);
			break;

		case 'b':
			bpp = atoi(optarg);
			break;

		case 'x':
			width = atoi(optarg);
			break;

		case 'y':
			height = atoi(optarg);
			break;

		default:
			usage(stderr, argc, argv);
			exit(EXIT_FAILURE);
			break;
		}
	}

#if 0
    printf("sizeof(unsigned long) = %ld\n", sizeof(unsigned long));
    printf("sizeof(long) = %ld\n", sizeof(long));
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(unsigned short) = %ld\n", sizeof(unsigned short));
#endif

    rgbSize = width * height * 3;

	rgbBuf = (unsigned char *)malloc(rgbSize);
    if(!rgbBuf) {
        printf("malloc rgbBuf failed !!\n");
        return -1;
    }

	yuv2rgb(srcBuf, rgbBuf, width, height);
	writBMPFile("./image/test.bmp", width, height, 24, rgbSize, rgbBuf);
    free(rgbBuf);

    return 0;
}
