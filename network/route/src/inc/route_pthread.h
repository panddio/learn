/******************************************************************************
  �� �� ��   : route_pthread.h
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��11��
  ����޸�   :
  ��������   : route_pthread.c ��ͷ�ļ�
******************************************************************************/

#ifndef __ROUTE_PTHREAD_H__
#define __ROUTE_PTHREAD_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * ����ԭ��˵��                                 *
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
