/******************************************************************************
  文 件 名   : route_firewall.c
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月15日
  最近修改   :
  功能描述   : 防火墙规则创建和过滤
  函数列表   :
              delete_firewall_rule
              firewall_build_rule
              firewall_filt
              firewall_filt_ip
              firewall_filt_mac
              firewall_filt_port
              firewall_filt_protocol
  修改历史   :
  1.日    期   : 2015年9月15日
    作    者   : if
    修改内容   : 创建文件

******************************************************************************/
#include "common.h"
#include "firewall_link.h"


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

#if 0
/*****************************************************************************
 函 数 名  : firewall_rule_set_help()
 功能描述  : 防火墙规则规则设置帮助
 输入参数  : NULL
 返 回 值  : NULL
 修改日期  : 2015年9月14日
*****************************************************************************/
void firewall_rule_set_help(void)
{
	printf("*************************************************************************\n");
	printf("-               >>>   温馨提示: ()是可选选项  <<<                       *\n");
	printf("-设置 ip 过滤规则，格式:    ip (opt) <ip>   -> ip (src) 192.168.1.1     *\n");
	printf("-设置 mac过滤规则，格式:   mac (opt) <mac>  -> mac (dst) 192.168.1.1    *\n");
	printf("-设置端口过滤规则，格式:  port (opt) <port> -> port (host) 8000         *\n");
	printf("-设置协议过滤规则，格式: <pro> (type) (opt) (type_val) -> udp port 8000 *\n");
	printf("-删除已设置的规则，输入: -d <要删除的规则>                              *\n");
	printf("-查看设置规则帮助，输入: -h                                             *\n");
	printf("-查看已设置的规则，输入: ls                                             *\n");
	printf("-退出防火墙设置，  输入: esc                                            *\n");
	printf("*************************************************************************\n");
}
#endif
/*****************************************************************************
 函 数 名  : firewall_build_rule()
 功能描述  : 建立防火墙规则表
 输入参数  : rt        TYPE_Route 类型结构指针
             rule      待插入的规则
             flag      是否保存到文件标准 1: 保存
 返 回 值  : NULL
 修改日期  : 2015年9月13日
*****************************************************************************/
void firewall_build_rule(TYPE_Route *rt, const char *rule, char flag)
{
	struct _firewall node;

	bzero(node.rule, sizeof(node.rule));
	strcpy(node.rule, rule);

	if(strncmp(rules[0], rule, strlen(rules[0])) == 0){
		rt->ip_head = (FIRE_Wall *)insert_firewall_node(rt->ip_head, node);
	}
	else if(strncmp(rules[1], rule, strlen(rules[1])) == 0){
		rt->mac_head = (FIRE_Wall *)insert_firewall_node(rt->mac_head, node);
	}
	else if(strncmp(rules[2], rule, strlen(rules[2])) == 0){
		rt->port_head = (FIRE_Wall *)insert_firewall_node(rt->port_head, node);
	}
	else{

		int i = 0;
		for(i = 3; i < sizeof(rules)/sizeof(rules[0]); i++)
		{
		   if(strncmp(rules[i], rule, strlen(rules[i])) == 0){
		   	rt->pro_head = (FIRE_Wall *)insert_firewall_node(rt->pro_head, node);
			break;
		   }
		}
	}

	if(flag == 1){
		filrewall_save_rule(rule); //保存规则到文件
	}

}

/*****************************************************************************
 函 数 名  : delete_firewall_rule()
 功能描述  : 删除防火墙规则表
 输入参数  : rt        TYPE_Route 类型结构指针
             rule      待删除的规则
 返 回 值  : NULL
 修改日期  : 2015年9月15日
*****************************************************************************/
void delete_firewall_rule(TYPE_Route *rt, const char *rule)
{
	if(strncmp(rules[0], rule, strlen(rules[0])) == 0){ 	
		rt->ip_head = (FIRE_Wall *)delete_firewall_node(rt->ip_head, rule);
	}
	else if(strncmp(rules[1], rule, strlen(rules[1])) == 0){
		rt->mac_head = (FIRE_Wall *)delete_firewall_node(rt->ip_head, rule);
	}	
	else if(strncmp(rules[2], rule, strlen(rules[2])) == 0){
		rt->port_head = (FIRE_Wall *)delete_firewall_node(rt->ip_head, rule);
	}	
	else{
		
		int i = 0;

		for(i = 3; i < sizeof(rules)/sizeof(rules[0]); i++)
		{
		   if(strncmp(rules[i], rule, strlen(rules[i])) == 0){
			rt->pro_head = (FIRE_Wall *)delete_firewall_node(rt->ip_head, rule);
			break;
		   }
		}
	}

}

