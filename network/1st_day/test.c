/* ************************************************************************
 *       Filename:  test.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月11日 14时42分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define uchar    unsigned char
#define uint     unsigned int
#define uint16   unsigned short
#define TRUE    (1)
#define FALSE   (0)

const char *rules[] = {
	"ip",
	"mac",
	"port",
	"arp",
	"tcp",
	"udp",
	"icmp",
	"igmp",
	"http",
	"tftp",
};

unsigned int iptoun_btol(unsigned char *ip)
{
	unsigned int ip_val = 0;

	ip_val = ip[0]<<24 | ip[1]<<16 | ip[2]<<8 | ip[3]; //如果把 “|” 换成 “+”，得到的结果是0

	return ip_val;
}
unsigned int iptoun_btob(unsigned char *ip)
{
	unsigned int ip_val = 0;

	//ip_val = ip[3]<<24 | ip[2]<<16 | ip[1]<<8 | ip[0];
	ip_val = *(unsigned int *)ip;
	return ip_val;
}

char check_if_same_subnet(uchar eth_mask[], uchar eth_ip[], uchar dst_ip[])
{
	if(((*(uint *)eth_ip) & (*(uint *)eth_mask)) ==\
		((*(uint *)dst_ip) & (*(uint *)eth_mask)))
		return TRUE;

	else
		return FALSE;
}
#if 1
int main(int argc, char *argv[])
{
	uchar buf[64] = "";
	int len =0;
	char tt[] = "5557";
	len = atoi(tt);
	printf("##%d\n",len);
	fgets(buf, 64, stdin);
	len = strlen(buf);

	buf[len] = 0;

	printf("%d\n", buf[0]);
}
#elif 0
int main(int argc, char *argv[])
{
	uchar ip[16] = "10.221.2.12";
	uchar part[4][6];
	bzero(part, sizeof(part));
	sscanf(ip, "%s.%s.%s.%s", *(part+0), *(part+1), *(part+2), *(part+3));

	printf("%s #%s #%s #%s\n",*(part+0), *(part+1), *(part+2), *(part+3));
#if 0
	int p[4];

	sscanf("10.221..12", "%d.%d.%d.%d", (int *)&p[0],(int *)&p[1],(int *)&p[2],(int *)&p[3]);
	printf("%d %d %d %d\n",p[0],p[1],p[2],p[3]);
#endif
	return 0;
}
#elif 0
int main(int argc, char *argv[])
{
	uchar part[2][18];
	uchar type[16];
	uchar port[16];
	uchar ip[4] = {10,221,2,12};
	uchar src_ip[16] = "";
	uchar dst_ip[16] = "";
	uint16 port_val = 0;
	uint16 temp = 8000;
	char rule[30] = "ip 10.221.2.12";

	//提取源ip
	sprintf(src_ip,"%d.%d.%d.%d",\
	ip[0],ip[1],ip[2],ip[3]);

	sscanf(rule, "%*s %s %s", *(part+0), *(part+1));

	int len = strlen(*(part+1));
	printf("len = %d\n",len);
	if(strcmp(src_ip, *(part+1)) == 0) printf("****OK\n");
#if 0
	sscanf(rule, "%*s %s %s", type, port);
	port_val = (uint16)atoi(port);

	if(port_val == temp) printf("***OK\n");
	return 0;
#endif
}
#elif 0
typedef struct _arphdr
{
	uint16 ar_hrd;
	uint16 ar_pro;
	uchar ar_hln;
	uchar ar_pln;
	uint16 ar_op;

	uchar src_mac[6];
	uchar src_ip[4];
	uchar dst_mac[6];
	uchar dst_ip[4];
}ARP_Hdr;

int main(int argc, char *argv[])
{
	uchar msg[256] = {
		//-----组mac----14----
		0xff,0xff,0xff,0xff,0xff,0xff,//dst_mac: ff:ff:ff:ff:ff:ff
		0x00,0x00,0x00,0x00,0x00,0x00,//src_mac:
		0x08,0x06,                    //类型: 0x0806 ARP协议

		//-----组ARP----28----
		0x00,0x01,0x08,0x00,          //硬件类型1(以太网地址)，协议类型:0x800(IP)
		0x06,0x04,0x00,0x01,          //硬件、协议的地址长度分别为6和4，ARP请求
		0x00,0x00,0x00,0x00,0x00,0x00,//发送端的mac
		0, 0, 0, 0,                   //发送端的ip
		0x00,0x00,0x00,0x00,0x00,0x00,//目的mac(获取对方的mac，设置为0)
		10, 221, 2, 221,              //目的ip
	};
	unsigned char p[4] = "";
	ARP_Hdr *arp = NULL;
	arp = (ARP_Hdr *)(msg+14);

	if(ntohs(arp->ar_op) == 1) printf("arp request\n");
	else if(arp->ar_op == 2) printf("arp reply\n");

	printf("dst_ip:%d\n",iptoun_btol(arp->dst_ip));

	unsigned char ip[4] = {10,221,2,221};



	sscanf("10.221.2.12", "%d.%d.%d.%d", (int *)&p[0],(int *)&p[1],(int *)&p[2],(int *)&p[3]);
	printf("%d %d %d %d\n",p[0],p[1],p[2],p[3]);

	printf("iptoun_btol -- ip=%d\n",iptoun_btol(ip));

	printf("rules count=%d\n", sizeof(rules)/sizeof(rules[0]));
	return 0;
}
#elif 0
int main(int argc, char *argv[])
{
	unsigned char ip[4] = {10,221,2,221};
	unsigned char ip2[4] = {192,221,2,1};
	unsigned char mask[4] = {255,255,255,0};
	unsigned int ip_val = 0, ip_val2 = 0, mask_val = 0;
	uchar ty[2] = {0x08,0x00};
	unsigned short type = 0;

	type = ntohs(*(uint16 *)(ty));

	printf("type=%d, %d\n", type, 0x0800);
	(*(uint *)ip) = ((*(uint *)ip) & (*(uint *)mask));
	printf("%d.%d.%d.%d\n",ip[0],ip[1],ip[2],ip[3]);

	char flag = check_if_same_subnet(mask,ip,ip2);
	if(flag == TRUE) printf("OK####\n");
	else printf("NO*****\n");

	//printf("%s\n",((*(uint *)ip) & (*(uint *)mask)));
#if 0
	printf("IP:%s\n",(char*)inet_ntoa(ip));

	ip_val = ntohl(*(unsigned int *)ip);
	printf("ntohl-- ip_val=%d\n",ip_val);

	ip_val = iptoun_btol(ip);
	printf("iptoun_btol-- ip_val=%d\n",ip_val);

	ip_val = htonl(*(unsigned int *)ip);
	printf("htonl-- ip_val=%d\n",ip_val);

	ip_val = iptoun_btob(ip);
	printf("iptoun_btob -1- ip_val=%u\n",ip_val);

	ip_val2 = iptoun_btob(ip2);
	printf("iptoun_btob -2- ip_val=%u\n",ip_val2);
	printf("iptoun_btob -2- ip_val=%u\n",*(unsigned int *)ip2);

	if(ip_val2 > ip_val) printf("good\n");

	ip_val = ntohl(ip_val2);
	printf("iptoun_btol -2- ip_val=%d\n",ip_val);
#endif
	return 0;
}
#endif

