/****************************BF3403_BYD_VGA_Sensor***************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
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
 *   image_sensor.h
 *
 * Version:
 * --------
 *   BF3703 MTK 6225 or 6226 DRV V1.0.0
 *
 * Release Date:
 * ------------
 *   2010-07-08
 *
 * Description:
 * ------------
 *   CMOS sensor header file
 *
 * Author:
 * -------
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
#ifndef _IMAGE_SENSOR_H
#define _IMAGE_SENSOR_H

	#include "isp_if.h"
	
	//------------------------Engineer mode---------------------------------
	
	#define FACTORY_START_ADDR 70
	
	typedef enum group_enum {
	   AWB_GAIN=0,
	   PRE_GAIN,
	   SENSOR_DBLC,
	   GAMMA_ENABLE,
	   CMMCLK_CURRENT,
	   FRAME_RATE_LIMITATION,
	   REGISTER_EDITOR,
	   GROUP_TOTAL_NUMS
	} FACTORY_CCT_GROUP_ENUM;
	
	typedef enum register_index {
	   AWB_GAIN_R_INDEX=FACTORY_START_ADDR,
	   AWB_GAIN_B_INDEX,
	   SENSOR_DBLC_INDEX,
	   GAMMA_ENABLE_INDEX,
	   CMMCLK_CURRENT_INDEX,	   
	   FACTORY_END_ADDR
	} FACTORY_REGISTER_INDEX;
	
	typedef enum cct_register_index {
	   GLOBAL_GAIN_INDEX=0,
	   PRE_GAIN_R_INDEX,
	   PRE_GAIN_B_INDEX,
	   CCT_END_ADDR
	} CCT_REGISTER_INDEX;
	
	typedef struct
	{
	   kal_uint8   item_name_ptr[50];         // item name
	   kal_int32	item_value;                // item value
	   kal_bool    is_true_false;             // is this item for enable/disable functions
	   kal_bool	   is_read_only;              // is this item read only
	   kal_bool	   is_need_restart;           // after set this item need restart
	   kal_int32	min;                       // min value of item value	
	   kal_int32	max;                       // max value of item value	
	} ENG_sensor_info;
	
	// API FOR ENGINEER FACTORY MODE
	void  get_sensor_group_count(kal_int32* sensor_count_ptr);
	void  get_sensor_group_info(kal_uint16 group_idx, kal_int8* group_name_ptr, kal_int32* item_count_ptr);
	void  get_sensor_item_info(kal_uint16 group_idx,kal_uint16 item_idx, ENG_sensor_info* info_ptr);
	kal_bool set_sensor_item_info(kal_uint16 group_idx, kal_uint16 item_idx, kal_int32 item_value);
	
	//------------------------Engineer mode---------------------------------
	
	typedef struct {
		kal_uint32	addr;
		kal_uint32	para;
	} sensor_reg_struct;
	
	typedef struct {
		sensor_reg_struct	reg[FACTORY_END_ADDR];
		sensor_reg_struct	cct[CCT_END_ADDR];
	} sensor_data_struct;
	
	// write camera_para to sensor register 
	void camera_para_to_sensor(void);
	// update camera_para from sensor register 
	void sensor_to_camera_para(void);
	// config sensor callback function 
	void image_sensor_func_config(void);
	// Compact Image Sensor Module Power ON/OFF
	void cis_module_power_on(kal_bool on);
	
	/* HW PRODUCE I2C SIGNAL TO CONTROL SENSOR REGISTER */
	//#define HW_SCCB
	
	/* OUTPUT DEBUG INFO. BY UART */
	//#define OUTPUT_DEBUG_INFO

	typedef enum _SENSOR_TYPE {
		CMOS_SENSOR=0,
		CCD_SENSOR
	} SENSOR_TYPE;

	typedef struct {
		kal_uint16		id;
		SENSOR_TYPE		type;
	} SensorInfo;

	/* MAXIMUM EXPLOSURE LINES USED BY AE */
	extern kal_uint16 MAX_EXPOSURE_LINES;
	extern kal_uint8  MIN_EXPOSURE_LINES;
	/* AE CONTROL CRITERION */
	extern kal_uint8  AE_AWB_CAL_PERIOD;
	extern kal_uint8  AE_GAIN_DELAY_PERIOD;
	extern kal_uint8  AE_SHUTTER_DELAY_PERIOD;

	/* DEFINITION USED BY CCT */
	extern SensorInfo	g_CCT_MainSensor;
	extern kal_uint8	g_CCT_FirstGrabColor;

	/* CAMERA PREVIEW FRAME RATE DEFINITION */
	#define CAM_PREVIEW_15FPS
	//	#define CAM_PREVIEW_22FPS
	//	#define CAM_PREVIEW_30FPS

	#define SYSTEM_CLK                           (48*1000*1000)
	/* PIXEL CLOCK USED BY BANDING FILTER CACULATION*/
