/******************************************************************************
  �� �� ��   : tcp_server.h
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��16��
  ����޸�   :
  ��������   : tcp_server.c ��ͷ�ļ�
******************************************************************************/

#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
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
