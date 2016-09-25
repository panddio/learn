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

#include "common.h"

char * read_src_file(ulint *file_length, char *lrc_src);
//char **get_musiclist();
char *get_musiclist(char ***plist);
void delete_dot(char *plist[]);
void recover_dot(char *plist[]);
int check_lines(ulint file_length, char *lrc_src);
int get_longestline(int lines, char *plines[]);
int get_longestlength(LRC *lrc_head);
int get_showoffset(char *pbuf, int longest);
int get_chrnumber(char *pbuf, int len);
#endif
