#include "bf3703.h"
#include "twi_s.h"
#include "system_gpio.h"


#define BF3703_ADDRESS		    0x6e
#define BF3703_IMG_WIDTH            640
#define BF3703_IMG_HEIGHT           480
#define BF3703_IMG_WIDTH_WITH_DATA  (0+BF3703_IMG_WIDTH)
#define BF3703_IMG_HEIGHT_WITH_DATA (0+BF3703_IMG_HEIGHT)
#define BF3703_IMG_SIZE             (BF3703_IMG_WIDTH*BF3703_IMG_HEIGHT)
#define BF3703_IMG_SIZE_WITH_DATA   (BF3703_IMG_WIDTH_WITH_DATA*BF3703_IMG_HEIGHT_WITH_DATA)


#define RegTable_size(table) (sizeof(table)/sizeof(table[0]))

typedef struct sensor_conf{
	u8 reg;
	u8 value;
	u8 delay_ms;
}sensor_conf;

static  const struct sensor_conf BF3703_reg[] =
{
  {0x15,0x22},//VSYNC = VSYNC_DAT		0x15[5] = 1	  
  {0x09,0x01},//0x01 ,standby
  {0x12,0x01},//0x01	VGA RAW Bayer RGB mode
  {0x3a,0x00},//0x00 
  //{0x1e,0x10},//Vertically flip
  {0xf1,0x28},
  {0x13,0x00},//关闭AEC和AGC
  {0x01,0x00},
  {0x02,0x00},
  //{0x8c,0x01},
  //{0x8d,0x32},
  {0x8c,0x00},
  {0x8d,0x2D},//曝光时间约3ms
  {0x87,0x20},//模拟增益设置到32
  //{0x13,0x05},
  {0x05,0x1f},
  {0x06,0x60},
  {0x14,0x20},
  {0x27,0x03},
  {0x06,0xe0},
  {0x11,0x40},//MCLK=XCLK
  {0x2a,0x00},//0x2a和0x2b是设置dummy pix。设置为16，是为了把每一行的pix设置到800。
  {0x2b,0x10},//这样一来，MCLK为24MHz时，每一行的时间就为1/15ms，方便计算。
  {0x9e,0x4c},
  {0x9e,0x3f},
  {0x92,225},//0x92和0x93,设置VSYNC后插入行。，这里设置为225行，也就是15ms
  {0x93,0x00},
  {0xe3,0x2D},//0x92和0x93,设置VSYNC前插入行。这里保持与初次设置的曝光时间一样。
  {0xe4,0x00},
  {0xeb,0x30},
  {0xbb,0x20},
  {0Xf5,0x21},
  {0Xe1,0X3c},
  {0X16,0x03},
  {0X2f,0Xf6},
  {0x33,0x20},
  {0x34,0x08},
  {0x35,0x56},
  {0x65,0x58},
  {0x66,0x52},
  {0x36,0x05},
  {0x37,0xc0},
  {0x38,0x46},
  {0x9b,0xf6},
  {0x9c,0x46},
  {0xbc,0x01},
  {0xbd,0xf6},
  {0xbe,0x46},
  {0x82,0x14},
  {0x83,0x23},
  {0x9a,0x23},
  {0x70,0x6f},
  {0x72,0x2f},
  {0x73,0x2f},
  {0x74,0x29},
  {0x77,0x90},
  {0x7a,0x26},
  {0x7b,0x30},
  {0x84,0x1a},
  {0x85,0x20},
  {0x89,0x02},
  {0x8a,0x64},
  {0x86,0x30},
  {0x96,0xa6},
  {0x97,0x0c},
  {0x98,0x18},
  {0x80,0x54},
  {0x24,0x88},
  {0x25,0x78},
  {0x69,0x20},
  {0x94,0x0a},
  {0X1F,0x20},
  {0X22,0x20},
  {0X26,0x20},
  {0x56,0x40},
  {0x61,0xd3},
  {0x79,0x48},
  {0x3b,0x60},
  {0x3c,0x28},
  {0x39,0x80},
  {0x3f,0xc0},
  {0x40,0X60},
  {0x41,0X60},
  {0x42,0X66},
  {0x43,0X57},
  {0x44,0X4c},
  {0x45,0X43},
  {0x46,0X3c},
  {0x47,0X37},
  {0x48,0X33},
  {0x49,0X2f},
  {0x4b,0X2c},
  {0x4c,0X29},
  {0x4e,0X25},
  {0x4f,0X22},
  {0x50,0X20},
  {0x6a,0x00},
  {0x23,0x00},
  {0xa0,0x03},
  {0x06,0xe0},
  {0x8e,0x01},
  {0x8f,0xfe},//{0xb6,0x20},//{0xb7,0x20},//{0xb8,0x20},{0xb9,0xc0}
  //{0xb9,0x80}
};

