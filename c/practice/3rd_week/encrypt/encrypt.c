/* ************************************************************************
 *       Filename:  encrypt.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月30日 星期四 02時04分32秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  王秋伟
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "encrypt.h"
/************************************************************************** 
*函数功能:获取 目的文件 和 源文件 的名字
*参数：src_file_name   源文件名字字符数组首地址。
*      dest_file_name  目的文件的名字字符数组首地址
**************************************************************************/ 
void get_file_name(char * dest_file_name,char * src_file_name)
{
	printf("请输入原文件的名称（30个字符）: ");
	scanf("%s",src_file_name);

	printf("请输入目的文件名（30个字符）： ");
	scanf("%s",dest_file_name);
}
/**************************************************************************
*函数功能:读出文件内容
*参数：file_length    整型指针，此地址中保存文件字节数。
*      src_file_name  文件名字，从此文件中读取内容。
* 返回值:读出字符串的首地址
* 函数中测文件的大小并分配空间，再把文件内容读出到分配的空间中，返回此空间首地址
**************************************************************************/ 
char * read_src_file(unsigned long int *file_length,char *src_file_name)
{
	FILE *fp = NULL;
	char *buf = NULL;

	fp = fopen(src_file_name,"rb");//以只读方式打开一个二进制文件

	if(fp == NULL)
	{
		printf("Cannot open the flie!\n");
		return;
	}
	fseek(fp,0,SEEK_END);
	*file_length = ftell(fp); //获取文件的大小

	buf = (char *)malloc(*file_length); //
	if(buf == NULL)
	{
		printf("malloc() cannot apply for memory!\n");
		goto out;
	}
	rewind(fp); //
	fread(buf,*file_length,1,fp);

	out:
	fclose(fp);
	return buf;
}

/**************************************************************************
*函数功能:加密字符串
*参数：src_file_text  要加密的字符串。length:字符串的长度
*      password       加密密码
*返回值: 加密后的字符串的首地址
*加密原理字符数组中每个元素加上password
**************************************************************************/ 
char * file_text_encrypt(char * src_file_text,unsigned long int length,unsigned int password)
{
	int i;

	for(i=0;i<length;i++)
	{
		*(src_file_text + i)  += password;
	}

	return src_file_text;
}
/**************************************************************************
*函数功能:解密字符串
*参数：src_file_text  要解密的字符串。length:字符串的长度
*      password       解密密码
*返回值: 解密后的字符串的首地址
*思想;把数组中的每个元素减去password 给自己赋值。
**************************************************************************/ 
char * file_text_decrypt(char * src_file_text,unsigned long int length,unsigned int password)
{
	int i;

	for(i=0;i<length;i++)
	{
		*(src_file_text + i)  -= password;
	}
	return src_file_text;
}
/**************************************************************************
*函数功能:将字符串保存到目的文件中
*参数：text       要保存的字符串首地址
*      file_name  目的文件的名字
*      length     字符串的长度
*思想：传入字符数组的首地址和数组的大小及保存后的文件的名字，即可保存数组到文件中
**************************************************************************/ 
void save_file(char* text,unsigned long int length,char * file_name)
{
	FILE *fp = NULL;

	fp = fopen(file_name,"wb");

	if(fp == NULL)
	{
		printf("Cannot open the file!\n");
		return;
	}

	fwrite(text,length,1,fp); //保存text中的数据到文件
	printf("Data is successfully saved!\n");
	fclose(fp);
}
