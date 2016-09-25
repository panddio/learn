#include "stdio.h"

void swap(int *a,int *b)
{                            
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void selectsort(int data[],int n)    /*ѡ������*/
{
	int i,j,k,max;
	//int temp;

	for(i=0;i<n-1;i++)// �� i �� ������ʼֵ
	{
		k = i;
		for(j=i+1;j<n;j++)          
		{
			if(data[j] < data[k])
				k = j;//k is the always the smaller data location
		}
		
		if(k != i)//move the smallest data to the first location
		{
			swap(&data[i], &data[k]);		
		}	
	}
	

}

int main()
{
    int i,a[10] = {2,5,6,3,7,8,0,9,12,1};        
    printf("The data array is:\n") ;
    for(i=0;i<10;i++)                        /*��ʾԭ����֮�е�Ԫ��*/
        printf("%d ",a[i]);

    selectsort(a,10);                         /*ִ��ѡ������*/
	printf("\nThe result of selection sorting for the array is:\n");
    for(i=0;i<10;i++)
        printf("%d ",a[i]);                        /*��������Ľ��*/
	printf("\n");
	
	return 0;
}