//设置图像传感器曝光时间
void BF3703_SetExposure(u16 exposure)
{
    u8 reg_val=0;
    
    // Integration time MSB 0x8c, stores the higher 8 bits of exposure time.
    // Integration time LSB 0x8d, stores the lower 8 bits of exposure time.
    reg_val=(u8)(exposure>>8);
    TWI_Write(TWI1, 0x6e, 0x8c, 1, &reg_val, 1);
    reg_val=(u8)(exposure&0xff);
    TWI_Write(TWI1, 0x6e, 0x8d, 1, &reg_val, 1);
}

void BF3703_SetAnalogGain(u16 gain)		  //set global gain register
{
  u8 reg_val=0;

  reg_val=(u8)MIN(0x3F,MAX(0x00,gain)); // Limit the value between 0 ~ 63
  TWI_Write(TWI1, 0x6e, 0x87, 1, &reg_val, 1);
}

//设置图像传感器帧率
void BF3703_SetDummyLine(u16 dummy_lines)
{
    u8 reg_val=0;

    // Dummy lines insert before active line MSB 0xe4, stores the higher 8 bits of dummy lines.
    // Dummy lines insert before active line LSB 0xe3, stores the lower 8 bits of dummy lines.
    reg_val=(u8)(dummy_lines>>8);
    TWI_Write(TWI1, 0x6e, 0xe4, 1, &reg_val, 1);
    reg_val=(u8)(dummy_lines&0xff);
    TWI_Write(TWI1, 0x6e, 0xe3, 1, &reg_val, 1);
}

u32 BF3703_GetExposure(void)		   
{
    u8 string[2]={0};
    u16 reg_val=0;
    
    TWI_Read(TWI1, 0x6e, 0x8c, 1, &(string[0]), 1);
    TWI_Read(TWI1, 0x6e, 0x8d, 1, &(string[1]), 1);
         
	reg_val =  string[1]; 			//lsb 8bit
	reg_val |= ((string[0]<<8));	//hsb 	     
	return (u32)reg_val;
}

u32 BF3703_GetAnalogGain(void)
{
	u8 reg_val=0;
    
    TWI_Read(TWI1, 0x6e, 0x87, 1, &reg_val, 1);   
	return (u32)reg_val;
}

//u32 BF3703_GetCurrentBin(void)
//{
//	u8 reg_val=0;
//    
//    TWI_Read(TWI1, 0x6e, 0x88, 1, &reg_val, 1);   
//	return (u32)reg_val;
//}

u32 BF3703_GetCurrentBin(u8* p_data)
{
	u32 BIN_NUM=256;
	u32 GREY_LEVEL=256;
	u32 IMG_STEP=4;
	u32 HIST_STEP=GREY_LEVEL/BIN_NUM;
	u32 width=0;
	u32 height=0;
	u32 w_offset=0;
	u32 h_offset=0;
	u32 w_start=0;
	u32 w_end=0;
	u32 h_start=0;
	u32 h_end=0;
	u8* data_addr=p_data; 
	u32 hist_temp[256]={0};
	u32 sum=0;
	u32 pix_num=0;
	u32 i=0,j=0;
	
	width=BF3703_IMG_WIDTH;
	height=BF3703_IMG_HEIGHT;
	w_offset=0;
	h_offset=0;
	w_start=0;
	w_end=width;
	h_start=0;
	h_end=height;
	
	// 1. 先创建一个256级的histogram，并对原图像下采样1/4 * 1/4 统计。
	memset(hist_temp,0,GREY_LEVEL*sizeof(u32));
	for(j=h_start;j<h_end;j+=IMG_STEP)
		for(i=w_start;i<w_end;i+=IMG_STEP)
			hist_temp[data_addr[i+j*width]]++;
	
	// 计算当前256级别下的Bin值
	for(i=0;i<GREY_LEVEL;i++)
	{
		sum+=(hist_temp[i]*i);	// 计算total sum的直方图。
		pix_num+=hist_temp[i];	// 计算pixel计入计算的总数。
	}
	sum=(sum/pix_num);
	
//	// 计算64级别下的Bin值
//	sum=(sum>>2);//((sum/GREY_LEVEL)*BIN_NUM)
	
	// 返回量程为256的图像bin值
	return sum;	
}

