/******************************************************************************
  文 件 名   : route_control.c
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月15日
  最近修改   :
  功能描述   : 数据发送
  函数列表   :
              broadcast
              build_arp_table
              get_ethernet_port
              route_init
              show_port_info
  修改历史   :
  1.日    期   : 2015年9月15日
    作    者   : if
    修改内容   : 创建文件

******************************************************************************/
#include "common.h"
#include "arp_link.h"
#include "firewall_file.h"
#include "route_control.h"

/*****************************************************************************
 函 数 名  : route_init()
 功能描述  : 初始化
 输入参数  : 无
 返 回 值  : NULL
 修改日期  : 2015年9月10日
*****************************************************************************/
void route_init(TYPE_Route *rt)
{
	//创建原始套接字
	rt->raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	//创建监听套接字
	rt->sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//让服务器绑定端口和ip
	bzero(&rt->s_addr, sizeof(rt->s_addr));
	rt->s_addr.sin_family = AF_INET;
	rt->s_addr.sin_port = htons(8080);
	rt->s_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(rt->sockfd, (struct sockaddr *)&rt->s_addr, sizeof(rt->s_addr));

	if(ret != 0)
	{
		perror("bind:");
		exit(-1);
	}
	//listen 创建链接队列
	listen(rt->sockfd, 5);

	rt->fire_status = UP; // 初始化防火墙的状态: 开启

	//初始化链表头指针
	rt->arp_head  = NULL;
	rt->mac_head  = NULL;
	rt->ip_head   = NULL;
	rt->port_head = NULL;
	rt->pro_head  = NULL;

	pthread_mutex_init(&rt->mutex, NULL); // 初始化互斥锁
	get_ethernet_port(rt);   // 获取网卡接口信息
	build_arp_table(rt);     // 创建ARP表
	firewall_config(rt);     // 读取规则文件，配置防火墙
	firewall_get_passwd(rt); // 获取保存在文件的防火墙密码
}

#if 0
/*****************************************************************************
 函 数 名  : show_help()
 功能描述  : 输入帮助提示
 输入参数  : 无
 返 回 值  : void
 修改日期  : 2015年9月10日
*****************************************************************************/
void show_help(void)
{
	printf("***************************************************\n");
	printf("-      help: 查看帮助信息                         *\n");
	printf("-       arp: 查看 ARP 表                          *\n");
	printf("-  ifconfig: 查看网卡信息                         *\n");
	printf("-   fire on: 开启防火墙                           *\n");
	printf("-  fire off: 关闭防火墙                           *\n");
	printf("-    lsfire: 查看防火墙规则                       *\n");
	printf("-   setfire: 设置防火墙规则                       *\n");
	printf("***************************************************\n");
}
#endif