/*****************************************************************************
 函 数 名  : firewall_filt_ip()
 功能描述  : 防火墙过滤ip
 输入参数  : rt        TYPE_Route 类型结构指针
             pinfo     MSG_Info 类型结构指针
 返 回 值  : 返回0，说明可以通过ip过滤，返回-1，说明不能通过ip过滤
 修改日期  : 2015年9月13日
*****************************************************************************/
static int firewall_filt_ip(TYPE_Route *rt, MSG_Info *pinfo)
{
	if(rt->ip_head != NULL){
		
		uchar type[16];
		uchar ip[16];
		uchar src_ip[16] = "";
		uchar dst_ip[16] = "";

		struct _firewall *pnode = NULL;
		pnode = rt->ip_head;

		//提取目的ip	
		sprintf(dst_ip,"%d.%d.%d.%d",\
		pinfo->dst_ip[0],pinfo->dst_ip[1],pinfo->dst_ip[2],pinfo->dst_ip[3]);
		
		//提取源ip	
		sprintf(src_ip,"%d.%d.%d.%d",\
		pinfo->src_ip[0],pinfo->src_ip[1],pinfo->src_ip[2],pinfo->src_ip[3]);

		while(pnode != NULL)
		{
			bzero(type, sizeof(type));
			bzero(ip, sizeof(ip));

			sscanf(pnode->rule, "%*s %s %s", type, ip);

			if(strcmp(type, "host") == 0 || strlen(ip) == 0) {

				if(strlen(ip) != 0){
					if(strcmp(src_ip, ip) == 0 || \
					   strcmp(dst_ip, ip) == 0){
						return -1;
					}
				}
				else {
					if(strcmp(src_ip, type) == 0 || \
					   strcmp(dst_ip, type) == 0){
						return -1;					
					}
				}
			}
			else if(strcmp(type, "src") == 0) {
				if(strcmp(src_ip, ip) == 0){
					return -1;
				}
			}
			else if(strcmp(type, "dst") == 0) {
				if(strcmp(dst_ip, ip) == 0) {
					return -1;
				}
			}	
			else {
				rt->mac_head = (FIRE_Wall *)delete_firewall_node(rt->ip_head, pnode->rule);
			}
			
			pnode = pnode->next;
		}
	}

	return 0;
}

