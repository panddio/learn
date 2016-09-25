/* ************************************************************************
 *       Filename:  scan_dir.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月11日 14时34分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


int  gs_index = 0; //指向当前显示的图片
int  gs_bmp_total = 0;	//图片总数
char *gs_bmp_name[50] = {""};//存放图片目录和文件名地址的指针数组


//=================================================================================
// 函数介绍：	保存图片的目录和名字的地址到指针数组里
// 输入参数：	图片的路径：path
// 				图片的名字：bmp
// 返回值：		无
//=================================================================================
void save_bmp_name(char *path, char *bmp)
{
	gs_bmp_name[gs_bmp_total] = (char *)malloc(strlen(bmp)+1+strlen(path));
	bzero(gs_bmp_name[gs_bmp_total], strlen(bmp)+1); //将申请的内存清零
	strcpy(gs_bmp_name[gs_bmp_total], path);
	strcat(gs_bmp_name[gs_bmp_total], bmp);
	gs_bmp_total++;
}
//=================================================================================
// 函数介绍：	获取并保存图片的名字
// 输入参数：	图片的路径：path
// 返回值：		无
//=================================================================================
void get_bmp_name(char *path)
{
	DIR *dir;
	struct dirent *ptr;
	
	dir = opendir(path);
	while((ptr = readdir(dir)) != NULL)
	{
		//存图片名
		if(strstr(ptr->d_name, ".bmp"))
		{
			//printf("ptr->d_name = %s\n", ptr->d_name);
			save_bmp_name(path, ptr->d_name);
		}
	}
	closedir(dir);
}
//=================================================================================
// 函数介绍：	转换图片的名字为数字
// 输入参数：	图片的路径+图片名：bmp_pathname
// 返回值：		图片的编号
//=================================================================================
int conver_bmp_name(char *bmp_pathname)
{
	int num = 0;
	
	sscanf(bmp_pathname, "./image/%d", &num);
	//printf("num=%d\n", num);
	return num;
}
//=================================================================================
// 函数介绍：	根据图片的名字排序
// 输入参数：	无
// 返回值：		无
//=================================================================================
void order_bmp_name(void)
{
	char *tmp = NULL;
	int j, k;
	
	for(j=0;j<gs_bmp_total-1;j++)
	{
		for(k=j+1; k<gs_bmp_total; k++)
		{
			if(conver_bmp_name(gs_bmp_name[j]) > conver_bmp_name(gs_bmp_name[k]))
			{
				tmp = gs_bmp_name[k];
				gs_bmp_name[k] = gs_bmp_name[j];
				gs_bmp_name[j]= tmp;
			}
		}
	}
	
}
//=================================================================================
// 函数介绍：	打印图片的名字
// 输入参数：	无
// 返回值：		无
//=================================================================================
void bmp_name_print(void)
{
	int i;
	
	printf("gs_bmp_total = %d\n", gs_bmp_total);
	for(i=0;i<gs_bmp_total;i++)
	{
		printf("bmp_name = %s\n", gs_bmp_name[i]);
	}
}