


// printf
#include <stdio.h>
#include <stdlib.h>
// memset
#include <string.h>

#include <getopt.h>           

#include <fcntl.h>  
// close write usleep read          
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
// mmap

#include <sys/mman.h>
#include <sys/ioctl.h>

#include <asm/types.h>        
#include <linux/videodev2.h>

// pthread_create pthread_join
#include <pthread.h>




#define CLEAR(x) memset (&(x), 0, sizeof (x))
#define REQ_COUNT 1
#define uchar unsigned char	




struct buffer {
	void *                  start;
	size_t                  length;
};

 static char *           dev_name        = "/dev/video0"; //����ͷ�豸��
//static char *           dev_name        = "/dev/video1";
static int              fd              = -1;
struct buffer *         buffers         = NULL;
// static unsigned int     n_buffers       = 0;




// 2012-7-13 11:33 camera flag
// static int iFlagCamera = 0;
volatile int iFlagCamera = 0;
// �������ƣ�thread1
// �������ܣ����ڽ��ܼ��̵����룬֮��֪ͨthread2ץͼ
// �����б�
// ����ֵ  ��
void thread1(void)
{
	char ch;
	printf("\n !!!!Warning!!!!\n Max 1000 color bmp\n Input the char: \n");
	printf("\n !!!!press o an capture 1 frame picture! \n");
	printf("\n !!!!press t an capture 10 frame picture! \n");
	printf("\n !!!!p/ress h an capture 100 frame picture! \n");

	while(1)
	{
		while((ch=getchar()) != '\n')
		{
			printf("%c\n", ch);

			if('o'==ch)
			{
				iFlagCamera = 1;

				printf("thread1=%d\n", iFlagCamera);
			}
			else if('t'==ch)
			{
				iFlagCamera = 10;

				printf("thread1=%d\n", iFlagCamera);
			}
			else if('h'==ch)
			{
				iFlagCamera = 101;

				printf("thread1=%d\n", iFlagCamera);
			}
			else if('q'==ch)
			{
				iFlagCamera = 10001;

				printf("thread1=%d\n", iFlagCamera);
			}
		}
		
		if(iFlagCamera>1000)
		{
			break;
		}
	}

	printf("\n exit\n");
}




FILE *file_fd;



int i;
int r;

struct v4l2_capability cap;
struct v4l2_format fmt;
struct v4l2_buffer buf[REQ_COUNT];
struct v4l2_requestbuffers req;
struct v4l2_buffer tmp_buf;
enum v4l2_buf_type type;

struct timeval tv;
struct timeval tp1;	
struct timeval tp3;
struct timeval tp4;

// void * mem[REQ_COUNT];

fd_set fds;




// // http://blog.sina.com.cn/s/blog_602f87700100znq7.html
// // Ƕ��ʽLinux��Camera���--V4L2
// // Z:\kernel_imx\include\linux\videodev2.h
// /* Values for 'capabilities' field */
#define V4L2_CAP_VIDEO_CAPTURE		0x00000001  /* Is a video capture device */
#define V4L2_CAP_VIDEO_OUTPUT		0x00000002  /* Is a video output device */
#define V4L2_CAP_VIDEO_OVERLAY		0x00000004  /* Can do video overlay */
#define V4L2_CAP_VBI_CAPTURE		0x00000010  /* Is a raw VBI capture device */
#define V4L2_CAP_VBI_OUTPUT		0x00000020  /* Is a raw VBI output device */
#define V4L2_CAP_SLICED_VBI_CAPTURE	0x00000040  /* Is a sliced VBI capture device */
#define V4L2_CAP_SLICED_VBI_OUTPUT	0x00000080  /* Is a sliced VBI output device */
#define V4L2_CAP_RDS_CAPTURE		0x00000100  /* RDS data capture */
#define V4L2_CAP_VIDEO_OUTPUT_OVERLAY	0x00000200  /* Can do video output overlay */
#define V4L2_CAP_HW_FREQ_SEEK		0x00000400  /* Can do hardware frequency seek  */
#define V4L2_CAP_RDS_OUTPUT		0x00000800  /* Is an RDS encoder */

/* Is a video capture device that supports multiplanar formats */
#define V4L2_CAP_VIDEO_CAPTURE_MPLANE	0x00001000
/* Is a video output device that supports multiplanar formats */
#define V4L2_CAP_VIDEO_OUTPUT_MPLANE	0x00002000

#define V4L2_CAP_TUNER			0x00010000  /* has a tuner */
#define V4L2_CAP_AUDIO			0x00020000  /* has audio support */
#define V4L2_CAP_RADIO			0x00040000  /* is a radio device */
#define V4L2_CAP_MODULATOR		0x00080000  /* has a modulator */

#define V4L2_CAP_READWRITE              0x01000000  /* read/write systemcalls */
#define V4L2_CAP_ASYNCIO                0x02000000  /* async I/O */
#define V4L2_CAP_STREAMING              0x04000000  /* streaming I/O ioctls */

#define V4L2_MBUS_FMT_YUYV8_2X8          0x2008


