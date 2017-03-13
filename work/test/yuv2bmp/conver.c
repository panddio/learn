/*
##############################################################################
# Raw Image Player [ImPlayer]                           					 #
# Copyright 2000 Yao-Jen Chang and Wei-Hsien Lin                             #
# Video Signal Processing Lab, Dept.EE, NTHU                                 #
# Version 1.5  Created 2/1/2000                                              #
##############################################################################
# COPYRIGHT NOTICE                                                           #
# Copyright 2000 Yao-Jen Chang and Wei-Hsien Lin, All Rights Reserved.       #
#                                                                            #
# [ImPlayer] may be used and modified free of charge by anyone so long as    #
# this copyright notice and the comments above remain intact. By using this  #
# code you agree to indemnify Yao-Jen Chang from any liability that might    #
# arise from it's use.                                                       #
#                                                                            #
# Comments, feedback, bug reports, improvements are encouraged. Please sent  #
# them to kc@benz.ee.nthu.edu.tw.                                            #
##############################################################################
*/
/************************************************************************
 *
 *  yuvrgb24.c, colour space conversion for tmndecode (H.263 decoder)
 *  Copyright (C) 1995, 1996  Telenor R&D, Norway
 *        Karl Olav Lillevold <Karl.Lillevold@nta.no>
 *  
 *  Contacts: 
 *  Karl Olav Lillevold               <Karl.Lillevold@nta.no>, or
 *  Robert Danielsen                  <Robert.Danielsen@nta.no>
 *
 *  Telenor Research and Development  http://www.nta.no/brukere/DVC/
 *  P.O.Box 83                        tel.:   +47 63 84 84 00
 *  N-2007 Kjeller, Norway            fax.:   +47 63 81 00 76
 *  
 ************************************************************************/

/*
 * Disclaimer of Warranty
 *
 * These software programs are available to the user without any
 * license fee or royalty on an "as is" basis.  Telenor Research and
 * Development disclaims any and all warranties, whether express,
 * implied, or statuary, including any implied warranties or
 * merchantability or of fitness for a particular purpose.  In no
 * event shall the copyright-holder be liable for any incidental,
 * punitive, or consequential damages of any kind whatsoever arising
 * from the use of these programs.
 *
 * This disclaimer of warranty extends to the user of these programs
 * and user's customers, employees, agents, transferees, successors,
 * and assigns.
 *
 * Telenor Research and Development does not represent or warrant that
 * the programs furnished hereunder are free of infringement of any
 * third-party patents.
 *
 * Commercial implementations of H.263, including shareware, are
 * subject to royalty fees to patent holders.  Many of these patents
 * are general enough such that they are unavoidable regardless of
 * implementation design.
 * */


#include "futil.h"

static unsigned char* clp = NULL;
static int crv_tab[256]={0};
static int cbu_tab[256]={0};
static int cgu_tab[256]={0};
static int cgv_tab[256]={0};
static int tab_76309[256]={0};
static int bilevel_tab_76309[256]={0};
BITMAPINFO  bmi;
static int inited = 0;

static int init_clp() 
{
  int i;
  if(clp == NULL)
  	{
  		clp = (unsigned char*)malloc(1024);
  		if(clp == NULL)
  			{
  				printf("init_clp malloc failed \r\n");
  				return -1;
  			}
  	}else
  		{
  			printf("init_clp always inited \r\n");
  			return 0;
  		}
  clp += 384;

  for (i=-384; i<640; i++)
  {
    clp[i] = (i<0) ? 0 : ((i>255) ? 255 : i);
  }

  return 0;
}

static void init_dither_tab()
{
  long int crv,cbu,cgu,cgv;
  int i;

  crv = 104597; cbu = 132201;  /* fra matrise i global.h */
  cgu = 25675;  cgv = 53279;

  for (i = 0; i < 256; i++) {
    crv_tab[i] = (i-128) * crv;
    cbu_tab[i] = (i-128) * cbu;
    cgu_tab[i] = (i-128) * cgu;
    cgv_tab[i] = (i-128) * cgv;
    tab_76309[i] = 76309*(i-16);
  }
  bilevel_tab_76309[0] = tab_76309[0];
  for (i = 1; i < 256; i++) {
	  bilevel_tab_76309[i] = tab_76309[255];
  }

}

