/******************************************************************************
  �� �� ��   : msg_dispose.c
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��15��
  ����޸�   :
  ��������   : ������������
  �����б�   :
              get_ip
              get_mac
              check_if_same_subnet
              dispose_arp_reply
              get_transpond_port
              get_type
              reply_arp_requset
              send_msg
              show_msg_ip
              transpond_msg
  �޸���ʷ   :
  1.��    ��   : 2015��9��15��
    ��    ��   : if
    �޸�����   : �����ļ�

******************************************************************************/
#include "common.h"
#include "arp_link.h"


/*****************************************************************************
 �� �� ��  : get_mac()
 ��������  : ��ȡĿ��mac��Դmac
 �������  : recv      �����������ݰ��Ļ���
 			 dst_mac   �洢Ŀ��mac���׵�ַ  ����NULL ����ȡ
 			 src_mac   �洢Դmac���׵�ַ    ����NULL ����ȡ
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��12��
*****************************************************************************/
void get_mac(uchar *recv, uchar *dst_mac, uchar *src_mac)
{
	if(dst_mac != NULL){
		memcpy(dst_mac, recv, 6);
	}

	if(src_mac != NULL){
		memcpy(src_mac, recv+6, 6);
	}
}

/*****************************************************************************
 �� �� ��  : get_type()
 ��������  : ��ȡЭ������
 �������  : recv     �����������ݰ��Ļ���
 �� �� ֵ  : ����Э������(�޷��Ŷ���������)
 �޸�����  : 2015��9��11��
*****************************************************************************/
uint16 get_type(const uchar *recv)
{
	uint16 type = 0;

	type = ntohs(*(uint16 *)(recv+12));

	return type;
}

/*****************************************************************************
 �� �� ��  : get_ip()
 ��������  : ��ȡĿ��ip��Դip
 �������  : recv     �����������ݰ��Ļ���
 			 dst_ip   �洢Ŀ��ip���׵�ַ  ����NULL ����ȡ
 			 src_ip   �洢Դip���׵�ַ    ����NULL ����ȡ
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��12��
*****************************************************************************/
void get_ip(const uchar *recv, uchar *dst_ip, uchar *src_ip)
{
	if(src_ip != NULL){
		//��ȡԴip
		memcpy(src_ip, recv+12, 4);
	}

	if(dst_ip != NULL){
		//��ȡĿ��ip
		memcpy(dst_ip, recv+16, 4);
	}
}

/*****************************************************************************
 �� �� ��  : show_msg_ip()
 ��������  : ��ȡĿ��ip��Դip
 �������  : recv     �����������ݰ��Ļ���
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��11��
*****************************************************************************/
void show_msg_ip(const uchar *recv)
{
	unsigned char dst_ip[16] = "";
	unsigned char src_ip[16] = "";

	//��ȡԴip
	sprintf(src_ip,"%d.%d.%d.%d",\
			recv[12],recv[13],recv[14],recv[15]);

	//��ȡĿ��ip
	sprintf(dst_ip,"%d.%d.%d.%d",\
			recv[16],recv[17],recv[18],recv[19]);

	printf("IP:%s >> %s\n", src_ip, dst_ip);
}

/*****************************************************************************
 �� �� ��  : check_if_same_subnet()
 ��������  : ���Ŀ��ip�������Ƿ���ͬһ����
 �������  : eth_mask     ������������
             eth_ip       ����ip
             dst_ip       Ŀ��ip
 �� �� ֵ  : ������
 �޸�����  : 2015��9��12��
*****************************************************************************/
Boolean check_if_same_subnet(const uchar eth_mask[], const uchar eth_ip[],const uchar dst_ip[])
{
	if(((*(uint *)eth_ip) & (*(uint *)eth_mask)) ==\
		((*(uint *)dst_ip) & (*(uint *)eth_mask)))
		return TRUE;

	else
		return FALSE;
}

/*****************************************************************************
 �� �� ��  : get_transpond_port()
 ��������  : ��ȡ����ת���Ľӿ�
 �������  : rt        TYPE_Route ���ͽṹָ��
 			 dst_ip    Ŀ��ip
 �� �� ֵ  : ���������ı��
 �޸�����  : 2015��9��12��
*****************************************************************************/
int get_transpond_port(TYPE_Route *rt, const uchar dst_ip[])
{
	int i = 0;
	Boolean flag = FALSE;

	for(i=0; i < rt->port_num; i++)
	{
		flag = check_if_same_subnet(rt->eth_port[i].netmask, rt->eth_port[i].ip, dst_ip);

		if(flag == TRUE) return i;
	}

	return -1;
}

