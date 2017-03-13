#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include "gc0308.h"


#define IOCTL_READ_REG                          0 
#define IOCTL_WRITE_REG                         1 
#define IOCTL_READ_EEPROM                       2 
#define IOCTL_WRITE_EEPROM                      3 
#define IOCTL_SET_ADDR                          4 
#define IOCTL_SET_CLK                           5 

#define GC0308_CHIPID	0x00

/*exp reg */
#define GC0308_EXP_H        0x03
#define GC0308_EXP_L        0x04

/* windows regs*/
#define GC0308_ROW_H        0x05
#define GC0308_ROW_L        0x06
#define GC0308_COL_H        0x08
#define GC0308_COL_L        0x07
#define GC0308_WINH_H       0x09
#define GC0308_WINH_L       0x0A
#define GC0308_WINW_H       0x0B
#define GC0308_WINW_L       0x0C

#define GC0308_CISCTL_MODE2 0x0E
#define GC0308_CISCTL_MODE1 0x0F

#define GC0308_SCTRA 0x28

#define GC0308ID	0x42
//static pbusparam bus;
 
static  int sensor_0308_fd = -1;
static  int m_sensitivity;
static  int m_sensor_opt;

static int m_image_reverse;
static int m_image_symmetry=1;
static int exposH;

#define SIZE 12
static struct IO_MSG {
	unsigned int write_size;
	unsigned int read_size;
	unsigned char reg_buf[SIZE];
} reg_msg ;

#define SENC0308  "/dev/sensor-gc0308"
int sensor_open_0308(void)
{
	sensor_0308_fd=open(SENC0308,O_RDWR);

	if(sensor_0308_fd < 0)
	{
		perror("sensor_open()");
		return -1;
	}
	
	printf("%s open ok. \n", SENC0308);
	
	return sensor_0308_fd;
}

int sensor_close_0308()
{
	close(sensor_0308_fd);
}

static int sensor_set_addr(unsigned int addr)
{
	if (ioctl(sensor_0308_fd, IOCTL_SET_ADDR, (unsigned int)&addr) < 0) {
		printf("ioctl: set gc0308 address failed!addr=%x\n",addr);
		return -1;
	}
	return 0;
}

static unsigned char read_reg(int sensor_fd, unsigned char reg)
{
	unsigned char read_val;
	reg_msg.write_size=1;
	reg_msg.read_size=1;
	reg_msg.reg_buf[0]=reg;
	if (ioctl(sensor_fd, IOCTL_READ_REG, (void *)&reg_msg) < 0) {
		printf("warning: read_reg failed!\n");
		return 0;
	}
	read_val = reg_msg.reg_buf[0];
	return read_val;
}

static int write_reg(int sensor_fd, unsigned char reg, unsigned char val)
{
	reg_msg.write_size=2;
	reg_msg.read_size=0;
	reg_msg.reg_buf[0]=reg;
	reg_msg.reg_buf[1]=val;
	if (ioctl(sensor_fd, IOCTL_WRITE_REG, (unsigned long *)&reg_msg) < 0) {
		printf("warning: write_reg failed!\n");
		return 0;
	}

	return 1;
}

int gc0308_set_clk(int sensor_fd,unsigned int clk)
{
	if(sensor_fd==-1)
	{
		printf("%s m_sensor_fd is -1\n", __FUNCTION__);
		return -1;
	}

	if (ioctl(sensor_fd, IOCTL_SET_CLK, (unsigned int)&clk) < 0)
	{
		printf("%s ioctl: set clock failed!\n", __FUNCTION__);
		return -1;
	}
	return 0;
}


static void set_EXPOS_GC308(int exposH)
{
	//int value=read_reg(m_sensor_fd, 0xd0);
	//write_reg(m_sensor_fd, 0xd0, value | 0x20);
	write_reg(sensor_0308_fd, GC0308_EXP_H, (exposH>>8)&0xff);
	write_reg(sensor_0308_fd, GC0308_EXP_L, exposH&0xff);
}


static void set_BackgroundRGB_GC308(int RBlackLevel, int BBlackLevel, int GBlackLevel, int RBlackFactor, int GBlackFactor, int BBlackFactor)
{
	write_reg(sensor_0308_fd, 0x85, RBlackLevel);
	write_reg(sensor_0308_fd, 0x86, BBlackLevel);
	write_reg(sensor_0308_fd, 0x87, GBlackLevel);
	write_reg(sensor_0308_fd, 0x88, RBlackFactor);
	write_reg(sensor_0308_fd, 0x89, GBlackFactor);
	write_reg(sensor_0308_fd, 0x8a, BBlackFactor);
}

static void set_Contrast_GC308(int contrast)
{
	write_reg(sensor_0308_fd, 0xb3, contrast);
	write_reg(sensor_0308_fd, 0xb4, 0x80);
}

