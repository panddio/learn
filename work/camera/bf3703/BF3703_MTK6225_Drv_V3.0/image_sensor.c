/****************************BF3703_BYD_VGA_Sensor***************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2010
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*****************************************************************************
 *
 * Filename:
 * ---------
 *   image_sensor.c
 *
 * Version:
 * --------
 *   BF3703 MTK 6225 or 6226 DRV V1.0.0
 *
 * Release Date:
 * ------------
 *   2010-07-26
 *
 * Description:
 * ------------
 *   Image sensor driver function
 *
 * Author:
 * BYD Sensor Group
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================

 ****************************************************************************/
#include "drv_comm.h"
#include "IntrCtrl.h"
#include "reg_base.h"
#include "gpio_sw.h"
#include "sccb.h"
#include "isp_if.h"
#include "image_sensor.h"
#include "camera_para.h"
#include "upll_ctrl.h"
#include "med_api.h"

#define BF3703_BYD			{ 128, 0 }

/* Global Valuable */
SensorInfo g_CCT_MainSensor=BF3703_BYD;// must be defined but not referenced by YUV driver
kal_uint8 g_CCT_FirstGrabColor = INPUT_ORDER_CbYCrY1;   // must be defined but not referenced by YUV driver
kal_uint8  start_grab_x_offset=0, start_grab_y_offset=0;
kal_bool   gVGAmode=KAL_TRUE, sensor_night_mode=KAL_FALSE, MPEG4_encode_mode=KAL_FALSE, g_bMJPEG_mode = KAL_FALSE;
kal_uint8  preview_pclk_division=0, capture_pclk_division=0;
kal_uint16 dummy_pixels=0,pre_dummy_pixels=0,cap_dummy_pixels=0,dummy_lines=0, extra_exposure_lines=0;
kal_uint16 exposure_lines=0;

/* MAX/MIN Explosure Lines Used By AE Algorithm */
kal_uint16 MAX_EXPOSURE_LINES=1000;
kal_uint8  MIN_EXPOSURE_LINES=2;
/* Parameter For Engineer mode function */
kal_uint32 FAC_SENSOR_REG;
/* Image Sensor ID */
kal_uint16 sensor_id=0;

kal_bool sensor_cap_state=KAL_FALSE;

#ifndef HW_SCCB

void SCCB_send_byte(kal_uint8 send_byte)
{
	volatile signed char i;
	volatile kal_uint32 j;

	for (i=7;i>=0;i--)
	{	/* data bit 7~0 */
		if (send_byte & (1<<i))
		{
			SET_SCCB_DATA_HIGH;
		}
		else
		{
			SET_SCCB_DATA_LOW;
		}
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		SET_SCCB_CLK_HIGH;
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		SET_SCCB_CLK_LOW;
		for(j=0;j<SENSOR_I2C_DELAY;j++);
	}
	/* don't care bit, 9th bit */
	SET_SCCB_DATA_LOW;
	SET_SCCB_DATA_INPUT;
	SET_SCCB_CLK_HIGH;
	for(j=0;j<SENSOR_I2C_DELAY;j++);
	SET_SCCB_CLK_LOW;
	SET_SCCB_DATA_OUTPUT;
}	/* SCCB_send_byte() */

kal_uint8 SCCB_get_byte(void)
{
	volatile signed char i;
	volatile kal_uint32 j;
	kal_uint8 get_byte=0;

	SET_SCCB_DATA_INPUT;

	for (i=7;i>=0;i--)
	{	/* data bit 7~0 */
		SET_SCCB_CLK_HIGH;
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		if (GET_SCCB_DATA_BIT)
			get_byte |= (1<<i);
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		SET_SCCB_CLK_LOW;
		for(j=0;j<SENSOR_I2C_DELAY;j++);
	}
	/* don't care bit, 9th bit */
	SET_SCCB_DATA_OUTPUT;
	SET_SCCB_DATA_HIGH;
	for(j=0;j<SENSOR_I2C_DELAY;j++);
	SET_SCCB_CLK_HIGH;
	for(j=0;j<SENSOR_I2C_DELAY;j++);
	SET_SCCB_CLK_LOW;

	return get_byte;
}	/* SCCB_get_byte() */

#endif

void write_cmos_sensor(kal_uint32 addr, kal_uint32 para)
{
	volatile kal_uint32 j;
	
	#ifdef HW_SCCB
		SET_SCCB_DATA_LENGTH(3);
		ENABLE_SCCB;
		REG_SCCB_DATA = BF3703_WRITE_ID | SCCB_DATA_REG_ID_ADDRESS;
		REG_SCCB_DATA = addr;
		REG_SCCB_DATA = para;
		while (SCCB_IS_WRITTING) {};
	#else
		I2C_START_TRANSMISSION;
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		SCCB_send_byte(BF3703_WRITE_ID);
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		SCCB_send_byte(addr);
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		SCCB_send_byte(para);
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		I2C_STOP_TRANSMISSION;
	#endif /* HW_SCCB */
}	/* write_cmos_sensor() */

kal_uint32 read_cmos_sensor(kal_uint32 addr)
{
	volatile kal_uint32 j;
	kal_uint8 get_byte=0;
	
	#ifdef HW_SCCB
		SET_SCCB_DATA_LENGTH(2);
		ENABLE_SCCB;
		REG_SCCB_DATA = BF3703_WRITE_ID | SCCB_DATA_REG_ID_ADDRESS;
		REG_SCCB_DATA = addr;
		while (SCCB_IS_WRITTING) {};
		ENABLE_SCCB;
		REG_SCCB_DATA = BF3703_READ_ID | SCCB_DATA_REG_ID_ADDRESS;
		REG_SCCB_DATA=0;
		while (SCCB_IS_READING) {};
		get_byte = REG_SCCB_READ_DATA & 0xFF;
	#else
		I2C_START_TRANSMISSION;
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		SCCB_send_byte(BF3703_WRITE_ID);
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		SCCB_send_byte(addr);
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		I2C_STOP_TRANSMISSION;
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		I2C_START_TRANSMISSION;
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		SCCB_send_byte(BF3703_READ_ID);
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		get_byte=SCCB_get_byte();
		for(j=0;j<SENSOR_I2C_DELAY;j++);
		I2C_STOP_TRANSMISSION;
	#endif

	return get_byte;
}	/* read_cmos_sensor() */

