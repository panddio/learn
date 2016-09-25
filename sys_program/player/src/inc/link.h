/* ************************************************************************
 *       Filename:  link.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月31日 星期五 05時39分46秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#ifndef __LINK_H__
#define __LINK_H__

#include "common.h"

LRC *insert_link(LRC *head, LRC slrc);
LRC *free_link(LRC *head);
void print_link(LRC *head);
LRC *search_link(LRC *head,int time);

#endif