/*****************************************************************************
 函 数 名  : get_ethernet_port()
 功能描述  : 获取网络接口信息
 输入参数  : 无
 返 回 值  : NULL
 修改日期  : 2015年9月10日
*****************************************************************************/
void get_ethernet_port(TYPE_Route *rt)
{
	struct ifreq buf[MAX_PORT];    /* ifreq结构数组 */
	struct ifconf ifc;             /* ifconf结构 */

	 /* 初始化ifconf结构 */
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = (caddr_t) buf;

	/* 获得接口列表 */
    if (ioctl(rt->raw_fd, SIOCGIFCONF, (char *)&ifc) == -1)
	{
        perror("SIOCGIFCONF ioctl");
        return ;
    }

	rt->port_num= ifc.ifc_len / sizeof(struct ifreq); /* 接口数量 */
    printf("port_num=%d\n\n", rt->port_num);

	char buff[20]="";
	int ip;
	int if_len = rt->port_num;

	while(if_len-- > 0) /* 遍历每个接口 */
	{
        sprintf(rt->eth_port[if_len].name, "%s", buf[if_len].ifr_name); /* 接口名称 */

		/* 获得接口标志 */
        if(!(ioctl(rt->raw_fd, SIOCGIFFLAGS, (char *) &buf[if_len])))
		{
            /* 接口状态 */
            if(buf[if_len].ifr_flags & IFF_UP)
			{
				rt->eth_port[if_len].status = UP;
            }
            else
			{
				rt->eth_port[if_len].status = DOWN;
            }
        }
		else
		{
            char str[256];
            sprintf(str, "SIOCGIFFLAGS ioctl %s", buf[if_len].ifr_name);
            perror(str);
        }

        /* IP地址 */
        if(!(ioctl(rt->raw_fd, SIOCGIFADDR, (char *)&buf[if_len])))
		{
			bzero(buff,sizeof(buff));
			sprintf(buff, "%s", (char*)inet_ntoa(((struct sockaddr_in*)(&buf[if_len].ifr_addr))->sin_addr));
			inet_pton(AF_INET, buff, &ip);
			memcpy(rt->eth_port[if_len].ip, &ip, 4);
		}
		else
		{
            char str[256];
            sprintf(str, "SIOCGIFADDR ioctl %s", buf[if_len].ifr_name);
            perror(str);
        }

        /* 子网掩码 */
        if(!(ioctl(rt->raw_fd, SIOCGIFNETMASK, (char *)&buf[if_len])))
		{
			bzero(buff,sizeof(buff));
			sprintf(buff, "%s", (char*)inet_ntoa(((struct sockaddr_in*)(&buf[if_len].ifr_addr))->sin_addr));
			inet_pton(AF_INET, buff, &ip);
			memcpy(rt->eth_port[if_len].netmask, &ip, 4);
        }
		else
		{
            char str[256];
            sprintf(str, "SIOCGIFADDR ioctl %s", buf[if_len].ifr_name);
            perror(str);
        }

        /* 广播地址 */
        if(!(ioctl(rt->raw_fd, SIOCGIFBRDADDR, (char *)&buf[if_len])))
		{
            //printf("bc_ip:%s\n",(char*)inet_ntoa(((struct sockaddr_in*)(&buf[if_len].ifr_addr))->sin_addr));
			bzero(buff,sizeof(buff));
			sprintf(buff, "%s", (char*)inet_ntoa(((struct sockaddr_in*)(&buf[if_len].ifr_addr))->sin_addr));
			inet_pton(AF_INET, buff, &ip);
			memcpy(rt->eth_port[if_len].bc_ip, &ip, 4);
        }
		else
		{
            char str[256];
            sprintf(str, "SIOCGIFADDR ioctl %s", buf[if_len].ifr_name);
            perror(str);
        }

        /*MAC地址 */
		if(!(ioctl(rt->raw_fd, SIOCGIFHWADDR, (char *) &buf[if_len])))
		{
			memcpy(rt->eth_port[if_len].mac, (unsigned char *)buf[if_len].ifr_hwaddr.sa_data, 6);
		}
		else
		{
            char str[256];
            sprintf(str, "SIOCGIFHWADDR ioctl %s", buf[if_len].ifr_name);
            perror(str);
        }
    }//–while end
}

/*****************************************************************************
 函 数 名  : show_port_info()
 功能描述  : 打印网络接口信息
 输入参数  : rt            TYPE_Route 类型指针
 			 port_name     网络接口名称，当为NULL时，打印所有接口信息
 返 回 值  : NULL
 修改日期  : 2015年9月10日
*****************************************************************************/
void show_port_info(TYPE_Route *rt, char *port_name)
{
	int i = 0;

	if(port_name != NULL)
	{
		for(i=0;i<rt->port_num;i++)
		{
			if(strcmp(port_name, rt->eth_port[i].name) == 0)
			{
				printf("___________%s___________\n", rt->eth_port[i].name);

				if(rt->eth_port[i].status == UP) printf("UP\n");
				else printf("DOWN\n");

				//ip
				printf("     ip: %d.%d.%d.%d\n",\
					   rt->eth_port[i].ip[0],rt->eth_port[i].ip[1],\
					   rt->eth_port[i].ip[2],rt->eth_port[i].ip[3]);
				//mac
				printf("    mac: %02x:%02x:%02x:%02x:%02x:%02x\n",\
					   rt->eth_port[i].mac[0],rt->eth_port[i].mac[1],\
					   rt->eth_port[i].mac[2],rt->eth_port[i].mac[3],\
					   rt->eth_port[i].mac[4],rt->eth_port[i].mac[5]);

				//netmask
				printf("netmask: %d.%d.%d.%d\n",\
					   rt->eth_port[i].netmask[0],rt->eth_port[i].netmask[1],\
					   rt->eth_port[i].netmask[2],rt->eth_port[i].netmask[3]);

				//broadcast ip
				printf("  bc_ip: %d.%d.%d.%d\n",\
					   rt->eth_port[i].bc_ip[0],rt->eth_port[i].bc_ip[1],\
					   rt->eth_port[i].bc_ip[2],rt->eth_port[i].bc_ip[3]);
				printf("__________________________\n");
			}
		}
	}
	else
	{
		for(i=0;i<rt->port_num;i++)
		{
			printf("___________%s___________\n", rt->eth_port[i].name);

			if(rt->eth_port[i].status == UP) printf("UP\n");
			else printf("DOWN\n");

			//ip
			printf("     ip: %d.%d.%d.%d\n",\
				   rt->eth_port[i].ip[0],rt->eth_port[i].ip[1],\
				   rt->eth_port[i].ip[2],rt->eth_port[i].ip[3]);
			//mac
			printf("    mac: %02x:%02x:%02x:%02x:%02x:%02x\n",\
				   rt->eth_port[i].mac[0],rt->eth_port[i].mac[1],\
				   rt->eth_port[i].mac[2],rt->eth_port[i].mac[3],\
				   rt->eth_port[i].mac[4],rt->eth_port[i].mac[5]);

			//netmask
			printf("netmask: %d.%d.%d.%d\n",\
				   rt->eth_port[i].netmask[0],rt->eth_port[i].netmask[1],\
				   rt->eth_port[i].netmask[2],rt->eth_port[i].netmask[3]);

			//broadcast ip
			printf("  bc_ip: %d.%d.%d.%d\n",\
				   rt->eth_port[i].bc_ip[0],rt->eth_port[i].bc_ip[1],\
				   rt->eth_port[i].bc_ip[2],rt->eth_port[i].bc_ip[3]);

			printf("__________________________\n");
		}
	}
}