void write_BF3703_shutter(kal_uint16 shutter)
{			 
	write_cmos_sensor(0x8c,(shutter&0xFF00)>>8);
	write_cmos_sensor(0x8D,shutter&0xFF);
}	/* write_BF3703_shutter */

kal_uint16 read_BF3703_shutter(void)
{
	kal_uint8 temp_reg1, temp_reg2;
	kal_uint16 shutter;

	temp_reg1=read_cmos_sensor(0x8c);
	temp_reg2=read_cmos_sensor(0x8d);
	
	shutter=((temp_reg1&0xff)<<8)|(temp_reg2);
	exposure_lines=shutter;

	return exposure_lines;
}	/* read_BF3703_shutter */

void set_BF3703_dummy(kal_uint16 pixels, kal_uint16 lines)
{
	write_cmos_sensor(0x2A,((pixels&0x700)>>4));
	write_cmos_sensor(0x2B,(pixels&0xFF));
	write_cmos_sensor(0x92,(lines&0xFF));
	write_cmos_sensor(0x93,((lines&0xFF00)>>8));
}	/* set_BF3703_dummy */



/*************************************************************************
* FUNCTION
*	init_BF3703
*
* DESCRIPTION
*	This function initialize the registers of CMOS sensor and ISP control register.
*
* PARAMETERS
*	None
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_int8 init_BF3703(void)
{
	kal_uint8 I;
	cis_module_power_on(KAL_TRUE);      // Power On CIS Power
	kal_sleep_task(2);
	PWRDN_PIN_LOW;

	/* Sensor Signal Polarity */
	/* Note: Set HSync Polarity to Low means High active */
	SET_CMOS_CLOCK_POLARITY_LOW;
	SET_VSYNC_POLARITY_LOW;
	SET_HSYNC_POLARITY_LOW;    
	kal_sleep_task(2);

	/* YUV Sensor Input Format */
	ENABLE_CAMERA_INDATA_FORMAT;  /* Enable yuv data input */
	SET_CAMERA_INPUT_TYPE(INPUT_YUV422);
	SET_CAMERA_INPUT_ORDER(INPUT_ORDER_CrYCbY1);

	/* Use UPLL to produce 48M clock, then divided by 2 */
	ENABLE_CAMERA_TG_CLK_48M;
	UPLL_Enable(UPLL_OWNER_ISP);    	
	set_isp_driving_current(camera_para.SENSOR.reg[CMMCLK_CURRENT_INDEX].para);

	/* Reset the sensor */
	RESET_PIN_HIGH;
	RESET_PIN_LOW;
	for (I = 0; I < 0x80; I++);
	RESET_PIN_HIGH;
	kal_sleep_task(10);

	sensor_id=(read_cmos_sensor(0xFC)<<8)|read_cmos_sensor(0xFD);
	kal_prompt_trace(MOD_MMI,"------->>>> BF3703 sensor_id==%x",sensor_id);
	
	if(sensor_id != BF3703_SENSOR_ID)
	return -1;
	kal_sleep_task(10);

	write_cmos_sensor(0x11,0x80);
	write_cmos_sensor(0x09,0x00);
	write_cmos_sensor(0x13,0x00);
	write_cmos_sensor(0x01,0x13);
	write_cmos_sensor(0x02,0x25);
	write_cmos_sensor(0x8c,0x02);//01 :devided by 2  02 :devided by 1
	write_cmos_sensor(0x8d,0xfd);//cb: devided by 2  fd :devided by 1
	write_cmos_sensor(0x87,0x1a);
	write_cmos_sensor(0x13,0x07);

	//POLARITY of Signal
	write_cmos_sensor(0x15,0x40);
	write_cmos_sensor(0x3a,0x03);		

	//black level ,对上电偏绿有改善,如果需要请选择使用
	/*
	write_cmos_sensor(0x05,0x1f);
	write_cmos_sensor(0x06,0x60);
	write_cmos_sensor(0x14,0x1f);
	write_cmos_sensor(0x27,0x03);
	write_cmos_sensor(0x06,0xe0);
	*/

	//lens shading
	write_cmos_sensor(0x35,0x68);
	write_cmos_sensor(0x65,0x68);
	write_cmos_sensor(0x66,0x62);
	write_cmos_sensor(0x36,0x05);
	write_cmos_sensor(0x37,0xf6);
	write_cmos_sensor(0x38,0x46);
	write_cmos_sensor(0x9b,0xf6);
	write_cmos_sensor(0x9c,0x46);
	write_cmos_sensor(0xbc,0x01);
	write_cmos_sensor(0xbd,0xf6);
	write_cmos_sensor(0xbe,0x46);

	//AE
	write_cmos_sensor(0x82,0x14);
	write_cmos_sensor(0x83,0x23);
	write_cmos_sensor(0x9a,0x23);//the same as 0x83
	write_cmos_sensor(0x84,0x1a);
	write_cmos_sensor(0x85,0x20);
	write_cmos_sensor(0x89,0x04);//02 :devided by 2  04 :devided by 1
	write_cmos_sensor(0x8a,0x08);//04: devided by 2  05 :devided by 1
	write_cmos_sensor(0x86,0x28);//the same as 0x7b
	write_cmos_sensor(0x96,0xa6);//AE speed
	write_cmos_sensor(0x97,0x0c);//AE speed
	write_cmos_sensor(0x98,0x18);//AE speed
	//AE target
	write_cmos_sensor(0x24,0x7a);//灯箱测试  0x6a
	write_cmos_sensor(0x25,0x8a);//灯箱测试  0x7a
	write_cmos_sensor(0x94,0x0a);//INT_OPEN  
	write_cmos_sensor(0x80,0x55);

	//denoise 
	write_cmos_sensor(0x70,0x6f);//denoise
	write_cmos_sensor(0x72,0x4f);//denoise
	write_cmos_sensor(0x73,0x2f);//denoise
	write_cmos_sensor(0x74,0x27);//denoise
	write_cmos_sensor(0x77,0x90);//去除格子噪声
	write_cmos_sensor(0x7a,0x4e);//denoise in	  low light,0x8e\0x4e\0x0e
	write_cmos_sensor(0x7b,0x28);//the same as 0x86

	//black level
	write_cmos_sensor(0X1F,0x20);//G target
	write_cmos_sensor(0X22,0x20);//R target
	write_cmos_sensor(0X26,0x20);//B target
	//模拟部分参数
	write_cmos_sensor(0X16,0x00);//如果觉得黑色物体不够黑，有点偏红，将0x16写为0x03会有点改善		
	write_cmos_sensor(0xbb,0x20);	// deglitch  对xclk整形
	write_cmos_sensor(0xeb,0x30);
	write_cmos_sensor(0xf5,0x21);
	write_cmos_sensor(0xe1,0x3c);
	write_cmos_sensor(0xbb,0x20);
	write_cmos_sensor(0X2f,0X66);
	write_cmos_sensor(0x06,0xe0);



	//anti black sun spot
	write_cmos_sensor(0x61,0xd3);//0x61[3]=0 black sun disable
	write_cmos_sensor(0x79,0x48);//0x79[7]=0 black sun disable

	//contrast
	write_cmos_sensor(0x56,0x40);

	//Gamma

	write_cmos_sensor(0x3b,0x60);//auto gamma offset adjust in  low light	  
	write_cmos_sensor(0x3c,0x20);//auto gamma offset adjust in  low light	  

	write_cmos_sensor(0x39,0x80);	  
	/*//gamma1
	write_cmos_sensor(0x3f,0xb0);
	write_cmos_sensor(0X40,0X88);
	write_cmos_sensor(0X41,0X74);
	write_cmos_sensor(0X42,0X5E);
	write_cmos_sensor(0X43,0X4c);
	write_cmos_sensor(0X44,0X44);
	write_cmos_sensor(0X45,0X3E);
	write_cmos_sensor(0X46,0X39);
	write_cmos_sensor(0X47,0X35);
	write_cmos_sensor(0X48,0X31);
	write_cmos_sensor(0X49,0X2E);
	write_cmos_sensor(0X4b,0X2B);
	write_cmos_sensor(0X4c,0X29);
	write_cmos_sensor(0X4e,0X25);
	write_cmos_sensor(0X4f,0X22);
	write_cmos_sensor(0X50,0X1F);*/

	/*gamma2	过曝过度好，高亮度
	write_cmos_sensor(0x3f,0xb0);
	write_cmos_sensor(0X40,0X9b);
	write_cmos_sensor(0X41,0X88);
	write_cmos_sensor(0X42,0X6e);
	write_cmos_sensor(0X43,0X59);
	write_cmos_sensor(0X44,0X4d);
	write_cmos_sensor(0X45,0X45);
	write_cmos_sensor(0X46,0X3e);
	write_cmos_sensor(0X47,0X39);
	write_cmos_sensor(0X48,0X35);
	write_cmos_sensor(0X49,0X31);
	write_cmos_sensor(0X4b,0X2e);
	write_cmos_sensor(0X4c,0X2b);
	write_cmos_sensor(0X4e,0X26);
	write_cmos_sensor(0X4f,0X23);
	write_cmos_sensor(0X50,0X1F);
	*/
	/*//gamma3 清晰亮丽 灰阶分布好
	write_cmos_sensor(0X3f,0Xb0);
	write_cmos_sensor(0X40,0X60);
	write_cmos_sensor(0X41,0X60);
	write_cmos_sensor(0X42,0X66);
	write_cmos_sensor(0X43,0X57);
	write_cmos_sensor(0X44,0X4c);
	write_cmos_sensor(0X45,0X43);
	write_cmos_sensor(0X46,0X3c);
	write_cmos_sensor(0X47,0X37);
	write_cmos_sensor(0X48,0X33);
	write_cmos_sensor(0X49,0X2f);
	write_cmos_sensor(0X4b,0X2c);
	write_cmos_sensor(0X4c,0X29);
	write_cmos_sensor(0X4e,0X25);
	write_cmos_sensor(0X4f,0X22);
	write_cmos_sensor(0X50,0X20);*/

	//gamma 4   low noise   
	write_cmos_sensor(0X3f,0Xa8);
	write_cmos_sensor(0X40,0X48);
	write_cmos_sensor(0X41,0X54);
	write_cmos_sensor(0X42,0X4E);
	write_cmos_sensor(0X43,0X44);
	write_cmos_sensor(0X44,0X3E);
	write_cmos_sensor(0X45,0X39);
	write_cmos_sensor(0X46,0X35);
	write_cmos_sensor(0X47,0X31);
	write_cmos_sensor(0X48,0X2E);
	write_cmos_sensor(0X49,0X2B);
	write_cmos_sensor(0X4b,0X29);
	write_cmos_sensor(0X4c,0X27);
	write_cmos_sensor(0X4e,0X23);
	write_cmos_sensor(0X4f,0X20);
	write_cmos_sensor(0X50,0X20);


	//color matrix
	write_cmos_sensor(0x51,0x0d);
	write_cmos_sensor(0x52,0x21);
	write_cmos_sensor(0x53,0x14);
	write_cmos_sensor(0x54,0x15);
	write_cmos_sensor(0x57,0x8d);
	write_cmos_sensor(0x58,0x78);
	write_cmos_sensor(0x59,0x5f);
	write_cmos_sensor(0x5a,0x84);
	write_cmos_sensor(0x5b,0x25);
	write_cmos_sensor(0x5D,0x95);
	write_cmos_sensor(0x5C,0x0e);

	/* 

	// color	艳丽
	write_cmos_sensor(0x51,0x0e);
	write_cmos_sensor(0x52,0x16);
	write_cmos_sensor(0x53,0x07);
	write_cmos_sensor(0x54,0x1a);
	write_cmos_sensor(0x57,0x9d);
	write_cmos_sensor(0x58,0x82);
	write_cmos_sensor(0x59,0x71);
	write_cmos_sensor(0x5a,0x8d);
	write_cmos_sensor(0x5b,0x1c);
	write_cmos_sensor(0x5D,0x95);
	write_cmos_sensor(0x5C,0x0e);
	//  

	//适中
	write_cmos_sensor(0x51,0x08);
	write_cmos_sensor(0x52,0x0E);
	write_cmos_sensor(0x53,0x06);
	write_cmos_sensor(0x54,0x12);
	write_cmos_sensor(0x57,0x82);
	write_cmos_sensor(0x58,0x70);
	write_cmos_sensor(0x59,0x5C);
	write_cmos_sensor(0x5a,0x77);
	write_cmos_sensor(0x5b,0x1B);
	write_cmos_sensor(0x5c,0x0e);//0x5c[3:0] low light color coefficient，smaller ,lower noise
	write_cmos_sensor(0x5d,0x95);


	//color 淡
	write_cmos_sensor(0x51,0x03);
	write_cmos_sensor(0x52,0x0d);
	write_cmos_sensor(0x53,0x0b);
	write_cmos_sensor(0x54,0x14);
	write_cmos_sensor(0x57,0x59);
	write_cmos_sensor(0x58,0x45);
	write_cmos_sensor(0x59,0x41);
	write_cmos_sensor(0x5a,0x5f);
	write_cmos_sensor(0x5b,0x1e);
	write_cmos_sensor(0x5c,0x0e);//0x5c[3:0] low light color coefficient，smaller ,lower noise
	write_cmos_sensor(0x5d,0x95);
	*/

	write_cmos_sensor(0x60,0x20);//color open in low light 
	//AWB
	write_cmos_sensor(0x6a,0x01);//如果肤色偏色，将0x6a写为0x81.
	write_cmos_sensor(0x23,0x66);//Green gain
	write_cmos_sensor(0xa0,0x07);//0xa0写0x03，黑色物体更红；0xa0写0x07，黑色物体更黑；

	write_cmos_sensor(0xa1,0X41);//
	write_cmos_sensor(0xa2,0X0e);
	write_cmos_sensor(0xa3,0X26);
	write_cmos_sensor(0xa4,0X0d);
	//冷色调
	write_cmos_sensor(0xa5,0x28);//The upper limit of red gain 

	/*暖色调
	write_cmos_sensor(0xa5,0x2d);
	*/
	write_cmos_sensor(0xa6,0x04);
	write_cmos_sensor(0xa7,0x80);//BLUE Target
	write_cmos_sensor(0xa8,0x80);//RED Target
	write_cmos_sensor(0xa9,0x28);
	write_cmos_sensor(0xaa,0x28);
	write_cmos_sensor(0xab,0x28);
	write_cmos_sensor(0xac,0x3c);
	write_cmos_sensor(0xad,0xf0);
	write_cmos_sensor(0xc8,0x18);
	write_cmos_sensor(0xc9,0x20);
	write_cmos_sensor(0xca,0x17);
	write_cmos_sensor(0xcb,0x1f);
	write_cmos_sensor(0xaf,0x00);			
	write_cmos_sensor(0xc5,0x18);		
	write_cmos_sensor(0xc6,0x00);
	write_cmos_sensor(0xc7,0x20);		
	write_cmos_sensor(0xae,0x83);//如果照户外偏蓝，将此寄存器0xae写为0x81。
	write_cmos_sensor(0xcc,0x30);
	write_cmos_sensor(0xcd,0x70);
	write_cmos_sensor(0xee,0x4c);// P_TH

	// color saturation
	write_cmos_sensor(0xb0,0xd0);
	write_cmos_sensor(0xb1,0xc0);
	write_cmos_sensor(0xb2,0xb0);

	/* // 饱和度艳丽
	write_cmos_sensor(0xb1,0xd0);
	write_cmos_sensor(0xb2,0xc0);		
	*/
	write_cmos_sensor(0xb3,0x88);

	//anti webcamera banding
	write_cmos_sensor(0x9d,0x4c);

	//switch direction
	write_cmos_sensor(0x1e,0x00);//00:normal  10:IMAGE_V_MIRROR   20:IMAGE_H_MIRROR  30:IMAGE_HV_MIRROR

	return 1;
	
		/* init_cmos_sensor() */
}
/*************************************************************************
* FUNCTION
*	power_off_BF3703
*
* DESCRIPTION
*	This function is to turn off sensor module power.
*
* PARAMETERS
*	None
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/

void power_off_BF3703(void)
{
	cis_module_power_on(KAL_FALSE);      // Power Off CIS Power
	UPLL_Disable(UPLL_OWNER_ISP);
	#ifndef HW_SCCB
	   SET_SCCB_CLK_LOW;
	   SET_SCCB_DATA_LOW;
	#endif
}	/* power_off_BF3703 */

