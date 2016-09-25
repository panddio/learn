#include "stdio.h"

void swap(int *a,int *b)
{                            
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void selectsort(int data[],int n)    /*选择排序*/
{
	int i,j,k,max;
	//int temp;

	for(i=0;i<n-1;i++)// “ i ” 就是起始值
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
    for(i=0;i<10;i++)                        /*显示原序列之中的元素*/
        printf("%d ",a[i]);

    selectsort(a,10);                         /*执行选择排序*/
	printf("\nThe result of selection sorting for the array is:\n");
    for(i=0;i<10;i++)
        printf("%d ",a[i]);                        /*输出排序后的结果*/
	printf("\n");
	
	return 0;
}