int  init_conver()
{
  init_dither_tab();
  if(init_clp() < 0)
  	{
  		return -1;
  	}
  bmi.bmiHeader.biSize = (LONG)sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biCompression = 0l;
  bmi.bmiHeader.biSizeImage = 0l;
  bmi.bmiHeader.biXPelsPerMeter = 0l;
  bmi.bmiHeader.biYPelsPerMeter = 0l;
  bmi.bmiHeader.biBitCount = 24;
  inited = 1;
  return 0;
}

/**********************************************************************
 *
 *	Name:	         ConvertYUVtoRGB
 *	Description:     Converts YUV image to RGB (packed mode)
 *
 *	Input:	         pointer to source luma, Cr, Cb, destination,
 *                       image width and height
 *	Returns:
 *	Side effects:
 *
 *	Date: 951208	Author: Karl.Lillevold@nta.no
 *
 ***********************************************************************/

void rgb5652rgb888(unsigned short* rgb565,unsigned int* rgb888,unsigned int framesize)
{
	unsigned int i;
	unsigned char r,g,b;
	r=g=b=0;
	for(i=0;i<framesize;i++)
	{
		r=((*((unsigned short*)rgb565 + i))>>11)&0x1f;
		g=((*((unsigned short*)rgb565 + i))>>5)&0x3f;
		b=(*((unsigned short*)rgb565 + i))&0x1f;
		*((unsigned int*)rgb888 + i)=(r<<19)|(g<<10)|(b<<3);
	}
}
/*
yuv422转换RGB565并缩小一半图像的函数
yuv422buf: input width*height picture buffer
rgb565:    output width/2*height/2 picture RGB565 buffer
width:     input picture width
height:    input  picture height
*/
int yuv422rgb565_scale(unsigned char *yuv422buf,unsigned short *rgb565,int width,int height)
{
	int i, j, k, u, v, u2g, u2b, v2g, v2r, y11, y12;
	int width4 = width + (4 - (width%4))%4;
	unsigned short R,G,B;
  	unsigned char *pucy,* pucu, * pucv;
	char crgbtmp;
  	if((yuv422buf==NULL)||(rgb565==NULL)){
		return -1;
	}
	if(inited == 0){
		if(init_conver() < 0){
			return -1;
		}
	}
	pucy = yuv422buf;
	pucu = yuv422buf + width * height;
	pucv = yuv422buf + width * height * 3/2;

	width		=	width/2;
	height		=	height/2;

	k	=	width * (height-1);		//Point to the last width_line of rgb565buf,why?
	for (i = 0; i < height; i++){
    		for (j = 0; j < width; j+=4)
		{
			y11 = tab_76309[*pucy++];
        	y12 = tab_76309[*pucy++];
        	u = *pucu++;
        	v = *pucv++;
        	u2g = cgu_tab[u];
        	u2b = cbu_tab[u];
        	v2g = cgv_tab[v];
        	v2r = crv_tab[v];


		     crgbtmp	=	clp[(y11 + v2r)>>16];
		     R 		= 	((crgbtmp >> 3)) & 0x001F;
		     crgbtmp 	= 	clp[(y11 - u2g - v2g)>>16];
		     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;
		     crgbtmp	= 	clp[(y11 + u2b)>>16];
		     B		=	((crgbtmp >> 3)<<11) & 0xF800;
			// printf(" ===  R = 0x%04x, G = 0x%04x B =0x%04x    \n",R,G,B);
		     rgb565[k++]	= 	(R | G | B);
			//printf("%d rgb565[%d] = 0x%04x  \n",__LINE__,k,rgb565[k]);
		     crgbtmp	=	clp[(y12 + v2r)>>16];
		     R 		= 	((crgbtmp >> 3)) & 0x001F;

		     crgbtmp 	= 	clp[(y12 - u2g - v2g)>>16];
		     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;

		     crgbtmp	= 	clp[(y12 + u2b)>>16];
		     B		=	((crgbtmp >> 3)<<11) & 0xF800;

		     rgb565[k++]	= 	(R | G | B);

//Skip two pixels,because two pixels as a unit.
		     pucy+=2;
		     pucu++;
		     pucv++;

// Let two ALU work at the same time
                y11 = tab_76309[*pucy++];
                y12 = tab_76309[*pucy++];
                u = *pucu++;
                v = *pucv++;
                u2g = cgu_tab[u];
                u2b = cbu_tab[u];
                v2g = cgv_tab[v];
                v2r = crv_tab[v];

			     crgbtmp	=	clp[(y11 + v2r)>>16];
			     R 		= 	((crgbtmp >> 3)) & 0x001F;

			     crgbtmp 	= 	clp[(y11 - u2g - v2g)>>16];
			     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;

			     crgbtmp	= 	clp[(y11 + u2b)>>16];	
			     B		=	((crgbtmp >> 3)<<11) & 0xF800;
	
			     rgb565[k++]	= 	(R | G | B);      
	
			     crgbtmp	=	clp[(y12 + v2r)>>16];
			     R 		= 	((crgbtmp >> 3)) & 0x001F;
			     crgbtmp 	= 	clp[(y12 - u2g - v2g)>>16];	
			     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;	
			     crgbtmp	= 	clp[(y12 + u2b)>>16];	
			     B		=	((crgbtmp >> 3)<<11) & 0xF800;
	
			     rgb565[k++]	= 	(R | G | B);      
	
	//Skip two pixels,because two pixels as a unit.
			     pucy+=2;
			     pucu++;
			     pucv++;
	            	}

					k=k - width*2;
					pucy+=width4;				//Skip one width_line Y,U,V
					pucu+=width4/2;
					pucv+=width4/2;
        }

	return 0;
}

