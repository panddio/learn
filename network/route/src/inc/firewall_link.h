/******************************************************************************
  �� �� ��   : firewall_link.h
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��13��
  ����޸�   :
  ��������   : firewall_link.c ��ͷ�ļ�
******************************************************************************/

#ifndef __FIREWALL_LINK_H__
#define __FIREWALL_LINK_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * ����ԭ��˵��                                 *
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
