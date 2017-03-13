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

static unsigned char* clp;
//modify by seven 2011-06-10
/*
static long int crv_tab[256];
static long int cbu_tab[256];
static long int cgu_tab[256];
static long int cgu_tab[256];
*/
static int crv_tab[256];
static int cbu_tab[256];
//static int cgu_tab[256];
static int cgu_tab[256];
static int cgv_tab[256];
//static long int tab_76309[256];
static int tab_76309[256];
static int bilevel_tab_76309[256];
BITMAPINFO  bmi;

static void init_clp() 
{
  int i;
  unsigned char clpbuf[1024]={0};
  clp = clpbuf;
  clp += 384;

  for (i=-384; i<640; i++)
    clp[i] = (i<0) ? 0 : ((i>255) ? 255 : i);
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

void init_player()
{
  init_dither_tab();
  init_clp();
  bmi.bmiHeader.biSize = (LONG)sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biCompression = 0l;
  bmi.bmiHeader.biSizeImage = 0l;
  bmi.bmiHeader.biXPelsPerMeter = 0l;
  bmi.bmiHeader.biYPelsPerMeter = 0l;
  bmi.bmiHeader.biBitCount = 24;
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

//modify by seven 2011-06-02
int yuv422rgb565(unsigned char *yuv422buf,unsigned short *rgb565,int width,int height)
{
	int i, j, k, u, v, u2g, u2b, v2g, v2r, y11, y12;
	int width4 = width + (4 - (width%4))%4;
	unsigned short R,G,B;
  	unsigned char *pucy,* pucu, * pucv;//, * pucraster0;
	char crgbtmp;

	pucy = yuv422buf;
	pucu = yuv422buf + width * height;
	pucv = yuv422buf + width * height * 3/2;

	width		=	width/2;
	height	=	height/2;

	init_player();		//Luck~

//	pucraster0 = rgb565 + (((width4/2) * (height-1)))*3;
	k	=	width * (height-1);		//Point to the last width_line of rgb565buf,why?
	#if 0
	for (i = 0; i<256;i++) {
		if (i%12==0)
			printf("\n");
		printf("tab_=[%d]\t",tab_76309[i]);
	}
	for (i = 0; i<256;i++) {
		if (i%12==0)
			printf("\n");	
		printf("cgu=[%d]\t",cgu_tab[i]);		
	}
	for (i = 0; i<256;i++) {
		if (i%12==0)
			printf("\n");	
		printf("cbu=[%d]\t",cbu_tab[i]);		
	}
	for (i = 0; i<256;i++) {
		if (i%12==0)
			printf("\n");	
		printf("cgv=[%d]\t",cgv_tab[i]);		
	}
	for (i = 0; i<256;i++) {
		
		if (i%12==0)
			printf("\n");	
		printf("crv=[%d]\t",crv_tab[i]);
	}	

	#endif
	
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

		
//modify by seven 2011-06-12
/*
                *pucraster0++ = clp[(y11 + u2b)>>16];			//B
                *pucraster0++ = clp[(y11 - u2g - v2g)>>16];		//G
                *pucraster0++ = clp[(y11 + v2r)>>16];			//R
*/
		     crgbtmp	=	clp[(y11 + v2r)>>16];
//		     R		=	((crgbtmp >> 3)<<11) & 0xF800;
		     R 		= 	((crgbtmp >> 3)) & 0x001F;
		     crgbtmp 	= 	clp[(y11 - u2g - v2g)>>16];	
		     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;	

		     crgbtmp	= 	clp[(y11 + u2b)>>16];	
//		     B 		= 	((crgbtmp >> 3)) & 0x001F;
		     B		=	((crgbtmp >> 3)<<11) & 0xF800;

		     rgb565[k++]	= 	(R | G | B);      

//modify by seven 2011-06-12
/*
                *pucraster0++ = clp[(y12 + u2b)>>16];
                *pucraster0++ = clp[(y12 - u2g - v2g)>>16];
                *pucraster0++ = clp[(y12 + v2r)>>16];
*/
	
		     crgbtmp	=	clp[(y12 + v2r)>>16];
//		     R		=	((crgbtmp >> 3)<<11) & 0xF800;
		     R 		= 	((crgbtmp >> 3)) & 0x001F;

		     crgbtmp 	= 	clp[(y12 - u2g - v2g)>>16];	
		     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;	

		     crgbtmp	= 	clp[(y12 + u2b)>>16];	
//		     B 		= 	((crgbtmp >> 3)) & 0x001F;
		     B		=	((crgbtmp >> 3)<<11) & 0xF800;

		     rgb565[k++]	= 	(R | G | B);      


//Skip two pixels,because two pixels as a unit.
		     pucy+=2;
		     pucu++;
		     pucv++;

//modify by seven 2011-06-10 Let two ALU work at the same time
                y11 = tab_76309[*pucy++];
                y12 = tab_76309[*pucy++];
                u = *pucu++;
                v = *pucv++;
                u2g = cgu_tab[u];
                u2b = cbu_tab[u];
                v2g = cgv_tab[v];
                v2r = crv_tab[v];
//modify by seven 2011-06-12
/*
                *pucraster0++ = clp[(y11 + u2b)>>16];			//R
                *pucraster0++ = clp[(y11 - u2g - v2g)>>16];		//G
                *pucraster0++ = clp[(y11 + v2r)>>16];			//B
*/
		     crgbtmp	=	clp[(y11 + v2r)>>16];
		     R 		= 	((crgbtmp >> 3)) & 0x001F;

		     crgbtmp 	= 	clp[(y11 - u2g - v2g)>>16];	
		     G 		= 	((crgbtmp >> 2)<<5) & 0x07E0;	

		     crgbtmp	= 	clp[(y11 + u2b)>>16];	
		     B		=	((crgbtmp >> 3)<<11) & 0xF800;

		     rgb565[k++]	= 	(R | G | B);      

//modify by seven 2011-06-12
/*
                *pucraster0++ = clp[(y12 + u2b)>>16];
                *pucraster0++ = clp[(y12 - u2g - v2g)>>16];
                *pucraster0++ = clp[(y12 + v2r)>>16];
*/	
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

//modify by seven 2011-06-12
//          pucraster0 = pucraster0 - width4*3;	//Back two lines to start store new datas.

		k=k - width*2;
		pucy+=width4;				//Skip one width_line Y,U,V
		pucu+=width4/2;
		pucv+=width4/2;
        }

	return 0;
}

//modify by seven 2011-06-02
// convert 24bit rgb888 to 16bit rgb565 color format

static inline unsigned short rgb888torgb565(unsigned char red,unsigned char green, unsigned char blue)
{
	unsigned short  B = (blue >> 3) & 0x001F;
	unsigned short  G = ((green >> 2) << 5) & 0x07E0;
	unsigned short  R = ((red >> 3) << 11) & 0xF800;

	return (unsigned short) (R | G | B);
}

//modify by seven 2011-06-02
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
//modify by seven 2011-06-02
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

//modify by seven 2011-0612
void rgb565_rotate90(
const unsigned short *input, int width_in, int height_in,
        unsigned short *output, int *width_out, int *height_out)
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

	*width_out = height_in;
      *height_out = width_in;
}

//modify by seven 2011-06-22
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
