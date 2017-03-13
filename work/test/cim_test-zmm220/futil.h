#ifndef _FUTIL_H_
#define _FUTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>
#include <sys/time.h>
#include "bmp.h"

DWORD GetTickCount(void);

int WriteBitmap(const BYTE *buffer, int Width, int Height, const char *file);

BYTE *LoadFile(const char *FileName);

int SaveToFile(const char *fileName, void *buffer, int size);

int logClose();

int logMsg(char *fmt, ...);


int ReadBitmap(BYTE *p, BYTE *buffer, int *Width, int *Height);

int LoadBitmapFile(const char *FileName, BYTE *buffer, int *Width, int *Height);

void msleep(int msec);

int dumpData(const unsigned char *data, int dataSize, const char *title);

#endif
