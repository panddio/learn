/******************************************************************************
  文 件 名   : arp_link.c
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月15日
  最近修改   :
  功能描述   : 链表创建、查找、打印、释放等
  函数列表   :
              iptoun_btob
              iptoun_btol
              insert_arp_table
              search_arp_table
              delete_arp_node
              free_arp_table
              change_arp_mac
              print_arp_table            
  修改历史   :
  1.日    期   : 2015年9月10日
    作    者   : if
    修改内容   : 创建文件

******************************************************************************/
#include "common.h"



/*****************************************************************************
 函 数 名  : iptoun_btol()
 功能描述  : 将存在ip[]的ip地址(大端)转化为32无符号整数(小端)，相当ntohl()函数
 输入参数  : ip[]
 返 回 值  : 返回32无符号整数的ip地址(小端)
 修改日期  : 2015年9月10日
*****************************************************************************/
uint iptoun_btol(const uchar *ip)
{
	uint ip_val = 0;

	ip_val = ip[0]<<24 | ip[1]<<16 | ip[2]<<8 | ip[3];

	return ip_val;
}

/*****************************************************************************
 函 数 名  : iptoun_btob()
 功能描述  : 将存在ip[]的ip地址(大端)转化为32无符号整数(大端)
 输入参数  : ip[]
 返 回 值  : 返回32无符号整数的ip地址(大端)
 修改日期  : 2015年9月10日
*****************************************************************************/
uint iptoun_btob(const uchar *ip)
{
	uint ip_val = 0;

	ip_val = ip[3]<<24 | ip[2]<<16 | ip[1]<<8 | ip[0];
	//ip_val = *(uint *)ip;

	return ip_val;
}

/*****************************************************************************
 函 数 名  : insert_arp_table()
 功能描述  : 建立ARP表
 输入参数  : head   链表头
             node   待插入节点
 返 回 值  : 链表头指针
 修改日期  : 2015年9月10日
*****************************************************************************/
ARP_Table *insert_arp_table(ARP_Table *head, ARP_Table node)
{
	ARP_Table *pi = NULL;
	pi = (ARP_Table *)malloc(sizeof(ARP_Table));
	
	//bzero(pi, 0, sizeof(ARP_Table));
	
	if(pi != NULL) //成功申请到空间
	{
		*pi = node;
		pi->next = NULL;
		
		int ip_val = iptoun_btol(node.ip);

		if(head == NULL)
		{
			head = pi;
		}
		else //链表不为空
		{
			ARP_Table *pb = NULL, *pf =NULL;
			pb = pf = head;

			//按从小到大插入链表
			while((ip_val > iptoun_btol(pb->ip)) && (pb->next != NULL))
			{
				pf = pb;
				pb = pb->next;
			}
			
			if(ip_val <= iptoun_btol(pb->ip))//链表头插入新节点
			{
				if(pb == head)
				{
					pi->next = pb;
					head = pi;
				}
				else //中间插入新节点
				{
					pi->next = pb;
					pf->next = pi;
				}
			}
			else //尾部插入新节点
			{
				pb->next = pi;
			}
		}
	}
	else
	{
		printf("Can not apply for a ARP_Table node memeory space!\n");
	}

	return head;
}

/*****************************************************************************
 函 数 名  : search_arp_table()
 功能描述  : 查找ARP表
 输入参数  : head   链表头
             ip     从链表查找的ip
 返 回 值  : 链表头指针
 修改日期  : 2015年9月10日
*****************************************************************************/
ARP_Table *search_arp_table(ARP_Table *head, const uchar *ip)
{
	if(head == NULL)
	{
		printf("Link is not exist!\n");
	}
	else
	{
		ARP_Table *pb = head;
		uint ip_val;
		
		ip_val = iptoun_btol(ip);
		
		while((ip_val != iptoun_btol(pb->ip)) && (pb->next != NULL))
			pb = pb->next;

		if(ip_val == iptoun_btol(pb->ip)) //在ARP表找到匹配的ip
		{
			return pb;
		}
	}
	return NULL; //没找到匹配的ip返回NULL
}

