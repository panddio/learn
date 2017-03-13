/*************************************************************************
	> Filename: capture.c
	>   Author: Qiuwei.wang
	>    Email: qiuwei.wang@ingenic.com / panddio@163.com
	> Datatime: Mon 28 Nov 2016 06:05:39 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>          /* for videodev2.h */
#include <linux/videodev2.h>

#include "common.h"
#include "yuv2bmp.h"
#include "capture.h"


/*
 * Functions
 */
static void init_read(struct capture_t *capt)
{
	capt->pbuf = calloc(1, sizeof(struct buffer));

	if(capt->pbuf) {
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}

	capt->pbuf[0].length = capt->sizeimage;
	capt->pbuf[0].start  = malloc(capt->sizeimage);

	if(!capt->pbuf[0].start) {
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}
}

static void init_mmap(struct capture_t *capt)
{
	int i;
	struct v4l2_requestbuffers req;

	CLEAR(req);
	req.count  = capt->nbuf;
	req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;

	/* Request buffer */
	if(-1 == xioctl(capt->fd, VIDIOC_REQBUFS, &req)) {
		if(EINVAL == errno) {
			fprintf(stderr, "%s does not support "
					"memory mapping\n", capt->dev_name);
			exit(EXIT_FAILURE);
		} else
			errno_exit("VIDIOC_REQBUFS");
	}

	if (req.count < 1) {
		fprintf(stderr, "Insufficient buffer memory on %s\n",
				capt->dev_name);
		exit(EXIT_FAILURE);
	}

	capt->pbuf = calloc(req.count, sizeof(struct buffer));
	if(!capt->pbuf) {
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}

	/* Update the value of nbuf */
	capt->nbuf = req.count;

	for(i = 0; i < req.count; i++) {
		struct v4l2_buffer buf;

		CLEAR(buf);
		buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index  = i;

		/* Get address and length of the frame buffer */
		if(-1 == xioctl(capt->fd, VIDIOC_QUERYBUF, &buf))
			errno_exit("VIDIOC_QUERYBUF");

		/* memory map */
		capt->pbuf[i].length = buf.length;
		capt->pbuf[i].start  = mmap(NULL,
								    buf.length,
								    PROT_READ | PROT_WRITE,
								    MAP_SHARED,
								    capt->fd, buf.m.offset);

		if(MAP_FAILED == capt->pbuf[i].start)
			errno_exit("mmap");
	}
}

static void init_userp(struct capture_t *capt)
{
	int i;
	unsigned int page_size;
	unsigned int buffer_size;
	struct v4l2_requestbuffers req;

	page_size = getpagesize();
	buffer_size = (capt->sizeimage + page_size - 1) & ~(page_size - 1);

	CLEAR(req);
	req.count  = capt->nbuf;
	req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_USERPTR;

	/* Request buffer */
	if(-1 == xioctl(capt->fd, VIDIOC_REQBUFS, &req)) {
		if(EINVAL == errno) {
			fprintf(stderr, "%s does not support "
					"user pointer i/o\n", capt->dev_name);
			exit(EXIT_FAILURE);
		} else
			errno_exit("VIDIOC_REQBUFS");
	}

	if (req.count < 1) {
		fprintf(stderr, "Insufficient buffer memory on %s\n",
				capt->dev_name);
		exit(EXIT_FAILURE);
	}

	capt->pbuf = calloc(req.count, sizeof(struct buffer));
	if(!capt->pbuf) {
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}

	/* Update the value of nbuf */
	capt->nbuf = req.count;

	for(i = 0; i < capt->nbuf; i++) {
		capt->pbuf[i].length = buffer_size;
		capt->pbuf[i].start  = JZMalloc(128, buffer_size);

		if(!capt->pbuf[i].start) {
			fprintf(stderr, "Out of memory\n");
			exit(EXIT_FAILURE);
		}
	}
}

