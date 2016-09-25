/* ************************************************************************
 *       Filename:  raw_udp.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月08日 17时41分48秒
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
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <net/ethernet.h>

typedef struct _raw_upd
{
	int raw_fd;

	unsigned char src_mac[6];
	unsigned char dst_mac[6];

	unsigned char src_ip[4];
	unsigned char dst_ip[4];

	struct sockaddr_ll sll;
	struct ifreq ethreq;
}UDP;

unsigned short checksum(unsigned short *buf, int nword)
{
	unsigned long sum;
	for(sum = 0; nword > 0; nword--)
	{
		sum += htons(*buf);
		buf++;
	}
	sum = (sum>>16) + (sum&0xffff);
	sum += (sum>>16);
	return ~sum;
}

char send_msg(unsigned char msg_buf[], int raw_fd, struct sockaddr_ll sll)
{
	int msg_len = 0;

	msg_len = strlen(msg_buf);
	msg_len--;
	msg_buf[msg_len] = 0; //去掉 \n

	if(msg_len%2 != 0) //数据个数不是偶数
	{
		msg_buf[msg_len] = 0;
		msg_len++; //
		msg_buf[msg_len] = 0;
	}
	printf("msg_len=%d\n",msg_len);

	//2.封装mac头
	unsigned char packet[2048] = "";
	unsigned char src_mac[6] = {0x00,0x0c,0x29,0xe4,0xd3,0xd6};
	unsigned char dst_mac[6] = {0xec,0xa8,0x6b,0xac,0xcf,0xf9};

	struct ether_header *eth_hdr = NULL;
	eth_hdr = (struct ether_header *)packet;
	memcpy(eth_hdr->ether_shost, src_mac, 6);
	memcpy(eth_hdr->ether_dhost, dst_mac, 6);
	eth_hdr->ether_type = htons(0x0800); //

	//3.封装ip头
	struct iphdr *ip_hdr = NULL;
	ip_hdr = (struct iphdr *)(packet+14);
	ip_hdr->ihl = 5;
	ip_hdr->version = 4;
	ip_hdr->tos = 0;       //服务类型
	ip_hdr->ttl = 128;     //生存时间
	ip_hdr->tot_len = htons(20+8+msg_len);//
	ip_hdr->protocol = 17; //UDP协议
	ip_hdr->saddr = inet_addr("10.221.2.221");
	ip_hdr->daddr = inet_addr("10.221.2.12");
	ip_hdr->check = htons(0);

	//4.封装UDP头部
	struct udphdr *udp_hdr = NULL;
	udp_hdr = (struct udphdr *)(packet+14+20);
	udp_hdr->source = htons(8000); //源端口
	udp_hdr->dest = htons(8080);   //目的端口
	udp_hdr->len  = htons(8+msg_len);
	udp_hdr->check = htons(0);

	//5.udp的数据
	memcpy(packet+14+20+8, msg_buf, msg_len);

	//6.ip首部校验和
	ip_hdr->check = htons(checksum((unsigned short *)(packet+14),20/2));

	//7.udp伪头部，用于计算校验和
	unsigned char fake[1024] = {
	10, 221, 2, 221, //源ip
	10, 221, 2,  12, //目的ip
	 0,  17, 0,   0, //最后两位是UDP的长度
	};

	*(unsigned short *)(fake+10) = htons(8+msg_len); //UDP的长度
	memcpy(fake+12, packet+14+20, 8+msg_len);
	udp_hdr->check = htons(checksum((unsigned short *)(fake),(12+8+msg_len)/2));//udp头部校验和

	sendto(raw_fd, packet, 14+20+8+msg_len, 0, (struct sockaddr *)&sll, sizeof(sll));

}

int main(int argc, char *argv[])
{

	//创建原始套接字
	int raw_fd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));

	//数据初始化
	struct sockaddr_ll sll;
	struct ifreq ethreq;
	bzero(&sll, sizeof(sll));

	strncpy(ethreq.ifr_name,"eth0", IFNAMSIZ);   //指定网卡名称
	ioctl(raw_fd, SIOCGIFINDEX, (char *)&ethreq);//获取网络接口
	sll.sll_ifindex = ethreq.ifr_ifindex;

	while(1)
	{
		unsigned char msg_buf[1024] = "";
		printf("please input the message you want to send:\n");
		fgets(msg_buf, sizeof(msg_buf),stdin);
		send_msg(msg_buf, raw_fd, sll);
	}
	return 0;
}
