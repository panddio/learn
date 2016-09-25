/* ************************************************************************
 *       Filename:  transform.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月20日 星期一 05時42分57秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/



#include <stdio.h>


int main(int argc, char *argv[])
{
	char ch[20]={0};
	char i;
	printf("请输入一个长度小于或等于20的字符串：");
	gets(ch);

	for(i=0;i<20;i++)
	{
		if(ch[i]>='a' && ch[i]<='z')
		{
			ch[i] -=32;
		}
		else if(ch[i]>='A' && ch[i]<='z')
		{
			ch[i] +=32;
		}
	}

	printf("转换后的字符串：%s\n",ch);
	return 0;
}
