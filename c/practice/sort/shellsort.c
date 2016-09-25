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

	for(i=0;i<n;i++)                            /*显示原序列之中的元素*/
        printf("%d ",k[i]);
	printf("\n");
}

void shellsort(int k[],int n)
{
	int i, j, flag ,gap = n;

	while(gap > 1)
	{
		gap = gap/2;                /*增量缩小，每次减半*/
		do
		{                        /*子序列应用冒泡排序*/
			flag = 0;
			for(i=0;i<n-gap;i++) //n-gap 是控制上限不让越界
			{
				j = i + gap;	//相邻间隔的前后值进行比较
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
	{                        /*子序列应用冒泡排序*/
		flag = 0;
		for(i=0;i<n-1;i++)
		{
			if(k[i]>k[i+1])	//相邻的前后值进行比较
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
    int i,a[10] = {2,5,6,3,7,8,0,9,12,1};            /*初始化序列，a[0]可任意置数*/
    printf("The data array is:\n") ;
    for(i=0;i<10;i++)                            /*显示原序列之中的元素*/
        printf("%d ",a[i]);
	printf("\n\n");
	
    shellsort(a,10);                                /*执行希尔排序*/
   //shellsort_1(a,10);                                /*执行希尔排序*/
   printf("\nThe result of Shell's sorting for the array is:\n");
    for(i=0;i<10;i++)
        printf("%d ",a[i]);                            /*输出排序后的结果*/
	printf("\n");
	
	return 0;
}

