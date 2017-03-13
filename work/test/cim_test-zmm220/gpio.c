
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/time.h>
#include "arca.h"

#define LEDR	104
#define LEDG	105


#define GPIO_DIR_IN             0
#define GPIO_DIR_OUT            1
#define GPIO_LEVEL_LOW          0
#define GPIO_LEVEL_HIGH         1

/* ioctl command */
#if 1
#define SETDIRECTION            0x01
#define GETDIRECTION            0x02
#define SETLEVEL                0x03
#define GETLEVEL                0x04
#define SETRISINGEDGE           0x05
#define GETRISINGEDGE           0x06
#define SETFALLINGEDGE          0x07
#define GETFALLINGEDGE          0x08
#define GETEDGEDETECTSTATUS     0x09
#define CLEAREDGEDETECTSTATUS   0x0A

#define NANDREADPAGE		0x0B
#define NANDWRITEPAGE		0x0C
#define NANDREADBLOCK		0x0D
#define NANDWRITEBLOCK		0x0E
#define NANDREASEBLOCK		0x0F
#define NANDSAVEMAC		0x10
#else
#define SETDIRECTION            _IOW ('N', 0x01, struct _MSG)
#define GETDIRECTION            _IOR ('N', 0x02, struct _MSG)
#define SETLEVEL                _IOW ('N', 0x03, struct _MSG)
#define GETLEVEL                _IOR ('N', 0x04, struct _MSG)
#define SETRISINGEDGE           _IOW ('N', 0x05, struct _MSG)
#define GETRISINGEDGE           _IOR ('N', 0x06, struct _MSG)
#define SETFALLINGEDGE          _IOW ('N', 0x07, struct _MSG)
#define GETFALLINGEDGE          _IOR ('N', 0x08, struct _MSG)
#define GETEDGEDETECTSTATUS     _IOR ('N', 0x09, struct _MSG)
#define CLEAREDGEDETECTSTATUS   _IOW ('N', 0x0A, struct _MSG)

#define NANDREADPAGE            _IOR ('N', 0x0B, struct _MSG)
#define NANDWRITEPAGE           _IOW ('N', 0x0C, struct _MSG)
#define NANDREADBLOCK           _IOR ('N', 0x0D, struct _MSG)
#define NANDWRITEBLOCK          _IOW ('N', 0x0E, struct _MSG)
#define NANDREASEBLOCK          _IOW ('N', 0x0F, struct _MSG)
#define NANDSAVEMAC             _IOW ('N', 0x10, struct _MSG)
#define NANDGETBLOCKSTATUS      _IOR ('N', 0x11, struct _MSG)

#define FREEGPIO                _IOW ('N', 0x12, struct _MSG)
#define MAPGPIO                 _IOW ('N', 0x13, struct _MSG)
#endif

static int fd = -1;

struct _MSG
{
	int param0;
        int param1;
//	unsigned char buf[2048];
}Info;


//static int BASELOOPTESTCNT = 30;
/*
void DelayUS(int us)
{
        int i, j, k;

        if (us <= CNT*1000)
        {
                for (i=0; i<us; i++)
                        for(j=0; j<BASELOOPTESTCNT; j++) k++;
        }
        else
        {
                usleep(us);
        }
}
*/
/*
void DelayMS(int ms)
{
        usleep(1000*ms);
}
*/
void __gpio_as_output(int n)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return;
	}
	Info.param0 = n;
	Info.param1 = GPIO_DIR_OUT;

	ioctl(fd, SETDIRECTION,&Info);
	
//	return;
}
void __gpio_as_input(int n)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return;
	}
	Info.param0 = n;
	Info.param1 = GPIO_DIR_IN;

	ioctl(fd, SETDIRECTION,&Info);
	
//	return;
}


void __gpio_set_pin(int n)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return;
	}
	Info.param0 = n;
	Info.param1 = GPIO_LEVEL_HIGH;

	ioctl(fd, SETLEVEL, &Info);
	
//	return;
}

void __gpio_clear_pin(int n)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return;
	}
	Info.param0 = n;
	Info.param1 = GPIO_LEVEL_LOW;

	ioctl(fd, SETLEVEL, &Info);
	
//	return;
}

int __gpio_get_pin(int n)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return -1;
	}
	Info.param0 = n;

	ioctl(fd, GETLEVEL,&Info);
	
	return Info.param1;
}

int gpio_open(void)
{
	fd = open("/dev/jzgpio", O_RDWR);
	if(fd<0)
		printf("Error: open dev/jzgpio\n");
	printf("open gpio control ok!\n");
	return fd;
}


int gpio_close(void)
{
	close(fd);
}
#if 0
void Nand_read_onePage(U32 page, U8 *buf)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return;
	}
	Info.param0 = page;
	memset(Info.buf, 0, sizeof(Info.buf));
	ioctl(fd, NANDREADPAGE,&Info);
	memcpy(buf, Info.buf, sizeof(Info.buf));
	return;
}

void Nand_write_onePage(U32 page, U8 *buf)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return;
	}
	Info.param0 = page;
	memcpy(Info.buf, buf, sizeof(Info.buf));
	ioctl(fd, NANDWRITEPAGE,&Info);
	return;
}

