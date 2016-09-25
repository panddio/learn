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

typedef struct _socket
{
	int fd;
	char server_ip[INET_ADDRSTRLEN];
	struct sockaddr_in addr;
}SOCK;

void *pthread_sndmsg(void *arg)
{
	SOCK *psock = (SOCK *)arg;

	//配置服务器地址
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000);//服务器的端口
	//服务器的IP
	inet_pton(AF_INET, psock->server_ip ,&server_addr.sin_addr.s_addr);
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
			sscanf(msg,"%*[^ ] %s",psock->server_ip);

			//printf("server_ip = %s##\n", psock->server_ip);
			ret = inet_pton(AF_INET, psock->server_ip, &server_addr.sin_addr.s_addr);

			if(ret == 1)
			{
				printf("connect %s successful!!\n", psock->server_ip);
			}
			else
			{
				printf("cannot connect to %s\n", psock->server_ip);
			}
		}
		else if(strlen(msg) != 0)
		{
			sendto(psock->fd, msg, strlen(msg), 0,\
				  (struct sockaddr *)&server_addr, sizeof(server_addr));
		}
	}

	return NULL;
}

void *pthread_rcvmsg(void *arg)
{
	char msg[128];
	char ip_buf[INET_ADDRSTRLEN] = "";
	SOCK *psock = (SOCK *)arg;

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	bzero(&client_addr, sizeof(client_addr));

	while(1)
	{
		//接收client发送来的数据
		bzero(msg, sizeof(msg));
		recvfrom(psock->fd, msg, sizeof(msg), 0, (struct sockaddr *)&client_addr, &client_len);
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
	SOCK sock;

	strcpy(sock.server_ip, "127.0.0.1");
	sock.fd = socket(AF_INET, SOCK_DGRAM, 0);
	sock.addr.sin_family = AF_INET;
	sock.addr.sin_port = htons(8000);
	sock.addr.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY: 通配地址

	bind(sock.fd, (struct sockaddr *)&sock.addr, sizeof(sock.addr));//bind只能bind自己的ip

	pthread_create(&pth_snd, NULL,pthread_sndmsg, (void *)&sock);
	pthread_create(&pth_rcv, NULL,pthread_rcvmsg, (void *)&sock);

	pthread_detach(pth_rcv);
	pthread_detach(pth_snd);

	while(1)
	{
		usleep(10000);
	}
	return 0;
}
