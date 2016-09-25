/******************************************************************************
  文 件 名   : firewall_link.h
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月13日
  最近修改   :
  功能描述   : firewall_link.c 的头文件
******************************************************************************/

#ifndef __FIREWALL_LINK_H__
#define __FIREWALL_LINK_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * 函数原型说明                                 *
 *----------------------------------------------*/
extern FIRE_Wall *delete_firewall_node(FIRE_Wall *head, const char *rule);
extern FIRE_Wall *free_firewall_link(FIRE_Wall *head);
extern FIRE_Wall *insert_firewall_node(FIRE_Wall *head, FIRE_Wall node);
extern void print_firewall(FIRE_Wall *head);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __FIREWALL_LINK_H__ */
