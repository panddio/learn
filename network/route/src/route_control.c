/******************************************************************************
  �� �� ��   : route_control.c
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��15��
  ����޸�   :
  ��������   : ���ݷ���
  �����б�   :
              broadcast
              build_arp_table
              get_ethernet_port
              route_init
              show_port_info
  �޸���ʷ   :
  1.��    ��   : 2015��9��15��
    ��    ��   : if
    �޸�����   : �����ļ�

******************************************************************************/
#include "common.h"
#include "arp_link.h"
#include "firewall_file.h"
#include "route_control.h"

/*****************************************************************************
 �� �� ��  : route_init()
 ��������  : ��ʼ��
 �������  : ��
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��10��
*****************************************************************************/
void route_init(TYPE_Route *rt)
{
	//����ԭʼ�׽���
	rt->raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	//���������׽���
	rt->sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//�÷������󶨶˿ں�ip
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
	//listen �������Ӷ���
	listen(rt->sockfd, 5);

	rt->fire_status = UP; // ��ʼ������ǽ��״̬: ����

	//��ʼ������ͷָ��
	rt->arp_head  = NULL;
	rt->mac_head  = NULL;
	rt->ip_head   = NULL;
	rt->port_head = NULL;
	rt->pro_head  = NULL;

	pthread_mutex_init(&rt->mutex, NULL); // ��ʼ��������
	get_ethernet_port(rt);   // ��ȡ�����ӿ���Ϣ
	build_arp_table(rt);     // ����ARP��
	firewall_config(rt);     // ��ȡ�����ļ������÷���ǽ
	firewall_get_passwd(rt); // ��ȡ�������ļ��ķ���ǽ����
}

#if 0
/*****************************************************************************
 �� �� ��  : show_help()
 ��������  : ���������ʾ
 �������  : ��
 �� �� ֵ  : void
 �޸�����  : 2015��9��10��
*****************************************************************************/
void show_help(void)
{
	printf("***************************************************\n");
	printf("-      help: �鿴������Ϣ                         *\n");
	printf("-       arp: �鿴 ARP ��                          *\n");
	printf("-  ifconfig: �鿴������Ϣ                         *\n");
	printf("-   fire on: ��������ǽ                           *\n");
	printf("-  fire off: �رշ���ǽ                           *\n");
	printf("-    lsfire: �鿴����ǽ����                       *\n");
	printf("-   setfire: ���÷���ǽ����                       *\n");
	printf("***************************************************\n");
}
#endif

