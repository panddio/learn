/* ************************************************************************
 *       Filename:  sock_ram.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月08日 10时30分52秒
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
#include <netinet/ether.h>
#include <netinet/in.h>

void get_port(unsigned char const *src)
{

}
void get_IP_type(unsigned char const *src, unsigned char *type)
{
	//提取数据包类型
	sprintf(type,"%c",src[9]);

	if(*type == 6)
		printf("TCP 数据包\n");
	else if(*type == 17)
		printf("UDP 数据包\n");
	//printf("IP_TYPE:%d\n", *type);
}

void get_ip(unsigned char const *src)
{
	unsigned char dst_ip[16] = "";
	unsigned char src_ip[16] = "";

	//提取目的ip
	sprintf(dst_ip,"%d.%d.%d.%d",\
			src[16],src[17],src[18],src[19]);

	//提取源ip
	sprintf(src_ip,"%d.%d.%d.%d",\
			src[12],src[13],src[14],src[15]);

	printf("IP:%s >> %s\n", src_ip, dst_ip);
}

void get_ARP_ip(unsigned char const *src)
{
	unsigned char dst_ip[16] = "";
	unsigned char src_ip[16] = "";

	//提取目的ip
	sprintf(dst_ip,"%d.%d.%d.%d",\
			src[24],src[25],src[26],src[27]);

	//提取源ip
	sprintf(src_ip,"%d.%d.%d.%d",\
			src[14],src[15],src[16],src[17]);

	printf("ARP_IP:%s >> %s\n", src_ip, dst_ip);
}
void get_mac(unsigned char const *src)
{
	unsigned char dst_mac[18] = "";
	unsigned char src_mac[18] = "";

	//提取目的mac
	sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x",\
			src[0],src[1],src[2],src[3],src[4],src[5]);
	//提取源mac
	sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x",\
			src[6],src[7],src[8],src[9],src[10],src[11]);

	printf("MAC:%s >> %s\n", src_mac, dst_mac);
}

unsigned short get_type(unsigned char const *src, unsigned char *type)
{
	//提取数据包类型
	sprintf(type,"%02x%02x",src[12],src[13]);

	printf("TYPE:%s\n", type);
	//printf("TYPE:%c%c%c%c\n", type[0],type[1],type[2],type[3]);
}
int main(int argc, char *argv[])
{
	unsigned char type[4] = "";
	unsigned char ip_type[1] = "";
	unsigned char buf[2048] = "";
	int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));


	while(1)
	{
		putchar('\n');
		int len  = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
		get_mac(buf);
		get_type(buf, type);

		if(strcmp(type, "0800") == 0)//ip
		{
			get_ip(buf+14);
			get_IP_type(buf+14, ip_type);
		}
		else if(strcmp(type, "0806") == 0) //ARP
		{
			get_ARP_ip(buf+14);
		}

		sleep(1);
	}

	close(sockfd);
	return 0;
}