/*****************************************************************************
 函 数 名  : firewall_filt_mac()
 功能描述  : 防火墙过滤mac
 输入参数  : rt        TYPE_Route 类型结构指针
             pinfo     MSG_Info 类型结构指针
 返 回 值  : 返回0，说明可以通过mac过滤，返回-1，说明不能通过mac过滤
 修改日期  : 2015年9月13日
*****************************************************************************/
static int firewall_filt_mac(TYPE_Route *rt, MSG_Info *pinfo)
{
	if(rt->mac_head != NULL){

		uchar type[18];
		uchar mac[18];
		uchar dst_mac[18] = "";
		uchar src_mac[18] = "";
		
		struct _firewall *pnode = NULL;
		pnode = rt->mac_head;
		
		//提取目的mac
		sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x",\
			   pinfo->dst_mac[0],pinfo->dst_mac[1],pinfo->dst_mac[2],\
			   pinfo->dst_mac[3],pinfo->dst_mac[4],pinfo->dst_mac[5]);
		
		//提取源mac		
		sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x",\
			pinfo->src_mac[0],pinfo->src_mac[1],pinfo->src_mac[2],\
			pinfo->src_mac[3],pinfo->src_mac[4],pinfo->src_mac[5]);

		while(pnode != NULL)
		{
			bzero(type, sizeof(type));
			bzero(mac, sizeof(mac));

			sscanf(pnode->rule, "%*s %s %s", type, mac);

			if(strcmp(type, "host") == 0 || strlen(mac) == 0) {

				if(strlen(mac) != 0){
					if(strcmp(src_mac, mac) == 0 || \
					   strcmp(src_mac, mac) == 0){
						return -1;
					}
				}
				else {
					if(strcmp(src_mac, type) == 0 || \
					   strcmp(src_mac, type) == 0){
						return -1;					
					}
				}				
			}
			else if(strcmp(type, "src") == 0) {
				if(strcmp(src_mac, mac) == 0){
					return -1;
				}
			}
			else if(strcmp(type, "dst") == 0) {
				if(strcmp(dst_mac, mac) == 0) {
					return -1;
				}
			}	
			else {
				rt->mac_head = (FIRE_Wall *)delete_firewall_node(rt->mac_head, pnode->rule);
			}

			pnode = pnode->next;
		}
	}

	return 0;
}

/*****************************************************************************
 函 数 名  : firewall_filt_port()
 功能描述  : 防火墙过滤端口
 输入参数  : rt        TYPE_Route 类型结构指针
             pinfo     MSG_Info 类型结构指针
 返 回 值  : 返回0，说明可以通过端口过滤，返回-1，说明不能通过端口过滤
 修改日期  : 2015年9月13日
*****************************************************************************/
static int firewall_filt_port(TYPE_Route *rt, MSG_Info *pinfo)
{
	if(rt->port_head != NULL){

		uchar type[6];
		uchar port[6];
		
		uint16 port_val = 0;
		
		struct _firewall *pnode = NULL;
		pnode = rt->port_head;

		while(pnode != NULL)
		{
			bzero(type, sizeof(type));
			bzero(port, sizeof(port));

			sscanf(pnode->rule, "%*s %s %s", type, port);

			if(strlen(port) != 0)
				port_val = (uint16)atoi(port);
			else
				port_val = (uint16)atoi(type);
			
			if(strcmp(type, "host") == 0 || strlen(port) == 0) {
				
				if(port_val == pinfo->s_port || \
				   port_val == pinfo->d_port){
					return -1;
				}
			}
			else if(strcmp(type, "src") == 0) {
				if(port_val == pinfo->s_port){
					return -1;
				}
			}
			else if(strcmp(type, "dst") == 0) {
				if(port_val == pinfo->d_port) {
					return -1;
				}
			}	
			else {
				rt->mac_head = (FIRE_Wall *)delete_firewall_node(rt->port_head, pnode->rule);
			}

			pnode = pnode->next;			
		}
	}	

	return 0;
}

