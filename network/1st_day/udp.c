/* ************************************************************************
 *       Filename:  udp.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月31日 16时37分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char *argv[])
{
	int sockfd = 0;
	unsigned short port = 8080;
	char *server_ip = "10.221.2.12";

	if(argc > 1)
	{
		server_ip = argv[1];
	}
	if(argc > 2)
	{
		port = atoi(argv[2]);
	}

	//AF_INET : ipv4
	//0: 根据
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	//配置服务器地址
	struct sockaddr_in server_addr;
	//memset(&server_addr, 0, sizeof(server_addr));
	bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);//服务器的端口
	//服务器的IP
	inet_pton(AF_INET, server_ip ,&server_addr.sin_addr.s_addr);

	//发送数据
	while(1)
	{
		char msg[256] = "";

		fgets(msg,sizeof(msg),stdin);

		sendto(sockfd, msg, strlen(msg), 0,\
			  (struct sockaddr *)&server_addr, sizeof(server_addr));
	}
	printf("fd = %d\n",sockfd);

	close(sockfd);
	return 0;
}