/*
yuv422转换RGB565图像的函数
yuv422buf: input width*height picture buffer
rgb565:    output width*height picture RGB565 buffer
width:     input picture width
height:    input  picture height
*/
int yuv422rgb565(unsigned char *yuv422buf,unsigned short *rgb565,int width,int height)
{
	int i, j, k, u, v, u2g, u2b, v2g, v2r, y11, y12;
	int width4 = width + (4 - (width%4))%4;
	unsigned short R,G,B;
  	unsigned char *pucy,* pucu, * pucv;
	char crgbtmp;
  	if((yuv422buf==NULL)||(rgb565==NULL)){
		return -1;
	}
	if(inited == 0){
		if(init_conver() < 0){
			return -1;
		}
	}
	pucy = yuv422buf;
	pucu = yuv422buf + width * height;
	pucv = yuv422buf + width * height * 3/2;

	k	=	width * (height-1);		//Point to the last width_line of rgb565buf,why?
	for (i = 0; i < height; i++){
    		for (j = 0; j < width; j+=4)
		{
			y11 = tab_76309[*pucy++];
        	y12 = tab_76309[*pucy++];
        	u = *pucu++;
        	v = *pucv++;
        	u2g = cgu_tab[u];
        	u2b = cbu_tab[u];
        	v2g = cgv_tab[v];
        	v2r = crv_tab[v];


		     crgbtmp	=	clp[(y11 + v2r)>>16];
		     R 		= 	((crgbtmp >> 3)) & 0x001F;
		     crgbtmp 	= 	clp[(y11 - u2g - v2g)>>16];	
		     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;	
		     crgbtmp	= 	clp[(y11 + u2b)>>16];	
		     B		=	((crgbtmp >> 3)<<11) & 0xF800;
		     rgb565[k++]	= 	(R | G | B);      
		     crgbtmp	=	clp[(y12 + v2r)>>16];
		     R 		= 	((crgbtmp >> 3)) & 0x001F;

		     crgbtmp 	= 	clp[(y12 - u2g - v2g)>>16];	
		     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;	

		     crgbtmp	= 	clp[(y12 + u2b)>>16];	
		     B		=	((crgbtmp >> 3)<<11) & 0xF800;

		     rgb565[k++]	= 	(R | G | B);      
		     
                y11 = tab_76309[*pucy++];
                y12 = tab_76309[*pucy++];
                u = *pucu++;
                v = *pucv++;
                u2g = cgu_tab[u];
                u2b = cbu_tab[u];
                v2g = cgv_tab[v];
                v2r = crv_tab[v];

			     crgbtmp	=	clp[(y11 + v2r)>>16];
			     R 		= 	((crgbtmp >> 3)) & 0x001F;
	
			     crgbtmp 	= 	clp[(y11 - u2g - v2g)>>16];	
			     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;	
	
			     crgbtmp	= 	clp[(y11 + u2b)>>16];	
			     B		=	((crgbtmp >> 3)<<11) & 0xF800;
	
			     rgb565[k++]	= 	(R | G | B);      
	
			     crgbtmp	=	clp[(y12 + v2r)>>16];
			     R 		= 	((crgbtmp >> 3)) & 0x001F;
			     crgbtmp 	= 	clp[(y12 - u2g - v2g)>>16];	
			     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;	
			     crgbtmp	= 	clp[(y12 + u2b)>>16];	
			     B		=	((crgbtmp >> 3)<<11) & 0xF800;
	
			     rgb565[k++]	= 	(R | G | B);      
	
	            }
					k=k - width*2;
        }

	return 0;
}


