#include "stdio.h"

void swap(int *a,int *b)
{                            
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubblesort(int k[],int n)
{                    /*ð������*/
	int i,j,tmp;
	int flag = 1,cont = 0;

	for(i=0;i<n && flag == 1;i++)	//����ÿ����ǰ��һ�������ٱȽ�һ��
	{             
		//flag = 0;	//����flag
		for(j=0;j<n-i-1;j++) //�ӵ�һ����ʼ�����������ڵ�ֵ�Ƚϣ���������ֵ��һֱ�Ƶ��������ð��
		{	
			cont++;
			if(k[j]<k[j+1])
			{
				swap(&k[j+1],&k[j]);
				flag = 1;
			}
		}
	}

	printf("\nѭ���Ƚϴ�����%d\n",cont);
}

int main()
{
    int i,a[10] = {2,5,6,3,7,8,12,9,1,0};   
	
    printf("The data array is\n") ;
    for(i=0;i<10;i++)                            /*��ʾԭ����֮�е�Ԫ��*/
        printf("%d ",a[i]);
	
	bubblesort(a,10);                            /*ִ��ð������*/
    printf("\nThe result of bubble sorting for the array is\n");
    for(i=0;i<10;i++)
        printf("%d ",a[i]);                            /*��������Ľ��*/
	printf("\n");
	
	return 0;
}
