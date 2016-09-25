/* ************************************************************************
 *       Filename:  mystring.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月24日 星期五 03時39分01秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  王秋伟 
 *        Company:  
 * ************************************************************************/
#include<math.h>
#include<string.h>
#include"mystring.h"

void mystrinv(char *src)
{
	char *head = NULL;
	char *trail= NULL;
	char ch;
	int i = 0;

	while(src[i++]);
	head = src;
	trail= head + i -2;

	while(trail > head)
	{
		ch = *head;
		*head = *trail;
		*trail= ch;
		head++;
		trail--;
	}
}

int mystrlen(char *src)
{
	int i= 0;

	while(src[i++]);

	return i-1;
}

int mystrcpy(char *obj, char *src)
{
	int i = 0;

	while(src[i])
	{
		obj[i] = src[i];
		i++;
	}

	obj[i] = '\0';

	return i;
}

int mystrcmp(char *src1, char *src2)
{
	int i = 0;

	while(src1[i++])
	{
		if(src1[i]>src2[i])
		{
			return 1;
		}
		else if(src1[i]<src2[i])
		{
			return -1;
		}
	}

	return 0;
}
int strchange(char *src)
{
	int i = 0;
	int len = 0, res = 0;
	len = strlen(src);

	for(i=0;i<len;i++)
	{
		res += pow(10,len-i-1) * (src[i]-48);
	}

	return res;
}