#define YCbCrtoR(Y,Cb,Cr) (1000*Y + 1371*(Cr-128))/1000
#define YCbCrtoG(Y,Cb,Cr) (1000*Y - 336*(Cb-128) - 698*(Cr-128))/1000
#define YCbCrtoB(Y,Cb,Cr) (1000*Y + 1732*(Cb-128))/1000
#define min(x1, x2)   (((x1)<(x2))?(x1):(x2))
typedef unsigned char __u8;
typedef unsigned short __u16;
typedef unsigned int __u32;

__u32 Conv_YCbCr_Rgb(__u8 y0, __u8 y1, __u8 cb0, __u8 cr0)
{
	// bit order is
	// YCbCr = [Cr0 Y1 Cb0 Y0], RGB=[R1,G1,B1,R0,G0,B0].

	int r0, g0, b0, r1, g1, b1;
	__u16 rgb0, rgb1;
	__u32 rgb;

#if 1 // 4 frames/s @192MHz, 12MHz ; 6 frames/s @450MHz, 12MHz
	r0 = YCbCrtoR(y0, cb0, cr0);
	g0 = YCbCrtoG(y0, cb0, cr0);
	b0 = YCbCrtoB(y0, cb0, cr0);
	r1 = YCbCrtoR(y1, cb0, cr0);
	g1 = YCbCrtoG(y1, cb0, cr0);
	b1 = YCbCrtoB(y1, cb0, cr0);
#endif

	if (r0>255 ) r0 = 255;
	if (r0<0) r0 = 0;
	if (g0>255 ) g0 = 255;
	if (g0<0) g0 = 0;
	if (b0>255 ) b0 = 255;
	if (b0<0) b0 = 0;

	if (r1>255 ) r1 = 255;
	if (r1<0) r1 = 0;
	if (g1>255 ) g1 = 255;
	if (g1<0) g1 = 0;
	if (b1>255 ) b1 = 255;
	if (b1<0) b1 = 0;

	// 5:6:5 16bit format
	rgb0 = (((__u16)r0>>3)<<11) | (((__u16)g0>>2)<<5) | (((__u16)b0>>3)<<0); //RGB565.
	rgb1 = (((__u16)r1>>3)<<11) | (((__u16)g1>>2)<<5) | (((__u16)b1>>3)<<0); //RGB565.

	rgb = (rgb1<<16) | rgb0;

	return(rgb);
}


