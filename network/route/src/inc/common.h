/******************************************************************************
  �� �� ��   : common.h
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��11��
  ����޸�   :
  ��������   : ͨ�� ��ͷ�ļ�
******************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

/*----------------------------------------------*
 * ��׼��ͷ�ļ�                                 *
 *----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>


/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#define uint    unsigned int
#define uint16  unsigned short
#define ulint   unsigned long
#define uchar   unsigned char

#define TRUE         (1)
#define FALSE        (0)
#define MS           (1000)
#define MAX_PORT     16
#define RULE_LEN     32

#define PASSWD_LEN    9  // ����� 8 λ �����Ϊ���ڱ��� \0
#define ENCRYPT_KEY   (23)
#define ROOT_PASSWD   "123456"


/*----------------------------------------------*
 * ö�����Ͷ���                                 *
 *----------------------------------------------*/

#undef TRUE
#undef FALSE
typedef enum _boolean
{
	FALSE = 0,
	TRUE  = 1,
}Boolean;

typedef enum _type
{
	MAC  = 0,
	IP   = 1,
	PORT = 2,
	PRO  = 3,
}TYPE_Rule;

typedef enum _status
{
	DOWN = 0,
	UP   = 1,
}STATUS;

/*----------------------------------------------*
 * �ṹ�����Ͷ���                               *
 *----------------------------------------------*/

typedef struct _firewall
{
	char rule[RULE_LEN];
	struct _firewall *next;
}FIRE_Wall;

typedef struct _arphdr
{
	uint16 ar_hrd;
	uint16 ar_pro;
	uint16 ar_hln;
	uint16 ar_pln;
	uint16 ar_op;

	uchar src_mac[6];
	uchar src_ip[4];
	uchar dst_mac[6];
	uchar dst_ip[4];
}ARP_Hdr;

typedef struct _msg
{
	uchar dst_mac[6];
	uchar src_mac[6];
	uchar dst_ip[4];
	uchar src_ip[4];

	uint16 frame_type;
	uchar  pro_type;
	uint16 s_port;
	uint16 d_port;

	int len;
	int port;
}MSG_Info;

typedef struct _eth_port
{
	char name[20];   //�ӿ�����

	uchar ip[4];     //ip��ַ
	uchar mac[6];    //mac��ַ
	uchar netmask[4];//��������
	uchar bc_ip[4];  //�㲥��ַ

	STATUS status;
}ETH_Port;

typedef struct _arp_table
{
	unsigned char ip[4];
	unsigned char mac[6];

	struct _arp_table *next;

}ARP_Table;

typedef struct _route
{
	uchar recv[2048];
	char passwd[PASSWD_LEN];

	int raw_fd;   // ԭʼ�׽���
	int sockfd;   // �����׽���
	int connfd;   // �����׽���
	int port_num; // �ӿ�����

	STATUS fire_status;

	pthread_t pth_getmsg;
	pthread_t pth_keyeve;
	pthread_mutex_t mutex;

	struct _arp_table *arp_head;
	struct _firewall *ip_head;
	struct _firewall *mac_head;
	struct _firewall *port_head;
	struct _firewall *pro_head;
	struct _eth_port  eth_port[MAX_PORT];

	struct ether_header *eth_hdr;
	struct _arphdr *arp_hdr;
	struct iphdr *ip_hdr;
	struct tcphdr *tcp_hdr;
	struct udphdr *udp_hdr;

	struct sockaddr_in s_addr;
	struct sockaddr_ll sll;
	struct ifreq ethreq;
}TYPE_Route;

#endif

