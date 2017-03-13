#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
//#include"mt9v136.h"

#define u16 unsigned short

#define IOCTL_READ_REG      0
#define IOCTL_WRITE_REG     1
#define JZ_CIM	1

typedef struct
{
        u16 reg;
        u16 val;
}S_CFG_16;

#define IOCTL_READ_EEPROM   2 /* read  sensor eeprom */
#define IOCTL_WRITE_EEPROM  3 /* write sensor eeprom */
#define IOCTL_SET_ADDR	    4
#define IOCTL_SET_CLK		  5 /* set i2c clock */


static int sensor_367_fd = -1;
#define I2C_MT9V136_CLOCK    100000
#define I2C_MT9V136_ADDR     0Xba
#define SIZE 12

static struct IO_MSG {
	unsigned int write_size;
	unsigned int read_size;
	unsigned char reg_buf[SIZE];
} reg_msg ;

static int MT9V136_set_addr(unsigned int addr)
{
	if (ioctl(sensor_367_fd, IOCTL_SET_ADDR, (unsigned int)&addr) < 0) {
		printf("ioctl: set address failed!\n");
		return -1;
	}
	return 0;
}

static int MT9V136_set_clk(int fd,unsigned int clk)
{
	if(fd==-1)
	{
		printf("%s m_sensor_fd is -1\n", __FUNCTION__);
		return -1;
	}

	if (ioctl(fd, IOCTL_SET_CLK, (unsigned int)&clk) < 0)
	{
		printf("%s ioctl: set clock failed!\n", __FUNCTION__);
		return -1;
	}
	return 0;
}

u16 read_reg_(u16 r)
{
	u16 read_val;
	reg_msg.write_size=2;
	reg_msg.read_size=2;
	reg_msg.reg_buf[0]=r>>8;
	reg_msg.reg_buf[1]=(0xff&r);
	if (ioctl(sensor_367_fd, IOCTL_READ_REG, (void *)&reg_msg) < 0) {
		printf("warning: read_reg failed!\n");
		return -1;
	}
	read_val = (reg_msg.reg_buf[0]<<8)|reg_msg.reg_buf[1];
	return read_val;
}

u16 write_reg_(u16 r,u16 v)
{
	reg_msg.write_size=4;
	reg_msg.reg_buf[0]=r>>8;
	reg_msg.reg_buf[1]=(0xff&r);
	reg_msg.reg_buf[2]=v>>8;
	reg_msg.reg_buf[3]=(0xff&v);	
	if (ioctl(sensor_367_fd, IOCTL_WRITE_REG, (unsigned long *)&reg_msg) < 0) {
		printf("warning: write_reg failed!\n");
		return -1;
	}
	return 0;
}

#define END_	0xff
void InitMT9V136(int width,int height,unsigned char *regs)
{
	u16	addr_,val_, ret;
	int i=0;
	u16 j=0;
	
	MT9V136_set_addr(I2C_MT9V136_ADDR);	     //IIC ADDR
	MT9V136_set_clk(sensor_367_fd,I2C_MT9V136_CLOCK);
	while((regs[i]!=END_)&&(regs[i+1]!=END_))
	{
		addr_ = (regs[i]<<8)|regs[i+1];	
		val_ = (regs[i+2]<<8)|regs[i+3];	
		ret = write_reg_(addr_,val_);
		if (ret == (u16)-1)
			exit(0);
//			printf("----write the reg and the i= %d,reg:%04x,val:%04x\n",i,addr_,val_);
//			j=read_reg_(addr_);
//			if(j!=val_)
//				printf("i2c write error addr=[%x] j=[%x],val=[%x] i=[%d]\n",addr_,j,val_,i);
		i += 4;
	}
	//printf("----write the reg and the i= %d,reg:%04x,val:%04x\n",i,addr_,val_);
	
	write_reg_(0xC854,width);
	write_reg_(0xC856,height);
	//printf("\n after read width= %d	heigh =%d\n",read_reg_(0xC854),read_reg_(0xC856));
}

#define SENMT367DEV  "/dev/sensor-mi367"
int sensor_open_mi367(void)
{
	sensor_367_fd = open(SENMT367DEV, O_RDWR);
	if(sensor_367_fd < 0)
	{
		printf("Error opening %s \n",SENMT367DEV);
		return -1;
	}
	
	printf("%s open ok!\n", SENMT367DEV);
	
	return sensor_367_fd;
}

void sensor_close_mi367()
{
	close(sensor_367_fd);
}