/*
yuv422转换RGB888并缩小一半图像的函数
yuv422buf: input width*height picture buffer
rgb888:    output width/2*height/2 picture RGB888 buffer
width:     input picture width
height:    input  picture height
*/
int yuv422rgb888_scale(unsigned char *yuv422buf,unsigned int *rgb888,int width,int height)
{
	int i, j, k, u, v, u2g, u2b, v2g, v2r, y11, y12;
	int width4 = width + (4 - (width%4))%4;
	unsigned int R,G,B;
  unsigned char *pucy,* pucu, * pucv;//, * pucraster0;
	char crgbtmp;
  if((yuv422buf==NULL)||(rgb888==NULL))
	{
		return -1;
	}
	if(inited == 0)
	{
			if(init_conver() < 0)
				{
					return -1;
				}
	}
	pucy = yuv422buf;
	pucu = yuv422buf + width * height;
	pucv = yuv422buf + width * height * 3/2;

	width		=	width/2;
	height	=	height/2;

	k	=	width * (height-1);		//Point to the last width_line of rgb565buf,why?
	for (i = 0; i < height; i++)
	{
    for (j = 0; j < width; j+=4)
		{

                y11 = tab_76309[*pucy++];
                y12 = tab_76309[*pucy++];
                u = *pucu++;
                v = *pucv++;
                u2g = cgu_tab[u];
                u2b = cbu_tab[u];
                v2g = cgv_tab[v];
                v2r = crv_tab[v];


		     crgbtmp	=	clp[(y11 + v2r)>>16];
		     R 		= 	crgbtmp ;
		     crgbtmp 	= 	clp[(y11 - u2g - v2g)>>16];	
		     G 		= 	crgbtmp ;	
		     crgbtmp	= 	clp[(y11 + u2b)>>16];	
		     B		=	  crgbtmp;
		     rgb888[k++]	= 	((R& 0x000000FF) | ((G << 8)& 0x0000FF00) | ((B << 16)& 0x00FF0000));      
	
		     crgbtmp	=	clp[(y12 + v2r)>>16];
		     R 		= 	crgbtmp ;

		     crgbtmp 	= 	clp[(y12 - u2g - v2g)>>16];	
		     G 		= 	crgbtmp ;	

		     crgbtmp	= 	clp[(y12 + u2b)>>16];	
		     B		=	 crgbtmp;

		     rgb888[k++]	= 	((R& 0x000000FF) | ((G << 8)& 0x0000FF00) | ((B << 16)& 0x00FF0000));       
		     
//Skip two pixels,because two pixels as a unit.
		     pucy+=2;
		     pucu++;
		     pucv++;

// Let two ALU work at the same time
                y11 = tab_76309[*pucy++];
                y12 = tab_76309[*pucy++];
                u = *pucu++;
                v = *pucv++;
                u2g = cgu_tab[u];
                u2b = cbu_tab[u];
                v2g = cgv_tab[v];
                v2r = crv_tab[v];

			     crgbtmp	=	clp[(y11 + v2r)>>16];
			     R 		= 	crgbtmp ;
	
			     crgbtmp 	= 	clp[(y11 - u2g - v2g)>>16];	
			     G 		= 	crgbtmp;	
	
			     crgbtmp	= 	clp[(y11 + u2b)>>16];	
			     B		=	crgbtmp;
	
			     rgb888[k++]	= 	((R& 0x000000FF) | ((G << 8)& 0x0000FF00) | ((B << 16)& 0x00FF0000));    
	
			     crgbtmp	=	clp[(y12 + v2r)>>16];
			     R 		= 	crgbtmp ;
			     crgbtmp 	= 	clp[(y12 - u2g - v2g)>>16];	
			     G 		= 	crgbtmp ;	
			     crgbtmp	= 	clp[(y12 + u2b)>>16];	
			     B		=	crgbtmp ;
	
			     rgb888[k++]	= 	((R& 0x000000FF) | ((G << 8)& 0x0000FF00) | ((B << 16)& 0x00FF0000));         
	
	//Skip two pixels,because two pixels as a unit.
			     pucy+=2;
			     pucu++;
			     pucv++;
	   	}

					k=k - width*2;
					pucy+=width4;				//Skip one width_line Y,U,V
					pucu+=width4/2;
					pucv+=width4/2;
    }

	return 0;
}

