/* ************************************************************************
 *       Filename:  link.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月29日 星期三 04時18分53秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  王秋伟
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"


/**************************************************
 *函数：insert_link
 *功能：给链表添加新节点，当链表为空时创建链表
 *************************************************/
#if 0
//从链表头插入节点
STU *insert_link(STU *head, STU stu) 
{
	STU *pi = NULL;
	pi = (STU *)malloc(sizeof(STU));

	if(pi != NULL) //成功申请到空间
	{
		*pi = stu;
		pi->next = NULL;


		if(head != NULL)
		{
			pi->next = head;
		}
		head = pi;
	}
	else
	{
		printf("Can not apply for a STU memeory space!\n");
	}

	return head;
}
#elif 1
//从链表尾部插入节点
STU *insert_link(STU *head, STU stu) 
{
	STU *pi = NULL;
	pi = (STU *)malloc(sizeof(STU));

	if(pi != NULL) //成功申请到空间
	{
		*pi = stu;
		pi->next = NULL;

		if(head == NULL)
		{
			head = pi;
		}
		else //链表不为空
		{
			STU *pb = head;

			while(pb->next != NULL)
				pb = pb->next;
			
			pb->next = pi;
		}
	}
	else
	{
		printf("Can not apply for a STU memeory space!\n");
	}

	return head;
}
#elif 0
//按某种顺序插入链表节点
STU *insert_link(STU *head, STU stu)
{
	STU *pi = NULL;
	pi = (STU *)malloc(sizeof(STU));

	if(pi != NULL) //成功申请到空间
	{
		*pi = stu;
		pi->next = NULL;

		if(head == NULL)
		{
			head = pi;
		}
		else //链表不为空
		{
			STU *pb = NULL, *pf =NULL;
			pb = pf = head;

			//按num从小到大插入链表
			while((pi->num > pb->num) && (pb->next != NULL))
			{
				pf = pb;
				pb = pb->next;
			}
			
			if(pi->num <= pb->num)//链表头插入新节点
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
		printf("Can not apply for a STU memeory space!\n");
	}

	return head;
}
#endif

/**************************************************
 *函数：delete_link
 *功能：删除链表中指定的节点
 *************************************************/
STU *delete_link(STU *head, int num)
{
	if(head == NULL)
	{
		printf("Link is not exist!\n");
	}
	else
	{
		STU *pb = NULL, *pf = NULL;
		pb = pf =head;

		while((pb->num != num) && (pb->next != NULL))
		{
			pf = pb;
			pb = pb->next;
		}

		if(pb->num == num)
		{
			if(pb == head) //删除的节点是链表头部
			{
				head = pb->next;
			}
			else if(pb->next == NULL) //删除的节点在链表尾部
			{
				pf->next = NULL;
			}
			else//删除的节点在中间
			{
				pf->next = pb->next;
			}
			free(pb);
		}
	}

	return head;
}
/**************************************************
 *函数：delete_head
 *功能：删除链表的头节点
 *************************************************/
STU *delete_head(STU *head)
{
	if(head == NULL)
	{
		printf("Link is empty!\n");
	}
	else
	{
		STU *pb = NULL;
		pb = head;

		head = pb->next; //删除链表头部
		free(pb);
	}

	return head;
}
/**************************************************
 *函数：search_link
 *功能：查询链表中指定的节点，找到返回节点地址，否则返回NULL
 *************************************************/
STU *search_link(STU *head,char *name)
{
	if(head == NULL)
	{
		printf("Link is not exist!\n");
	}
	else
	{
		STU *pb = head;

		while((strcmp(pb->name,name) !=0) && (pb->next != NULL))
			pb = pb->next;

		if(strcmp(pb->name,name) == 0) //找到
		{
			return pb;
		}
	}
	return NULL; //没找到返回NULL指针
}
/**************************************************
 *函数：print_link
 *功能：遍历链表中每个节点，并打印节点的内容
 *************************************************/
void print_link(STU *head)
{

	if(head == NULL)
	{
		printf("Link is not exist!\n"); 
	}
	else
	{
		STU *pb = head;
		
		while(pb != NULL)
		{
			printf("num: %-4d name: %-8s score: %-3d\n",pb->num,pb->name,pb->score);
			pb = pb->next;
		}
	}
}
/**************************************************
 *函数：free_link
 *功能：将整个链表所占的内存空间释放
 *************************************************/
STU *free_link(STU *head)
{
	if(head == NULL)
	{
		printf("Link is not exist!\n");
	}
	else
	{
		STU *pb = head;

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
 *函数：sort_link
 *功能：采用"选择法"将链表按 scort 从大到小排序
 *************************************************/
STU *sort_link(STU *head)
{
	if(head != NULL)
	{
		STU *i, *j, *k, buf;

		for(i=head;i->next != NULL; i=i->next)
		{
			k = i;

			for(j=i->next;j != NULL;j=j->next)
			{
				if(k->score < j->score)
				{
					k = j;	
				}
			}
			
			if(k != i) //不相等，进行交换 i 和 k
			{
				buf = *i;
				buf.next = k->next;
				k->next  = i->next;
				*i = *k;
				*k = buf;
			}
		}
	}
	
	return head;
}
/**************************************************
 *函数：invert_link
 *功能：倒置整个链表
 **************************************************/
STU *invert_link(STU *head)
{
	if(head == NULL)
	{
		printf("Link is not exist!\n");
		return NULL;
	}
	if( head->next != NULL) //不等与NULL，说明链表节点大于或等于二
	{
		STU *pb = NULL, *pf = NULL, *pn = NULL;

#if 0
		pf = head; //指向链表头
		pb = pn = head->next; //指向链表第二个元素

		while(pn != NULL)
		{
			pn = pn->next;
			pb->next = pf;
			pf = pb;
			pb = pn;
		}
		head->next = NULL;
		head = pf; //
#else
		pb = pf = head;
		pn = head->next;
		printf("akkk\n");
		while(pn != NULL)
		{
			pb = pn;
			pn = pn->next;
			pb->next = pf;
			pf = pb;
		}
		
		head->next = NULL;
		head = pb;
#endif
	}

	return head;
}
