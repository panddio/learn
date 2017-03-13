/*************************************************************************
	> Filename: jz_mem.c
	>   Author: Qiuwei.wang
	>    Email: qiuwei.wang@ingenic.com
	> Datatime: Fri 02 Dec 2016 05:58:47 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


struct JZ_MEM_DEV {
	unsigned int vaddr;
	unsigned int paddr;
	unsigned int totalsize;
	unsigned int usedsize;
} 
