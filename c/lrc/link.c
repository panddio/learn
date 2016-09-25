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

	if(pi != NULL) //成功申请到空间
	{
		*pi = slrc;
		pi->next = NULL;

		if(head == NULL)
		{
			head = pi;
		}
		else //链表不为空
		{
			LRC *pb = NULL, *pf =NULL;
			pb = pf = head;

			//按num从小到大插入链表
			while((pi->time > pb->time) && (pb->next != NULL))
			{
				pf = pb;
				pb = pb->next;
			}

			if(pi->time <= pb->time)//链表头插入新节点
			{
				if(pb == head)
				{
					pi->next = pb;
					pb->prev = pi;
					head = pi;
				}
				else //中间插入新节点
				{
					pb->prev = pi;
					pi->prev = pf;

					pi->next = pb;
					pf->next = pi;
				}
			}
			else //尾部插入新节点
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
LRC *free_link(LRC *head)
{
	if(head == NULL)
	{
		printf("Link is not exist!\n");
	}
	else
	{
		LRC *pb = head;

		//循环删除链表每个节点的方法：
		//1.判断 head 是否为空
		//2.让 pb 指向和 head 相同的节点
		//3.然后 让 head 指向下个节点
		//4.再把 pb 指向的节点释放掉
		//5.返回步骤 1
		while(head != NULL)
		{
			pb = head;
			head = pb->next;
			free(pb);
		}
	}

	return head;
}

/**************************************************
 *函数：print_link
 *功能：遍历链表中每个节点，并打印节点的内容
 *************************************************/
void print_link(LRC *head)
{

	if(head == NULL)
	{
		printf("Link is not exist!\n");
	}
	else
	{
		LRC *pb = head;

		while(pb != NULL)
		{
			//printf("%.2f  %s\n",pb->time,pb->psrc);
			printf("%d  %s\n",pb->time,pb->psrc);
			pb = pb->next;
		}
	}
}