/*
yuv422转换RGB888图像的函数
yuv422buf: input width*height picture buffer
rgb888:    output width*height picture RGB888 buffer
width:     input picture width
height:    input  picture height
*/
int yuv422rgb888(unsigned char *yuv422buf,unsigned int *rgb888,int width,int height)
{
	int i, j, k, u, v, u2g, u2b, v2g, v2r, y11, y12;
	int width4 = width + (4 - (width%4))%4;
	unsigned int R,G,B;
  unsigned char *pucy,* pucu, * pucv;//, * pucraster0;
	char crgbtmp;
  if((yuv422buf==NULL)||(rgb888==NULL))
	{
		return -1;
	}
	if(inited == 0)
	{
			if(init_conver() < 0)
				{
					return -1;
				}
	}
	pucy = yuv422buf;
	pucu = yuv422buf + width * height;
	pucv = yuv422buf + width * height * 3/2;


	k	=	width * (height-1);		//Point to the last width_line of rgb565buf,why?
	for (i = 0; i < height; i++)
	{
    for (j = 0; j < width; j+=4)
		{

                y11 = tab_76309[*pucy++];
                y12 = tab_76309[*pucy++];
                u = *pucu++;
                v = *pucv++;
                u2g = cgu_tab[u];
                u2b = cbu_tab[u];
                v2g = cgv_tab[v];
                v2r = crv_tab[v];


		     crgbtmp	=	clp[(y11 + v2r)>>16];
		     R 		= 	crgbtmp ;
		     crgbtmp 	= 	clp[(y11 - u2g - v2g)>>16];	
		     G 		= 	crgbtmp ;	
		     crgbtmp	= 	clp[(y11 + u2b)>>16];	
		     B		=	  crgbtmp;
		     rgb888[k++]	= 	((R& 0x000000FF) | ((G << 8)& 0x0000FF00) | ((B << 16)& 0x00FF0000));      
	
		     crgbtmp	=	clp[(y12 + v2r)>>16];
		     R 		= 	crgbtmp ;

		     crgbtmp 	= 	clp[(y12 - u2g - v2g)>>16];	
		     G 		= 	crgbtmp ;	

		     crgbtmp	= 	clp[(y12 + u2b)>>16];	
		     B		=	 crgbtmp;

		     rgb888[k++]	= 	((R& 0x000000FF) | ((G << 8)& 0x0000FF00) | ((B << 16)& 0x00FF0000));       
		     
// Let two ALU work at the same time
                y11 = tab_76309[*pucy++];
                y12 = tab_76309[*pucy++];
                u = *pucu++;
                v = *pucv++;
                u2g = cgu_tab[u];
                u2b = cbu_tab[u];
                v2g = cgv_tab[v];
                v2r = crv_tab[v];

			     crgbtmp	=	clp[(y11 + v2r)>>16];
			     R 		= 	crgbtmp ;
	
			     crgbtmp 	= 	clp[(y11 - u2g - v2g)>>16];	
			     G 		= 	crgbtmp;	
	
			     crgbtmp	= 	clp[(y11 + u2b)>>16];	
			     B		=	crgbtmp;
	
			     rgb888[k++]	= 	((R& 0x000000FF) | ((G << 8)& 0x0000FF00) | ((B << 16)& 0x00FF0000));    
	
			     crgbtmp	=	clp[(y12 + v2r)>>16];
			     R 		= 	crgbtmp ;
			     crgbtmp 	= 	clp[(y12 - u2g - v2g)>>16];	
			     G 		= 	crgbtmp ;	
			     crgbtmp	= 	clp[(y12 + u2b)>>16];	
			     B		=	crgbtmp ;
	
			     rgb888[k++]	= 	((R& 0x000000FF) | ((G << 8)& 0x0000FF00) | ((B << 16)& 0x00FF0000));         
	
	   	}

					k=k - width;
    }

	return 0;
}