void getCameraCapabilities(int iCameraCapabilities)
{
	if(iCameraCapabilities&V4L2_CAP_VIDEO_CAPTURE)
	{
		printf("!!!!**** camera ****!!!! Is a video capture device\n");
	}

	if(iCameraCapabilities&V4L2_CAP_VIDEO_OUTPUT)
	{
		printf("**** camera **** Is a video output device\n");
	}

	if(iCameraCapabilities&V4L2_CAP_VIDEO_OVERLAY)
	{
		printf("**** camera **** Can do video overlay\n");
	}

	if(iCameraCapabilities&V4L2_CAP_VBI_CAPTURE)
	{
		printf("**** camera **** Is a raw VBI capture device\n");
	}

	if(iCameraCapabilities&V4L2_CAP_VBI_OUTPUT)
	{
		printf("**** camera **** Is a raw VBI output device\n");
	}

	if(iCameraCapabilities&V4L2_CAP_SLICED_VBI_CAPTURE)
	{
		printf("**** camera **** Is a sliced VBI capture device\n");
	}

	if(iCameraCapabilities&V4L2_CAP_SLICED_VBI_OUTPUT)
	{
		printf("**** camera **** Is a sliced VBI output device\n");
	}

	if(iCameraCapabilities&V4L2_CAP_RDS_CAPTURE)
	{
		printf("**** camera **** RDS data capture\n");
	}

	if(iCameraCapabilities&V4L2_CAP_VIDEO_OUTPUT_OVERLAY)
	{
		printf("**** camera **** Can do video output overlay\n");
	}

	if(iCameraCapabilities&V4L2_CAP_HW_FREQ_SEEK)
	{
		printf("**** camera **** Can do hardware frequency seek\n");
	}

	if(iCameraCapabilities&V4L2_CAP_RDS_OUTPUT)
	{
		printf("**** camera **** Is an RDS encoder\n");
	}

	if(iCameraCapabilities&V4L2_CAP_VIDEO_CAPTURE_MPLANE)
	{
		printf("**** camera **** Is a video capture device that supports multiplanar formats\n");
	}

	if(iCameraCapabilities&V4L2_CAP_VIDEO_OUTPUT_MPLANE)
	{
		printf("**** camera **** Is a video output device that supports multiplanar formats\n");
	}

	if(iCameraCapabilities&V4L2_CAP_TUNER)
	{
		printf("**** camera **** has a tuner\n");
	}

	if(iCameraCapabilities&V4L2_CAP_AUDIO)
	{
		printf("**** camera **** has audio support\n");
	}

	if(iCameraCapabilities&V4L2_CAP_RADIO)
	{
		printf("**** camera **** is a radio device\n");
	}

	if(iCameraCapabilities&V4L2_CAP_MODULATOR)
	{
		printf("**** camera **** has a modulator\n");
	}

	if(iCameraCapabilities&V4L2_CAP_READWRITE)
	{
		printf("**** camera **** read/write systemcalls\n");
	}

	if(iCameraCapabilities&V4L2_CAP_ASYNCIO)
	{
		printf("**** camera **** async I/O\n");
	}

	if(iCameraCapabilities&V4L2_CAP_STREAMING)
	{
		printf("!!!!**** camera ****!!!! streaming I/O ioctls\n");
	}
}
/*  Four-character-code (FOURCC) */
#define v4l2_fourcc(a, b, c, d)\
	((__u32)(a) | ((__u32)(b) << 8) | ((__u32)(c) << 16) | ((__u32)(d) << 24))
#define V4L2_PIX_FMT_JZ420B  v4l2_fourcc('J', 'Z', '1', '2') /* 12  YUV 4:2:0 B   */



// ��˾    ������Ƽ������ڣ����޹�˾ 
// ����    �������� 0755-86139000-1052
// �ļ���  ��main.c
// ����    ��N001
// ����    ��2012-7-28 10:08
// ά����  ��
// ά����¼��

// #include "imgprocess.h"

#include <sys/time.h>