#if defined(CAM_PREVIEW_15FPS)
	#define PIXEL_CLK							         (SYSTEM_CLK/8)		// 52/8 MHz
#elif defined(CAM_PREVIEW_22FPS)
   #define PIXEL_CLK							         (SYSTEM_CLK/6)		// 52/6 MHz
#elif defined(CAM_PREVIEW_30FPS)
   #define PIXEL_CLK 						      	(SYSTEM_CLK/4)		// 52/4 MHz
#endif
 
	/* MAX/MIN FRAME RATE (FRAMES PER SEC.) */
	#define MAX_FRAME_RATE								15		// Limitation for MPEG4 Encode Only
	#define MIN_FRAME_RATE								12

	/* LINE NUMBERS IN MAX_FRAME_RATE */
	#define MIN_LINES_PER_FRAME						((SYSTEM_CLK/8/MAX_FRAME_RATE)/VGA_PERIOD_PIXEL_NUMS)

	/* SENSOR GLOBAL GAIN AT NIGHT MODE */
	#define SENSOR_NIGHT_MODE_GAIN					0x08

	/* SENSOR PIXEL/LINE NUMBERS IN ONE PERIOD */
	#define VGA_PERIOD_PIXEL_NUMS					784
	#define VGA_PERIOD_LINE_NUMS					510

	/* SENSOR EXPOSURE LINE LIMITATION */
	#define VGA_EXPOSURE_LIMITATION					510
	
	/* 1M RESOLUTION SIZE */
	#define IMAGE_SENSOR_1M_WIDTH					1280
	#define IMAGE_SENSOR_1M_HEIGHT					960

	/* SENSOR VGA SIZE */
	#define IMAGE_SENSOR_VGA_WIDTH					640
	#define IMAGE_SENSOR_VGA_HEIGHT					480

	/* SETUP TIME NEED TO BE INSERTED */
	#define IMAGE_SENSOR_VGA_INSERTED_PIXELS		     133
	#define IMAGE_SENSOR_VGA_INSERTED_LINES		      16
	 

	/* SENSOR READ/WRITE ID */
	#define BF3703_WRITE_ID							0xdc
	#define BF3703_READ_ID							0xdd
	
	/* SENSOR CHIP VERSION */
	#define BF3703_SENSOR_ID						0x3703

	// BB's reset pin high low control MACROs
    #define RESET_PIN_LOW   (REG_ISP_CMOS_SENSOR_MODE_CONFIG &= ~REG_CMOS_SENSOR_RESET_BIT)
    #define RESET_PIN_HIGH  (REG_ISP_CMOS_SENSOR_MODE_CONFIG |= REG_CMOS_SENSOR_RESET_BIT)

    #define PWRDN_PIN_LOW           (REG_ISP_CMOS_SENSOR_MODE_CONFIG &= ~REG_CMOS_SENSOR_POWER_ON_BIT)
    #define PWRDN_PIN_HIGH          (REG_ISP_CMOS_SENSOR_MODE_CONFIG |= REG_CMOS_SENSOR_POWER_ON_BIT)

	
	
#ifdef MCU_104M
	#define SENSOR_I2C_DELAY							0xFF
#else
	#define SENSOR_I2C_DELAY							0x10
#endif

	#define I2C_START_TRANSMISSION \
	{ \
		volatile kal_uint32 j; \
		SET_SCCB_CLK_OUTPUT; \
		SET_SCCB_DATA_OUTPUT; \
		SET_SCCB_CLK_HIGH; \
		SET_SCCB_DATA_HIGH; \
		for(j=0;j<SENSOR_I2C_DELAY;j++);\
		SET_SCCB_DATA_LOW; \
		for(j=0;j<SENSOR_I2C_DELAY;j++);\
		SET_SCCB_CLK_LOW; \
	}
	
	#define I2C_STOP_TRANSMISSION \
	{ \
		volatile kal_uint32 j; \
		SET_SCCB_CLK_OUTPUT; \
		SET_SCCB_DATA_OUTPUT; \
		SET_SCCB_CLK_LOW; \
		SET_SCCB_DATA_LOW; \
		for(j=0;j<SENSOR_I2C_DELAY;j++);\
		SET_SCCB_CLK_HIGH; \
		for(j=0;j<SENSOR_I2C_DELAY;j++);\
		SET_SCCB_DATA_HIGH; \
	}

#endif /* _IMAGE_SENSOR_H */