void FilterRGB(unsigned char *PixelsBuffer, int Width, int Height) {
	int i, j;
	unsigned char p, *p1, *p2, *p3, *p4;
	p1 = (unsigned char *) PixelsBuffer;
	p2 = p1 + 1;
	p3 = p1 + Width;
	p4 = p3 + 1;
	for (i = 0; i < Height - 1; i++) {
		for (j = 0; j < Width - 1; j++) {
			p = (*p1 + *p2++ + *p3++ + *p4++ + 2) / 4;
			*p1++ = p;
		}
		p1++;
		p2++;
		p3++;
		p4++;
	}
}


// convert 24bit rgb888 to 16bit rgb565 color format

static inline unsigned short rgb888torgb565(unsigned char red,unsigned char green, unsigned char blue)
{
	unsigned short  B = (blue >> 3) & 0x001F;
	unsigned short  G = ((green >> 2) << 5) & 0x07E0;
	unsigned short  R = ((red >> 3) << 11) & 0xF800;

	return (unsigned short) (R | G | B);
}

int rgb8882rgb565(unsigned short *rgb565,unsigned char *rgb888,unsigned int imagesize)
{
	unsigned int i,j;
	unsigned short R,G,B;
	for(i = 0; i < imagesize; ++i)
	{
		j = i * 3;
        	R = ((rgb888[j++] >> 3)<<11) & 0xF800;	//
       	G = ((rgb888[j++] >> 2)<<5) & 0x07E0; //
        	B = ((rgb888[j] >> 3)) & 0x001F;		
		rgb565[i] = R | G | B;
	}

	return 0;
}
/*
把rgb565src的图像宽度截取width
rgb565src：输入图像源
rgb565cut：截取后的输出图像数据
width：需要截取的宽度
imagesize：输入图像源的图像大小（这个数据是原始没有缩放的图像长度）
*/
int cut_rgb565(unsigned short *rgb565cut,unsigned short *rgb565src,unsigned int width,unsigned int imagesize)
{
	int i=0,j=0,n=-1,length=0;

	length = imagesize>>2;
	unsigned short *p_input		=	rgb565src;
	unsigned short *p_output	=	rgb565cut;	

  while(i < length)
	{
		if(0==(j%width))
			p_input +=  width;

		*p_output++ = *p_input++;
		 p_input++;
		 j+=2;
		 i++;
	}	

	return 0;
}


void rgb565_rotate90(const unsigned short *input, int width_in, int height_in,unsigned short *output)//, int *width_out, int *height_out)
{
        unsigned short *pIn=(unsigned short *)input;
        unsigned short *pOut=(unsigned short *)output;

        int i,j;

        for(i=0; i<height_in; i++)
        {
                for(j=0; j<width_in; j++)
                {
                        *pOut = *pIn++;
                        pOut = output+height_in*j + i;
                }
        }

//      *width_out = height_in;
//      *height_out = width_in;
}

/*************************
 *Translate the picture Right_Left.
 * ***********************/
void rgb565_folio(unsigned short *rgb565,int width,int height)
{
	printf("rgb565_folio\n");

	unsigned short *p;
	unsigned short *q;
	p = rgb565;
	q = p + width - 1;
	unsigned short ustmp;
	int x,y;

	for(y=1; y <= height; ++y)
	{
		for(x=0; x < width; ++x)
		{
			ustmp	=	*q;
			*q	=	*p;
			*p	=	ustmp;
			 q--;
			 p++;
		}
		p++;
		q=q+width;
	}
}

int  close_conver()
{
	if(clp != NULL)
		{
			clp -= 384;
			free(clp);
			clp=NULL;
		}
		inited = 0;
		return 0;
}
