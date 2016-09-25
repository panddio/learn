/* ************************************************************************
 *       Filename:  file.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月31日 星期五 05時35分04秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "common.h"
#include "process_lrc.h"
#include "file.h"

/**************************************************************************
*函数功能:读出文件内容
*参数：file_length    整型指针，此地址中保存文件字节数。
*      lrc_src  文件名字，从此文件中读取内容。
* 返回值:读出字符串的首地址
* 函数中测文件的大小并分配空间，再把文件内容读出到分配的空间中，返回此空间首地址
**************************************************************************/ 
char *read_src_file(ulint *file_length, char *lrc_src)
{
	FILE *fp = NULL;
	char *buf = NULL;	
	
	fp = fopen(lrc_src,"rb");//以只读方式打开一个二进制文件
	
	if(fp == NULL)
	{
		printf("Cannot open the flie!\n");
		return NULL;
	}
	fseek(fp,0,SEEK_END);
	*file_length = ftell(fp); //获取文件的大小
	
	buf = (char *)malloc(*file_length+1); //
	
	if(buf == NULL)
	{
		printf("malloc() cannot apply for memory!\n");
		goto out;
	}
	
	bzero(buf, *file_length+1);
	
	rewind(fp); //
	fread(buf,*file_length,1,fp);
	
	out:
	fclose(fp);
	return buf;
}
#if 1
char *get_musiclist(char ***plist, int *plines)
{
	FILE *fp =NULL;
	char *buf = NULL;	
	ulint list_length = 0;
	//uint lines = 0;
	int part = 0;
	system("ls ./music | grep .mp3 >./music/musiclist");
	
	fp = fopen("music/musiclist","rb");
	if(fp == NULL)
	{
		printf("Cannot open the flie!\n");
		return NULL;
	}
	buf = read_src_file(&list_length,"music/musiclist");	
	*plines = check_lines(list_length, buf);
	
	*plist = (char **)malloc((*plines  + 1) * sizeof(char **));  //动态分配空间存储每行的首地址
	
	if(*plist == NULL)
	{
		goto out;
		return NULL; 
	}

	bzero(*plist, *plines+1);
	
	part = src_segment(buf, *plist, "\r\n");	              //按行分割
	plist[*plines ] = NULL; 
	
#if 0 //
   int i, len;
	for(i=0;i<part;i++)
	{
		len = strlen(*(*(plist) + i));
		*(*(*(plist) + i) + len -4) = '\0';
		//printf("%s\n",plist[i]);
	}	
#endif	
	out:
	fclose(fp);
	return buf;
}
#else
char **get_musiclist()
{
	FILE *fp =NULL;
	char *buf = NULL, **plist = NULL;	
	ulint list_length = 0;
	uint lines = 0;
	int part = 0;
	system("ls ./music | grep .mp3 >./music/musiclist");
	
	fp = fopen("music/musiclist","rb");
	if(fp == NULL)
	{
		printf("Cannot open the flie!\n");
		return;
	}
	buf = read_src_file(&list_length,"music/musiclist");	
	lines = check_lines(list_length, buf);
	
	plist = (char **)malloc((lines + 1) * sizeof(char **));  //动态分配空间存储每行的首地址
	
	if(plist == NULL) return NULL; 
	
	part = src_segment(buf, plist, "\r\n");	         //按行分割
	plist[lines] = NULL; 
	
#if 1
   int i, len;
	for(i=0;i<part-1;i++)
	{
		len = strlen(*(*(plist) + i));
		//printf("len =%d\n",len);
		*(*(*(plist) + i) + len -1) = '\0';
		//printf("%s\n",plist[i]);
	}	
#endif
	fclose(fp);
	return plist;
}
#endif
int check_lines(ulint file_length, char *src)
{
	uint lines = 0;
	ulint i = 0;
	char *p = NULL;
	
	p = src;
	
	#if 1
	for(i = 0;i < file_length;i++)
	{
		if(p[i]=='\n')  lines++;
	}
	#elif 0 //这种方法不行，因为strchr函数和strstr函数遇到 '\0' 就返回
	while(p != NULL)
	{
		p = strchr(p,'\n');
		lines++;
	}
	#endif
	return lines;
}

