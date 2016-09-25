/* ************************************************************************
 *       Filename:  encrypt.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月30日 星期四 01時59分46秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "encrypt.h"

char mygetch() 
{
    struct termios oldt, newt;
    char ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

void print_help()
{
	printf("输入 1：加密文件\n");
	printf("输入 2：解密文件\n");
	printf("输入 3：退出程序\n");
}

void main()
{
	char ch, *buf = NULL;
	char dest_file_name[30] = "";
	char src_file_name[30] = "";
	long unsigned int length = 0,password = 0;;
	
	while(1)
	{
		print_help(); //显示提示
		
		do
		{
			ch = mygetch();
		}while(ch != '1' && ch != '2' && ch != '3');
		
		switch(ch)
		{
			#if 0
			case '1':
			{
				get_file_name(dest_file_name,src_file_name); //获取加密文件名和目的文件名
				buf = read_src_file(&length,src_file_name);  //读取待加密文件内容
				printf("Please input your poassword: ");
				scanf("%lu",&password);  //获取加密密码
				buf = file_text_encrypt(buf,length,password); //进行加密
				save_file(buf,length,dest_file_name);
				break;
			}
			case '2':
			{
				get_file_name(dest_file_name,src_file_name); //获取解密文件名和目的文件名
				buf = read_src_file(&length,src_file_name);  //读取待解密文件内容
				printf("Please input your poassword: ");
				scanf("%lu",&password);  //获取解密密码
				buf = file_text_decrypt(buf,length,password); //进行解密	
				save_file(buf,length,dest_file_name);
				break;
			}
			case '3': free(buf); exit(0);
			#elif 1
			case '3': free(buf); exit(0);			
			case '1':	
			case '2':
			{
				get_file_name(dest_file_name,src_file_name); //获取源文件名和目的文件名
				buf = read_src_file(&length,src_file_name);  //读取待操作的文件内容
				printf("Please input your poassword: ");
				scanf("%lu",&password);  //获取密码
				if(ch == '1')
				{
					buf = file_text_encrypt(buf,length,password); //进行加密
					save_file(buf,length,dest_file_name);
					break;
				}
				else
				{
					buf = file_text_decrypt(buf,length,password); //进行解密	
					save_file(buf,length,dest_file_name);
					break;					
				}
			}
			#endif
		}
	}
}


