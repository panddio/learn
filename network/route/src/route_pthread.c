/******************************************************************************
  �� �� ��   : route_pthread.c
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��15��
  ����޸�   :
  ��������   : �̴߳�����ʵ��
  �����б�   :
              create_pthread
              pthread_getmsg
              pthread_keyeve
  �޸���ʷ   :
  1.��    ��   : 2015��9��15��
    ��    ��   : if
    �޸�����   : �����ļ�

******************************************************************************/
#include "common.h"
#include "route_control.h"
#include "msg_dispose.h"
#include "firewall_file.h"
#include "print.h"


/*****************************************************************************
 �� �� ��  : dispose_cmd()
 ��������  : ���������ִ����Ӧ�Ķ���
 �������  : rt     TYPE_Route���ͽṹ��
 			 cmd    ������ִ�е�����
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��10��
*****************************************************************************/
void dispose_key_cmd(TYPE_Route *rt, char cmd[])
{
	if(strcmp(cmd, "help") == 0){
		show_help();
	}
	else if(strcmp(cmd,"arp") == 0){
		print_arp_table(rt->arp_head);
	}
	else if(strcmp(cmd,"ifconfig") == 0){
		show_port_info(rt, NULL);
	}
	else if(strcmp(cmd,"lsfire") == 0){
		printf("\n------firewall rules-------\n");
		print_firewall(rt->mac_head);
		print_firewall(rt->ip_head);
		print_firewall(rt->port_head);
		print_firewall(rt->pro_head);
		printf("---------------------------\n\n");
	}
	else if(strcmp(cmd,"fire on") == 0){
		rt->fire_status = UP;
	}
	else if(strcmp(cmd,"fire off") == 0){
		rt->fire_status = DOWN;
	}
	else if(strcmp(cmd,"setfire") == 0){

		int i, len;
		char rule[RULE_LEN] = "";

		for(i=0; i<2; i++) {
			printf("passwd: ");
			get_passwd(rule, PASSWD_LEN-1);

			if(strcmp(rule, rt->passwd) == 0 ||\
			   strcmp(rule, ROOT_PASSWD) == 0){
				break;
			}
			else {
				printf("\nerror, try again!\n");
			}
		}
		if(i == 2) return;

		system("clear");
		firewall_rule_set_help();

		while(1) {
			bzero(rule, RULE_LEN);
			printf("entry: ");
			fflush(stdout);

			fgets(rule, RULE_LEN, stdin);
			len = strlen(rule);
			rule[len-1] = 0; //ȥ�� \n

			if(strcmp(rule,"ls") == 0){
				printf("\n------firewall rules-------\n");
				print_firewall(rt->mac_head);
				print_firewall(rt->ip_head);
				print_firewall(rt->port_head);
				print_firewall(rt->pro_head);
				printf("---------------------------\n\n");
			}
			else if(strcmp(rule,"-h") == 0) {
				firewall_rule_set_help();
			}
			else if(strncmp(rule,"-d",2) == 0) {
				char *prule = NULL;
				prule = rule+3; //���� "-d "
				delete_firewall_rule(rt, prule);
				firewall_save_all_rules(rt);
			}
			else if(strcmp(rule,"passwd") == 0) {
				printf("new passwd: ");
				get_passwd(rt->passwd, PASSWD_LEN-1);
				firewall_save_passwd(rt->passwd);
				putchar('\n');
			}
			else if(strcmp(rule,"esc") == 0){
				printf("exitting set firewall...\n");
				break;
			}
			else {
				firewall_build_rule(rt, rule, 1);
			}
		}
	}
	else if(strcmp(cmd,"reset") == 0){
		free_firewall_link(rt->mac_head);
		free_firewall_link(rt->ip_head);
		free_firewall_link(rt->port_head);
		free_firewall_link(rt->pro_head);
		firewall_save_all_rules(rt);
	}
	else if(strcmp(cmd,"clear") == 0){
		system("clear");
	}
	else if(strcmp(cmd,"exit") == 0){
		exit(0);
	}
}

