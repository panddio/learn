/******************************************************************************
  文 件 名   : msg_dispose.c
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月15日
  最近修改   :
  功能描述   : 处理网络数据
  函数列表   :
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
  修改历史   :
  1.日    期   : 2015年9月15日
    作    者   : if
    修改内容   : 创建文件

******************************************************************************/
#include "common.h"
#include "arp_link.h"


/*****************************************************************************
 函 数 名  : get_mac()
 功能描述  : 提取目的mac、源mac
 输入参数  : recv      接收网络数据包的缓存
 			 dst_mac   存储目的mac的首地址  传入NULL 则不提取
 			 src_mac   存储源mac的首地址    传入NULL 则不提取
 返 回 值  : NULL
 修改日期  : 2015年9月12日
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
 函 数 名  : get_type()
 功能描述  : 获取协议类型
 输入参数  : recv     接收网络数据包的缓存
 返 回 值  : 返回协议类型(无符号短整型整数)
 修改日期  : 2015年9月11日
*****************************************************************************/
uint16 get_type(const uchar *recv)
{
	uint16 type = 0;

	type = ntohs(*(uint16 *)(recv+12));

	return type;
}

/*****************************************************************************
 函 数 名  : get_ip()
 功能描述  : 提取目的ip、源ip
 输入参数  : recv     接收网络数据包的缓存
 			 dst_ip   存储目的ip的首地址  传入NULL 则不提取
 			 src_ip   存储源ip的首地址    传入NULL 则不提取
 返 回 值  : NULL
 修改日期  : 2015年9月12日
*****************************************************************************/
void get_ip(const uchar *recv, uchar *dst_ip, uchar *src_ip)
{
	if(src_ip != NULL){
		//提取源ip
		memcpy(src_ip, recv+12, 4);
	}

	if(dst_ip != NULL){
		//提取目的ip
		memcpy(dst_ip, recv+16, 4);
	}
}

/*****************************************************************************
 函 数 名  : show_msg_ip()
 功能描述  : 提取目的ip、源ip
 输入参数  : recv     接收网络数据包的缓存
 返 回 值  : NULL
 修改日期  : 2015年9月11日
*****************************************************************************/
void show_msg_ip(const uchar *recv)
{
	unsigned char dst_ip[16] = "";
	unsigned char src_ip[16] = "";

	//提取源ip
	sprintf(src_ip,"%d.%d.%d.%d",\
			recv[12],recv[13],recv[14],recv[15]);

	//提取目的ip
	sprintf(dst_ip,"%d.%d.%d.%d",\
			recv[16],recv[17],recv[18],recv[19]);

	printf("IP:%s >> %s\n", src_ip, dst_ip);
}

/*****************************************************************************
 函 数 名  : check_if_same_subnet()
 功能描述  : 检测目的ip跟网卡是否在同一网段
 输入参数  : eth_mask     网卡子网掩码
             eth_ip       网卡ip
             dst_ip       目的ip
 返 回 值  : 布尔型
 修改日期  : 2015年9月12日
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
 函 数 名  : get_transpond_port()
 功能描述  : 获取数据转发的接口
 输入参数  : rt        TYPE_Route 类型结构指针
 			 dst_ip    目的ip
 返 回 值  : 返回网卡的编号
 修改日期  : 2015年9月12日
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
 函 数 名  : send_msg()
 功能描述  : 获取ip数据包的转发接口
 输入参数  : rt        TYPE_Route 类型结构指针
 			 port      网络接口的编号
 			 msg_len   发送数据长度
 返 回 值  :
 修改日期  : 2015年9月12日
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
 函 数 名  : transpond_msg()
 功能描述  : 获取ip数据包的转发接口
 输入参数  : rt        TYPE_Route 类型结构指针
 			 dst_ip    目的ip
 			 port      网络接口的编号
 			 msg_len   发送数据包的长度
 返 回 值  : 无法获取目的mac时，返回-1，否则返回实际发送的长度
 修改日期  : 2015年9月12日
*****************************************************************************/
int transpond_msg(TYPE_Route *rt, const uchar dst_ip[], int port, int msg_len)
{
	ARP_Table *pnode = NULL;

	if(rt->arp_head == NULL){ //如果ARP表为空，则建立ARP表
		build_arp_table(rt);
	}

	pnode = (ARP_Table *)search_arp_table(rt->arp_head, dst_ip);

	if(pnode == NULL){ //在arp表中没有找到目的ip
		Boolean flag = broadcast(rt, dst_ip); //广播获取目的mac

		if(flag == FALSE) { //广播没有获取到目的mac

			return -1;
		}
		pnode = (ARP_Table *)search_arp_table(rt->arp_head, dst_ip);
	}

//	uchar dst_mac[6] = "";
//	uchar src_mac[6] = "";
//
//	memcpy(dst_mac, pnode->mac, 6);
//	memcpy(src_mac, rt->eth_port[port].mac, 6);

	memcpy(rt->recv,   pnode->mac, 6); //修改ip数据包的目的mac地址
	memcpy(rt->recv+6, rt->eth_port[port].mac, 6); //修改ip数据包的源mac地址


	int send_len = send_msg(rt, port, msg_len);

	return send_len;
}

/*****************************************************************************
 函 数 名  : reply_arp_requset()
 功能描述  : 应答arp请求
 输入参数  : rt        TYPE_Route 类型结构指针
 			 pinfo     MSG_Info 类型指针
 			 ARP_Hdr   ARP_Hdr 类型指针
 返 回 值  : 返回发送的长度，出错返回-1
 修改日期  : 2015年9月12日
*****************************************************************************/
int reply_arp_requset(TYPE_Route *rt, MSG_Info *pinfo, ARP_Hdr *arp_hdr)
{
	int port = 0;

	memcpy(pinfo->dst_ip, arp_hdr->dst_ip, 6);
	port = get_transpond_port(rt, pinfo->dst_ip);

	if(port != -1)
	{
		//获取ARP请求端的ip和mac地址
		memcpy(pinfo->src_mac, arp_hdr->src_mac, 6);
		memcpy(pinfo->src_ip,  arp_hdr->src_ip, 4);

		//组ARP应答包
		memcpy(rt->recv, pinfo->src_mac, 6); //
		memcpy(rt->recv+6, rt->eth_port[port].mac, 6);

		arp_hdr->ar_op = htons(2); // -> 运算符优先级高于 &

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
 函 数 名  : dispose_arp_reply()
 功能描述  : 处理arp请求
 输入参数  : rt        TYPE_Route 类型结构指针
 			 ARP_Hdr   ARP_Hdr 类型指针
 返 回 值  : NULL
 修改日期  : 2015年9月12日
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
