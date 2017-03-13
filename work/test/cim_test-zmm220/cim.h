#ifndef __CIM_H__
#define __CIM_H__

/*
typedef unsigned int u32;
typedef unsigned char BYTE;
typedef unsigned char u8;
*/
/* timing parameters */
typedef struct
{
	unsigned long mclk_freq;
	unsigned int pclk_active_direction;//o for rising edge, 1 for falling edge
	unsigned int hsync_active_level;
	unsigned int vsync_active_level;
} TIMING_PARAM;

/* image parameters */
typedef struct
{
        unsigned int width;      /* width */
        unsigned int height;     /* height */
        unsigned int bpp;        /* bits per pixel: 8/16/32 */
} IMG_PARAM;

/* image format */
typedef enum {
	NO_FORMAT = 0,
	YUV422_SEP,
	YUV422_PACK,
	RGB565,
	RGB888,
	RAW
} img_format_t;

int cim_open(int id,int width, int height, int bpp);
void cim_close(int id);
int cim_read(unsigned char id,unsigned char *buf, int frame_size);
int set_timing_param(int id,TIMING_PARAM *timing);
void  *cim_mmap(int id, unsigned int size);

#endif /* __CIM_H__ */

