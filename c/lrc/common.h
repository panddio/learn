#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>


#define  uint   unsigned int
#define  ulint  unsigned long int
#define  uchar  unsigned char

typedef struct lrc
{
	//float time;
	int time;
	char *psrc;
	
	struct lrc *prev;
	struct lrc *next;
}LRC;

#endif