/*************************************************************************
* FUNCTION
*	get_BF3703_id
*
* DESCRIPTION
*	This function return the sensor read/write id of SCCB interface.
*
* PARAMETERS
*	*sensor_write_id : address pointer of sensor write id
*  *sensor_read_id  : address pointer of sensor read id
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
void get_BF3703_id(kal_uint8 *sensor_write_id, kal_uint8 *sensor_read_id)
{
	*sensor_write_id=BF3703_WRITE_ID;
	*sensor_read_id=BF3703_READ_ID;
}	/* get_BF3703_id */

/*************************************************************************
* FUNCTION
*	get_BF3703_size
*
* DESCRIPTION
*	This function return the image width and height of image sensor.
*
* PARAMETERS
*	*sensor_width : address pointer of horizontal effect pixels of image sensor
*  *sensor_height : address pointer of vertical effect pixels of image sensor
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
void get_BF3703_size(kal_uint16 *sensor_width, kal_uint16 *sensor_height)
{
	*sensor_width=IMAGE_SENSOR_VGA_WIDTH;			/* pixel numbers actually used in one frame */
	*sensor_height=IMAGE_SENSOR_VGA_HEIGHT;		/* line numbers actually used in one frame */
}	/* get_BF3703_size */

/*************************************************************************
* FUNCTION
*	get_BF3703_period
*
* DESCRIPTION
*	This function return the image width and height of image sensor.
*
* PARAMETERS
*	*pixel_number : address pointer of pixel numbers in one period of HSYNC
*  *line_number : address pointer of line numbers in one period of VSYNC
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
void get_BF3703_period(kal_uint16 *pixel_number, kal_uint16 *line_number)
{
	*pixel_number=VGA_PERIOD_PIXEL_NUMS;		/* pixel numbers in one period of HSYNC */
	*line_number=VGA_PERIOD_LINE_NUMS;			/* line numbers in one period of VSYNC */
}	/* get_BF3703_period */