/*****************************************************************************
 函 数 名  : firewall_filt_protocol()
 功能描述  : 防火墙过滤协议类型
 输入参数  : rt        TYPE_Route 类型结构指针
             pinfo     MSG_Info 类型结构指针
 返 回 值  : 返回0，说明可以通过协议过滤，返回-1，说明不能通过协议过滤
 修改日期  : 2015年9月13日
*****************************************************************************/
static int firewall_filt_protocol(TYPE_Route *rt, MSG_Info *pinfo)
{
	if(rt->pro_head != NULL){

		uchar part[4][18];
		
		struct _firewall *pnode = NULL;
		pnode = rt->pro_head;

		while(pnode != NULL)
		{
			sscanf(pnode->rule, "%s %s %s %s", *(part+0), *(part+1), *(part+2), *(part+3));

			if(strlen(*(part+1)) == 0){
				
				if(strcmp(*(part+0), "arp") == 0){
					if(pinfo->frame_type == 0x0806){
						return -1;
					}
				}
				else if(strcmp(*(part+0), "icmp") == 0){
					if(pinfo->pro_type == 1){
						return -1;
					}
				}
				else if(strcmp(*(part+0), "igmp") == 0){
					if(pinfo->pro_type == 2){
						return -1;
					}
				}
				else if(strcmp(*(part+0), "tcp") == 0){
					if(pinfo->pro_type == 6){
						return -1;
					}
				}
				else if(strcmp(*(part+0), "udp") == 0){
					if(pinfo->pro_type == 17){
						return -1;
					}
				}
				else if(strcmp(*(part+0), "ftp") == 0){
					if(pinfo->d_port == 21){
						return -1;
					}
				}
				else if(strcmp(*(part+0), "http") == 0){
					if(pinfo->d_port == 80){
						return -1;
					}
				}
				else if(strcmp(*(part+0), "tftp") == 0){
					if(pinfo->d_port == 69){
						return -1;
					}
				}
				else{
					rt->pro_head = (FIRE_Wall *)delete_firewall_node(rt->pro_head, pnode->rule);
				}
			}
			
			else {
				if(strcmp(*(part+1), "mac")) {
					
					uchar dst_mac[18] = "";
					uchar src_mac[18] = "";
					
					//提取目的mac
					sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x",\
						   pinfo->dst_mac[0],pinfo->dst_mac[1],pinfo->dst_mac[2],\
						   pinfo->dst_mac[3],pinfo->dst_mac[4],pinfo->dst_mac[5]);
					
					//提取源mac 	
					sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x",\
						pinfo->src_mac[0],pinfo->src_mac[1],pinfo->src_mac[2],\
						pinfo->src_mac[3],pinfo->src_mac[4],pinfo->src_mac[5]);

					if(strcmp(*(part+2), "host") == 0 || strlen(*(part+3)) == 0) {

						if(strlen(*(part+3)) != 0){
							if(strcmp(src_mac, *(part+3)) == 0 || \
							   strcmp(src_mac, *(part+3)) == 0){
								return -1;
							}
						}
						else {
							if(strcmp(src_mac, *(part+2)) == 0 || \
							   strcmp(src_mac, *(part+2)) == 0){
								return -1;					
							}
						}				
					}
					else if(strcmp(*(part+2), "src") == 0) {
						if(strcmp(src_mac, *(part+3)) == 0){
							return -1;
						}
					}
					else if(strcmp(*(part+2), "dst") == 0) {
						if(strcmp(dst_mac, *(part+3)) == 0) {
							return -1;
						}
					}	
					else {
						rt->pro_head = (FIRE_Wall *)delete_firewall_node(rt->pro_head, pnode->rule);
					}					
				}
				else if(strcmp(*(part+1), "ip")) {
					
					uchar src_ip[16] = "";
					uchar dst_ip[16] = "";

					//提取目的ip	
					sprintf(dst_ip,"%d.%d.%d.%d",\
					pinfo->dst_ip[0],pinfo->dst_ip[1],pinfo->dst_ip[2],pinfo->dst_ip[3]);
					
					//提取源ip	
					sprintf(src_ip,"%d.%d.%d.%d",\
					pinfo->src_ip[0],pinfo->src_ip[1],pinfo->src_ip[2],pinfo->src_ip[3]);

					if(strcmp(*(part+2), "host") == 0 || strlen(*(part+3)) == 0) {

						if(strlen(*(part+3)) != 0){
							if(strcmp(src_ip, *(part+3)) == 0 || \
							   strcmp(dst_ip, *(part+3)) == 0){
								return -1;
							}
						}
						else {
							if(strcmp(src_ip, *(part+2)) == 0 || \
							   strcmp(dst_ip, *(part+2)) == 0){
								return -1;					
							}
						}
					}
					else if(strcmp(*(part+2), "src") == 0) {
						if(strcmp(src_ip, *(part+3)) == 0){
							return -1;
						}
					}
					else if(strcmp(*(part+2), "dst") == 0) {
						if(strcmp(dst_ip, *(part+3)) == 0) {
							return -1;
						}
					}	
					else {
						rt->pro_head = (FIRE_Wall *)delete_firewall_node(rt->pro_head, pnode->rule);
					}					
				}
				else if(strcmp(*(part+1), "port")) {

					uint16 port_val = 0;
					if(strlen(*(part+3)) != 0)
						port_val = (uint16)atoi(*(part+3));
					else
						port_val = (uint16)atoi(*(part+2));

					if(strcmp(*(part+2), "host") == 0 || strlen(*(part+3)) == 0) {
			
					if(port_val == pinfo->s_port || \
					   port_val == pinfo->d_port){
						return -1;
						}
					}
					else if(strcmp(*(part+2), "src") == 0) {
						if(port_val == pinfo->s_port){
							return -1;
						}
					}
					else if(strcmp(*(part+2), "dst") == 0) {
						if(port_val == pinfo->d_port) {
							return -1;
						}
					}	
					else {
						rt->pro_head = (FIRE_Wall *)delete_firewall_node(rt->pro_head, pnode->rule);
					}
				}
				else {
					rt->pro_head = (FIRE_Wall *)delete_firewall_node(rt->pro_head, pnode->rule);
				}				
			}
		
			pnode = pnode->next;
		}		
	}
}

