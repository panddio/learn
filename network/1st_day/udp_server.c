/* ************************************************************************
 *       Filename:  udp_server.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月31日 17时33分36秒
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
	//创建一个通信socket
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	//作为一个服务器应该有一个固定的ip、port
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8030);
	//INADDR_ANY: 通配地址
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind只能bind自己的ip
	bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

	//定义保存接收信息的源地址信息
	char buf[128];
	char ip_buf[INET_ADDRSTRLEN] = ""; //INET_ADDRSTRLEN = 16
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	bzero(&client_addr, sizeof(client_addr));

	//接收client发送来的数据
	recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &client_len);

	inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip_buf, INET_ADDRSTRLEN);
	printf("ipaddr:%s\n",ip_buf);
	//printf("ipaddr:%d\n",ntohl(client_addr.sin_addr.s_addr));
	printf("port  :%d\n",ntohs(client_addr.sin_port));
	printf("buf = %s\n",buf);
	return 0;
}
