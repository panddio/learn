#include "stdio.h"

void swap(int *a,int *b)
{                            
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void display(int k[],int n)
{
	int i;

	for(i=0;i<n;i++)                            /*��ʾԭ����֮�е�Ԫ��*/
        printf("%d ",k[i]);
	printf("\n");
}

void shellsort(int k[],int n)
{
	int i, j, flag ,gap = n;

	while(gap > 1)
	{
		gap = gap/2;                /*������С��ÿ�μ���*/
		do
		{                        /*������Ӧ��ð������*/
			flag = 0;
			for(i=0;i<n-gap;i++) //n-gap �ǿ������޲���Խ��
			{
				j = i + gap;	//���ڼ����ǰ��ֵ���бȽ�
				if(k[i]>k[j])
				{
					swap(&k[i],&k[j]);
					flag = 1;
				}
			}
			printf("gap = %d:\n",gap);
			display(k,10);
		}while(flag !=0);
	}
}

void shellsort_1(int k[],int n)
{
	int i,flag;

	do
	{                        /*������Ӧ��ð������*/
		flag = 0;
		for(i=0;i<n-1;i++)
		{
			if(k[i]>k[i+1])	//���ڵ�ǰ��ֵ���бȽ�
			{
				swap(&k[i],&k[i+1]);
				flag = 1;
			}
		}
		printf("gap=1:\n");
 		display(k,10);
	}while(flag !=0);
}

int main()
{
    int i,a[10] = {2,5,6,3,7,8,0,9,12,1};            /*��ʼ�����У�a[0]����������*/
    printf("The data array is:\n") ;
    for(i=0;i<10;i++)                            /*��ʾԭ����֮�е�Ԫ��*/
        printf("%d ",a[i]);
	printf("\n\n");
	
    shellsort(a,10);                                /*ִ��ϣ������*/
   //shellsort_1(a,10);                                /*ִ��ϣ������*/
   printf("\nThe result of Shell's sorting for the array is:\n");
    for(i=0;i<10;i++)
        printf("%d ",a[i]);                            /*��������Ľ��*/
	printf("\n");
	
	return 0;
}

