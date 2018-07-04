/* ************************************************************************
 *       Filename:  multicast.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月02日 11时44分58秒
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


int main(int argc, char *argv[])
{
	char group[INET_ADDRSTRLEN] = "224.0.1.1";
	char msg[512] = "";
	int sockfd;
	struct sockaddr_in addr;
	struct ip_mreq mreq;//定义一个多播组

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

	mreq.imr_multiaddr.s_addr = inet_addr(group); //设置多播组IP
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);//向多播组添加一个IP
	setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

	while(1)
	{
		bzero(msg, sizeof(msg));
		recvfrom(sockfd, msg, sizeof(msg), 0, NULL, NULL);
		printf("msg = %s\n",msg);
	}
	close(sockfd);
	return 0;
}

