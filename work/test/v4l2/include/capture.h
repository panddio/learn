/*************************************************************************
	> Filename: capture.h
	>   Author: Qiuwei.wang
	>    Email: qiuwei.wang@ingenic.com
	> Datatime: Fri 02 Dec 2016 10:07:17 AM CST
 ************************************************************************/

#ifndef _CAPTURE_H
#define _CAPTURE_H

/*
 * Struct
 */
typedef enum {
	IO_METHOD_READ,
	IO_METHOD_MMAP,
	IO_METHOD_USERPTR,
} io_method;

struct buffer {
	void *start;
	size_t length;
};

struct capture_t {
	char *dev_name;
	int fd;
	unsigned int width;
	unsigned int height;
	unsigned int bpp;
	unsigned int sizeimage;
	unsigned int nbuf;
	unsigned int count;

	io_method io;
	struct buffer *pbuf;
};

/*
 * Extern functions
 */
int read_frame(struct capture_t *capt);
void process_image(struct capture_t *capt, int index);
void start_capturing(struct capture_t *capt);
void stop_capturing(struct capture_t *capt);
void test_framerate(struct capture_t *capt);
void open_device(struct capture_t *capt);
void close_device(struct capture_t *capt);
void init_device(struct capture_t *capt);
void free_device(struct capture_t *capt);
void main_loop(struct capture_t *capt);

#endif