void BF3703_preview(image_sensor_exposure_window_struct *image_window, image_sensor_config_struct *sensor_config_data)
{

	sensor_cap_state=KAL_FALSE;
	g_bMJPEG_mode = KAL_FALSE;

	write_cmos_sensor(0x11,0x80);	//MCLK = PCLK

	if((sensor_config_data->isp_op_mode==ISP_MJPEG_PREVIEW_MODE)||(sensor_config_data->isp_op_mode==ISP_MJPEG_ENCODE_MODE))
	{   //MT6225 video mode
		
		MPEG4_encode_mode=KAL_FALSE;
		g_bMJPEG_mode = KAL_TRUE;

		/* config TG of ISP to match the setting of image sensor*/
		SET_TG_OUTPUT_CLK_DIVIDER(3);			
		SET_CMOS_RISING_EDGE(0);
		SET_CMOS_FALLING_EDGE(2);
		ENABLE_CAMERA_PIXEL_CLKIN_ENABLE;
		SET_TG_PIXEL_CLK_DIVIDER(3);
		SET_CMOS_DATA_LATCH(2);

		pre_dummy_pixels=32;
		dummy_lines=32;//anti_flicker 32:devided by 2   103: devided by 1	

	}
	else
	{
		if(sensor_config_data->frame_rate==0x0F)		// MPEG4 Encode Mode
		{
			//MT6226 video mode 
			kal_prompt_trace(MOD_MMI," BF3703  video");
			MPEG4_encode_mode=KAL_TRUE;

			/* config TG of ISP to match the setting of image sensor*/
			SET_TG_OUTPUT_CLK_DIVIDER(3);
			SET_CMOS_RISING_EDGE(0);
			SET_CMOS_FALLING_EDGE(2);
			ENABLE_CAMERA_PIXEL_CLKIN_ENABLE;
			SET_TG_PIXEL_CLK_DIVIDER(3);
			SET_CMOS_DATA_LATCH(2);

			pre_dummy_pixels=32;
			dummy_lines=32;//anti_flicker 32:devided by 2   103: devided by 1	
		}
		else
		{

			kal_prompt_trace(MOD_MMI," BF3703  preview");
			MPEG4_encode_mode=KAL_FALSE;

			/* config TG of ISP to match the setting of image sensor*/
			SET_TG_OUTPUT_CLK_DIVIDER(1);			
			SET_CMOS_RISING_EDGE(0);
			SET_CMOS_FALLING_EDGE(1);
			ENABLE_CAMERA_PIXEL_CLKIN_ENABLE;
			SET_TG_PIXEL_CLK_DIVIDER(1);
			SET_CMOS_DATA_LATCH(1);

			pre_dummy_pixels=32;
			dummy_lines=64;//anti_flicker 32:devided by 2   64: devided by 1	
		}
	}

	preview_pclk_division=((DRV_Reg32(ISP_TG_PHASE_COUNTER_REG)&0xF0)>>4)+1;

	image_window->grab_start_x=IMAGE_SENSOR_VGA_INSERTED_PIXELS;
	image_window->grab_start_y=IMAGE_SENSOR_VGA_INSERTED_LINES+start_grab_y_offset;
	image_window->exposure_window_width=IMAGE_SENSOR_VGA_WIDTH;
	image_window->exposure_window_height=IMAGE_SENSOR_VGA_HEIGHT-1;	
	
	set_BF3703_dummy(pre_dummy_pixels,dummy_lines);
	write_BF3703_shutter(exposure_lines); 

	if (sensor_config_data->isp_op_mode == ISP_MJPEG_ENCODE_MODE) 
	{
	;
	}else 
	{
	// ISP_MJPEG_ENCODE_MODE mode does not invok YUV setting API after preview function
	// If turn on AEC/AGC/AWB in ISP_MJPEG_ENCODE_MODE mode, the AWB setting will be overwriten.
	write_cmos_sensor(0x13, 0x07);	// Turn ON AEC/AGC/AWB
	}
	
	kal_sleep_task(30);
		
}
void BF3703_capture(image_sensor_exposure_window_struct *image_window, image_sensor_config_struct *sensor_config_data)
{
	volatile kal_uint32 shutter=exposure_lines;

	sensor_cap_state=KAL_TRUE;
	
	if(sensor_config_data->enable_shutter_tansfer==KAL_TRUE)
		shutter=sensor_config_data->capture_shutter;
			
	if(!(sensor_config_data->frame_rate==0xF0))	// If not WEBCAM mode.
	{
		kal_prompt_trace(MOD_MMI,"Not WEBCAM MODE");  

	    write_cmos_sensor(0x13,0xE2);  // Turn OffF AGC/AEC
	    
	    shutter=read_BF3703_shutter();
	}
	    	
	if ((image_window->image_target_width<IMAGE_SENSOR_1M_WIDTH)&&
		(image_window->image_target_height<IMAGE_SENSOR_1M_HEIGHT))
	{	/* Less than VGA Mode */
		if (image_window->digital_zoom_factor>=(ISP_DIGITAL_ZOOM_INTERVAL<<1))
		{
			kal_prompt_trace(MOD_MMI,"BF3703 ZOOM ");

			write_cmos_sensor(0x11,0xB0);

			SET_TG_PIXEL_CLK_DIVIDER(7);
			SET_CMOS_DATA_LATCH(4);
			cap_dummy_pixels=VGA_PERIOD_PIXEL_NUMS/4;
			dummy_lines=0;
		}
		else
		{
			if(sensor_config_data->frame_rate==0xF0)	//  WEBCAM  Preview mode.
			{
				write_cmos_sensor(0x11,0x90);

				SET_TG_PIXEL_CLK_DIVIDER(1);
				SET_CMOS_DATA_LATCH(1);

				start_grab_x_offset=0;
				start_grab_y_offset=0;
				cap_dummy_pixels=0;
				dummy_lines=0;
			}
			else
			{
				kal_prompt_trace(MOD_MMI,"BF3703 Capture");

				write_cmos_sensor(0x11,0x90);
			    
				SET_TG_PIXEL_CLK_DIVIDER(3);//3
				SET_CMOS_DATA_LATCH(2);
				cap_dummy_pixels=0;

			}
		}
			
			capture_pclk_division=((DRV_Reg32(ISP_TG_PHASE_COUNTER_REG)&0xF0)>>4)+1;
			
			shutter=(shutter*preview_pclk_division)/capture_pclk_division;
			shutter=(shutter*(VGA_PERIOD_PIXEL_NUMS+pre_dummy_pixels))/(VGA_PERIOD_PIXEL_NUMS+cap_dummy_pixels);
			if(shutter<1)
			shutter=1;
		}

	if ((image_window->image_target_width>=IMAGE_SENSOR_1M_WIDTH)&&
			(image_window->image_target_height>=IMAGE_SENSOR_1M_HEIGHT))
	{

		write_cmos_sensor(0x11,0x90);

		SET_TG_PIXEL_CLK_DIVIDER(3); 
		SET_CMOS_DATA_LATCH(2);

		cap_dummy_pixels=1000;
		capture_pclk_division=((DRV_Reg32(ISP_TG_PHASE_COUNTER_REG)&0xF0)>>4)+1;

		shutter=(shutter*preview_pclk_division)/capture_pclk_division;
		shutter=(shutter*(VGA_PERIOD_PIXEL_NUMS+pre_dummy_pixels))/((VGA_PERIOD_PIXEL_NUMS+cap_dummy_pixels));
		if(shutter<1)
		shutter=1;
	 }
			
	image_window->grab_start_x=IMAGE_SENSOR_VGA_INSERTED_PIXELS;
	image_window->grab_start_y=IMAGE_SENSOR_VGA_INSERTED_LINES;
	image_window->exposure_window_width=IMAGE_SENSOR_VGA_WIDTH;
	image_window->exposure_window_height=IMAGE_SENSOR_VGA_HEIGHT-1; // minus 1 to avoid the last black line


	set_BF3703_dummy(cap_dummy_pixels,dummy_lines);
	write_BF3703_shutter(shutter);
	
}	/* BF3703_capture() */