/*****************************************************************************
 函 数 名  : build_arp_table()
 功能描述  : 建立ARP表
 输入参数  : 无
 返 回 值  : void
 修改日期  : 2015年9月10日
*****************************************************************************/
void build_arp_table(TYPE_Route *rt)
{
	int i = 0, port_num = 0;
	uchar recv[2024] = "";
	uchar arp[256] = {
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
		0, 0, 0, 0,                   //目的ip
	};

	if(rt->arp_head != NULL){
		free_arp_table(rt->arp_head);
		rt->arp_head = NULL;
	}

	while(port_num < rt->port_num)
	{
		memcpy(arp+6, rt->eth_port[port_num].mac, 6);
		memcpy(arp+22,rt->eth_port[port_num].mac, 6);
		memcpy(arp+28,rt->eth_port[port_num].ip,  4);
		memcpy(arp+38,rt->eth_port[port_num].ip,  4);

		strncpy(rt->ethreq.ifr_name,rt->eth_port[port_num].name, IFNAMSIZ);
		ioctl(rt->raw_fd, SIOCGIFINDEX, (char *)&rt->ethreq);
		bzero(&rt->sll, sizeof(rt->sll));
		rt->sll.sll_ifindex = rt->ethreq.ifr_ifindex;

		for(i=0;i<255;i++)
		{
			arp[41] = i;

			//发送ARP请求
			sendto(rt->raw_fd, arp, 42, 0, (struct sockaddr *)&rt->sll, sizeof(rt->sll));

			//接收对方的ARP应答
			recvfrom(rt->raw_fd, recv, sizeof(recv), 0, NULL, NULL);

			if(recv[21] == 2) //接收到ARP应答数据包
			{
				ARP_Table node;

				memcpy(node.ip,  recv + 28, 4); //提取ip
				memcpy(node.mac, recv + 22, 6); //提取mac

				rt->arp_head = (ARP_Table *)insert_arp_table(rt->arp_head, node);
			}
		}

		port_num++;
	}

	//print_arp_table(rt->arp_head);
}

Boolean broadcast(TYPE_Route *rt, const uchar ip[])
{
	int i = 0, port_num = 0;
	uchar recv[2024] = "";
	uchar arp[256] = {
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
		0, 0, 0, 0,                   //目的ip
	};

	while(port_num < rt->port_num)
	{
		memcpy(arp+6, rt->eth_port[port_num].mac, 6);
		memcpy(arp+22,rt->eth_port[port_num].mac, 6);
		memcpy(arp+28,rt->eth_port[port_num].ip,  4);
		memcpy(arp+38,ip,  4);

		strncpy(rt->ethreq.ifr_name,rt->eth_port[port_num].name, IFNAMSIZ);
		ioctl(rt->raw_fd, SIOCGIFINDEX, (char *)&rt->ethreq);
		bzero(&rt->sll, sizeof(rt->sll));
		rt->sll.sll_ifindex = rt->ethreq.ifr_ifindex;

		for(i=0;i<5;i++) //广播五次
		{
			//发送ARP请求
			sendto(rt->raw_fd, arp, 42, 0, (struct sockaddr *)&rt->sll, sizeof(rt->sll));

			//接收对方的ARP应答
			recvfrom(rt->raw_fd, recv, sizeof(recv), 0, NULL, NULL);

			if(recv[21] == 2) //接收到ARP应答数据包
			{
				if(iptoun_btol(recv + 28) == iptoun_btol(ip))
				{
					ARP_Table node;

					memcpy(node.ip,  recv + 28, 4); //提取ip
					memcpy(node.mac, recv + 22, 6); //提取mac

					rt->arp_head = (ARP_Table *)insert_arp_table(rt->arp_head, node);
					return TRUE;
				}
			}
		}

		port_num++;
	}

	return FALSE;
}
