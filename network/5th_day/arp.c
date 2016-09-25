/* ************************************************************************
 *       Filename:  arp.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月08日 15时05分02秒
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

int main(int argc, char *argv[])
{
	int i = 0;
	//创建原始套接字
	int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	unsigned char send_msg[1024] = {
		//-----组MAC----14----
		0xff,0xff,0xff,0xff,0xff,0xff,//dst_mac: ff:ff:ff:ff:ff:ff
		0x00,0x0c,0x29,0xe4,0xd3,0xd6,//src_mac: 00:0c:29:e4:d3:d6
		0x08,0x06,                    //类型: 0x0806 ARP协议

		//-----组ARP----28----
		0x00,0x01,0x08,0x00,          //硬件类型1(以太网地址)，协议类型0x0800(IP)
		0x06,0x04,0x00,0x01,          //硬件、协议的地址长度分别为6和4，ARP请求
		0x00,0x0c,0x29,0xe4,0xd3,0xd6,//发送端的mac
		10, 221, 2, 221,              //发送端的IP
		0x00,0x00,0x00,0x00,0x00,0x00,//目的mac(获取对方的mac，设置为0)
		10, 221, 2, 255,               //目的IP
	};

	//数据初始化
	struct sockaddr_ll sll;
	struct ifreq ethreq;
	bzero(&sll, sizeof(sll));

	strncpy(ethreq.ifr_name,"eth0", IFNAMSIZ);    //指定网卡名称
	ioctl(sockfd, SIOCGIFINDEX, (char *)&ethreq); //获取网络接口
	sll.sll_ifindex = ethreq.ifr_ifindex;         //将网络接口赋值给原始套接字地址结构

	for(i=1;i<50;i++)
	{
		send_msg[41] = i;
		sendto(sockfd, send_msg, 42, 0, (struct sockaddr *)&sll, sizeof(sll));

		//接收对方的ARP应答
		unsigned char recv_msg[1024] = "";
		recvfrom(sockfd, recv_msg, sizeof(recv_msg), 0, NULL, NULL);

		if(recv_msg[21] == 2) //ARP应答
		{
			unsigned char resp_mac[18] = "";
			unsigned char resp_ip[16] = "";

			//提取mac地址
			sprintf(resp_mac, "%02x:%02x:%02x:%02x:%02x:%02x", \
					recv_msg[22],recv_msg[23],recv_msg[24],recv_msg[25],recv_msg[26],recv_msg[27]);

			//提取ip
			sprintf(resp_ip,"%d.%d.%d.%d",\
				   recv_msg[28],recv_msg[29],recv_msg[30],recv_msg[31]);

			printf("IP:%s -- %s\n",resp_ip,resp_mac);
		}
	}

	close(sockfd);
	return 0;
}
