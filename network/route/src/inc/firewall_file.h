/******************************************************************************
  �� �� ��   : firewall_file.h
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��15��
  ����޸�   :
  ��������   : firewall_file.c ��ͷ�ļ�
******************************************************************************/
#ifndef __FIREWALL_FILE_H__
#define __FIREWALL_FILE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/
static char *firewall_read_rule_file(const char *file_name);
static char getch();

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/
extern void firewall_save_all_rules(TYPE_Route *rt);
extern void filrewall_save_rule(const char *rule);
extern void firewall_config(TYPE_Route *rt);
extern void firewall_get_passwd(TYPE_Route *rt);
extern void firewall_save_passwd(char passwd[]);
extern void get_passwd(char passwd[], int max_len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __FIREWALL_FILE_H__ */