void process_image(struct capture_t *capt, int index)
{
	unsigned char *rgbbuf = NULL;
	unsigned char *yuvbuf = NULL;

	yuvbuf = (unsigned char *)capt->pbuf[index].start;
	rgbbuf = (unsigned char *)malloc(capt->width * capt->height * 3);
	if(!rgbbuf) {
		fprintf(stderr, "malloc rgbbuf failed!!\n");
		errno_exit("malloc");
	}

	yuv2rgb(yuvbuf, rgbbuf, capt->width, capt->height);
	rgb2bmp("test.bmp", capt->width, capt->height, 24, rgbbuf);

	free(rgbbuf);
}

int read_frame(struct capture_t *capt)
{
	struct v4l2_buffer buf;
	unsigned int i;

	switch(capt->io) {
	case IO_METHOD_READ:
		if(-1 == read(capt->fd, capt->pbuf[0].start, capt->pbuf[0].length)) {
			switch(errno) {
			case EAGAIN:
				fprintf(stderr, "Read frame error: %d, %s\n", \
						errno, strerror(errno));
				return FALSE;

			case EIO:
			default:
				errno_exit("read");
			}
		}

		process_image(capt, 0);
		break;

	case IO_METHOD_MMAP:
		CLEAR(buf);
		buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;

		if(-1 == xioctl(capt->fd, VIDIOC_DQBUF, &buf)) {
			switch(errno) {
			case EAGAIN:
				fprintf(stderr, "Read frame error: %d, %s\n", \
						errno, strerror(errno));
				return FALSE;

			case EIO:
			default:
				errno_exit("VIDIOC_DQBUF");
			}
		}

		assert(buf.index < capt->nbuf);
		process_image(capt, buf.index);

		if(-1 == xioctl(capt->fd, VIDIOC_QBUF, &buf))
			errno_exit("VIDIOC_QBUF");

		break;

	case IO_METHOD_USERPTR:
		CLEAR(buf);
		buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_USERPTR;

		if(-1 == xioctl(capt->fd, VIDIOC_DQBUF, &buf)) {
			switch(errno) {
			case EAGAIN:
				fprintf(stderr, "Read frame error: %d, %s\n", \
						errno, strerror(errno));
				return FALSE;

			case EIO:
			default:
				errno_exit("VIDIOC_DQBUF");
			}
		}

		unsigned int page_size   = getpagesize();
		unsigned int buffer_size = (buf.length + page_size - 1) & ~(page_size - 1);
		for(i = 0; i < capt->nbuf; i++) {
			if((unsigned long)(capt->pbuf[i].start) == buf.m.userptr && \
			   (unsigned long)(capt->pbuf[i].length) == buffer_size)
				break;
		}

		assert(i < capt->nbuf);
		process_image(capt, i);

		if(-1 == xioctl(capt->fd, VIDIOC_QBUF, &buf))
			errno_exit("VIDIOC_QBUF");

		break;
	}

	return TRUE;
}

void start_capturing(struct capture_t *capt)
{
	int i;
	enum v4l2_buf_type type;

	switch(capt->io) {
	case IO_METHOD_READ:
		/* Nothing to do */
		break;

	case IO_METHOD_MMAP:
		/* Add to buffer queue */
		for(i = 0; i < capt->nbuf; i++) {
			struct v4l2_buffer buf;

			CLEAR(buf);
			buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory = V4L2_MEMORY_MMAP;
			buf.index  = i;

			if(-1 == xioctl(capt->fd, VIDIOC_QBUF, &buf))
				errno_exit("VIDIOC_QBUF");
		}

		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if(-1 == xioctl(capt->fd, VIDIOC_STREAMON, &type))
			errno_exit("VIDIOC_STREAMON");

		break;

	case IO_METHOD_USERPTR:
		/* Add to buffer queue */
		for(i = 0; i < capt->nbuf; i++) {
			struct v4l2_buffer buf;

			CLEAR(buf);
			buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory = V4L2_MEMORY_USERPTR;
			buf.index  = i;
			buf.length = capt->pbuf[i].length;
			buf.m.userptr = (unsigned long)capt->pbuf[i].start;

			if(-1 == xioctl(capt->fd, VIDIOC_QBUF, &buf))
				errno_exit("VIDIOC_QBUF");
		}

		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if(-1 == xioctl(capt->fd, VIDIOC_STREAMON, &type))
			errno_exit("VIDIOC_STREAMON");

		break;
	}
}

