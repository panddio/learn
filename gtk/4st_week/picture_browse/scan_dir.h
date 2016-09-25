/* ************************************************************************
 *       Filename:  scan_dir.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月11日 14时38分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#ifndef __SCAN_DIR_H__
#define __SCAN_DIR_H__

#define IMAGE_WIDTH				400
#define IMAGE_HEIGTH			300
#define IMAGE_DIR				"./image/"

extern int gs_index;
extern int gs_bmp_total;	//图片总数
extern char *gs_bmp_name[50];//存放图片目录和文件名地址的指针数组


void save_bmp_name(char *path, char *bmp);
void get_bmp_name(char *path);
int conver_bmp_name(char *bmp_pathname);
void order_bmp_name(void);
void bmp_name_print(void);

#endif


