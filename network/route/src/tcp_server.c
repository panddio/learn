/******************************************************************************
  �� �� ��   : tcp_server.c
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��16��
  ����޸�   :
  ��������   : tcp ������ ���ú���
  �����б�   :            
              tcp_send_arp_table
              tcp_send_firewall_rules
              tcp_send_port_info
              dispose_tcp_cmd
  �޸���ʷ   :
  1.��    ��   : 2015��9��16��
    ��    ��   : if
    �޸�����   : �����ļ�

******************************************************************************/
#include "common.h"


/*****************************************************************************
 �� �� ��  : tcp_send_arp_table()
 ��������  : ��TCP�ͻ��˷���ARP�����Ϣ
 �������  : rt       TYPE_Route���ͽṹ�� 
 			 connfd   �����׽���
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��16��
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
 �� �� ��  : tcp_send_firewall_rules()
 ��������  : ��TCP�ͻ��˷��ͷ���ǽ���趨����
 �������  : rt       TYPE_Route���ͽṹ�� 
 			 connfd   �����׽���
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��16��
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
 �� �� ��  : tcp_send_port_info()
 ��������  : ��TCP�ͻ��˷��ͽӿ���Ϣ
 �������  : rt       TYPE_Route���ͽṹ�� 
 			 connfd   �����׽���
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��16��
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
 �� �� ��  : dispose_cmd()
 ��������  : ���������ִ����Ӧ�Ķ���
 �������  : rt     TYPE_Route���ͽṹ�� 
 			 cmd    ������ִ�е�����
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��16��
*****************************************************************************/
void dispose_tcp_cmd(TYPE_Route *rt, int connfd, char cmd[])
{
	pthread_mutex_lock(&rt->mutex); // ����
	
	if(strcmp(cmd, "help") == 0){

		char route_help[] = {
		"***************************************************\n\
		 -      help: �鿴������Ϣ                         *\n\
		 -       arp: �鿴 ARP ��                          *\n\
		 -  ifconfig: �鿴������Ϣ                         *\n\
		 -   fire on: ��������ǽ                           *\n\
		 -  fire off: �رշ���ǽ                           *\n\
		 -    lsfire: �鿴����ǽ����                       *\n\
		 -   setfire: ���÷���ǽ����                       *\n\
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
			 -				>>>   ��ܰ��ʾ: ()�ǿ�ѡѡ��  <<<						 *\n\
			 -���� ip ���˹��򣬸�ʽ:	ip (opt) <ip>	-> ip (src) 192.168.1.1 	 *\n\
			 -���� mac���˹��򣬸�ʽ:   mac (opt) <mac>	-> mac (dst) 192.168.1.1	 *\n\
			 -���ö˿ڹ��˹��򣬸�ʽ:  port (opt) <port> -> port (host) 8000 		 *\n\
			 -����Э����˹��򣬸�ʽ: <pro> (type) (opt) (type_val) -> udp port 8000 *\n\
			 -ɾ�������õĹ�������: -d <Ҫɾ���Ĺ���>								 *\n\
			 -�鿴���ù������������: -h 											 *\n\
			 -�鿴�����õĹ�������: ls 											 *\n\
			 -�˳�����ǽ���ã�  ����: esc											 *\n\
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
				prule = rule+3; //���� "-d "
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
	pthread_mutex_unlock(&rt->mutex);// ����
}