static void set_RGBGain_GCC308(int GGain, int G1Gain, int RGain, int BGain, int G2Gain)
{
	if(GGain > 0)
		write_reg(sensor_0308_fd, 0x50, GGain);//Global_Gain
	if(G1Gain > 0)
		write_reg(sensor_0308_fd, 0x53, G1Gain);//Gain_G1
	if(RGain > 0)
		write_reg(sensor_0308_fd, 0x54, RGain);//Gain_R
	if(BGain > 0)
		write_reg(sensor_0308_fd, 0x55, BGain);//Gain_B
	if(G2Gain > 0)
		write_reg(sensor_0308_fd, 0x56, G2Gain);//Gain_G2
}

static void select_page_gc308(int page)
{
	write_reg(sensor_0308_fd, 0xFE, page);
}

static void set_window_GC308(int l, int t, int w, int h)
{
	/* Set the row start address */
	write_reg(sensor_0308_fd,GC0308_ROW_H, (t >> 8) & 0xff);
	write_reg(sensor_0308_fd,GC0308_ROW_L, t & 0xff);

	/* Set the column start address */
	write_reg(sensor_0308_fd,GC0308_COL_H, (l >> 8) & 0xff);
	write_reg(sensor_0308_fd,GC0308_COL_L, l & 0xff);

	/* Set the image window width*/
	write_reg(sensor_0308_fd,GC0308_WINW_H, ((w+8)>> 8) & 0xff);
	write_reg(sensor_0308_fd,GC0308_WINW_L, (w+8) & 0xff);

	/* Set the image window height*/
	write_reg(sensor_0308_fd,GC0308_WINH_H, ((h+8) >> 8) & 0xff);
	write_reg(sensor_0308_fd,GC0308_WINH_L, (h+8) & 0xff);
}

/* VCLK = MCLK/div */
static void set_sensor_clock_gc308(int div)
{
	/* ABLC enable */
	int FrequencyNumber=div&0x0F;
	int FrequencyDiv=(div>>4)&0x0F;
	switch (FrequencyNumber+FrequencyDiv) {
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		write_reg(sensor_0308_fd,GC0308_SCTRA, (FrequencyNumber+FrequencyDiv-1)<<4 | FrequencyDiv);       // DCF=MCLK
		break;
	default:
		write_reg(sensor_0308_fd,GC0308_SCTRA, 0x00);       // DCF=MCLK
		break;
	}
}

static void set_vertical_GC308(int vertical)
{
	int value=0;
	value=read_reg(sensor_0308_fd, 0x14);
	if(vertical)
		write_reg(sensor_0308_fd, 0x14, value | 0x02);
	else
		write_reg(sensor_0308_fd, 0x14, value & (~0x02));
}

//设置图像是否需要左右镜像处理
static void set_symmetry_GC308(int symmetry)
{
	int value=read_reg(sensor_0308_fd, 0x14);
	if(symmetry==1)
		write_reg(sensor_0308_fd, 0x14, value | 0x01);//图像需要垂直翻转
	else
		write_reg(sensor_0308_fd, 0x14, value & (~0x01));//图像不需要垂直翻转
}

static void sensor_power_on_GC308(void)
{
	unsigned char value;
	value = read_reg(sensor_0308_fd, 0x24);
	write_reg(sensor_0308_fd, 0x24, value & 0xe0);
	value = read_reg(sensor_0308_fd, 0x25);
	write_reg(sensor_0308_fd, 0x25, value | 0x0F);
}

static void sensor_power_down_GC308(void)
{
	unsigned char value;
	value = read_reg(sensor_0308_fd, 0x25);
	write_reg(sensor_0308_fd, 0x25, value & (~0x0F));
}


static int sensorid_read(int sensorfd,unsigned char regs)
{
	return read_reg(sensorfd,regs);
}


void __gc0308_init(unsigned int (*regs)[2])
{
	int i=0;

	while (1)
	{		
		if ((_END_==regs[i][0])&&(_END_==regs[i][1])){
				break;
		}	
		
		write_reg(sensor_0308_fd,regs[i][0],regs[i][1]);	
		
		i++;		
	}
}

static int sensor_init_GC308(int left, int top, int width, int height)
{    
    int ret;
	#if 1
	gc0308_set_clk(sensor_0308_fd,100000);
	sleep(1);
	sensor_set_addr(GC0308ID);	     //IIC ADDR
	select_page_gc308(0);
	#endif
	//
	ret = read_reg(sensor_0308_fd,0x00);
	if(0x9b == ret){
		printf("Found Sensor-Gc0308...\n");
	}
	else{
		printf("That Should Be GC0308.Something-Unlucky-Happen.SensorID = 0x%x\n",ret);
		exit(1);
	}
	
	__gc0308_init(gc0308reg);
	
	set_window_GC308(left, top, width, height);

	return 0;
}




int gc0308_init(void)
{
    return sensor_init_GC308(0,0,640,480);    
}

