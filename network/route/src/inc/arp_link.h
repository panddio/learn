/******************************************************************************
  �� �� ��   : link.h
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��11��
  ����޸�   :
  ��������   : link.c ��ͷ�ļ�
******************************************************************************/
#ifndef __LINK_H__
#define __LINK_H__


/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/
extern uint iptoun_btob(const uchar *ip);
extern uint iptoun_btol(const uchar *ip);
extern ARP_Table *insert_arp_table(ARP_Table *head, ARP_Table node);
extern ARP_Table *delete_arp_node(ARP_Table *head, const uchar *ip);
extern ARP_Table *free_arp_table(ARP_Table *pnode);
extern Boolean change_arp_mac(ARP_Table *head, const uchar ip[], const uchar mac[]);
extern void print_arp_table(ARP_Table *head);


#endif /* __LINK_H__ */
