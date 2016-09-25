/******************************************************************************
  文 件 名   : firewall_link.c
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月15日
  最近修改   :
  功能描述   : 创建防火墙链表
  函数列表   :
              delete_firewall_node
              free_firewall_link
              insert_firewall_node
              print_firewall
  修改历史   :
  1.日    期   : 2015年9月15日
    作    者   : if
    修改内容   : 创建文件

******************************************************************************/
#include "common.h"


/*****************************************************************************
 函 数 名  : insert_firewall_node()
 功能描述  : 插入一条防火墙规则表
 输入参数  : head   链表头
             node   待插入节点
 返 回 值  : 链表头指针
 修改日期  : 2015年9月13日
*****************************************************************************/
FIRE_Wall *insert_firewall_node(FIRE_Wall *head, FIRE_Wall node)
{
	FIRE_Wall *pi = NULL;
	pi = (FIRE_Wall *)malloc(sizeof(FIRE_Wall));

	if(pi != NULL){ //成功申请到空间

		*pi = node;
		pi->next = NULL;

		if(head != NULL){

			FIRE_Wall *pb = NULL;
			pb = head;

			while((strcmp(pb->rule, pi->rule)) != 0 && (pb->next!= NULL))
				pb = pb->next;

			if(strcmp(pb->rule, pi->rule) != 0){
				pi->next = head;
			}
		}
		head = pi;
	}
	else{
		printf("Can not apply for a FIRE_Wall memeory space!\n");
	}

	return head;
}

/*****************************************************************************
 函 数 名  : delete_firewall_node()
 功能描述  : 查找ARP表,并删除链表中的指定节点
 输入参数  : head     链表头
             rule     从链表查找删除的规则
 返 回 值  : 链表头指针
 修改日期  : 2015年9月13日
*****************************************************************************/
FIRE_Wall *delete_firewall_node(FIRE_Wall *head, const char *rule)
{
	if(head == NULL) {
		printf("Link is not exist!\n");
	}
	else
	{
		FIRE_Wall *pb = NULL, *pf = NULL;
		pb = pf =head;

		while((strcmp(pb->rule, rule) !=0) && (pb->next != NULL))
		{
			pf = pb;
			pb = pb->next;
		}

		if(strcmp(pb->rule, rule) == 0)
		{
			if(pb == head) {//删除的节点是链表头部
				head = pb->next;
			}
			else if(pb->next == NULL) { //删除的节点在链表尾部
				pf->next = NULL;
			}
			else { //删除的节点在中间
				pf->next = pb->next;
			}

			free(pb);
		}
		else {
			printf("haved not set this firewall rule!\n");
		}
	}

	return head;
}

/*****************************************************************************
 函 数 名  : print_firewall()
 功能描述  : 打印整个防火墙规则表
 输入参数  : head   链表头
 返 回 值  : 链表头指针
 修改日期  : 2015年9月13日
*****************************************************************************/
void print_firewall(FIRE_Wall *head)
{

	if(head != NULL){

		FIRE_Wall *pb = head;

		while(pb != NULL)
		{
			printf("%s\n", pb->rule);
			pb = pb->next;
		}
	}
}

/*****************************************************************************
 函 数 名  : free_firewall_link()
 功能描述  : 释放整个防火墙规则表
 输入参数  : head   链表头
 返 回 值  : 链表头指针
 修改日期  : 2015年9月13日
*****************************************************************************/
FIRE_Wall *free_firewall_link(FIRE_Wall *head)
{
	if(head != NULL){
		FIRE_Wall *pb = head;

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

