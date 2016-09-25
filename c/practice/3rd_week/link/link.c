#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

#if 0
//尾部插入
STU *insert_link(STU *head, STU temp)
{
	//申请插入节点并赋值
	STU *pi = NULL;
	pi = (STU *)malloc(sizeof(STU));
	*pi = temp;
	pi->next = NULL;	
	
	//判断链表是否为空
	if(head == NULL)
	{
		head = pi;
	}
	else
	{
		//寻找链表的尾部
		STU *pb = head;
		while(pb->next != NULL)
			pb = pb->next;
		
		pb->next = pi; //在链表尾部添加pi节点
	}
	
	return head;
}
#elif 0
//头部之前插入
STU *insert_link(STU *head, STU temp)
{
	//申请插入节点并赋值
	STU *pi = NULL;
	pi = (STU *)malloc(sizeof(STU));
	*pi = temp;
	pi->next = NULL;
	
	//判断链表是否为空
	if(head == NULL)
	{
		head = pi;
	}
	else
	{
		pi->next = head;
		head = pi;
	}
	
	return head;
}
#elif 1
//有序插入链表节点
STU *insert_link(STU *head, STU temp)
{
	//申请插入节点并赋值
	STU *pi = NULL;
	pi = (STU *)malloc(sizeof(STU));
	*pi = temp;
	pi->next = NULL;
	
	if(head == NULL)
	{
		head = pi;
	}
	else
	{
		STU *pb = NULL,*pf = NULL;
		
		pb = pf = head;
		//寻找插入点(以num从小到大插入)
		while((pb->num < pi->num) && (pb->next != NULL))
		{
			pf = pb;
			pb = pb->next;
		}
		
		//找到插入点
		if(pb->num >= pi->num)
		{
			//判断是否在；链表头插入
			if(pb == head) //头部插入
			{
				pi->next = head;
				head = pi;
			}
			else //中部插入
			{
				pf->next = pi;
				pi->next = pb;
			}
		}
		else //尾部插入
		{
			pb->next = pi;
		}
	}
	
	return head;
}
#endif
void print_link(STU *head)
{
	//1.判断链表是否存在
	
	if(head == NULL)
	{
		printf("The link not exist!\n");
	}
	else
	{
		STU *pb = head;
		
		while(pb != NULL)
		{
			printf("%d %s %d\n",pb->num,pb->name,pb->score);
			pb = pb->next; // 指向链表下个节点
		}
		
	}
	return;
}

STU *search_link(STU *head, char *name)
{
	
	if(head == NULL)
	{
		return NULL;
	}
	else
	{
		STU *pb = head;
		
		while((strcmp(pb->name,name) != 0) && (pb->next != NULL))
			pb = pb->next;
		
		if(strcmp(pb->name,name) == 0)
		{
			return pb;
		}
	}
	return NULL;	
}

STU *delete_link(STU *head, int num)
{

	if(head != NULL)//链表不为空
	{
		STU *pb = NULL, *pf = NULL;
		pb = pf = head;
		
		while((pb->num != num) && (pb->next !=NULL))
		{
			pf = pb;
			pb = pb->next;
		}
		
		if(pb->num == num) //找到要删除的num
		{
			if(pb == head) //删除链表头
			{
				head = pb->next;
			}
			else if(pb->next == NULL)//删除最后一个
			{
				pf->next = NULL;
			}
			else //删除中间位置
			{
				pf->next = pb->next;
			}
			free(pb);
		}
	}
	
	return head;
}
STU *free_link(STU *head) 
{
	if(head == NULL)
	{
		printf("Link not exist!\n");
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
