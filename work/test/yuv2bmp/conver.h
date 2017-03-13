#ifndef __CONVER_H__
#define __CONVER_H__

int  init_conver();
void rgb5652rgb888(unsigned short* rgb565,unsigned int* rgb888,unsigned int framesize);

int yuv422rgb565_scale(unsigned char *yuv422buf,unsigned short *rgb565,int width,int height);
int yuv422rgb565(unsigned char *yuv422buf,unsigned short *rgb565,int width,int height);
int yuv422rgb888_scale(unsigned char *yuv422buf,unsigned int *rgb888,int width,int height);
int yuv422rgb888(unsigned char *yuv422buf,unsigned int *rgb888,int width,int height);

int rgb8882rgb565(unsigned short *rgb565,unsigned char *rgb888,unsigned int imagesize);

int cut_rgb565(unsigned short *rgb565cut,unsigned short *rgb565src,unsigned int width,unsigned int imagesize);

void rgb565_rotate90(const unsigned short *input, int width_in, int height_in,unsigned short *output);//, int *width_out, int *height_out);

/*************************
 *Translate the picture Right_Left.
 * ***********************/
void rgb565_folio(unsigned short *rgb565,int width,int height);

int  close_conver();
#endif



