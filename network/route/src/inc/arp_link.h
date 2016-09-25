/******************************************************************************
  文 件 名   : link.h
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月11日
  最近修改   :
  功能描述   : link.c 的头文件
******************************************************************************/
#ifndef __LINK_H__
#define __LINK_H__


/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/
extern uint iptoun_btob(const uchar *ip);
extern uint iptoun_btol(const uchar *ip);
extern ARP_Table *insert_arp_table(ARP_Table *head, ARP_Table node);
extern ARP_Table *delete_arp_node(ARP_Table *head, const uchar *ip);
extern ARP_Table *free_arp_table(ARP_Table *pnode);
extern Boolean change_arp_mac(ARP_Table *head, const uchar ip[], const uchar mac[]);
extern void print_arp_table(ARP_Table *head);


#endif /* __LINK_H__ */
