/******************************************************************************
  �� �� ��   : main.c
  �� �� ��   : ����
  ��    ��   : �Ǻ�
  ��������   : 2015��9��11��
  ��������   : ������
******************************************************************************/
#include "common.h"
#include "route_control.h"
#include "route_pthread.h"



int main(int argc, char *argv[])
{
	TYPE_Route route;       // ����·�����ṹ�����

	route_init(&route);     // ·������ʼ��
	create_pthread(&route); // �����߳�

	return 0;
}


