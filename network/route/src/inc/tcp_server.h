/******************************************************************************
  文 件 名   : tcp_server.h
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月16日
  最近修改   :
  功能描述   : tcp_server.c 的头文件
******************************************************************************/

#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/
extern void tcp_send_arp_table(TYPE_Route *rt, int connfd);
extern void tcp_send_firewall_rules(TYPE_Route *rt, int connfd);
extern void tcp_send_port_info(TYPE_Route *rt, int connfd);
extern void dispose_tcp_cmd(TYPE_Route *rt, int connfd, char cmd[]);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TCP_SERVER_H__ */
