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
#ifndef __PTHREAD_LRC_H__
#define __PTHREAD_LRC_H__

extern uint src_segment(char *psrc, char *plines[], char *str);
extern uint line_segment(char *pline, char *pbuf[], char *str);
//extern LRC *build_link(char *lrc_pline[], char *ptitle[], int lines);
extern LRC *build_link(MPLAYER *pm,char *plines[],int lines);
extern LRC *dispose_lrc(MPLAYER *pm, char *name);
extern void show_lyric(LRC *pnode, int longest);
extern void mplayer_show_lyric(MPLAYER *pm, LRC *pnode);
//extern void mplayer_show_lyrtitle(MPLAYER *pm, char *title[]);
extern void mplayer_show_lyrtitle(MPLAYER *pm, char *ptitle, int i);

//void mplayer_show_lyric(MPLAYER *pm, int cur_time);

#endif



