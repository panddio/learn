/* ************************************************************************
 *       Filename:  tcp_server.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月02日 15时19分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

void *fun(void *arg)
{
	int confd = (int )arg;
	send(confd, "connect successful!\n", strlen("connect successful!\n"), 0);
	while(1)
	{
		char buf[512]="";
		int recv_len = recv(confd, buf, sizeof(buf),0);
		if(recv_len == 0) break;
		strcat(buf, "\n");
		send(confd, buf, strlen(buf), 0);
	}
	close(confd);
}

int main(int argc, char *argv[])
{
	//1.创建一个用于通信的tcp 监听 套接字
	unsigned short port = 8080;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

//	if(argc < 2)
//	{
//		printf("parameter too little\n");
//		exit(-1);
//	}
//	port = atoi(argv[1]);

	//2.让服务器绑定IP和端口
	struct sockaddr_in s_addr;
	bzero(&s_addr, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(port);
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(sockfd, (struct sockaddr *)&s_addr, sizeof(s_addr));
	if(ret != 0)
	{
		perror("bind:");
		exit(-1);
	}
	//3.listen创建连接队列
	listen(sockfd, 10);

	while(1)
	{
		struct sockaddr_in c_addr;
		socklen_t c_addr_len = sizeof(c_addr);

		int confd = accept(sockfd, (struct sockaddr *)&c_addr, &c_addr_len);

		pthread_t pthid;
		pthread_create(&pthid, NULL, (void *)fun, (void *)confd);
		pthread_detach(pthid); //线程分离
	}
	close(sockfd);
	return 0;
}




#if 0
int main(int argc, char *argv[])
{
	//1.创建一个用于通信的tcp 监听 套接字
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//2.让服务器绑定IP和端口
	struct sockaddr_in s_addr;
	bzero(&s_addr, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(8080);
	s_addr.sin_addr.s_addr = htons(INADDR_ANY);

	int ret = bind(sockfd, (struct sockaddr *)&s_addr, sizeof(s_addr));
	if(ret != 0)
	{
		perror("bind:");
		exit(-1);
	}
	//3.listen创建连接队列
	listen(sockfd, 10);

	while(1)
	{
		char ip[16] = "";
		struct sockaddr_in c_addr;
		socklen_t c_addr_len= sizeof(c_addr);
		//4.提取客户端的连接
		int confd = accept(sockfd, (struct sockaddr *)&c_addr, &c_addr_len);

		inet_ntop(AF_INET, &c_addr.sin_addr.s_addr, ip,16);

		while(confd != 0)
		{
			send(confd, "hongbao", strlen("hongbao"), 0);
			//printf("ip:%s  port:%d\n",ip, ntohs(c_addr.sin_port));

			//4.接收
			char buf[128]="";
			int recv_len = recv(confd, buf, sizeof(buf),0);
			if(recv_len == 0) break;
			printf("ip:%s  port:%d recv = %s\n",ip, ntohs(c_addr.sin_port),buf);
		}

		break;
	}
	close(sockfd);
	return 0;
}
#endif