u32 BF3703_GetCurrentBin_80Per(u8* p_data)
{
	u32 BIN_NUM=256;
	u32 GREY_LEVEL=256;
	u32 IMG_STEP=4;
	u32 HIST_STEP=GREY_LEVEL/BIN_NUM;
	u32 width=0;
	u32 height=0;
	u32 w_offset=0;
	u32 h_offset=0;
	u32 w_start=0;
	u32 w_end=0;
	u32 h_start=0;
	u32 h_end=0;
	u8* data_addr=p_data; 
	u32 hist_temp[256]={0};
	u32 sum=0;
	u32 pix_num=0;
	u32 i=0,j=0;
	
	width=BF3703_IMG_WIDTH;
	height=BF3703_IMG_HEIGHT;
	w_offset=width*(20-19)/20;
	h_offset=height*(20-19)/20;
	w_start=w_offset;
	w_end=width-w_offset;
	h_start=h_offset;
	h_end=height-h_offset;
	
	// 1. 先创建一个256级的histogram，并对原图像下采样1/4 * 1/4 统计。
	memset(hist_temp,0,GREY_LEVEL*sizeof(u32));
	for(j=h_start;j<h_end;j+=IMG_STEP)
		for(i=w_start;i<w_end;i+=IMG_STEP)
			hist_temp[data_addr[i+j*width]]++;
	
	// 计算当前256级别下的Bin值
	for(i=0;i<GREY_LEVEL;i++)
	{
		sum+=(hist_temp[i]*i);	// 计算total sum的直方图。
		pix_num+=hist_temp[i];	// 计算pixel计入计算的总数。
	}
	sum=(sum/pix_num);
	
//	// 计算64级别下的Bin值
//	sum=(sum>>2);//((sum/GREY_LEVEL)*BIN_NUM)
	
	// 返回量程为256的图像bin值
	return sum;
}

void BF3703_AE_Enable(void)
{
  u8 reg_val=0;
  
  reg_val = 0x05;
  TWI_Write(TWI1, 0x6e, 0x13, 1, &reg_val, 1);
}

void BF3703_AE_Disable(void)
{
  u8 reg_val=0;
  
  reg_val = 0x00;
  TWI_Write(TWI1, 0x6e, 0x13, 1, &reg_val, 1);
}

void BF3703_ExitStandby(void)
{
//    u8 reg_val=0;
//    u32 delay=0;
  
//  // Software Power Down
//  reg_val = 0x01;
//  TWI_Write(TWI1, 0x6e, 0x09, 1, &reg_val, 1);
    // Hardware Power Down
    PIO_Clear(&Pin_ISI_PWDN);// 1:pwdn mode
}

void BF3703_EnterStandby(void)
{
//  u8 reg_val=0;
//  u32 delay=0;
//  // Software Power Up  
//    reg_val = 0x11;
//    TWI_Write(TWI1, 0x6e, 0x09, 1, &reg_val, 1);
    // Hardware Power Up  
    PIO_Set(&Pin_ISI_PWDN);// 0:normal mode
}

/*********************************************************************************
Function:       BF3703_GetHistogram()
Description:    Fetch Histogram based on the image info area and loaded into a
				existing histo array
Input:          u32 	bin_num
         		u8* 	pImgData
Output:			u32*	_hist
Return:         None
Create Date:	2014/09/09
Last Update:	None
**********************************************************************************/
void BF3703_GetHistogram(u32* _hist, u32 bin_num, u8* pImgData)
{
	u32 BIN_NUM=bin_num;
	u32 GREY_LEVEL=256;
	u32 IMG_STEP=4;
	u32 HIST_STEP=GREY_LEVEL/BIN_NUM;
	u32 width=BF3703_IMG_WIDTH;
	u32 height=BF3703_IMG_HEIGHT;
	u8* data_addr=pImgData; 
	u32 hist_temp[256]={0};
	u32 temp=0;
	u32 i=0,j=0;
	
	// 1. 先创建一个256级的histogram，并对原图像下采样1/4 * 1/4 统计。
	memset(hist_temp,0,GREY_LEVEL*sizeof(u32));
	for(j=0;j<height;j+=IMG_STEP)
		for(i=0;i<width;i+=IMG_STEP)
			hist_temp[data_addr[i+j*width]]++;
	// 2. 将256级的临时histogram降入64级
	for(i=0;i<BIN_NUM;i++)
	{
		temp=0;
		for(j=0;j<HIST_STEP;j++)
			temp+=hist_temp[i*HIST_STEP+j];
		// 每4个256级的元素，组成一个64级元素
		_hist[i]=temp;
	}
	return;
}

void BF3703_Init(void)
{
  uint32_t i;
  uint8_t tmp_val;// read for check 
  volatile uint32_t delay;//need use volatile？

  for (i = 0; i < RegTable_size(BF3703_reg); i++)  
  {
    //TWI_Write(Twi *pTwi, uint8_t address, uint32_t iaddress, uint8_t isize, uint8_t *pData, uint32_t num)
    TWI_Write(TWI1, 0x6e, BF3703_reg[i].reg, 1, (u8*)&(BF3703_reg[i].value), 1);
  } 	
}

void BF3703_WriteRegister(u8 reg_addr,u8 reg_val)
{
  TWI_Write(TWI1, 0x6e, reg_addr, 1, &reg_val, 1);
}

void BF3703_Reset(void)
{
  u8 reg_val=0;
  u32 delay=0;
  
  reg_val = 0x10;
  TWI_Write(TWI1, 0x6e, 0x12, 1, &reg_val, 1);
}
