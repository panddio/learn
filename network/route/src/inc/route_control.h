/******************************************************************************
  文 件 名   : route_control.h
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月11日
  最近修改   :
  功能描述   : route_control.c 的头文件
******************************************************************************/
#ifndef __ROUTE_CONTROL_H__
#define __ROUTE_CONTROL_H__


/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/
extern void route_init(TYPE_Route *rt);
extern void show_port_info(TYPE_Route *rt, char *port_name);
extern void get_ethernet_port(TYPE_Route *rt);
extern void build_arp_table(TYPE_Route *rt);
extern Boolean broadcast(TYPE_Route *rt, const uchar ip[]);


#endif /* __ROUTE_CONTROL_H__ */