/*************************************************************************
* FUNCTION
*	write_BF3703_reg
*
* DESCRIPTION
*	This function set the register of BF3703.
*
* PARAMETERS
*	addr : the register index of BF3703
*  para : setting parameter of the specified register of BF3703
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
void write_BF3703_reg(kal_uint32 addr, kal_uint32 para)
{
	write_cmos_sensor(addr,para);
}	/* write_BF3703_reg() */

/*************************************************************************
* FUNCTION
*	read_cmos_sensor
*
* DESCRIPTION
*	This function read parameter of specified register from BF3703.
*
* PARAMETERS
*	addr : the register index of BF3703
*
* RETURNS
*	the data that read from BF3703
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 read_BF3703_reg(kal_uint32 addr)
{
	return (read_cmos_sensor(addr));
}	/* read_BF3703_reg() */

/*************************************************************************
* FUNCTION
*	set_BF3703_shutter
*
* DESCRIPTION
*	This function set e-shutter of BF3703 to change exposure time.
*
* PARAMETERS
*	shutter : exposured lines
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
void set_BF3703_shutter(kal_uint16 shutter)
{
	exposure_lines=shutter;
	write_BF3703_shutter(shutter); 
}	/* set_BF3703_shutter */

/*************************************************************************
* FUNCTION
*	set_BF3703_gain
*
* DESCRIPTION
*	This function is to set global gain to sensor.
*
* PARAMETERS
*	gain : sensor global gain(base: 0x40)
*
* RETURNS
*	the actually gain set to sensor.
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint16 set_BF3703_gain(kal_uint16 gain)
{
   return gain;
}

/*************************************************************************
* FUNCTION
*	BF3703_night_mode
*
* DESCRIPTION
*	This function night mode of BF3703.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
void BF3703_night_mode(kal_bool enable)
{

	if (enable)
	{
		if (g_bMJPEG_mode||MPEG4_encode_mode)
		{
			// this mode is used by MT6225 or MT6226 video Night mode
			write_cmos_sensor(0X85, 0X2a);
			write_cmos_sensor(0X86, 0X30);
			write_cmos_sensor(0x7b, 0x30);		
			write_cmos_sensor(0x8e, 0x07);//Min fps =4	07 分频  0e 不分频
			write_cmos_sensor(0x8f, 0x79);// 79 分频   F2 不分频

		}
		else
		{  
			// this mode is used by camera Night mode
			write_cmos_sensor(0X85, 0X2a);
			write_cmos_sensor(0X86, 0X30);
			write_cmos_sensor(0x7b, 0x30);		
			write_cmos_sensor(0x8e, 0x0E);//Min fps =4  07 分频  0e 不分频
			write_cmos_sensor(0x8f, 0xF2);// 79 分频   F2 不分频     			                                                                                			                
		}

	}
	else
	{
		if (g_bMJPEG_mode||MPEG4_encode_mode)
		{
			// this mode is used by MT6225 or MT6226 video Normal mode
			write_cmos_sensor(0x8e, 0x03);
			write_cmos_sensor(0x8f, 0xbc);
		}
		else
		{  
			// this mode is used by camera  Normal mode 
			write_cmos_sensor(0x8e, 0x07);// MIN FPS=8  03 分频  07 不分频
			write_cmos_sensor(0x8f, 0x79);// bc 分频   79 不分频   			                                                                                			                
		}
	}	
	
}/* BF3703_night_mode */

