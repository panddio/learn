/* ************************************************************************
 *       Filename:  message.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月27日 星期一 11時55分11秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msg.h"
void main()
{
	char msg_src[]={"+CMGR:REC UNREAD,+8613466630259,98/10/01,18:22:11+00,ABCdefGHI"};
	char *msg_done[5] = {NULL};
	
	msg_deal(msg_src,msg_done,",");
	show_message(msg_done);
}


