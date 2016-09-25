/******************************************************************************
  文 件 名   : tcp_server.c
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月16日
  最近修改   :
  功能描述   : tcp 服务器 调用函数
  函数列表   :            
              tcp_send_arp_table
              tcp_send_firewall_rules
              tcp_send_port_info
              dispose_tcp_cmd
  修改历史   :
  1.日    期   : 2015年9月16日
    作    者   : if
    修改内容   : 创建文件

******************************************************************************/
#include "common.h"


/*****************************************************************************
 函 数 名  : tcp_send_arp_table()
 功能描述  : 给TCP客户端发送ARP表的信息
 输入参数  : rt       TYPE_Route类型结构体 
 			 connfd   监听套接字
 返 回 值  : NULL
 修改日期  : 2015年9月16日
*****************************************************************************/
void tcp_send_arp_table(TYPE_Route *rt, int connfd)
{
	uchar ip[16] = "";
	uchar mac[18]= "";
	uchar msg[50]= "";
	ARP_Table *pb = NULL;
	
	pb = rt->arp_head;

	send(connfd, "_____IP________________MAC_______\n", \
		 strlen("_____IP________________MAC_______\n"), 0);
	
	while(pb != NULL) {
		//bzero(ip,  sizeof(ip));
		//bzero(mac, sizeof(mac));
		//bzero(msg, sizeof(msg));
		
		sprintf(ip,"%d.%d.%d.%d",\
				pb->ip[0],pb->ip[1],pb->ip[2],pb->ip[3]);
		
		sprintf(mac,"%02x:%02x:%02x:%02x:%02x:%02x",\
				pb->mac[0],pb->mac[1],pb->mac[2],pb->mac[3],pb->mac[4],pb->mac[5]);
	
		sprintf(msg, "-%-12s -- %s\n", ip, mac);
		send(connfd, msg, strlen(msg), 0);
		
		pb = pb->next;
	}

	send(connfd, "_________________________________\n", \
		 strlen("_________________________________\n"), 0);
	send(connfd, "#end#", strlen("#end#"), 0);
}

/*****************************************************************************
 函 数 名  : tcp_send_firewall_rules()
 功能描述  : 给TCP客户端发送防火墙的设定规则
 输入参数  : rt       TYPE_Route类型结构体 
 			 connfd   监听套接字
 返 回 值  : NULL
 修改日期  : 2015年9月16日
*****************************************************************************/
void tcp_send_firewall_rules(TYPE_Route *rt, int connfd)
{
	FIRE_Wall *pnode = NULL;
	FIRE_Wall *pbuf[4] = {rt->mac_head,rt->ip_head,rt->port_head,rt->pro_head};
	char rule[RULE_LEN] = "";
	int i = 0;

	send(connfd,"\n------firewall rules-------\n", \
		 strlen("\n------firewall rules-------\n"), 0);
	
	for(i=0; i<4; i++) {
		pnode = pbuf[i];
	
		while(pnode != NULL) {
			strcpy(rule, pnode->rule);
			strcat(rule,"\n");
			
			send(connfd, rule, strlen(rule), 0);			
			pnode = pnode->next;
		}		
	}

	send(connfd,"---------------------------\n\n", \
		 strlen("---------------------------\n\n"), 0);
	send(connfd, "#end#", strlen("#end#"), 0);
}

/*****************************************************************************
 函 数 名  : tcp_send_port_info()
 功能描述  : 给TCP客户端发送接口信息
 输入参数  : rt       TYPE_Route类型结构体 
 			 connfd   监听套接字
 返 回 值  : NULL
 修改日期  : 2015年9月16日
*****************************************************************************/
void tcp_send_port_info(TYPE_Route *rt, int connfd)
{
	int i = 0;
	char name[64];
	char ip[16];
	char mask[16];
	char b_ip[16];
	char mac[18];
	char msg[200];

	for(i=0;i<rt->port_num;i++)
	{
		
		sprintf(name, "___________%s___________", rt->eth_port[i].name);
	
		//ip
		sprintf(ip, "%d.%d.%d.%d",\
			   rt->eth_port[i].ip[0],rt->eth_port[i].ip[1],\
			   rt->eth_port[i].ip[2],rt->eth_port[i].ip[3]);
		//mac
		sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",\
			   rt->eth_port[i].mac[0],rt->eth_port[i].mac[1],\
			   rt->eth_port[i].mac[2],rt->eth_port[i].mac[3],\
			   rt->eth_port[i].mac[4],rt->eth_port[i].mac[5]);
		//netmask
		printf(mask, "%d.%d.%d.%d",\
			   rt->eth_port[i].netmask[0],rt->eth_port[i].netmask[1],\
			   rt->eth_port[i].netmask[2],rt->eth_port[i].netmask[3]);
		//broadcast ip
		sprintf(b_ip, "%d.%d.%d.%d",\
			   rt->eth_port[i].bc_ip[0],rt->eth_port[i].bc_ip[1],\
			   rt->eth_port[i].bc_ip[2],rt->eth_port[i].bc_ip[3]);
		
		sprintf(msg, "%s\n%s\n%s\n%s\n%s\n", name, ip, mac, mask, b_ip);

		send(connfd, msg, strlen(msg), 0);
		send(connfd, "__________________________\n", \
			 strlen("__________________________\n"), 0);
		send(connfd, "#end#", strlen("#end#"), 0);
	}
		

}