/*************************************************************************
* FUNCTION
*	set_BF3703_flashlight
*
* DESCRIPTION
*	turn on/off BF3703 flashlight .
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
void set_BF3703_flashlight(kal_bool enable)
{
	// Todo
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_zoom
*
* DESCRIPTION
*	BF3703 zoom setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_zoom(kal_uint32 para)
{
	return KAL_FALSE;
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_contrast
*
* DESCRIPTION
*	BF3703 contrast setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_contrast(kal_uint32 para)
{
	// Not Support
	return KAL_FALSE;	
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_brightness
*
* DESCRIPTION
*	BF3703 brightness setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_brightness(kal_uint32 para)
{
	// Not Support
	return KAL_FALSE;	
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_hue
*
* DESCRIPTION
*	BF3703 hue setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_hue(kal_uint32 para)
{
	// Not Support
	return KAL_FALSE;	
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_gamma
*
* DESCRIPTION
*	BF3703 gamma setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_gamma(kal_uint32 para)
{
	return KAL_FALSE;	
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_wb
*
* DESCRIPTION
*	BF3703 wb setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_wb(kal_uint32 para)
{
	kal_uint8  temp_reg;	
	temp_reg=read_cmos_sensor(0x13);

	switch (para)
	{
		case CAM_WB_AUTO:
			kal_prompt_trace(MOD_MMI,"------->>>AWB");
			write_cmos_sensor(0x01,0x15);
			write_cmos_sensor(0x02,0x24);
			write_cmos_sensor(0x13,temp_reg|0x2);   // Enable AWB		
			break;

		case CAM_WB_CLOUD:
			write_cmos_sensor(0x13,temp_reg&~0x2);  // Disable AWB				
			write_cmos_sensor(0x01,0x10);
			write_cmos_sensor(0x02,0x28);			
			break;		

		case CAM_WB_DAYLIGHT:
			write_cmos_sensor(0x13,temp_reg&~0x2);  // Disable AWB				
			write_cmos_sensor(0x01,0x13);
			write_cmos_sensor(0x02,0x26);
			break;		

		case CAM_WB_INCANDESCENCE:
			write_cmos_sensor(0x13,temp_reg&~0x2);  // Disable AWB				
			write_cmos_sensor(0x01,0x1f);
			write_cmos_sensor(0x02,0x15);
			break;		

		case CAM_WB_FLUORESCENT:
			write_cmos_sensor(0x13,temp_reg&~0x2);  // Disable AWB				
			write_cmos_sensor(0x01,0x1a);
			write_cmos_sensor(0x02,0x1e);
			break;		

		case CAM_WB_TUNGSTEN:
			write_cmos_sensor(0x13,temp_reg&~0x2);  // Disable AWB				
			write_cmos_sensor(0x01,0x1a);
			write_cmos_sensor(0x02,0x0d);
			break;

		case CAM_WB_MANUAL:		
		    // TODO
			break;		

		default:
			return KAL_FALSE;	
	}

	return KAL_TRUE;
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_exposure
*
* DESCRIPTION
*	BF3703 exposure setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_exposure(kal_uint32 para)
{
	switch (para)
	{
		case CAM_EV_NEG_4_3:    
            write_cmos_sensor(0x55, 0xF8);		
			break;		
		case CAM_EV_NEG_3_3:
            write_cmos_sensor(0x55, 0xD8);
			break;		
		case CAM_EV_NEG_2_3:
            write_cmos_sensor(0x55, 0xB8);
			break;				
		case CAM_EV_NEG_1_3:
            write_cmos_sensor(0x55, 0x98);
			break;				
		case CAM_EV_ZERO:
            write_cmos_sensor(0x55, 0x00);
			break;				
		case CAM_EV_POS_1_3:
            write_cmos_sensor(0x55, 0x18);
			break;				
		case CAM_EV_POS_2_3:
            write_cmos_sensor(0x55, 0x38);
			break;				
		case CAM_EV_POS_3_3:
            write_cmos_sensor(0x55, 0x58);
			break;				
		case CAM_EV_POS_4_3:	
            write_cmos_sensor(0x55, 0x78);
			break;
		default:
			return KAL_FALSE;    
	}	
	return KAL_TRUE;	
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_effect
*
* DESCRIPTION
*	BF3703 effect setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_effect(kal_uint32 para)
{
    kal_uint32  ret = KAL_TRUE;
    
    kal_prompt_trace(MOD_MMI,"---->>effect");
	
	switch (para)
	{	
		case CAM_EFFECT_ENC_NORMAL:
			write_cmos_sensor(0x80,0x45);		
			write_cmos_sensor(0x76,0x00);
			write_cmos_sensor(0x69,0x00);		
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);
			break;		
		case CAM_EFFECT_ENC_GRAYSCALE:	
			write_cmos_sensor(0x80,0x45);		
			write_cmos_sensor(0x76,0x00);
			write_cmos_sensor(0x69,0x20);		
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);	
			break;		
		case CAM_EFFECT_ENC_SEPIA:		
			write_cmos_sensor(0x80,0x45);		
			write_cmos_sensor(0x76,0x00);
			write_cmos_sensor(0x69,0x20);		
			write_cmos_sensor(0x67,0x60);		
			write_cmos_sensor(0x68,0x98);	
			break;		
		case CAM_EFFECT_ENC_COLORINV:	
			write_cmos_sensor(0x80,0x45);		
			write_cmos_sensor(0x76,0x00);
			write_cmos_sensor(0x69,0x40);		
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);	
			break;		
		case CAM_EFFECT_ENC_SEPIAGREEN:		
			write_cmos_sensor(0x80,0x45);		
			write_cmos_sensor(0x76,0x00);
			write_cmos_sensor(0x69,0x20);		
			write_cmos_sensor(0x67,0x40);		
			write_cmos_sensor(0x68,0x40);	
			break;					
		case CAM_EFFECT_ENC_SEPIABLUE:	
			write_cmos_sensor(0x80,0x45);		
			write_cmos_sensor(0x76,0x00);
			write_cmos_sensor(0x69,0x20);		
			write_cmos_sensor(0x67,0xA0);		
			write_cmos_sensor(0x68,0x40);
			break;								
		case CAM_EFFECT_ENC_GRAYINV:	
			write_cmos_sensor(0x80,0x45);		
			write_cmos_sensor(0x76,0x00);
			write_cmos_sensor(0x69,0x20);		
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);				
			break;								
		case CAM_EFFECT_ENC_COPPERCARVING:
			write_cmos_sensor(0x69,0x00);
			write_cmos_sensor(0x80,0xc5);
			write_cmos_sensor(0x76,0xc0);
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);   	
			break;								
    	case CAM_EFFECT_ENC_BLUECARVING:
			write_cmos_sensor(0x69,0x00);
			write_cmos_sensor(0x80,0xc5);	
			write_cmos_sensor(0x76,0xd0);
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);
			break;								
		case CAM_EFFECT_ENC_CONTRAST:	
			write_cmos_sensor(0x80,0x45);		
			write_cmos_sensor(0x76,0x00);
			write_cmos_sensor(0x69,0x00);		
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);
			break;							
		case CAM_EFFECT_ENC_EMBOSSMENT:
			write_cmos_sensor(0x69,0x00);
			write_cmos_sensor(0x80,0xc5);	
			write_cmos_sensor(0x77,0x80);
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);
			break;
		case CAM_EFFECT_ENC_SKETCH:
			write_cmos_sensor(0x69,0x00);
			write_cmos_sensor(0x80,0xc5);		
			write_cmos_sensor(0x76,0xb0);
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);
			break;	
		case CAM_EFFECT_ENC_BLACKBOARD:
			write_cmos_sensor(0x69,0x00);
			write_cmos_sensor(0x80,0xc5);		
			write_cmos_sensor(0x76,0xe0);
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);
			break;
		case CAM_EFFECT_ENC_WHITEBOARD:
			write_cmos_sensor(0x69,0x00);
			write_cmos_sensor(0x80,0xc5);		
			write_cmos_sensor(0x76,0xf0);
			write_cmos_sensor(0x67,0x80);		
			write_cmos_sensor(0x68,0x80);
			break;
		case CAM_EFFECT_ENC_JEAN:
		case CAM_EFFECT_ENC_OIL:			
		default:
			ret = KAL_FALSE;
	}

	return ret;
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_banding
*
* DESCRIPTION
*	BF3703 banding setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_banding(kal_uint32 para)
{
	kal_uint8 temp_Reg_80,temp_Reg_2a,temp_Reg_2b;
	kal_uint16 dummy_pixels_banding;

	temp_Reg_80=read_cmos_sensor(0x80);
	temp_Reg_2a=read_cmos_sensor(0x2a);
	temp_Reg_2b=read_cmos_sensor(0x2b);
	dummy_pixels_banding=((temp_Reg_2a&0xF0)<<4)|(temp_Reg_2b);

	kal_prompt_trace(MOD_MMI,"------>>Banding");

	switch (para)
	{
		case CAM_BANDING_50HZ:
			if(g_bMJPEG_mode||MPEG4_encode_mode)   // video , MCLK=12M
			{			
				write_cmos_sensor(0x80,temp_Reg_80); 
				write_cmos_sensor(0x9d,60000/(784+dummy_pixels_banding));
			}
			else
			{
				write_cmos_sensor(0x80,temp_Reg_80);
				write_cmos_sensor(0x9d,120000/(784+dummy_pixels_banding));
			}
				break;                        
		case CAM_BANDING_60HZ:
			if(g_bMJPEG_mode||MPEG4_encode_mode)   //video , MCLK=12M
			{			
				write_cmos_sensor(0x80,temp_Reg_80&0xFE);	
				write_cmos_sensor(0x9e,6000000/(784+dummy_pixels_banding)/120);
			}
			else
			{
				write_cmos_sensor(0x80,temp_Reg_80&0xFE);	
				write_cmos_sensor(0x9e,12000000/(784+dummy_pixels_banding)/120);
			}
			break;
		default:
			return KAL_FALSE;	
		}

	return KAL_TRUE;
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_saturation
*
* DESCRIPTION
*	BF3703 SATURATION setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_saturation(kal_uint32 para)
{
    // Not Support
	return KAL_FALSE;	
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_nightmode
*
* DESCRIPTION
*	BF3703 night mode setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_nightmode(kal_uint32 para)
{
	BF3703_night_mode((kal_bool)para);
	return KAL_TRUE;	
}

/*************************************************************************
* FUNCTION
*	set_BF3703_param_ev
*
* DESCRIPTION
*	BF3703 ev setting.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 set_BF3703_param_ev(kal_uint32 para)
{
	return set_BF3703_param_exposure(para);
}

/*************************************************************************
* FUNCTION
*	BF3703_yuv_sensor_setting
*
* DESCRIPTION
*	This function send command and parameter to yuv sensor module BF3703
*  to configure it
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
kal_uint32 BF3703_yuv_sensor_setting(kal_uint32 cmd, kal_uint32 para)
{
	kal_uint32 ret = KAL_TRUE;
	switch (cmd)
	{
		case CAM_PARAM_ZOOM_FACTOR:
			ret = set_BF3703_param_zoom(para);		
			break;			
		case CAM_PARAM_CONTRAST:
			ret = set_BF3703_param_contrast(para);		
			break;					
		case CAM_PARAM_BRIGHTNESS:
			ret = set_BF3703_param_brightness(para);		
			break;							
		case CAM_PARAM_HUE:
			ret = set_BF3703_param_hue(para);		
			break;							
		case CAM_PARAM_GAMMA:
			ret = set_BF3703_param_gamma(para);		
			break;							
		case CAM_PARAM_WB:
			ret = set_BF3703_param_wb(para);		
			break;
		case CAM_PARAM_EXPOSURE:
			ret = set_BF3703_param_exposure(para);		
			break;							
		case CAM_PARAM_EFFECT:
			ret = set_BF3703_param_effect(para);
			break;		
		case CAM_PARAM_BANDING:
			ret = set_BF3703_param_banding(para);		
			break;		
		case CAM_PARAM_SATURATION:
			ret = set_BF3703_param_saturation(para);				
			break;						
		case CAM_PARAM_NIGHT_MODE:
			ret = set_BF3703_param_nightmode(para);				
			break;						
		case CAM_PARAM_EV_VALUE:
			ret = set_BF3703_param_ev(para);				
			break;				
		default:
			ret = KAL_FALSE;
	}
	return ret;
}

/*************************************************************************
* FUNCTION
*	image_sensor_func_BF3703
*
* DESCRIPTION
*	BF3703 Image Sensor functions struct.
*
* PARAMETERS
*	none
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
image_sensor_func_struct image_sensor_func_BF3703=
{
	init_BF3703,
	get_BF3703_id,
	get_BF3703_size,
	get_BF3703_period,
	BF3703_preview,
	BF3703_capture,
	write_BF3703_reg,
	read_BF3703_reg,
	set_BF3703_shutter,
	BF3703_night_mode,
	power_off_BF3703,
	set_BF3703_gain,
	set_BF3703_flashlight,
	BF3703_yuv_sensor_setting
};	/* image_sensor_func_BF3703 */

/*************************************************************************
* FUNCTION
*	cam_module_func_config
*
* DESCRIPTION
*	This function maps the external camera module function API structure.
*
* PARAMETERS
*
* RETURNS
*	None
*
* GLOBALS AFFECTED
*
*************************************************************************/
void image_sensor_func_config(void)
{
	image_sensor_func=&image_sensor_func_BF3703;
}	/* cam_module_func_config() */

// write camera_para to sensor register
void camera_para_to_sensor(void)
{
}

// update camera_para from sensor register
void sensor_to_camera_para(void)
{
}

//------------------------Engineer mode---------------------------------

void  get_sensor_group_count(kal_int32* sensor_count_ptr)
{
}

void get_sensor_group_info(kal_uint16 group_idx, kal_int8* group_name_ptr, kal_int32* item_count_ptr)
{
}

void get_sensor_item_info(kal_uint16 group_idx,kal_uint16 item_idx, ENG_sensor_info* info_ptr)
{
}

kal_bool set_sensor_item_info(kal_uint16 group_idx, kal_uint16 item_idx, kal_int32 item_value)
{

	return KAL_TRUE;
}
