/******************************************************************************
  文 件 名   : route_pthread.h
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月11日
  最近修改   :
  功能描述   : route_pthread.c 的头文件
******************************************************************************/

#ifndef __ROUTE_PTHREAD_H__
#define __ROUTE_PTHREAD_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * 函数原型说明                                 *
 *----------------------------------------------*/
extern void create_pthread(TYPE_Route *rt);
extern void dispose_key_cmd(TYPE_Route *rt, char cmd[]);
extern void *pthread_deal_message(void *arg);
extern void *pthread_key_event(void *arg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ROUTE_PTHREAD_H__ */