/*****************************************************************************
 函 数 名  : dispose_cmd()
 功能描述  : 处理命令，并执行相应的动作
 输入参数  : rt     TYPE_Route类型结构体 
 			 cmd    待处理、执行的命令
 返 回 值  : NULL
 修改日期  : 2015年9月16日
*****************************************************************************/
void dispose_tcp_cmd(TYPE_Route *rt, int connfd, char cmd[])
{
	pthread_mutex_lock(&rt->mutex); // 上锁
	
	if(strcmp(cmd, "help") == 0){

		char route_help[] = {
		"***************************************************\n\
		 -      help: 查看帮助信息                         *\n\
		 -       arp: 查看 ARP 表                          *\n\
		 -  ifconfig: 查看网卡信息                         *\n\
		 -   fire on: 开启防火墙                           *\n\
		 -  fire off: 关闭防火墙                           *\n\
		 -    lsfire: 查看防火墙规则                       *\n\
		 -   setfire: 设置防火墙规则                       *\n\
		 ***************************************************\n"			
		};

		send(connfd, route_help, strlen(route_help), 0);
		send(connfd, "#end#", strlen("#end#"), 0);
	}
	else if(strcmp(cmd,"arp") == 0){
		tcp_send_arp_table(rt, connfd);
	}
	else if(strcmp(cmd,"ifconfig") == 0){
		tcp_send_port_info(rt, connfd);
	}
	else if(strcmp(cmd,"lsfire") == 0){	
		tcp_send_firewall_rules(rt, connfd);
	}
	else if(strcmp(cmd,"setfire") == 0){
		
		int i, len;
		char rule[RULE_LEN] = "";
		char passwd[PASSWD_LEN] = "";

		for(i=0; i<2; i++) {	
			send(connfd, "passwd: ", strlen("passwd: "), 0);
			send(connfd, "#end#", strlen("#end#"), 0);
			len = recv(connfd, passwd, sizeof(passwd), 0);
			if(len == 0) goto out;
			
			if(strcmp(passwd, rt->passwd) == 0){
			    send(connfd, "passed", strlen("passed"), 0);
			    send(connfd, "#end#", strlen("#end#"), 0);
				break;
			}
			else {
				send(connfd, "\nerror, try again!\n", strlen("\nerror, try again!\n"), 0);
				send(connfd, "#end#", strlen("#end#"), 0);
			}
		}		
		if(i == 2) goto out;
		
		char fire_help[] = {
			"*************************************************************************\n\
			 -				>>>   温馨提示: ()是可选选项  <<<						 *\n\
			 -设置 ip 过滤规则，格式:	ip (opt) <ip>	-> ip (src) 192.168.1.1 	 *\n\
			 -设置 mac过滤规则，格式:   mac (opt) <mac>	-> mac (dst) 192.168.1.1	 *\n\
			 -设置端口过滤规则，格式:  port (opt) <port> -> port (host) 8000 		 *\n\
			 -设置协议过滤规则，格式: <pro> (type) (opt) (type_val) -> udp port 8000 *\n\
			 -删除已设置的规则，输入: -d <要删除的规则>								 *\n\
			 -查看设置规则帮助，输入: -h 											 *\n\
			 -查看已设置的规则，输入: ls 											 *\n\
			 -退出防火墙设置，  输入: esc											 *\n\
			 *************************************************************************\n"
		};
		send(connfd, fire_help, strlen(fire_help), 0);
		send(connfd, "#end#", strlen("#end#"), 0);
			
		while(1) {			
			bzero(rule, RULE_LEN);
			send(connfd, "entry: ", strlen("entry: "), 0);
			send(connfd, "#end#", strlen("#end#"), 0);
			len = recv(connfd, rule, RULE_LEN, 0);		
			if(len == 0) goto out;			

			if(strcmp(rule,"ls") == 0){
				tcp_send_firewall_rules(rt, connfd);
			}
			else if(strcmp(rule,"-h") == 0) {
				send(connfd, fire_help, strlen(fire_help), 0);
				send(connfd, "#end#", strlen("#end#"), 0);
			}	
			else if(strncmp(rule,"-d",2) == 0) {
				char *prule = NULL;
				prule = rule+3; //跳过 "-d "
				delete_firewall_rule(rt, prule);
				firewall_save_all_rules(rt);
			}
			else if(strcmp(rule,"passwd") == 0) {
				send(connfd, "new passwd: ", strlen("new passwd: "), 0);
				send(connfd, "#end#", strlen("#end#"), 0);
				len = recv(connfd, passwd, sizeof(passwd), 0);				
				if(len == 0) goto out;
				
				get_passwd(rt->passwd, PASSWD_LEN-1);
				firewall_save_passwd(rt->passwd);
			}
			else if(strcmp(rule,"esc") == 0){
				send(connfd, "exitting set firewall...\n", 
					 strlen("exitting set firewall...\n"), 0);
				send(connfd, "#end#", strlen("#end#"), 0);
				break;
			}
			else {			
				firewall_build_rule(rt, rule, 1);
			}
		}		
	}	

	out:
	pthread_mutex_unlock(&rt->mutex);// 解锁
}

