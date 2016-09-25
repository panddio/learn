/******************************************************************************
  文 件 名   : main.c
  版 本 号   : 初稿
  作    者   : 呵呵
  生成日期   : 2015年9月11日
  功能描述   : 主函数
******************************************************************************/
#include "common.h"
#include "route_control.h"
#include "route_pthread.h"



int main(int argc, char *argv[])
{
	TYPE_Route route;       // 定义路由器结构体变量

	route_init(&route);     // 路由器初始化
	create_pthread(&route); // 创建线程

	return 0;
}