int get_longestline(int lines, char *plines[])
{
	int longestline = 0, temp = 0, i = 0;
	
	for(i=0;i<lines;i++)
	{
		temp = strlen(plines[i]);
		
		if(temp > longestline) longestline = i;
	}
	return longestline;
}

int get_chrnumber(char *pbuf, int len)
{
	int i = 0,count = 0;
	
	for(i=0;i<len;i++)
	{
		if(pbuf[i] > 0 && pbuf[i] <127) count++;
	}
	return count;
}
int get_longestlength(LRC *lrc_head)
{
	int longest = 0, temp = 0, chrnum = 0;
	
	if(lrc_head != NULL)
	{
		LRC *pb = NULL, *pf = NULL;
		pb = lrc_head;
		
		while(pb != NULL)
		{
			temp = strlen(pb->src);
			if(temp > longest) 
			{
				pf = pb;
				longest = temp;
			}		
			//printf("len=%d  %s\n",temp,pb->src);
			pb = pb->next;
		}
		
		temp = strlen(pf->src);
		chrnum = get_chrnumber(pf->src,temp);
		longest += chrnum/2;
	}

	return longest;
}

int get_showoffset(char *pbuf, int longest)
{
	int len = 0, offset = 0;
	int count = 0;
	
	len = strlen(pbuf);
	count = get_chrnumber(pbuf, len);
	len += count/2;
	
	offset = (longest - len)/3;
	//printf("longest=%d len=%d offset=%d  %s\n",longest,len,offset,pbuf);
	if(offset < 0) offset = 0; //一定要加此判断
	return offset;
}
char get_songname(char *desr, char *src)
{
	char *p = NULL;
	char buf[256];

	bzero(buf,sizeof(buf));
	
	if((p = strstr(src, ".mp3")) != NULL)
	{
		sscanf(src,"%[^.mp3]",buf);
		strcat(buf,".mp3");
		strcpy(desr,buf);
		return 0;
	}
	return -1;
}

char get_lrcname(char *src)
{
	char *p = NULL;

	if((p = strstr(src, ".mp3")) != NULL)
	{
		*p = '\0';
		strcat(src,".lrc");
		return 0;
	}	

	return -1;
}

char *transfer_space(char src[])
{
	int i = 0, j = 0, len = 0;
	int space = 0;
	char *pbuf = NULL;
	
	len = strlen(src);
	
	while(src[i])
	{
		if(src[i] == ' ')
		{
			space++;
		}
		i++;
	}

	pbuf = (char *)malloc(sizeof(char) * (len + space + 2));

	if(pbuf == NULL) 
	{
		printf("transfer_space >> malloc failed\n");
		return NULL;
	}
	
	i = 0;
	while(src[i])
	{
		if(src[i] == ' ')
		{
			pbuf[j] = '\\';
			j++;
		}

		pbuf[j] = src[i];
		j++;
		i++;
	}	
	pbuf[j] = '\0';
	return pbuf;
}

void delete_dot(char *plist[])
{
	int i = 0,len = 0;
	
	for(i=0;plist[i] != NULL;i++)
	{
		len = strlen(plist[i]);
		plist[i][len-1] = '\0';
	}
}
void recover_dot(char *plist[])
{
	int i = 0,len = 0;
	
	for(i=0;plist[i] != NULL;i++)
	{
		len = strlen(plist[i]);
		plist[i][len] = '.';
	}
}

void recover_line_dot(char *plist[],int line_num)
{
	int len = 0;
	
	len = strlen(plist[line_num]);
	plist[line_num][len] = '.';

}

