/******************************************************************************
  文 件 名   : tftp_client.c
  版 本 号   : 
  作    者   : 
  生成日期   : 2015年9月1日
  最近修改   :
  功能描述   : TFTP 客户端
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef enum _mode
{
	pull = 0,
	push = 1,
}MODE;

int main(int argc, char *argv[])
{
	fd_set rfds;
	MODE flag;
	struct timeval tv;
	FILE *fp = NULL;
	char file_name[128] = "";
	char server_ip[16]  = "10.221.2.12";
	unsigned char cmd[128]  = "", msg[1024] = "";
	int sockfd = 0, ask = 0, ret = 0;
	int cmd_len = 0, msg_len = 0, snd_len = 0;
	unsigned short port = 69; // TFTP服务器的固定端口

	if(argc < 2)
	{
		printf("parameter too little!\n");
		printf("please run again: ./elf  pull/push  filename\n");
		exit(-1);
	}
	strcpy(file_name, argv[2]);
	printf("file_name = %s\n",file_name);

	//创建一个套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	//配置服务器的地址
	struct sockaddr_in server_addr;
	socklen_t server_len = sizeof(server_addr);
	bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);//服务器的端口
	inet_pton(AF_INET, server_ip ,&server_addr.sin_addr.s_addr);//服务器的IP

	if(strcmp("pull", argv[1]) == 0) //下载
	{
		flag = pull;
		printf("pull>>>\n");
		cmd_len = sprintf(cmd, "%c%c%s%c%s%c", 0, 1, file_name, 0, "octet", 0); //octet: 二进制模式；netascii: 文本模式
		sendto(sockfd, cmd, cmd_len, 0,\
		      (struct sockaddr *)&server_addr, sizeof(server_addr));

		fp = fopen(file_name, "wb");
		if(fp == NULL)
		{
			printf("%s is not exist!!\n", file_name);
			exit(-1);
		}
	}
	else if(strcmp("push", argv[1]) == 0) //上传
	{
		flag = push;
		printf("push>>>\n");
		cmd_len = sprintf(cmd, "%c%c%s%c%s%c", 0, 2, file_name, 0, "octet", 0);
		sendto(sockfd, cmd, cmd_len, 0,\
		      (struct sockaddr *)&server_addr, sizeof(server_addr));

		fp = fopen(file_name, "rb");
		if(fp == NULL)
		{
			printf("%s is not exist!!\n", file_name);
			exit(-1);
		}
	}
	else
	{
		printf("Err: argv[1] != pull/push\n");
		exit(-1);
	}

	while(1)
	{
		bzero(msg, sizeof(msg));
		bzero(&server_addr, sizeof(server_addr));

		FD_ZERO(&rfds);
		FD_SET(sockfd, &rfds);

		/* Wait up to one second. */
		tv.tv_sec  = 1;
		tv.tv_usec = 0;

		ret = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);

		if(ret < 0) perror("");

		if(FD_ISSET(sockfd, &rfds))
		{
			msg_len = recvfrom(sockfd, msg, sizeof(msg), 0, \
							  (struct sockaddr *)&server_addr, &server_len);
		}
		else
		{
			printf("time out, continue!\n");
			continue;
		}

		if(flag == pull) //下载
		{
			if(msg[1] == 3) //数据确认
			{
				//printf("ask_no = %d&&&&&&&&&\n",msg[3]);
				if(ask != msg[3])
				{
					ask = msg[3];
					//把接收的数据写入文件
					fwrite((msg+4), msg_len - 4, 1, fp);
				}

				if(msg_len < 516)
				{
					//fclose(fp);
					break;
				}

				msg[1] = 4; //数据确认操作码

				//发送确认信号
				sendto(sockfd, msg, 4, 0,\
					  (struct sockaddr *)&server_addr, sizeof(server_addr));
				printf("ask_no = %d&&&&&&&&&\n",msg[3]);
			}
		}
		else if(flag == push)
		{
			if(msg_len == 4)
			{
				//bzero(msg, sizeof(msg));
				msg_len = fread((msg+4), 1, 512, fp);//用fread((msg+4), 512, 1, fp);只能读到一个字节
				//printf("read_len = %d\n",msg_len);
				if(msg_len == 0)
				{
					printf("push %s finish!\n",file_name);
					break;
				}

				ask++;
				msg[0] = 0;
				msg[1] = 3;
				msg[2] = ask/256;
				msg[3] = ask%256;

				printf("msg[1]=%d msg[2~3]=%d\n",msg[1], msg[2] * 256 + msg[3]);
				//发送数据
				snd_len = sendto(sockfd, msg, msg_len+4, 0,\
								(struct sockaddr *)&server_addr, sizeof(server_addr));

				if(snd_len != msg_len+4)
				{
					printf("Err: send msg to server error!\n");
				}
			}
		}
	}
	fclose(fp);
	close(sockfd);
	return 0;
}
