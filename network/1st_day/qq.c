/* ************************************************************************
 *       Filename:  qq.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月31日 19时32分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

void *pthread_sndmsg(void *arg)
{
	int snd_fd = 0;
	unsigned short port = 8000;
	char server_ip[INET_ADDRSTRLEN] = "127.0.0.1";

	snd_fd = socket(AF_INET, SOCK_DGRAM, 0);

	//配置服务器地址
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);//服务器的端口
	inet_pton(AF_INET, server_ip ,&server_addr.sin_addr.s_addr);//服务器的IP

	while(1)
	{
		char msg[128] = "";
		char buf[10]  = "";

		bzero(msg, sizeof(msg));
		bzero(buf, sizeof(buf));

		printf("\033[34mQQudp:\033[0m");
		fflush(stdout);
		fgets(msg,sizeof(msg),stdin);
		msg[strlen(msg) - 1] = 0;
		//printf("sndmsg = %s\n", msg);
		sscanf(msg,"%[^ ]",buf);

		if(strcmp("sayto",buf) == 0)
		{
			int ret = 0;
			sscanf(msg,"%*[^ ] %s",server_ip);
			//printf("server_ip = %s##\n", server_ip);
			ret = inet_pton(AF_INET, server_ip ,&server_addr.sin_addr.s_addr);

			if(ret == 1)
			{
				printf("connect %s successful!!\n",server_ip);
			}
			else
			{
				printf("cannot connect to %s\n",server_ip);
			}
		}
		else if(strlen(msg) != 0)
		{
			sendto(snd_fd, msg, strlen(msg), 0,\
				  (struct sockaddr *)&server_addr, sizeof(server_addr));
		}
	}

	return NULL;
}

void *pthread_rcvmsg(void *arg)
{
	char msg[128];
	char ip_buf[INET_ADDRSTRLEN] = "";
	//创建一个通信socket
	int rvc_fd = socket(AF_INET, SOCK_DGRAM, 0);

	//作为一个服务器应该有一个固定的ip、port
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	//INADDR_ANY: 通配地址
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind只能bind自己的ip
	bind(rvc_fd, (struct sockaddr *)&addr, sizeof(addr));

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	bzero(&client_addr, sizeof(client_addr));

	while(1)
	{
		//接收client发送来的数据
		bzero(msg, sizeof(msg));
		recvfrom(rvc_fd, msg, sizeof(msg), 0, (struct sockaddr *)&client_addr, &client_len);
		inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip_buf, INET_ADDRSTRLEN);

		printf("\033[32m\r[%s]: %s\033[0m\n",ip_buf, msg);
		printf("\033[34mQQudp:\033[0m");
		fflush(stdout);
		//printf("port:%d\n",ntohs(client_addr.sin_port));
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t pth_snd, pth_rcv;

	pthread_create(&pth_snd, NULL,pthread_sndmsg, NULL);
	pthread_create(&pth_rcv, NULL,pthread_rcvmsg, NULL);

	pthread_detach(pth_rcv);
	pthread_detach(pth_snd);

	while(1)
	{
		sleep(10);
	}
	return 0;
}
