/* ************************************************************************
 *       Filename:  process_lrc.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月31日 星期五 09時17分38秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#ifndef __PROCESS_LRC_H__
#define __PROCESS_LRC_H__

int src_segment(char *lrc_src, char *plines[], char *str);
int line_segment(char *pline, char *pbuf[], char *str);
LRC *build_link(char *lrc_pline[], char *pheader[], int lines);
void show_lyric(LRC *pnode, int longest);
int get_showoffset(char *pbuf,int longest);
int get_maxtime(LRC *head);
int get_timelag(LRC *head);

#endif



