/*=========================================================================
  �������ƣ�	��ϰ  
  ����ļ���	main.c
  ���������� 	ͨ�����������У�,��ѭ�������м�����Ϣ
  ���������	��ջ��ͬ���ǣ����е�ָ����Ӧ�������˳��ָ�ģ���Ҫ�ǿ��ƶ���ͷ��βָ����в���
  ά����¼��	2010-09-12 v1.1	
=========================================================================*/

#include <stdio.h>
#include <stdlib.h>

 typedef  struct Qnode
{
    int  data;
    struct Qnode *next;
 }Qnode;

Qnode  *front;                   //��ͷָ��
Qnode  *rear;                    //��βָ��

int EnQueue( int *e)
{
    Qnode *p;
    p=(Qnode *)malloc(sizeof(Qnode));

    p->data=*e;         //�����ݼ��뵽������
    p->next=NULL;		//��βָ��NULL
    rear->next=p;       //������βָ��λ�ã�Ϊ��һ��ѹջ��׼��
    rear=p;
    return  1;
}



int DeQueue( int *e)
{
    Qnode *p;

    if(front==rear)
        return 0;   	    //�ӿ�

    p=front->next;          //��ó���ָ��
    *e=p->data;             //�������ӽڵ������ȡ��
    front->next= p->next;   //������ͷָ�룬Ϊ�´γ�����׼��

    if(p == rear)           //����ͷָ��׷�϶�βָ�룬������ͷָ�룬��ʱ�ӿ�
        rear = front;

    free(p);                //�ͷ��ѳ�������
    return 1;
}

int main()
{
    int a = 11;
	int c = 12;
    int b = 0;
    rear=front=(Qnode *)malloc(sizeof(Qnode));
    EnQueue(&a);        //�������
	EnQueue(&c);        //�������

    DeQueue(&b);        //��������
    printf("%d\n",b);
	DeQueue(&b);        //��������
    printf("%d\n",b);
}