/*****************************************************************************
 �� �� ��  : send_msg()
 ��������  : ��ȡip���ݰ���ת���ӿ�
 �������  : rt        TYPE_Route ���ͽṹָ��
 			 port      ����ӿڵı��
 			 msg_len   �������ݳ���
 �� �� ֵ  :
 �޸�����  : 2015��9��12��
*****************************************************************************/
int send_msg(TYPE_Route *rt, int port, int msg_len)
{
	int send_len = 0;

	strncpy(rt->ethreq.ifr_name,rt->eth_port[port].name, IFNAMSIZ);
	ioctl(rt->raw_fd, SIOCGIFINDEX, (char *)&rt->ethreq);
	bzero(&rt->sll, sizeof(rt->sll));
	rt->sll.sll_ifindex = rt->ethreq.ifr_ifindex;

	send_len = sendto(rt->raw_fd, rt->recv, msg_len, 0, (struct sockaddr *)&rt->sll, sizeof(rt->sll));

	return send_len;
}
/*****************************************************************************
 �� �� ��  : transpond_msg()
 ��������  : ��ȡip���ݰ���ת���ӿ�
 �������  : rt        TYPE_Route ���ͽṹָ��
 			 dst_ip    Ŀ��ip
 			 port      ����ӿڵı��
 			 msg_len   �������ݰ��ĳ���
 �� �� ֵ  : �޷���ȡĿ��macʱ������-1�����򷵻�ʵ�ʷ��͵ĳ���
 �޸�����  : 2015��9��12��
*****************************************************************************/
int transpond_msg(TYPE_Route *rt, const uchar dst_ip[], int port, int msg_len)
{
	ARP_Table *pnode = NULL;

	if(rt->arp_head == NULL){ //���ARP��Ϊ�գ�����ARP��
		build_arp_table(rt);
	}

	pnode = (ARP_Table *)search_arp_table(rt->arp_head, dst_ip);

	if(pnode == NULL){ //��arp����û���ҵ�Ŀ��ip
		Boolean flag = broadcast(rt, dst_ip); //�㲥��ȡĿ��mac

		if(flag == FALSE) { //�㲥û�л�ȡ��Ŀ��mac

			return -1;
		}
		pnode = (ARP_Table *)search_arp_table(rt->arp_head, dst_ip);
	}

//	uchar dst_mac[6] = "";
//	uchar src_mac[6] = "";
//
//	memcpy(dst_mac, pnode->mac, 6);
//	memcpy(src_mac, rt->eth_port[port].mac, 6);

	memcpy(rt->recv,   pnode->mac, 6); //�޸�ip���ݰ���Ŀ��mac��ַ
	memcpy(rt->recv+6, rt->eth_port[port].mac, 6); //�޸�ip���ݰ���Դmac��ַ


	int send_len = send_msg(rt, port, msg_len);

	return send_len;
}

/*****************************************************************************
 �� �� ��  : reply_arp_requset()
 ��������  : Ӧ��arp����
 �������  : rt        TYPE_Route ���ͽṹָ��
 			 pinfo     MSG_Info ����ָ��
 			 ARP_Hdr   ARP_Hdr ����ָ��
 �� �� ֵ  : ���ط��͵ĳ��ȣ�������-1
 �޸�����  : 2015��9��12��
*****************************************************************************/
int reply_arp_requset(TYPE_Route *rt, MSG_Info *pinfo, ARP_Hdr *arp_hdr)
{
	int port = 0;

	memcpy(pinfo->dst_ip, arp_hdr->dst_ip, 6);
	port = get_transpond_port(rt, pinfo->dst_ip);

	if(port != -1)
	{
		//��ȡARP����˵�ip��mac��ַ
		memcpy(pinfo->src_mac, arp_hdr->src_mac, 6);
		memcpy(pinfo->src_ip,  arp_hdr->src_ip, 4);

		//��ARPӦ���
		memcpy(rt->recv, pinfo->src_mac, 6); //
		memcpy(rt->recv+6, rt->eth_port[port].mac, 6);

		arp_hdr->ar_op = htons(2); // -> ��������ȼ����� &

		memcpy(arp_hdr->src_mac, rt->eth_port[port].mac, 6);
		memcpy(arp_hdr->src_ip, pinfo->dst_ip, 4);

		memcpy(arp_hdr->dst_mac, pinfo->src_mac,6);
		memcpy(arp_hdr->dst_ip,  pinfo->src_ip, 4);


		int send_len = send_msg(rt, port, pinfo->len);

		return send_len;
	}

	return -1;
}

/*****************************************************************************
 �� �� ��  : dispose_arp_reply()
 ��������  : ����arp����
 �������  : rt        TYPE_Route ���ͽṹָ��
 			 ARP_Hdr   ARP_Hdr ����ָ��
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��12��
*****************************************************************************/
void dispose_arp_reply(ARP_Table *head, ARP_Hdr *arp_hdr)
{
	ARP_Table *pnode = NULL, node;

	memcpy(node.ip,  arp_hdr->src_ip, 4);
	memcpy(node.mac, arp_hdr->src_mac,6);

	pnode = (ARP_Table *)search_arp_table(head, node.ip);

	if(pnode != NULL) {
		change_arp_mac(head, node.ip, node.mac);
	}
	else {
		head = (ARP_Table *)insert_arp_table(head, node);
	}
}
