/* ************************************************************************
 *       Filename:  msg.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月27日 星期一 02時29分22秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#ifndef __MSG_H__
#define __MSG_H__

extern void show_number(const char *src);
extern void show_time( char *src1,char *src2);
extern void show_content(const char *src);
extern void show_message(char **src);
extern int msg_deal(char *msg_src, char *msg_done[],char *str);
#endif
