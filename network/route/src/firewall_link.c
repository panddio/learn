/******************************************************************************
  �� �� ��   : firewall_link.c
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��15��
  ����޸�   :
  ��������   : ��������ǽ����
  �����б�   :
              delete_firewall_node
              free_firewall_link
              insert_firewall_node
              print_firewall
  �޸���ʷ   :
  1.��    ��   : 2015��9��15��
    ��    ��   : if
    �޸�����   : �����ļ�

******************************************************************************/
#include "common.h"


/*****************************************************************************
 �� �� ��  : insert_firewall_node()
 ��������  : ����һ������ǽ�����
 �������  : head   ����ͷ
             node   ������ڵ�
 �� �� ֵ  : ����ͷָ��
 �޸�����  : 2015��9��13��
*****************************************************************************/
FIRE_Wall *insert_firewall_node(FIRE_Wall *head, FIRE_Wall node)
{
	FIRE_Wall *pi = NULL;
	pi = (FIRE_Wall *)malloc(sizeof(FIRE_Wall));

	if(pi != NULL){ //�ɹ����뵽�ռ�

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
 �� �� ��  : delete_firewall_node()
 ��������  : ����ARP��,��ɾ�������е�ָ���ڵ�
 �������  : head     ����ͷ
             rule     ���������ɾ���Ĺ���
 �� �� ֵ  : ����ͷָ��
 �޸�����  : 2015��9��13��
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
			if(pb == head) {//ɾ���Ľڵ�������ͷ��
				head = pb->next;
			}
			else if(pb->next == NULL) { //ɾ���Ľڵ�������β��
				pf->next = NULL;
			}
			else { //ɾ���Ľڵ����м�
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
 �� �� ��  : print_firewall()
 ��������  : ��ӡ��������ǽ�����
 �������  : head   ����ͷ
 �� �� ֵ  : ����ͷָ��
 �޸�����  : 2015��9��13��
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
 �� �� ��  : free_firewall_link()
 ��������  : �ͷ���������ǽ�����
 �������  : head   ����ͷ
 �� �� ֵ  : ����ͷָ��
 �޸�����  : 2015��9��13��
*****************************************************************************/
FIRE_Wall *free_firewall_link(FIRE_Wall *head)
{
	if(head != NULL){
		FIRE_Wall *pb = head;

		//ѭ��ɾ������ÿ���ڵ�ķ�����
		//1.�ж� head �Ƿ�Ϊ��
		//2.�� pb ָ��� head ��ͬ�Ľڵ�
		//3.Ȼ�� �� head ָ���¸��ڵ�
		//4.�ٰ� pb ָ��Ľڵ��ͷŵ�
		//5.���ز��� 1
		while(head != NULL)
		{
			pb = head;
			head = pb->next;
			free(pb);
		}
	}

	return head;
}

