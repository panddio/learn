/* ************************************************************************
 *       Filename:  encrypt.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月30日 星期四 02時04分56秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

void get_file_name(char * dest_file_name,char * src_file_name);
char * read_src_file(unsigned long int *file_length,char *src_file_name);
char * file_text_encrypt(char * src_file_text,unsigned long int length,unsigned int password);
char * file_text_decrypt(char * src_file_text,unsigned long int length,unsigned int password);
void save_file(char* text,unsigned long int length,char * file_name);

#endif