/*****************************************************************************
 �� �� ��  : get_ethernet_port()
 ��������  : ��ȡ����ӿ���Ϣ
 �������  : ��
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��10��
*****************************************************************************/
void get_ethernet_port(TYPE_Route *rt)
{
	struct ifreq buf[MAX_PORT];    /* ifreq�ṹ���� */
	struct ifconf ifc;             /* ifconf�ṹ */

	 /* ��ʼ��ifconf�ṹ */
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = (caddr_t) buf;

	/* ��ýӿ��б� */
    if (ioctl(rt->raw_fd, SIOCGIFCONF, (char *)&ifc) == -1)
	{
        perror("SIOCGIFCONF ioctl");
        return ;
    }

	rt->port_num= ifc.ifc_len / sizeof(struct ifreq); /* �ӿ����� */
    printf("port_num=%d\n\n", rt->port_num);

	char buff[20]="";
	int ip;
	int if_len = rt->port_num;

	while(if_len-- > 0) /* ����ÿ���ӿ� */
	{
        sprintf(rt->eth_port[if_len].name, "%s", buf[if_len].ifr_name); /* �ӿ����� */

		/* ��ýӿڱ�־ */
        if(!(ioctl(rt->raw_fd, SIOCGIFFLAGS, (char *) &buf[if_len])))
		{
            /* �ӿ�״̬ */
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

        /* IP��ַ */
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

        /* �������� */
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

        /* �㲥��ַ */
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

        /*MAC��ַ */
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
    }//�Cwhile end
}

/*****************************************************************************
 �� �� ��  : show_port_info()
 ��������  : ��ӡ����ӿ���Ϣ
 �������  : rt            TYPE_Route ����ָ��
 			 port_name     ����ӿ����ƣ���ΪNULLʱ����ӡ���нӿ���Ϣ
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��10��
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
 �� �� ��  : build_arp_table()
 ��������  : ����ARP��
 �������  : ��
 �� �� ֵ  : void
 �޸�����  : 2015��9��10��
*****************************************************************************/
void build_arp_table(TYPE_Route *rt)
{
	int i = 0, port_num = 0;
	uchar recv[2024] = "";
	uchar arp[256] = {
		//-----��mac----14----
		0xff,0xff,0xff,0xff,0xff,0xff,//dst_mac: ff:ff:ff:ff:ff:ff
		0x00,0x00,0x00,0x00,0x00,0x00,//src_mac:
		0x08,0x06,                    //����: 0x0806 ARPЭ��

		//-----��ARP----28----
		0x00,0x01,0x08,0x00,          //Ӳ������1(��̫����ַ)��Э������:0x800(IP)
		0x06,0x04,0x00,0x01,          //Ӳ����Э��ĵ�ַ���ȷֱ�Ϊ6��4��ARP����
		0x00,0x00,0x00,0x00,0x00,0x00,//���Ͷ˵�mac
		0, 0, 0, 0,                   //���Ͷ˵�ip
		0x00,0x00,0x00,0x00,0x00,0x00,//Ŀ��mac(��ȡ�Է���mac������Ϊ0)
		0, 0, 0, 0,                   //Ŀ��ip
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

			//����ARP����
			sendto(rt->raw_fd, arp, 42, 0, (struct sockaddr *)&rt->sll, sizeof(rt->sll));

			//���նԷ���ARPӦ��
			recvfrom(rt->raw_fd, recv, sizeof(recv), 0, NULL, NULL);

			if(recv[21] == 2) //���յ�ARPӦ�����ݰ�
			{
				ARP_Table node;

				memcpy(node.ip,  recv + 28, 4); //��ȡip
				memcpy(node.mac, recv + 22, 6); //��ȡmac

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
		//-----��mac----14----
		0xff,0xff,0xff,0xff,0xff,0xff,//dst_mac: ff:ff:ff:ff:ff:ff
		0x00,0x00,0x00,0x00,0x00,0x00,//src_mac:
		0x08,0x06,                    //����: 0x0806 ARPЭ��

		//-----��ARP----28----
		0x00,0x01,0x08,0x00,          //Ӳ������1(��̫����ַ)��Э������:0x800(IP)
		0x06,0x04,0x00,0x01,          //Ӳ����Э��ĵ�ַ���ȷֱ�Ϊ6��4��ARP����
		0x00,0x00,0x00,0x00,0x00,0x00,//���Ͷ˵�mac
		0, 0, 0, 0,                   //���Ͷ˵�ip
		0x00,0x00,0x00,0x00,0x00,0x00,//Ŀ��mac(��ȡ�Է���mac������Ϊ0)
		0, 0, 0, 0,                   //Ŀ��ip
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

		for(i=0;i<5;i++) //�㲥���
		{
			//����ARP����
			sendto(rt->raw_fd, arp, 42, 0, (struct sockaddr *)&rt->sll, sizeof(rt->sll));

			//���նԷ���ARPӦ��
			recvfrom(rt->raw_fd, recv, sizeof(recv), 0, NULL, NULL);

			if(recv[21] == 2) //���յ�ARPӦ�����ݰ�
			{
				if(iptoun_btol(recv + 28) == iptoun_btol(ip))
				{
					ARP_Table node;

					memcpy(node.ip,  recv + 28, 4); //��ȡip
					memcpy(node.mac, recv + 22, 6); //��ȡmac

					rt->arp_head = (ARP_Table *)insert_arp_table(rt->arp_head, node);
					return TRUE;
				}
			}
		}

		port_num++;
	}

	return FALSE;
}