/*****************************************************************************
 函 数 名  : delete_arp_node()
 功能描述  : 查找ARP表,并删除链表中的指定节点
 输入参数  : head   链表头
             ip     从链表查找的ip
 返 回 值  : 链表头指针
 修改日期  : 2015年9月10日
*****************************************************************************/
ARP_Table *delete_arp_node(ARP_Table *head, const uchar *ip)
{
	if(head == NULL)
	{
		printf("Link is not exist!\n");
	}
	else
	{
		ARP_Table *pb = NULL, *pf = NULL;
		pb = pf =head;	
		uint ip_val = iptoun_btol(ip);
		
		while((ip_val != iptoun_btol(pb->ip)) && (pb->next != NULL))
		{
			pf = pb;
			pb = pb->next;
		}

		if(ip_val == iptoun_btol(pb->ip))
		{
			if(pb == head) //删除的节点再链表头
				head = pb->next; 
			
			else if(pb->next == NULL) //删除的节点在表尾
				pf->next = NULL;
			
			else //删除的节点再中间
				pf->next = pb->next;
			
			free(pb);
		}
	}

	return head;
}

/*****************************************************************************
 函 数 名  : free_arp_table()
 功能描述  : 释放整个ARP表
 输入参数  : head   链表头
 返 回 值  : 链表头指针
 修改日期  : 2015年9月10日
*****************************************************************************/
ARP_Table *free_arp_table(ARP_Table *head)
{
	if(head == NULL)
	{
		printf("Link is not exist!\n");
	}
	else
	{
		ARP_Table *pb = head;

		//释放整个链表的方法:
		//1、判断head是否为空
		//2、让pb指向和head相同的节点
		//3、然后head指向下一个节点
		//4、再释放pb指向的节点
		//5、返回步骤1
		while(head != NULL)
		{
			pb = head;
			head = pb->next;
			free(pb);
		}
	}

	return head;
}

/*****************************************************************************
 函 数 名  : change_arp_mac()
 功能描述  : 查找整个ARP表，修改ip对应的mac
 输入参数  : head   链表头
 			 ip     要修改mac对应的ip
 			 mac    新的mac
 返 回 值  : Boolean 类型值，成功返回:TRUE
 修改日期  : 2015年9月12日
*****************************************************************************/
Boolean change_arp_mac(ARP_Table *head, const uchar ip[], const uchar mac[])
{
	if(head == NULL){
		printf("Link is not exist!\n");
	}	
	else {

		ARP_Table *pnode = NULL;

		pnode = search_arp_table(head, ip);

		if(pnode != NULL){
			memcpy(pnode->mac, mac, 6);

			return TRUE;
		}
	}

	return FALSE;
}

/*****************************************************************************
 函 数 名  : print_arp_table()
 功能描述  : 打印整个ARP表
 输入参数  : head   链表头
 返 回 值  : 链表头指针
 修改日期  : 2015年9月10日
*****************************************************************************/
void print_arp_table(ARP_Table *head)
{

	if(head == NULL)
	{
		printf("Link is not exist!\n"); 
	}
	else
	{
		uchar ip[16] ="";
		uchar mac[18]="";
		ARP_Table *pb = head;

		printf("_____IP________________MAC_______\n");
		while(pb != NULL)
		{
			bzero(ip, 16);
			bzero(mac,18);

			sprintf(ip,"%d.%d.%d.%d",\
				    pb->ip[0],pb->ip[1],pb->ip[2],pb->ip[3]);
			
			sprintf(mac,"%02x:%02x:%02x:%02x:%02x:%02x",\
				    pb->mac[0],pb->mac[1],pb->mac[2],pb->mac[3],pb->mac[4],pb->mac[5]);

			printf("%-12s -- %s\n", ip,mac);
			
			pb = pb->next;
		}
		printf("_________________________________\n");
	}
}