void stop_capturing(struct capture_t *capt)
{
    enum v4l2_buf_type type;

	switch(capt->io) {
	case IO_METHOD_READ:
		/* Nothing to do */
		break;

	case IO_METHOD_MMAP:
	case IO_METHOD_USERPTR:
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if(-1 == xioctl(capt->fd, VIDIOC_STREAMOFF, &type))
			errno_exit("VIDIOC_STREAMOFF");

		break;
	}
}

void test_framerate(struct capture_t *capt)
{
	fd_set fds;
	struct timeval tv;
	struct timeval start_tv;
	struct timeval end_tv;
	struct v4l2_buffer buf;
	int ret = 0;
	int count = 0;
	int costtime = 0;

	fprintf(stdout, "Start to test frame rate ...\n");
	start_capturing(capt);
	gettimeofday(&start_tv, NULL);

	while(1) {
		FD_ZERO(&fds);
		FD_SET(capt->fd, &fds);

		/* Select time */
		tv.tv_sec  = 2;
		tv.tv_usec = 0;

		ret = select(capt->fd + 1, &fds, NULL, NULL, &tv);
		if(ret < 0) {
			if(EINTR == errno)
				continue;
			errno_exit("select");
		} else if(0 == ret) {
			fprintf(stderr, "Select timeout\n");
			exit(EXIT_FAILURE);
		}

		CLEAR(buf);
		buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;

		if(-1 == xioctl(capt->fd, VIDIOC_DQBUF, &buf)) {
			switch(errno) {
			case EAGAIN:
			case EIO:
			default:
				errno_exit("VIDIOC_DQBUF");
			}
		}

		assert(buf.index < capt->nbuf);

		if(-1 == xioctl(capt->fd, VIDIOC_QBUF, &buf))
			errno_exit("VIDIOC_QBUF");

		count++;
		if(count == 60)
			break;
	}

	gettimeofday(&end_tv, NULL);
	costtime = (end_tv.tv_sec - start_tv.tv_sec) * 1000000 + \
			   (end_tv.tv_usec - start_tv.tv_usec);

	fprintf(stdout, "%s: get %d frame = %dus, fps = %f\n", \
			capt->dev_name, count, costtime, 1000000.0 * count/costtime);

	stop_capturing(capt);
}

