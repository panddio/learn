/******************************************************************************
  �� �� ��   : msg_dispose.h
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��11��
  ����޸�   :
  ��������   : msg_dispose.c ��ͷ�ļ�
******************************************************************************/
#ifndef __MSG_DISPOSE_H__
#define __MSG_DISPOSE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * ����ԭ��˵��                                 *
 *----------------------------------------------*/
extern uint16 get_type(const uchar *recv);
extern void get_mac(const uchar *recv, uchar *dst_mac, uchar *src_mac);
extern void get_ip(const uchar *recv, uchar *dst_ip, uchar *src_ip);
extern void show_msg_ip(uchar const *recv);
extern Boolean check_if_same_subnet(const uchar eth_mask[], const uchar eth_ip[], const uchar dst_ip[]);
extern int get_transpond_port(TYPE_Route *rt, const uchar dst_ip[]);
extern int send_msg(TYPE_Route *rt, int port, int msg_len);
extern int transpond_msg(TYPE_Route *rt, const uchar dst_ip[], int port, int msg_len);
extern int reply_arp_requset(TYPE_Route *rt, MSG_Info *pinfo, ARP_Hdr *arp_hdr);
extern void dispose_arp_reply(ARP_Table *head, ARP_Hdr *arp_hdr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __MSG_DISPOSE_H__ */
