/*************************************************************************
	> Filename: common.h
	>   Author: Qiuwei.wang
	>    Email: qiuwei.wang@ingenic.com / panddio@163.com
	> Datatime: Fri 02 Dec 2016 02:24:29 PM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

#define TRUE   1
#define FALSE  0
#define CLEAR(x) memset (&(x), 0, sizeof (x))

#define errno_exit(str)     \
	do {                    \
		fprintf(stderr, "%s error %d, %s\n",  \
			str, errno, strerror(errno));     \
		exit(EXIT_FAILURE); \
	} while(0)

#define xioctl(fd, request, arg)  \
	({                             \
		int ret;                  \
		do {                      \
			ret = ioctl(fd, request, arg);    \
		} while(-1 == ret && EINTR == errno); \
                                              \
		ret; \
	})


/*
 * Extern functions
 */
void *JZMalloc(int align, int size);
void jz47_free_alloc_mem();
unsigned int get_phy_addr(unsigned int vaddr);

#endif
