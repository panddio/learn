/******************************************************************************
  文 件 名   : firewall_file.h
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月15日
  最近修改   :
  功能描述   : firewall_file.c 的头文件
******************************************************************************/
#ifndef __FIREWALL_FILE_H__
#define __FIREWALL_FILE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/
static char *firewall_read_rule_file(const char *file_name);
static char getch();

/*----------------------------------------------*
 * 外部函数原型说明                             *
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
