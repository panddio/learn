/******************************************************************************
  �� �� ��   : arp_link.c
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��15��
  ����޸�   :
  ��������   : �����������ҡ���ӡ���ͷŵ�
  �����б�   :
              iptoun_btob
              iptoun_btol
              insert_arp_table
              search_arp_table
              delete_arp_node
              free_arp_table
              change_arp_mac
              print_arp_table            
  �޸���ʷ   :
  1.��    ��   : 2015��9��10��
    ��    ��   : if
    �޸�����   : �����ļ�

******************************************************************************/
#include "common.h"



/*****************************************************************************
 �� �� ��  : iptoun_btol()
 ��������  : ������ip[]��ip��ַ(���)ת��Ϊ32�޷�������(С��)���൱ntohl()����
 �������  : ip[]
 �� �� ֵ  : ����32�޷���������ip��ַ(С��)
 �޸�����  : 2015��9��10��
*****************************************************************************/
uint iptoun_btol(const uchar *ip)
{
	uint ip_val = 0;

	ip_val = ip[0]<<24 | ip[1]<<16 | ip[2]<<8 | ip[3];

	return ip_val;
}

/*****************************************************************************
 �� �� ��  : iptoun_btob()
 ��������  : ������ip[]��ip��ַ(���)ת��Ϊ32�޷�������(���)
 �������  : ip[]
 �� �� ֵ  : ����32�޷���������ip��ַ(���)
 �޸�����  : 2015��9��10��
*****************************************************************************/
uint iptoun_btob(const uchar *ip)
{
	uint ip_val = 0;

	ip_val = ip[3]<<24 | ip[2]<<16 | ip[1]<<8 | ip[0];
	//ip_val = *(uint *)ip;

	return ip_val;
}

/*****************************************************************************
 �� �� ��  : insert_arp_table()
 ��������  : ����ARP��
 �������  : head   ����ͷ
             node   ������ڵ�
 �� �� ֵ  : ����ͷָ��
 �޸�����  : 2015��9��10��
*****************************************************************************/
ARP_Table *insert_arp_table(ARP_Table *head, ARP_Table node)
{
	ARP_Table *pi = NULL;
	pi = (ARP_Table *)malloc(sizeof(ARP_Table));
	
	//bzero(pi, 0, sizeof(ARP_Table));
	
	if(pi != NULL) //�ɹ����뵽�ռ�
	{
		*pi = node;
		pi->next = NULL;
		
		int ip_val = iptoun_btol(node.ip);

		if(head == NULL)
		{
			head = pi;
		}
		else //����Ϊ��
		{
			ARP_Table *pb = NULL, *pf =NULL;
			pb = pf = head;

			//����С�����������
			while((ip_val > iptoun_btol(pb->ip)) && (pb->next != NULL))
			{
				pf = pb;
				pb = pb->next;
			}
			
			if(ip_val <= iptoun_btol(pb->ip))//����ͷ�����½ڵ�
			{
				if(pb == head)
				{
					pi->next = pb;
					head = pi;
				}
				else //�м�����½ڵ�
				{
					pi->next = pb;
					pf->next = pi;
				}
			}
			else //β�������½ڵ�
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
 �� �� ��  : search_arp_table()
 ��������  : ����ARP��
 �������  : head   ����ͷ
             ip     ��������ҵ�ip
 �� �� ֵ  : ����ͷָ��
 �޸�����  : 2015��9��10��
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

		if(ip_val == iptoun_btol(pb->ip)) //��ARP���ҵ�ƥ���ip
		{
			return pb;
		}
	}
	return NULL; //û�ҵ�ƥ���ip����NULL
}

/*****************************************************************************
 �� �� ��  : delete_arp_node()
 ��������  : ����ARP��,��ɾ�������е�ָ���ڵ�
 �������  : head   ����ͷ
             ip     ��������ҵ�ip
 �� �� ֵ  : ����ͷָ��
 �޸�����  : 2015��9��10��
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
			if(pb == head) //ɾ���Ľڵ�������ͷ
				head = pb->next; 
			
			else if(pb->next == NULL) //ɾ���Ľڵ��ڱ�β
				pf->next = NULL;
			
			else //ɾ���Ľڵ����м�
				pf->next = pb->next;
			
			free(pb);
		}
	}

	return head;
}

/*****************************************************************************
 �� �� ��  : free_arp_table()
 ��������  : �ͷ�����ARP��
 �������  : head   ����ͷ
 �� �� ֵ  : ����ͷָ��
 �޸�����  : 2015��9��10��
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

		//�ͷ���������ķ���:
		//1���ж�head�Ƿ�Ϊ��
		//2����pbָ���head��ͬ�Ľڵ�
		//3��Ȼ��headָ����һ���ڵ�
		//4�����ͷ�pbָ��Ľڵ�
		//5�����ز���1
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
 �� �� ��  : change_arp_mac()
 ��������  : ��������ARP���޸�ip��Ӧ��mac
 �������  : head   ����ͷ
 			 ip     Ҫ�޸�mac��Ӧ��ip
 			 mac    �µ�mac
 �� �� ֵ  : Boolean ����ֵ���ɹ�����:TRUE
 �޸�����  : 2015��9��12��
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
 �� �� ��  : print_arp_table()
 ��������  : ��ӡ����ARP��
 �������  : head   ����ͷ
 �� �� ֵ  : ����ͷָ��
 �޸�����  : 2015��9��10��
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

