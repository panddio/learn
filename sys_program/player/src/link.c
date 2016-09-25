/* ************************************************************************
 *       Filename:  link.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月01日 星期六 10時18分27秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "common.h"


LRC *insert_link(LRC *head, LRC slrc)
{
	LRC *pi = NULL;
	pi = (LRC *)malloc(sizeof(LRC));
	
	//bzero(pi, 0, sizeof(LRC));
	
	if(pi != NULL) //�ɹ����뵽�ռ�
	{
		*pi = slrc;

		pi->prev = NULL;
		pi->next = NULL;

		if(head == NULL)
		{
			head = pi;
		}
		else //������Ϊ��
		{
			LRC *pb = NULL, *pf =NULL;
			pb = pf = head;

			//��num��С�����������
			while((pi->time > pb->time) && (pb->next != NULL))
			{
				pf = pb;
				pb = pb->next;
			}
			
			if(pi->time <= pb->time)//����ͷ�����½ڵ�
			{
				if(pb == head)
				{
					pi->next = pb;
					pb->prev = pi;
					head = pi;
				}
				else //�м�����½ڵ�
				{
					pb->prev = pi;
					pi->prev = pf;
					
					pi->next = pb;
					pf->next = pi;
				}
			}
			else //β�������½ڵ�
			{
				pb->next = pi;
				pi->prev = pb;
			}
		}
	}
	else
	{
		printf("Can not apply for a LRC memeory space!\n");
	}

	return head;
}
/**************************************************
 *函数：free_link
 *功能：将整个链表所占的内存空间释放
 *************************************************/
LRC *free_link(LRC *pnode)
{
	if(pnode == NULL)
	{
		printf("Link is not exist!\n");
	}
	else
	{
		LRC *pb = pnode;

		//循环删除链表每个节点的方法：
		//1.判断 pnode 是否为空
		//2.让 pb 指向和 pnode 相同的节点
		//3.然后 让 pnode 指向下个节点
		//4.再把 pb 指向的节点释放掉
		//5.返回步骤 1
		while(pnode != NULL)
		{
			pb = pnode;
			pnode = pb->next;
			free(pb);
		}
	}

	return pnode;
}

/**************************************************
 *函数：print_link
 *功能：遍历链表中每个节点，并打印节点的内容
 *************************************************/
void print_link(LRC *pnode)
{

	if(pnode == NULL)
	{
		printf("Link is not exist!\n"); 
	}
	else
	{
		LRC *pb = pnode;
		
		while(pb != NULL)
		{
			//printf("%.2f  %s\n",pb->time,pb->psrc);
			printf("%d  %s\n",pb->time,pb->src);
			pb = pb->next;
		}
	}
}
/**************************************************
 *函数：search_link
 *功能：查询链表中指定的节点，找到返回节点地址，否则返回NULL
 *************************************************/
LRC *search_link(LRC *pnode, int time)
{
	if(pnode->next == NULL)
	{
		if(pnode->time == time) return pnode;
		else return NULL;
	}
	else
	{
		LRC *pb = pnode;
		LRC *pf = pnode->next;
		
		while((time > pb->time) && (time > pf->time) && (pf != NULL))
		{
			pb = pf;
			pf = pf->next;
		}
			
		if((time >= pb->time) && (pf != NULL)) //找到
		{
			return pb;
		}					
	}
	return NULL; //没找到返回NULL指针
}