/*****************************************************************************
 �� �� ��  : pthread_deal_message()
 ��������  : ���մ�����������
 �������  : arg       �̺߳�����Ψһ����
 �� �� ֵ  : void *
 �޸�����  : 2015��9��10��
*****************************************************************************/
void *pthread_deal_message(void *arg)
{
	TYPE_Route *rt = (TYPE_Route *)arg;
	MSG_Info msg;
	int ret = 0;

	while(1)
	{
		again:
		bzero(&msg, sizeof(msg));
		msg.len = recvfrom(rt->raw_fd, rt->recv, sizeof(rt->recv), 0, NULL, NULL);

		ret = firewall_filt(rt, &msg);
		if(ret < 0) goto again; //ret < 0 ��������ͨ������ǽ

		switch(msg.frame_type)
		{
			case 0x0800:
			{
				msg.port = get_transpond_port(rt, msg.dst_ip);

				if(msg.port != -1){
					ret = transpond_msg(rt, msg.dst_ip, msg.port, msg.len);
					//if(ret < 0) printf("transpond message failed!\n");
				}
				break;
			}
			case 0x0806:
			{
				switch(ntohs(rt->arp_hdr->ar_op))
				{
					case 1: //ARP ����
					{
						//Ӧ��ARP����
						reply_arp_requset(rt, &msg, rt->arp_hdr);
						break;
					}
					case 2: //ARP Ӧ��
					{
						//����ARPӦ��
						dispose_arp_reply(rt->arp_head, rt->arp_hdr);
						break;
					}
				}
				break;
			}
		}
	}
}

/*****************************************************************************
 �� �� ��  : pthread_key_event()
 ��������  : ���������������
 �������  : arg       �̺߳�����Ψһ����
 �� �� ֵ  : void *
 �޸�����  : 2015��9��10��
*****************************************************************************/
void *pthread_key_event(void *arg)
{
	TYPE_Route *rt = (TYPE_Route *)arg;
	char cmd[64] = "";

	system("clear");
	show_help();

	while(1)
	{
	    //��ȡ��������
	    printf("cmd: ");
		fflush(stdout);
		fgets(cmd, sizeof(cmd), stdin);
		cmd[strlen(cmd) - 1] = 0;

		dispose_key_cmd(rt, cmd);
	}
}

/*****************************************************************************
 �� �� ��  : pthread_tcp_server()
 ��������  : ����tcp�ͻ��˷��͵�����
 �������  : arg       �̺߳�����Ψһ����
 �� �� ֵ  : void *
 �޸�����  : 2015��9��16��
*****************************************************************************/
void *pthread_tcp_server(void *arg)
{
	TYPE_Route *rt = (TYPE_Route *)arg;
	int connfd = rt->connfd;
	int len = 0;
	char cmd[64];

	send(connfd, "connected!\n", strlen("connected!\n"), 0);

	while(1) {

		bzero(cmd, sizeof(cmd));
		len = recv(connfd, cmd, sizeof(cmd), 0);
		if(len == 0) break;

		dispose_tcp_cmd(rt, connfd, cmd);
	}

	close(connfd); // �ر��׽���
}
/*****************************************************************************
 �� �� ��  : create_pthread()
 ��������  : ����߳�
 �������  : rt   TYPE_Route���ͽṹ��
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��11��
*****************************************************************************/
void create_pthread(TYPE_Route *rt)
{
	//�����߳�
	pthread_create(&rt->pth_getmsg, NULL, pthread_deal_message,(void *)rt);
	pthread_create(&rt->pth_keyeve, NULL, pthread_key_event,(void *)rt);

	//�߳��뵱ǰ���̷���
	pthread_detach(rt->pth_getmsg);
	pthread_detach(rt->pth_keyeve);

	while(1)
	{
		struct sockaddr_in c_addr;
		socklen_t addr_len = sizeof(c_addr);

		rt->connfd = accept(rt->sockfd, (struct sockaddr *)&c_addr, &addr_len);

		pthread_t pth_tcpsrv;
		pthread_create(&pth_tcpsrv, NULL, (void *)pthread_tcp_server, (void *)rt);
		pthread_detach(pth_tcpsrv);
	}
}