// int main ()
void thread2(void)
{

	int iCounterCamera = 0;
	int iCounter100frame = 0;

	// 2012-11-8 05:27���� RGB24 640*480�ֱ��ʵ�BMPͼ��ͷ�ļ�
// unsigned char head[54] = {0x42,0x4d,0x36,0x10,0x0e,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0xe0,0x01,0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	// ץȡY������ȡ�õĻҶ�ͼ
unsigned char graybmphead[1078] = { 0x42, 0x4d, 0x36, 0xb4, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x04, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x02, 0x02, 0x02, 0x00, 0x03, 0x03, 0x03, 0x00, 0x04, 0x04, 0x04, 0x00, 0x05, 0x05, 0x05, 0x00, 0x06, 0x06, 0x06, 0x00, 0x07, 0x07, 0x07, 0x00, 0x08, 0x08, 0x08, 0x00, 0x09, 0x09, 0x09, 0x00, 0x0a, 0x0a, 0x0a, 0x00, 0x0b, 0x0b, 0x0b, 0x00, 0x0c, 0x0c, 0x0c, 0x00, 0x0d, 0x0d, 0x0d, 0x00, 0x0e, 0x0e, 0x0e, 0x00, 0x0f, 0x0f, 0x0f, 0x00, 0x10, 0x10, 0x10, 0x00, 0x11, 0x11, 0x11, 0x00, 0x12, 0x12, 0x12, 0x00, 0x13, 0x13, 0x13, 0x00, 0x14, 0x14, 0x14, 0x00, 0x15, 0x15, 0x15, 0x00, 0x16, 0x16, 0x16, 0x00, 0x17, 0x17, 0x17, 0x00, 0x18, 0x18, 0x18, 0x00, 0x19, 0x19, 0x19, 0x00, 0x1a, 0x1a, 0x1a, 0x00, 0x1b, 0x1b, 0x1b, 0x00, 0x1c, 0x1c, 0x1c, 0x00, 0x1d, 0x1d, 0x1d, 0x00, 0x1e, 0x1e, 0x1e, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x20, 0x20, 0x20, 0x00, 0x21, 0x21, 0x21, 0x00, 0x22, 0x22, 0x22, 0x00, 0x23, 0x23, 0x23, 0x00, 0x24, 0x24, 0x24, 0x00, 0x25, 0x25, 0x25, 0x00, 0x26, 0x26, 0x26, 0x00, 0x27, 0x27, 0x27, 0x00, 0x28, 0x28, 0x28, 0x00, 0x29, 0x29, 0x29, 0x00, 0x2a, 0x2a, 0x2a, 0x00, 0x2b, 0x2b, 0x2b, 0x00, 0x2c, 0x2c, 0x2c, 0x00, 0x2d, 0x2d, 0x2d, 0x00, 0x2e, 0x2e, 0x2e, 0x00, 0x2f, 0x2f, 0x2f, 0x00, 0x30, 0x30, 0x30, 0x00, 0x31, 0x31, 0x31, 0x00, 0x32, 0x32, 0x32, 0x00, 0x33, 0x33, 0x33, 0x00, 0x34, 0x34, 0x34, 0x00, 0x35, 0x35, 0x35, 0x00, 0x36, 0x36, 0x36, 0x00, 0x37, 0x37, 0x37, 0x00, 0x38, 0x38, 0x38, 0x00, 0x39, 0x39, 0x39, 0x00, 0x3a, 0x3a, 0x3a, 0x00, 0x3b, 0x3b, 0x3b, 0x00, 0x3c, 0x3c, 0x3c, 0x00, 0x3d, 0x3d, 0x3d, 0x00, 0x3e, 0x3e, 0x3e, 0x00, 0x3f, 0x3f, 0x3f, 0x00, 0x40, 0x40, 0x40, 0x00, 0x41, 0x41, 0x41, 0x00, 0x42, 0x42, 0x42, 0x00, 0x43, 0x43, 0x43, 0x00, 0x44, 0x44, 0x44, 0x00, 0x45, 0x45, 0x45, 0x00, 0x46, 0x46, 0x46, 0x00, 0x47, 0x47, 0x47, 0x00, 0x48, 0x48, 0x48, 0x00, 0x49, 0x49, 0x49, 0x00, 0x4a, 0x4a, 0x4a, 0x00, 0x4b, 0x4b, 0x4b, 0x00, 0x4c, 0x4c, 0x4c, 0x00, 0x4d, 0x4d, 0x4d, 0x00, 0x4e, 0x4e, 0x4e, 0x00, 0x4f, 0x4f, 0x4f, 0x00, 0x50, 0x50, 0x50, 0x00, 0x51, 0x51, 0x51, 0x00, 0x52, 0x52, 0x52, 0x00, 0x53, 0x53, 0x53, 0x00, 0x54, 0x54, 0x54, 0x00, 0x55, 0x55, 0x55, 0x00, 0x56, 0x56, 0x56, 0x00, 0x57, 0x57, 0x57, 0x00, 0x58, 0x58, 0x58, 0x00, 0x59, 0x59, 0x59, 0x00, 0x5a, 0x5a, 0x5a, 0x00, 0x5b, 0x5b, 0x5b, 0x00, 0x5c, 0x5c, 0x5c, 0x00, 0x5d, 0x5d, 0x5d, 0x00, 0x5e, 0x5e, 0x5e, 0x00, 0x5f, 0x5f, 0x5f, 0x00, 0x60, 0x60, 0x60, 0x00, 0x61, 0x61, 0x61, 0x00, 0x62, 0x62, 0x62, 0x00, 0x63, 0x63, 0x63, 0x00, 0x64, 0x64, 0x64, 0x00, 0x65, 0x65, 0x65, 0x00, 0x66, 0x66, 0x66, 0x00, 0x67, 0x67, 0x67, 0x00, 0x68, 0x68, 0x68, 0x00, 0x69, 0x69, 0x69, 0x00, 0x6a, 0x6a, 0x6a, 0x00, 0x6b, 0x6b, 0x6b, 0x00, 0x6c, 0x6c, 0x6c, 0x00, 0x6d, 0x6d, 0x6d, 0x00, 0x6e, 0x6e, 0x6e, 0x00, 0x6f, 0x6f, 0x6f, 0x00, 0x70, 0x70, 0x70, 0x00, 0x71, 0x71, 0x71, 0x00, 0x72, 0x72, 0x72, 0x00, 0x73, 0x73, 0x73, 0x00, 0x74, 0x74, 0x74, 0x00, 0x75, 0x75, 0x75, 0x00, 0x76, 0x76, 0x76, 0x00, 0x77, 0x77, 0x77, 0x00, 0x78, 0x78, 0x78, 0x00, 0x79, 0x79, 0x79, 0x00, 0x7a, 0x7a, 0x7a, 0x00, 0x7b, 0x7b, 0x7b, 0x00, 0x7c, 0x7c, 0x7c, 0x00, 0x7d, 0x7d, 0x7d, 0x00, 0x7e, 0x7e, 0x7e, 0x00, 0x7f, 0x7f, 0x7f, 0x00, 0x80, 0x80, 0x80, 0x00, 0x81, 0x81, 0x81, 0x00, 0x82, 0x82, 0x82, 0x00, 0x83, 0x83, 0x83, 0x00, 0x84, 0x84, 0x84, 0x00, 0x85, 0x85, 0x85, 0x00, 0x86, 0x86, 0x86, 0x00, 0x87, 0x87, 0x87, 0x00, 0x88, 0x88, 0x88, 0x00, 0x89, 0x89, 0x89, 0x00, 0x8a, 0x8a, 0x8a, 0x00, 0x8b, 0x8b, 0x8b, 0x00, 0x8c, 0x8c, 0x8c, 0x00, 0x8d, 0x8d, 0x8d, 0x00, 0x8e, 0x8e, 0x8e, 0x00, 0x8f, 0x8f, 0x8f, 0x00, 0x90, 0x90, 0x90, 0x00, 0x91, 0x91, 0x91, 0x00, 0x92, 0x92, 0x92, 0x00, 0x93, 0x93, 0x93, 0x00, 0x94, 0x94, 0x94, 0x00, 0x95, 0x95, 0x95, 0x00, 0x96, 0x96, 0x96, 0x00, 0x97, 0x97, 0x97, 0x00, 0x98, 0x98, 0x98, 0x00, 0x99, 0x99, 0x99, 0x00, 0x9a, 0x9a, 0x9a, 0x00, 0x9b, 0x9b, 0x9b, 0x00, 0x9c, 0x9c, 0x9c, 0x00, 0x9d, 0x9d, 0x9d, 0x00, 0x9e, 0x9e, 0x9e, 0x00, 0x9f, 0x9f, 0x9f, 0x00, 0xa0, 0xa0, 0xa0, 0x00, 0xa1, 0xa1, 0xa1, 0x00, 0xa2, 0xa2, 0xa2, 0x00, 0xa3, 0xa3, 0xa3, 0x00, 0xa4, 0xa4, 0xa4, 0x00, 0xa5, 0xa5, 0xa5, 0x00, 0xa6, 0xa6, 0xa6, 0x00, 0xa7, 0xa7, 0xa7, 0x00, 0xa8, 0xa8, 0xa8, 0x00, 0xa9, 0xa9, 0xa9, 0x00, 0xaa, 0xaa, 0xaa, 0x00, 0xab, 0xab, 0xab, 0x00, 0xac, 0xac, 0xac, 0x00, 0xad, 0xad, 0xad, 0x00, 0xae, 0xae, 0xae, 0x00, 0xaf, 0xaf, 0xaf, 0x00, 0xb0, 0xb0, 0xb0, 0x00, 0xb1, 0xb1, 0xb1, 0x00, 0xb2, 0xb2, 0xb2, 0x00, 0xb3, 0xb3, 0xb3, 0x00, 0xb4, 0xb4, 0xb4, 0x00, 0xb5, 0xb5, 0xb5, 0x00, 0xb6, 0xb6, 0xb6, 0x00, 0xb7, 0xb7, 0xb7, 0x00, 0xb8, 0xb8, 0xb8, 0x00, 0xb9, 0xb9, 0xb9, 0x00, 0xba, 0xba, 0xba, 0x00, 0xbb, 0xbb, 0xbb, 0x00, 0xbc, 0xbc, 0xbc, 0x00, 0xbd, 0xbd, 0xbd, 0x00, 0xbe, 0xbe, 0xbe, 0x00, 0xbf, 0xbf, 0xbf, 0x00, 0xc0, 0xc0, 0xc0, 0x00, 0xc1, 0xc1, 0xc1, 0x00, 0xc2, 0xc2, 0xc2, 0x00, 0xc3, 0xc3, 0xc3, 0x00, 0xc4, 0xc4, 0xc4, 0x00, 0xc5, 0xc5, 0xc5, 0x00, 0xc6, 0xc6, 0xc6, 0x00, 0xc7, 0xc7, 0xc7, 0x00, 0xc8, 0xc8, 0xc8, 0x00, 0xc9, 0xc9, 0xc9, 0x00, 0xca, 0xca, 0xca, 0x00, 0xcb, 0xcb, 0xcb, 0x00, 0xcc, 0xcc, 0xcc, 0x00, 0xcd, 0xcd, 0xcd, 0x00, 0xce, 0xce, 0xce, 0x00, 0xcf, 0xcf, 0xcf, 0x00, 0xd0, 0xd0, 0xd0, 0x00, 0xd1, 0xd1, 0xd1, 0x00, 0xd2, 0xd2, 0xd2, 0x00, 0xd3, 0xd3, 0xd3, 0x00, 0xd4, 0xd4, 0xd4, 0x00, 0xd5, 0xd5, 0xd5, 0x00, 0xd6, 0xd6, 0xd6, 0x00, 0xd7, 0xd7, 0xd7, 0x00, 0xd8, 0xd8, 0xd8, 0x00, 0xd9, 0xd9, 0xd9, 0x00, 0xda, 0xda, 0xda, 0x00, 0xdb, 0xdb, 0xdb, 0x00, 0xdc, 0xdc, 0xdc, 0x00, 0xdd, 0xdd, 0xdd, 0x00, 0xde, 0xde, 0xde, 0x00, 0xdf, 0xdf, 0xdf, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0xe1, 0xe1, 0xe1, 0x00, 0xe2, 0xe2, 0xe2, 0x00, 0xe3, 0xe3, 0xe3, 0x00, 0xe4, 0xe4, 0xe4, 0x00, 0xe5, 0xe5, 0xe5, 0x00, 0xe6, 0xe6, 0xe6, 0x00, 0xe7, 0xe7, 0xe7, 0x00, 0xe8, 0xe8, 0xe8, 0x00, 0xe9, 0xe9, 0xe9, 0x00, 0xea, 0xea, 0xea, 0x00, 0xeb, 0xeb, 0xeb, 0x00, 0xec, 0xec, 0xec, 0x00, 0xed, 0xed, 0xed, 0x00, 0xee, 0xee, 0xee, 0x00, 0xef, 0xef, 0xef, 0x00, 0xf0, 0xf0, 0xf0, 0x00, 0xf1, 0xf1, 0xf1, 0x00, 0xf2, 0xf2, 0xf2, 0x00, 0xf3, 0xf3, 0xf3, 0x00, 0xf4, 0xf4, 0xf4, 0x00, 0xf5, 0xf5, 0xf5, 0x00, 0xf6, 0xf6, 0xf6, 0x00, 0xf7, 0xf7, 0xf7, 0x00, 0xf8, 0xf8, 0xf8, 0x00, 0xf9, 0xf9, 0xf9, 0x00, 0xfa, 0xfa, 0xfa, 0x00, 0xfb, 0xfb, 0xfb, 0x00, 0xfc, 0xfc, 0xfc, 0x00, 0xfd, 0xfd, 0xfd, 0x00, 0xfe, 0xfe, 0xfe, 0x00, 0xff, 0xff, 0xff, 0x00 };

//	int g_nWidth  = 640;
//	int g_nHeight = 480;
//       int g_nWidth  = 320;
//       int g_nHeight = 240;

       int g_nWidth  = 1280;
       int g_nHeight = 720;




	// 2012-8-8 04:29���� V4L2��ʼ������ͷ
	// ע��������Դ��
	// http://wenku.baidu.com/view/2f92ce8c680203d8ce2f247f.html
	// ����Linux��Ƶ�����ӿ�V4L2��Ƶ�ɼ����
	// �÷�����ģʽ������ͷ�豸
	if((fd=open(dev_name,O_RDWR | O_NONBLOCK,0))<0)
	{
		printf("Error   66666: open %s\n",dev_name);

		// return 0;
		return;
	}
	else
	{
		printf("**** wyb01 Open camera video0 success!!!! fd=%d\n", fd);
	}


	//return ;//for test bill

	// ��ȡ��ǰ��Ƶ�豸֧�ֵ���Ƶ��ʽ
	struct v4l2_fmtdesc fmtd; 
	int ret = 0;
	memset(&fmtd, 0, sizeof(fmtd)); 
	fmtd.index = 0; 
	fmtd.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; 

	while ((ret = ioctl(fd, VIDIOC_ENUM_FMT, &fmtd)) == 0) 
	{ 
		fmtd.index++; 
		printf("\n...... pixelformat = ''%c%c%c%c'', description = ''%s'' \n", fmtd.pixelformat & 0xFF, (fmtd.pixelformat >> 8) & 0xFF, (fmtd.pixelformat >> 16) & 0xFF, (fmtd.pixelformat >> 24) & 0xFF, fmtd.description); 
	}




	// ��ѯ��Ƶ�豸�Ĺ��ܣ�ִ���� VIDIOC_QUERYCAP �����cap�����а����˸���Ƶ�豸��������Ϣ��
	// ������ͨ�����cap�е��豸������Ϣ���ж��豸�Ƿ�֧��ĳ��ܡ�
	if(ioctl(fd, VIDIOC_QUERYCAP, &cap)<0)
	{
		printf("Error: query cap\n");

		// return 0;
		return;
	}
	printf("\n capabilities= 0x%08x\n",cap.capabilities);
	int iCapCapabilities=cap.capabilities;




	// if(ioctl(fd, VIDIOC_S_INPUT, 0)<0)
	
	int index = 0;
	if(ioctl(fd, VIDIOC_S_INPUT, &index)<0)
	{
		printf("Error:VIDIOC_S_INPUT \n");

		// return 0;
		return;
	}
           struct v4l2_format fmt2;
      fmt2.type=V4L2_BUF_TYPE_VIDEO_CAPTURE; 
      ret = ioctl(fd,VIDIOC_G_FMT, &fmt2);
      printf("VIDIOC_G_FMT ret=%d \n", ret);
	
	
	#if 0
	
	fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width       = g_nWidth;
	fmt.fmt.pix.height      = g_nHeight;
	// fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	//fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV422P;
	//fmt.fmt.pix.field       = V4L2_FIELD_BOTTOM;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV21;
	fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	#endif
	
	// ������Ƶ�豸����Ƶ���ݸ�ʽ������������Ƶͼ�����ݵĳ�����ͼ���ʽ��JPEG��YUYV ��ʽ����
	// ע�⣺�������Ƶ�豸������֧�������趨��ͼ���ʽ��
	// ��Ƶ�����������޸�struct v4l2_format �ṹ�������ֵΪ����Ƶ�豸��֧�ֵ�ͼ���ʽ��
	// �����ڳ�������У��趨�����е���Ƶ��ʽ��Ҫ��ȡʵ�ʵ���Ƶ��ʽ��
	// Ҫ���¶�ȡstruct v4l2_format �ṹ�������
	//memset ( &fmt, 0, sizeof(fmt) );
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//	fmt.fmt.pix.width = 640;
//	fmt.fmt.pix.height = 480;
//           fmt.fmt.pix.width = 320;
//      fmt.fmt.pix.height = 240;
         fmt.fmt.pix.width = 1280;
      fmt.fmt.pix.height = 720;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_JZ420B;//V4L2_PIX_FMT_YUYV;// V4L2_PIX_FMT_JZ420B;// V4L2_PIX_FMT_YUV422P;// V4L2_PIX_FMT_YUYV;// V4L2_PIX_FMT_SBGGR8;// V4L2_PIX_FMT_YUYV;// 0x55595659;// V4L2_PIX_FMT_YUV420;//V4L2_MBUS_FMT_YUYV8_2X8;// V4L2_PIX_FMT_JPEG
//        fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	if (ioctl(fd, VIDIOC_S_FMT, &fmt) < 0)
	{
	  printf("set chenmuyuan7777777777777777777777777777format failed\n");
	  return ;
	}

	printf("**** chenmuyuan77776666666fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV; ****\n");


	#if 0
	if(ioctl(fd,VIDIOC_S_FMT, &fmt)<0)
	{
		printf("Error:VIDIOC_S_FMT \n");

		// return 0;
		return;
	}
	#endif



	// ��ȡ��ǰ������Ƶ�����ʽ
	// 2012-8-8 03:07���� ȷ�������õ���ʽ�Ƿ�����������Ҫ����ʽ
//	struct v4l2_format fmt2;
//	fmt2.type=V4L2_BUF_TYPE_VIDEO_CAPTURE; 
//	ret = ioctl(fd,VIDIOC_G_FMT, &fmt2);
//	printf("VIDIOC_G_FMT ret=%d \n", ret);

	printf("pixelformat = ''%c%c%c%c''\n", fmt2.fmt.pix.pixelformat & 0xFF, (fmt2.fmt.pix.pixelformat >> 8) & 0xFF, (fmt2.fmt.pix.pixelformat >> 16) & 0xFF, (fmt2.fmt.pix.pixelformat >> 24) & 0xFF); 




	req.count               = REQ_COUNT ;
	req.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory              = V4L2_MEMORY_MMAP;

	// ����V4L2����������Ƶ������ ������ V4L2��Ƶ���������ڴ棩��V4L2����Ƶ�豸�������㣬
	// λ���ں˿ռ䣬����ͨ�� VIDIOC_REQBUFS ����������������ڴ�λ���ں˿ռ䣬
	// Ӧ�ó�����ֱ�ӷ��ʣ���Ҫͨ������ mmap�ڴ�ӳ�亯�����ں˿ռ��ڴ�ӳ�䵽�û��ռ��
	// Ӧ�ó���ͨ�������û��ռ��ַ�������ں˿ռ䡣 
	// ע�⣺ VIDIOC_REQBUFS���޸�tV4L2_reqbuf��countֵ��
	// tV4L2_reqbuf��countֵ����ʵ������ɹ�����Ƶ��������Ŀ��
	if(ioctl(fd, VIDIOC_REQBUFS, &req)<0)
	{
		printf("Error:VIDIOC_REQBUFS\n");

		// return 0;
		return;
	}

	printf("req.count=%d\n",req.count);




	buffers = calloc (req.count, sizeof (*buffers));//�ڴ��н�����Ӧ�ռ�
	printf(" chenmuyuan767676767sizeof (*buffers) =%08x\n", sizeof (*buffers));

	for(i=0;i<req.count;i++)
	{
		buf[i].type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf[i].memory      = V4L2_MEMORY_MMAP;
		buf[i].index       = i;
		printf("**chenmuyuan 1**  buf.length=%d \n",buf[i].length);

		// ��ѯ�Ѿ������ V4L2����Ƶ�������������Ϣ��������Ƶ��������ʹ��״̬�����ں˿ռ��
		// ƫ�Ƶ�ַ�����������ȵȡ���Ӧ�ó��������ͨ����VIDIOC_QUERYBUF ����ȡ�ں˿ռ��
		// ��Ƶ��������Ϣ��Ȼ����ú���mmap���ں˿ռ��ַӳ�䵽�û��ռ䣬����Ӧ�ó�����ܹ�
		// ����λ���ں˿ռ����Ƶ��������ͨ������ VIDIOC_QUERYBUF ȡ���ں˿ռ�Ļ�������Ϣ��
		// ���ŵ��� mmap�������ں˿ռ仺����ӳ�䵽�û��ռ䡣
		if(ioctl(fd, VIDIOC_QUERYBUF, buf+i)<0)
		{
			printf("Error:VIDIOC_QUERYBUF\n");

			// return 0;
			return;
		}


		printf("**cmy 2** i=%d buf.length=%d, \n",buf[i].length);

		buffers[i].length =buf[i].length;//14400
		buffers[i].start =
		mmap (NULL /* start anywhere */,    //ͨ��mmap����ӳ���ϵ
		buf[i].length,
		PROT_READ | PROT_WRITE /* required */,
		MAP_SHARED /* recommended */,
		fd, buf[i].m.offset);

		//printf("**** i=%d buf.length=%d, buffers[i].start=%08x buf.m.offset=%08x\n", i, buf[i].length, *( (unsigned int *) (buffers[i].start) ), buf.m.offset);
		printf("**** i=%d buf.length=%d, buffers[i].start=%08x buf.m.offset=%08x\n", i, buf[i].length, *( (unsigned int *) (buffers[i].start) ), buf[i].m.offset);




		buf[i].type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf[i].memory      = V4L2_MEMORY_MMAP;
		buf[i].index       = i;

		// Ͷ��һ���յ���Ƶ����������Ƶ��������������С�����ִ�гɹ���ָ�����Ƶ������
		// ������Ƶ������У���������Ƶ�豸����ͼ��ʱ����Ӧ����Ƶ���ݱ����浽��Ƶ�������
		// ��Ӧ����Ƶ�������С� 
		if(ioctl(fd, VIDIOC_QBUF, buf+i)<0)
		{
			printf("Error: VIDIOC_QBUF\n");
		}
	}




	// ������Ƶ�ɼ����Ӧ�ó������ VIDIOC_STREAMON ������Ƶ�ɼ������
	// ��Ƶ�豸��������ʼ�ɼ���Ƶ���ݣ����Ѳɼ�������Ƶ���ݱ��浽
	// ��Ƶ��������Ƶ�������С� 
	type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(ioctl(fd, VIDIOC_STREAMON, &type)<0)
	{
		printf("Error: VIDIOC_STREAMON\n");

		// return 0;
		return;
	}
	
	
	
	
	gettimeofday(&tv, NULL);
	int iSecond = tv.tv_sec;
	int iuSecond = tv.tv_usec;
	int iCostTime = 0;
	
	int iSecond3 = tv.tv_sec;
	int iuSecond3 = tv.tv_usec;
	int iCostTime3 = 0;
	
	int iSecond4 = tv.tv_sec;
	int iuSecond4 = tv.tv_usec;
	int iCostTime4 = 0;
	
	int iCameraCounter = 0;
	
	int iFrameCounter = 0;
	int iFrameCounter3 = 0;
	int iFrameCounter4 = 0;
	while(1)
	{
		// 2013/5/14 17:59:02 ��q�˳�
		if(iFlagCamera>1000)
		{
			break;
		}
		
		
		
		
		// 2013-5-14 19:13 ��֡��
		iFrameCounter++;
		 
		 if(iFrameCounter%100==0)
		 {
		 	gettimeofday(&tp1, NULL);
		 	
		 	iCostTime = (tp1.tv_sec - iSecond)*1000000 + tp1.tv_usec - iuSecond;
		 	printf("@@@@ 100 frame=%u us, fps=%f\n",iCostTime, 1000000*100.0/iCostTime) ;
		 	
		 	iSecond = tp1.tv_sec;
		 	iuSecond = tp1.tv_usec;
		 }




		FD_ZERO (&fds);
		FD_SET (fd, &fds);
		tv.tv_sec = 2;
		tv.tv_usec = 0;

		// VIDIOC_STREAMON����ִ�гɹ�����Ƶ�豸��������ʼ�ɼ���Ƶ���ݣ���ʱӦ�ó���
		// һ��ͨ������ select �������ж�һ֡��Ƶ�����Ƿ�ɼ���ɣ�����Ƶ�豸�������
		// һ֡��Ƶ���ݲɼ������浽��Ƶ��������ʱ��select �������أ�Ӧ�ó�����ſ���
		// ��ȡ��Ƶ���ݣ����� select ��������ֱ����Ƶ���ݲɼ���ɡ�
		r = select (fd + 1, &fds, NULL, NULL, &tv);
		//printf("------------r=%d\n",r);

		if(r<0)
		{
      
			printf("**** 98987766555555555555555555555555555555555555Error:select error no %d\n", errno);
//			 continue;
			// return 0;
			return;
		}




		tmp_buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		tmp_buf.memory      = V4L2_MEMORY_MMAP;
		tmp_buf.index = 0;

		// ����Ƶ�����������������ȡ��һ���Ѿ�������һ֡��Ƶ���ݵ���Ƶ��������
		// ����VIDIOC_DQBUFִ�гɹ�����Ӧ���ں���Ƶ�������б����е�ǰ���㵽��
		// ��Ƶ���ݣ�Ӧ�ó������ͨ�������û��ռ�����ȡ����Ƶ���ݡ�
#if 1
		if(ioctl(fd, VIDIOC_DQBUF, &tmp_buf)<0)
		{
			printf("**** cmy1111111Error:VIDIOC_DQBUF\n");

			// return 0;
	          continue;
               //    return;
		}
#endif



		 iFrameCounter3++;
		 if(iFrameCounter3%100==0)
		 {
		 	gettimeofday(&tp3, NULL);
		 	
		 	iCostTime3 = (tp3.tv_sec - iSecond3)*1000000 + tp3.tv_usec - iuSecond3;
		 	 printf("####100 frame=%u us, fps=%f\n", iCostTime3, 1000000*100.0/iCostTime3) ;
		 	
		 	iSecond3 = tp3.tv_sec;
		 	iuSecond3 = tp3.tv_usec;
		 }
		
		
	printf("test Segmetation fault ...11...\n");	
		
		// 2013/2/20 19:54:10 �洢�Ҷ�ͼ
		// if(j>200)
		// if(j>20)
		if(iFlagCamera)
		{
			iCameraCounter++;
			iFlagCamera--;
			printf("test Segmetation fault ...1...\n");
			// д�Ҷ�ͼ
			char GRAYname[100];

			// sprintf(GRAYname, "gray%04d.bmp", j);
			// sprintf(GRAYname, "/sdcard/gray%04d.bmp", j);
			sprintf(GRAYname, "/testsuit/gray%04d.bmp", iCameraCounter);
			file_fd = fopen(GRAYname, "w");

			if(file_fd)
			{
				// fwrite(graybmphead, sizeof (unsigned char),1078,fp_YUV );
				fwrite(graybmphead, sizeof (unsigned char), 1078, file_fd );
				fwrite(buffers[tmp_buf.index].start, 640*480, 1, file_fd);
               //    fwrite(buffers[tmp_buf.index].start, 1280*720, 1, file_fd);
//				 fwrite(ucGrayBMP, 640*480, 1, file_fd);
			}

			fclose (file_fd);

			// printf ("**** wyb3 write BMP success j=%d!!!!\n", j);
			printf ("**** cmy3 write BMP success j=%d!!!!\n", iCameraCounter);
		}




		tmp_buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		tmp_buf.memory      = V4L2_MEMORY_MMAP;

		// Ͷ��һ���յ���Ƶ����������Ƶ��������������С�����ִ�гɹ���ָ�����Ƶ������
		// ������Ƶ������У���������Ƶ�豸����ͼ��ʱ����Ӧ����Ƶ���ݱ����浽��Ƶ�������
		// ��Ӧ����Ƶ�������С�
		if(ioctl(fd, VIDIOC_QBUF, &tmp_buf)<0)
		{
		     printf("#### cmy55555555Error:VIDIOC_QBUF\n");

			// return 0;
			continue;
		}
		
		
		
		
		iFrameCounter4++;
		if(iFrameCounter4%100==0)
		{
			gettimeofday(&tp4, NULL);
			
			iCostTime4 = (tp4.tv_sec - iSecond4)*1000000 + tp4.tv_usec - iuSecond4;
			printf("@@@@ 100 frame=%u us, fps=%f\n",iCostTime, 1000000*100.0/iCostTime) ;
			printf("####100 frame=%u us, fps=%f\n", iCostTime3, 1000000*100.0/iCostTime3) ;
			printf("^^^^ 100 frame=%u us, fps=%f\n", iCostTime4, 1000000*100.0/iCostTime4) ;
			//	fps = 1/( (iCostTime4/1000000)/100 );
			  printf("^^^^ 100 frame=%u us, fps=%f iCounter100frame=%d\n", iCostTime4, 1000000*100.0/iCostTime4, iCounter100frame) ;
			  //	printf("&&&&video0 100 frame=%u us, fps=%f iCounter100frame=%d\n", iCostTime4, 1000000*100.0/iCostTime4, iCounter100frame) ;
			
			iSecond4 = tp4.tv_sec;
			iuSecond4 = tp4.tv_usec;
			
			iCounter100frame++;
			printf("\n\n") ;
		}
	}




	// ֹͣ��Ƶ�ɼ����Ӧ�ó������ VIDIOC_ STREAMOFFͣ�������
	// ��Ƶ�豸���������ٲɼ���Ƶ���ݡ� 
	if(ioctl(fd, VIDIOC_STREAMOFF, &type)<0)
	{
		printf("Error:VIDIOC_STREAMOFF\n");

		// return 0;
		return;
	}

	printf("================streamoff\n");




	printf("\n capabilities= 0x%08x, iCapCapabilities=0x%08x \n",cap.capabilities, iCapCapabilities);
	getCameraCapabilities(iCapCapabilities);
	// ����ڴ�ӳ��
	for(i=0;i<req.count;i++)
	{
		munmap(buffers[i].start, buf[i].length);
	}

	close(fd);

	// return 0;
	return;
} 




// �������ƣ�main
// �������ܣ�������
// �����б�
// ����ֵ  ��
int main(int argc, char **argv)
{
	pthread_t id1;
	pthread_t id2;
	int ret2;




	ret2=pthread_create(&id1,NULL,(void *) thread1,NULL);

	if(ret2!=0)
	{
		printf ("Create pthread1 error!\n");
		// exit (1);

		return 0;
	}




	ret2=pthread_create(&id2,NULL,(void *) thread2,NULL);

	if(ret2!=0)
	{
		printf ("Create pthread2 error!\n");
		// exit (1);

		return 0;
	}




	pthread_join(id1,NULL);
	pthread_join(id2,NULL);




	return 0;
}

