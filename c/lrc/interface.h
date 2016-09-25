/* ************************************************************************
 *       Filename:  interface.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月03日 星期一 03時39分16秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

extern char move;

void show_musicbar();
void show_interface();
void show_pattern(const char *src[], int lines, int SROW, int COL);
void show_musiclist(char *plist[]);
void show_progressbar(int time, int timelag);
void show_lrcheader(char *pheader[]);
void show_time(int time, int maxtime);

#endif
