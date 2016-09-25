/******************************************************************************
  �� �� ��   : route_control.h
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��11��
  ����޸�   :
  ��������   : route_control.c ��ͷ�ļ�
******************************************************************************/
#ifndef __ROUTE_CONTROL_H__
#define __ROUTE_CONTROL_H__


/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/
extern void route_init(TYPE_Route *rt);
extern void show_port_info(TYPE_Route *rt, char *port_name);
extern void get_ethernet_port(TYPE_Route *rt);
extern void build_arp_table(TYPE_Route *rt);
extern Boolean broadcast(TYPE_Route *rt, const uchar ip[]);


#endif /* __ROUTE_CONTROL_H__ */
