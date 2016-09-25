/* ************************************************************************
 *       Filename:  file.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月31日 星期五 05時35分49秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#ifndef __FILE_H__
#define __FILE_H__

//#include "common.h"

extern char *read_src_file(ulint *file_length,char *lrc_src);
//char **get_musiclist();
extern char *get_musiclist(char ***plist, int *plines);
extern int check_lines(ulint file_length, char *psrc);
extern int get_longestline(int lines, char *plines[]);
extern int get_longestlength(LRC *lrc_head);
extern int get_showoffset(char *pbuf, int longest);
extern int get_chrnumber(char *pbuf, int len);
extern char get_songname(char *desr, char *src);
extern char get_lrcname(char *src);
extern char *transfer_space(char src[]);
extern void delete_dot(char *plist[]);
extern void recover_dot(char *plist[]);
extern void recover_line_dot(char *plist[],int line_num);
#endif