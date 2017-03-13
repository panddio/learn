#include "futil.h"


#ifndef WIN32
DWORD GetTickCount(void)
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	return (tv.tv_sec*1000 + tv.tv_usec/1000);
}
#endif

int WriteBitmap(const BYTE *buffer, int Width, int Height, const char *file)
{
	char Buffer[0x500];
	BITMAPFILEHEADER *bmpfheader=(BITMAPFILEHEADER *)Buffer;
	BITMAPINFO *bmpinfo=(BITMAPINFO *)(((char*)bmpfheader)+14);
	int i,w;
	FILE *f;
	memset(bmpfheader,0,0x500);
	bmpfheader->bfType =19778;
	w = ((Width+3)/4)*4*Height+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFO)+255*sizeof(RGBQUAD);
	memcpy((void*)(((char*)bmpfheader)+2), &w, 4);
	//bmpfheader->bfOffBits;
	w= sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFO)+255*sizeof(RGBQUAD);
	memcpy((void*)(((char*)bmpfheader)+10), &w, 4);
	bmpinfo->bmiHeader.biWidth=Width;
	bmpinfo->bmiHeader.biHeight=Height;
	bmpinfo->bmiHeader.biBitCount=8;
	bmpinfo->bmiHeader.biClrUsed=0;
	bmpinfo->bmiHeader.biSize=sizeof(bmpinfo->bmiHeader);
	bmpinfo->bmiHeader.biPlanes=1;
	bmpinfo->bmiHeader.biSizeImage=((Width+3)/4)*4*Height;
	f=fopen(file, "wb");
	if(f)
	{
		for(i=1;i<256;i++)
		{
			bmpinfo->bmiColors[i].rgbBlue=i;
			bmpinfo->bmiColors[i].rgbGreen=i;
			bmpinfo->bmiColors[i].rgbRed=i;
		}
		fwrite(Buffer, sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD), 1, f);

		w = ((Width+3)/4)*4;
		buffer+=Width*(Height-1);
		for(i=0; i<Height; i++)
		{
			fwrite(buffer, Width, 1, f);
			if(w-Width)
				fwrite(buffer, w-Width, 1, f);
			buffer-=Width;
		}
		fclose(f);
		return Width*Height;
	}
	return 0;
}

BYTE *LoadFile(const char *FileName)
{
	BYTE *data=NULL;
	FILE *f=fopen(FileName, "rb"); 
	long s;
	if(!f) return 0;
	fseek(f,0,SEEK_END);
	s=ftell(f);
	if(s>0)
	{
		fseek(f,0,SEEK_SET);
		data=(BYTE*)malloc(s);
		if (1>(long)fread(data, s, 1, f))
		{
			free(data);
			data=NULL;
		}
	}
	fclose(f);
	return data;
}

int SaveToFile(const char *fileName, void *buffer, int size)
{
	FILE *f=fopen(fileName, "wb");
	if(f==NULL)
	{
		logMsg("Open file %s to write fail.\n", fileName);
		return 0;
	}
	fwrite(buffer, size, 1, f);
	fclose(f);
	return 1;
}

static FILE *logf=NULL;
static unsigned int startTick=0;

int logClose()
{
	if(logf) 
	{
		fprintf(logf, "%ld:\tEnd Log.\n", GetTickCount()-startTick);
		fclose(logf);
		logf=NULL;
	}
	return 0;
}

int logMsg(char *fmt, ...)
{
	static int lastEnd=0;
	unsigned int theTick=GetTickCount();
	va_list argptr;
	va_start(argptr, fmt);
//	return 0;
	if(logf==NULL)
	{
		logf=fopen("log.txt", "w");
	}
	if(logf==NULL) return 0;
	if(startTick==0)
	{
		startTick=theTick;
		fprintf(logf, "%d:\tStart Log.\n", startTick);
		lastEnd=1;
	}
	if(lastEnd)
		fprintf(logf, "%d:\t",theTick-startTick);
	lastEnd=(fmt[strlen(fmt)-1]=='\n')?1:0;
	vfprintf(logf, fmt, argptr);
	vprintf(fmt, argptr);
	return 1;
}


int ReadBitmap(BYTE *p, BYTE *buffer, int *Width, int *Height)
{
	BITMAPFILEHEADER *bmpfheader=(BITMAPFILEHEADER *)p;
	BITMAPINFO *bmpinfo=(BITMAPINFO *)(p+14);
	int i,w;
	if(!p) return 0;

	*Width = bmpinfo->bmiHeader.biWidth;
	*Height=bmpinfo->bmiHeader.biHeight;
	if((bmpfheader->bfType ==19778) && (bmpinfo->bmiHeader.biCompression==0) &&
		(bmpinfo->bmiHeader.biBitCount==8))
	{
		if(bmpinfo->bmiHeader.biClrUsed==0) bmpinfo->bmiHeader.biClrUsed=256;
		if(bmpinfo->bmiHeader.biClrUsed!=256) return 0;
		p+=0x436;
		w = ((*Width+3)/4)*4;
		p+=w*(*Height-1);
		if(buffer)
			for(i=0; i<(int)*Height; i++)
			{
				memcpy(buffer, p, *Width);
				buffer+=*Width;
				p-=w;
			}
	}
	return *Width**Height;
}

int LoadBitmapFile(const char *FileName, BYTE *buffer, int *Width, int *Height)
{
	unsigned char *p=LoadFile(FileName);
	int res=ReadBitmap(p, buffer, Width, Height);
	free(p);
	return res;
}

void msleep(int msec)
{
	struct timeval delay;
	delay.tv_sec =msec /1000;
	delay.tv_usec =(msec%1000)*1000;
	select(0, NULL, NULL, NULL, &delay);
}

int dumpData(const unsigned char *data, int dataSize, const char *title)
{
	static char Hex[17]="0123456789ABCDEF";
	int i, linec=0;
	char line[20];
	printf("Dump %s: Size=%d\n", title? title: "Data", dataSize);
	for(i=0; i<dataSize;i++)
	{
		char HexData[3];
		HexData[0]=Hex[data[i]>>4]; HexData[1]=Hex[data[i]&0x0F]; HexData[2]=0;
		if(linec==0) printf("  ");
		printf("%s ", HexData);
		if(data[i]>=0x20 && data[i]<0x7F)
			line[linec]=data[i];
		else
			line[linec]='.';
		if(++linec>=16)
		{
			line[linec]=0;
			printf("  %s\n", line);
			linec=0;
		}
	}
	if(linec)
	{
		for(i=0;i<16-linec;i++) printf("   ");
		line[linec]=0;
		printf("  %s\n",line);
	}
	return 0;
}
