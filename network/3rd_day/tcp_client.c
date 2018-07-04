/* ************************************************************************
 *       Filename:  tcp_client.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月02日 14时38分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	//1.创建一个用于通信的tcp套接字
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//2.连接制定的服务器
	struct sockaddr_in s_addr;
	bzero(&s_addr, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(8080);
	s_addr.sin_addr.s_addr = inet_addr("194.169.3.8");
	//连接
	int ret = connect(sockfd, (struct sockaddr *)&s_addr, sizeof(s_addr));
	if(ret != 0)
	{
		perror("connect:");
		exit(-1);
	}
	//3.给服务器发送数据
	send(sockfd, "hehe", strlen("hehe"), 0);

	//4.接收服务器的应答
	char buf[128]="";
	recv(sockfd, buf, sizeof(buf),0);
	printf("client recv=%s\n", buf);

	//5.关闭tcp套接字
	close(sockfd);
	return 0;
}