/*****************************************************************************
 函 数 名  : firewall_filt()
 功能描述  : 防火墙过滤
 输入参数  : rt        TYPE_Route 类型结构指针
             pinfo     MSG_Info 类型结构指针
 返 回 值  : 返回0，说明可以通过ip过滤，返回-1，说明不能通过ip过滤
 修改日期  : 2015年9月13日
*****************************************************************************/
int firewall_filt(TYPE_Route *rt, MSG_Info *pinfo)
{
	int ret = 0;
	rt->eth_hdr = (struct ether_header *)rt->recv;

	memcpy(pinfo->dst_mac, rt->eth_hdr->ether_dhost, ETH_ALEN);
	memcpy(pinfo->src_mac, rt->eth_hdr->ether_shost, ETH_ALEN);

	if(rt->fire_status == UP){
		ret = firewall_filt_mac(rt, pinfo);
		if(ret < 0) return -1;
	}
		
	pinfo->frame_type = ntohs(rt->eth_hdr->ether_type);

	if(pinfo->frame_type == 0x0800) {
		//recv+14 跳过mac头
		rt->ip_hdr = (struct iphdr *)(rt->recv + 14);
		
		memcpy(pinfo->src_ip, (uchar *)&rt->ip_hdr->saddr, 4);
		memcpy(pinfo->dst_ip, (uchar *)&rt->ip_hdr->daddr, 4);

		pinfo->pro_type = rt->ip_hdr->protocol;
		
		switch(pinfo->pro_type)
		{	
			case 6:
			{	// rt->ip_hdr->ihl * 4	跳过ip头部	
				rt->udp_hdr = (struct udphdr *)(rt->recv + 14 + rt->ip_hdr->ihl * 4);

				pinfo->s_port = ntohs(rt->udp_hdr->source);
				pinfo->d_port = ntohs(rt->udp_hdr->dest);
				break;
			}
			case 17:
			{
				rt->tcp_hdr = (struct tcphdr *)(rt->recv + 14 + rt->ip_hdr->ihl * 4);

				pinfo->s_port = ntohs(rt->tcp_hdr->source);
				pinfo->d_port = ntohs(rt->tcp_hdr->dest);
				break;
			}
		}

		if(rt->fire_status == UP){
			ret = firewall_filt_port(rt, pinfo);
			if(ret < 0) return -1;
		}
		
	}
	else if(pinfo->frame_type == 0x0806) {
		rt->arp_hdr = (struct _arphdr *)(rt->recv + 14);

		memcpy(pinfo->src_ip, rt->arp_hdr->src_ip, 4);
		memcpy(pinfo->dst_ip, rt->arp_hdr->dst_ip, 4);
	}

	if(rt->fire_status == UP){
		ret = firewall_filt_ip(rt, pinfo);
		if(ret < 0) return -1;
		
		ret = firewall_filt_protocol(rt, pinfo);
		if(ret < 0) return -1;
	}
	
	return 0;
}

