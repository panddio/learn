/* ************************************************************************
 *       Filename:  variable_arg.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月23日 星期四 08時20分25秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdarg.h>

int demo(char *msg,...)
{
	va_list argp; //定义保存函数参数的结构
	int argno;    //记录参数个数
	char *para;   //存放取出的字符串参数

	//argp 指向第一个可选的参数
	//msg  是最后一个确定的参数
	va_start(argp,msg);
	while(1)
	{
		para = va_arg(argp,char *);//取出当前参数，类型为char *
		if(strcmp(para,"\0")==0) break;//采用空串指示参数输入结束

		printf("argument #%d is: %s\n",argno,para);
		argno++;
	}

	va_end(argp);//将argp设置为NULL
	return argno;
}
int main()
{
	demo("DEMO","This","is","a","test!","\0");

	return 0;
}
