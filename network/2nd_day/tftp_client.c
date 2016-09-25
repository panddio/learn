/******************************************************************************
  文 件 名   : tftp_client.c
  版 本 号   : 
  作    者   : 
  生成日期   : 2015年9月1日
  最近修改   :
  功能描述   : TFTP 客户端
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>


int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char *p  = NULL;
	char file_name[128] = "a.txt";
	char server_ip[16]  = "10.221.2.12";
	char cmd[128]  = "", msg[1024] = "";
	int sockfd = 0, cmd_len = 0, msg_len = 0, ask = 0;
	unsigned short port = 69; // TFTP服务器的固定端口


	if(argc > 1)
	{
		strcpy(server_ip, argv[1]);
	}
	if(argc > 2)
	{
		bzero(file_name, sizeof(file_name));
		strcpy(file_name, argv[2]);
	}

	//创建一个套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	//配置服务器的地址
	struct sockaddr_in server_addr;
	socklen_t server_len = sizeof(server_addr);
	bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);//服务器的端口
	inet_pton(AF_INET, server_ip ,&server_addr.sin_addr.s_addr);//服务器的IP

	//printf("file_name = %s\n",file_name);

	cmd_len = sprintf(cmd, "%c%c%s%c%s%c", 0, 1, file_name, 0, "octet", 0);
	sendto(sockfd, cmd, cmd_len, 0,\
		  (struct sockaddr *)&server_addr, sizeof(server_addr));

	p = msg; //
	fp = fopen(file_name, "wb");

	while(1)
	{
	  	bzero(msg, sizeof(msg));
		//bzero(&server_addr, sizeof(server_addr));
		msg_len = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&server_addr, &server_len);

		if(*(p+1) == 3) //数据确认
		{
			//printf("ask_no = %d&&&&&&&&&\n",*(p+3));
			if(ask != *(p+3))
			{
				ask = *(p+3);
				//把接收的数据写入文件
				fwrite((p+4), msg_len - 4, 1, fp);
			}

			if(msg_len < 516)
			{
				fclose(fp);
				break;
			}

			*(p+1) = 4; //数据确认操作码

			//发送确认信号
			sendto(sockfd, msg, 4, 0,\
				  (struct sockaddr *)&server_addr, sizeof(server_addr));
		}
	}

	//fclose(fp);
	close(sockfd);
	return 0;
}
