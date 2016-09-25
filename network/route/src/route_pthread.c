/******************************************************************************
  文 件 名   : route_pthread.c
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月15日
  最近修改   :
  功能描述   : 线程创建与实现
  函数列表   :
              create_pthread
              pthread_getmsg
              pthread_keyeve
  修改历史   :
  1.日    期   : 2015年9月15日
    作    者   : if
    修改内容   : 创建文件

******************************************************************************/
#include "common.h"
#include "route_control.h"
#include "msg_dispose.h"
#include "firewall_file.h"
#include "print.h"


/*****************************************************************************
 函 数 名  : dispose_cmd()
 功能描述  : 处理命令，并执行相应的动作
 输入参数  : rt     TYPE_Route类型结构体
 			 cmd    待处理、执行的命令
 返 回 值  : NULL
 修改日期  : 2015年9月10日
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
			rule[len-1] = 0; //去掉 \n

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
				prule = rule+3; //跳过 "-d "
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
 函 数 名  : pthread_deal_message()
 功能描述  : 接收处理网络数据
 输入参数  : arg       线程函数的唯一参数
 返 回 值  : void *
 修改日期  : 2015年9月10日
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
		if(ret < 0) goto again; //ret < 0 表明不能通过防火墙

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
					case 1: //ARP 请求
					{
						//应答ARP请求
						reply_arp_requset(rt, &msg, rt->arp_hdr);
						break;
					}
					case 2: //ARP 应答
					{
						//处理ARP应答
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
 函 数 名  : pthread_key_event()
 功能描述  : 处理键盘输入命令
 输入参数  : arg       线程函数的唯一参数
 返 回 值  : void *
 修改日期  : 2015年9月10日
*****************************************************************************/
void *pthread_key_event(void *arg)
{
	TYPE_Route *rt = (TYPE_Route *)arg;
	char cmd[64] = "";

	system("clear");
	show_help();

	while(1)
	{
	    //获取输入命令
	    printf("cmd: ");
		fflush(stdout);
		fgets(cmd, sizeof(cmd), stdin);
		cmd[strlen(cmd) - 1] = 0;

		dispose_key_cmd(rt, cmd);
	}
}

/*****************************************************************************
 函 数 名  : pthread_tcp_server()
 功能描述  : 处理tcp客户端发送的命令
 输入参数  : arg       线程函数的唯一参数
 返 回 值  : void *
 修改日期  : 2015年9月16日
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

	close(connfd); // 关闭套接字
}
/*****************************************************************************
 函 数 名  : create_pthread()
 功能描述  : 添加线程
 输入参数  : rt   TYPE_Route类型结构体
 返 回 值  : NULL
 修改日期  : 2015年9月11日
*****************************************************************************/
void create_pthread(TYPE_Route *rt)
{
	//创建线程
	pthread_create(&rt->pth_getmsg, NULL, pthread_deal_message,(void *)rt);
	pthread_create(&rt->pth_keyeve, NULL, pthread_key_event,(void *)rt);

	//线程与当前进程分离
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