void Nand_read_oneBlock(U32 page, U8 *buf)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return;
	}
//	ioctl(fd, NANDREADBLOCK,&buf);
	return;
}

void Nand_write_oneBlock(U32 page, U8 *buf)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return;
	}
//	ioctl(fd, NANDWRITEBLOCK,&buf);
	return;
}

void Nand_erase_oneBlock(U32 block)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return;
	}
	Info.param0 = block;
	ioctl(fd, NANDREASEBLOCK,NULL);
	return;
}

void Nand_save_MAC(U8 *buf)
{
	if(fd<0)
	{
		printf("invalid operation!\n");
		return;
	}
	memcpy(Info.buf, buf,6);
	ioctl(fd, NANDSAVEMAC,&Info);
	return;
}
#endif 
/*
int swi2c_write(uint8_t i2caddr, uint8_t subaddr, uint8_t data);
int swi2c_blkwrite(uint8_t i2caddr, uint8_t subaddr, uint8_t *data, uint32_t blksize);
int swi2c_read(uint8_t i2caddr, uint8_t subaddr, uint8_t *data);
int swi2c_blkread(uint8_t i2caddr, uint8_t subaddr, uint8_t *data, uint32_t blksize);
*/


int CNT=8;
#if 0
int main(int argc, int **argv)
{
	unsigned char buf[100];
	int i;
	int sw = 0;

//	if(argc>=1)
//		CNT=strtoul(argv[1], NULL, 0);
//	if(argc>=2)
//		sw=strtoul(argv[2], NULL, 0);

	fd = open("/dev/gpio", O_RDWR);
	if(fd<0)	
	{
		printf("Error: open dev/gpio\n");
		return 0;
	}

	__gpio_as_output(LEDR);
	__gpio_as_output(LEDG);

	while(1)
	{
		__gpio_set_pin(LEDR);
		__gpio_set_pin(LEDG);
		printf("set pin\n");
		DelayMS(500);
		__gpio_clear_pin(LEDR);
		__gpio_clear_pin(LEDG);
		printf("clear pin\n");
		DelayMS(500);
	}
	
#if 0
	if(sw==0)
	{
	#if 0
		for(i=0; i<CNT; i++) buf[i]=i+10;
		printf("write EEPROM.\n");
		swi2c_blkwrite(0xa0,0, buf, CNT);

		memset(buf, 0, CNT);	
		printf("read EEPROM:\n");
		if(swi2c_blkread(0xa0, 0, buf, CNT)!=0)
			printf("read failed\n");
		for(i=0; i<CNT; i++)
			printf("%02x ",buf[i]);
		printf("\n\n");
	#else
                printf("write EEPROM.\n");
                for(i=0; i<CNT; i++)
			swi2c_write(0xa0,i,i);

                memset(buf, 0, CNT);
                printf("read EEPROM:\n");

                for(i=0; i<CNT; i++)
			if(swi2c_read(0xa0, i, buf+i)!=0)
				printf("read failed\n");
		for(i=0; i<CNT; i++)
                        printf("%02x ",buf[i]);

		memset(buf, 0, CNT);	
		printf("block read EEPROM:\n");
		if(swi2c_blkread(0xa0, 0, buf, CNT)!=0)
			printf("read failed\n");
		for(i=0; i<CNT; i++)
			printf("%02x ",buf[i]);
                printf("\n\n");

	#endif
	}

	if(sw==1)
	{
		memset(buf, 0, CNT);	
		printf("read MI0360:\n");
		if(swi2c_blkread(0xBA, 0, buf, CNT)!=0)
			printf("read failed\n");

		for(i=0; i<CNT; i++)
			printf("%02x ",buf[i]);
		printf("\n");
	}

	if(sw==2)
	{
		memset(buf, 0, CNT);	
		printf("read RTC:\n");
		if(swi2c_blkread(0x65, 0, buf, CNT)!=0)
			printf("read failed\n");
		for(i=0; i<CNT; i++)
			printf("%02x ",buf[i]);
		printf("\n\n");

		memset(buf, 0, CNT);	
		if(swi2c_read(0x65, 0, buf)!=0)
			printf("read failed\n");
		printf("%02x\n",buf[0]);
	}


	if(sw==3)
	{

		memset(buf, 0, CNT);	
		printf("read HVCNT131:\n");
		if(swi2c_blkread(0x22, 0, buf, CNT)!=0)
			printf("read failed\n");
		for(i=0; i<CNT; i++)
			printf("%02x ",buf[i]);
		printf("\n\n");
	}

	if(sw==4)
	{
		memset(buf, 0, CNT);	
		printf("read GC030CNT:\n");
		if(swi2c_blkread(0x42, 0, buf, CNT)!=0)
			printf("read failed\n");
		for(i=0; i<CNT; i++)
			printf("%02x ",buf[i]);
		printf("\n\n");
	}


	if(sw==5)
	{
		memset(buf, 0, CNT);	
		printf("read GC0303:\n");
		if(swi2c_blkread(0x30, 0x90, buf, CNT)!=0)
			printf("read failed\n");
		for(i=0; i<CNT; i++)
			printf("%02x ",buf[i]);
		printf("\n\n");
	}
*/

#endif
	return 0;
}
#endif