void open_device(struct capture_t *capt)
{
	struct stat st;

	if(-1 == stat(capt->dev_name, &st)) {
		fprintf(stderr, "Cannot identify '%s': %d, %s\n",
				capt->dev_name, errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(!S_ISCHR(st.st_mode)) {
		fprintf(stderr, "%s is no device\n", capt->dev_name);
		exit(EXIT_FAILURE);
	}

	capt->fd = open(capt->dev_name, O_RDWR | O_NONBLOCK, 0);

	if(capt->fd < 0) {
		fprintf(stderr, "Cannot open '%s': %d, %s\n",
				capt->dev_name, errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void close_device(struct capture_t *capt)
{
	if(-1 == close(capt->fd))
		errno_exit("close");

	capt->fd = -1;
	free(capt->pbuf);
}

void init_device(struct capture_t *capt)
{
	unsigned int min;
	struct v4l2_capability cap;
	struct v4l2_cropcap cropcap;
	struct v4l2_crop crop;
	struct v4l2_format fmt;

	if(-1 == xioctl(capt->fd, VIDIOC_QUERYCAP, &cap)) {
		if(EINVAL == errno) {
			fprintf(stderr, "%s is no V4L2 device\n",
					capt->dev_name);
			exit(EXIT_FAILURE);
		} else
			errno_exit("VIDIOC_QUERYCAP");
	}

	if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
		fprintf(stderr, "%s is no video capture device\n",
				capt->dev_name);
		exit(EXIT_FAILURE);
	}

	switch(capt->io) {
	case IO_METHOD_READ:
		if(!(cap.capabilities & V4L2_CAP_READWRITE)) {
			fprintf(stderr, "%s does not support read i/o\n",
					capt->dev_name);
			exit(EXIT_FAILURE);
		}

		break;

	case IO_METHOD_MMAP:
	case IO_METHOD_USERPTR:
		if(!(cap.capabilities & V4L2_CAP_STREAMING)) {
			fprintf(stderr, "%s does not support streaming i/o\n",
					capt->dev_name);
			exit(EXIT_FAILURE);
		}

		break;
	}

	/* Select video input, video standard and tune here */
	CLEAR(cropcap);

	cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(0 == xioctl(capt->fd, VIDIOC_CROPCAP, &cropcap)) {
		crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		crop.c = cropcap.defrect; /* reset to default */

		if(-1 == xioctl(capt->fd, VIDIOC_S_CROP, &crop)) {
			switch(errno) {
			case EINVAL:
				/* Cropping not supported. */
				break;
			default:
				/* Errors ignored. */
				break;
			}
		}
	} else {
		/* Errors ignored */
	}

	CLEAR(fmt);
	fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width       = capt->width;
	fmt.fmt.pix.height      = capt->height;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	fmt.fmt.pix.field       = V4L2_FIELD_NONE; //V4L2_FIELD_INTERLACED;

	if(-1 == xioctl(capt->fd, VIDIOC_S_FMT, &fmt))
		errno_exit ("VIDIOC_S_FMT");

	/* Note VIDIOC_S_FMT may change width and height */
	min = fmt.fmt.pix.width * 2;
	if(fmt.fmt.pix.bytesperline < min)
		fmt.fmt.pix.bytesperline = min;

	min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
	if(fmt.fmt.pix.sizeimage < min)
		fmt.fmt.pix.sizeimage = min;

	/* Save image size */
	capt->sizeimage = min;

	capt->width  = fmt.fmt.pix.width;
	capt->height = fmt.fmt.pix.height;

	fprintf(stdout, "==> %s L%d: sizeimage = 0x%x, width = %d, height = %d\n", \
			__FUNCTION__, __LINE__, capt->sizeimage, capt->width, capt->height);

	switch(capt->io) {
	case IO_METHOD_READ:
		init_read(capt);
		break;

	case IO_METHOD_MMAP:
		init_mmap(capt);
		break;

	case IO_METHOD_USERPTR:
		init_userp(capt);
		break;
	}
}

void free_device(struct capture_t *capt)
{
	int i;

	switch(capt->io) {
	case IO_METHOD_READ:
		free(capt->pbuf[0].start);
		break;

	case IO_METHOD_MMAP:
		for(i = 0; i < capt->nbuf; i++) {
			if(-1 == munmap(capt->pbuf[i].start, \
							capt->pbuf[i].length))
				errno_exit("munmap");
		}

		break;

	case IO_METHOD_USERPTR:
		jz47_free_alloc_mem();
		break;
	}
}

void main_loop(struct capture_t *capt)
{
	fd_set fds;
	struct timeval tv;
	int ret;
	int count = 5;

	while(count--) {
		FD_ZERO(&fds);
		FD_SET(capt->fd, &fds);

		/* Select time */
		tv.tv_sec  = 2;
		tv.tv_usec = 0;

		ret = select(capt->fd + 1, &fds, NULL, NULL, &tv);
		if(ret < 0) {
			if(EINTR == errno)
				continue;
			errno_exit("select");
		} else if(0 == ret) {
			fprintf(stderr, "Select timeout\n");
			exit(EXIT_FAILURE);
		}

		if(read_frame(capt))
			break;
	}
}
