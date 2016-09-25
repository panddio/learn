#include <stdio.h>

void swap(int *a,int *b)
{                            /*序列中元素位置的交换*/
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void print(int k[])
{
	int i;
	static int cont = 0;

	cont++;
	printf("\n第 %d 次:   ",cont);
	for(i=0;i<10;i++)
	{
		printf("%d ",k[i]);
	}
	printf("\n");

}
void quicksort(int k[], int start_num, int end_num)
{                            /*快速排序*/
	int i, j;
	
	if(start_num < end_num)
	{
		i = start_num;
		j = end_num + 1;
		
		while(1)
		{
			do{
				i++;
			}while( !(k[i] >= k[start_num] || i == end_num));  //从第一个开始求出第一个大于基准值的元素位置i
			
			do{
				j--;
			}while( !(k[j] <= k[start_num] || j == start_num)); //从最后开始求出第一个小于基准值的元素位置j
			
			if(i < j) swap(&k[i], &k[j]);
			else break;
		}
		
		swap(&k[start_num], &k[j]);
		quicksort(k, start_num, j-1);   /*递归排序基准元素前面的子序列*/
		quicksort(k, j+1, end_num);     /*递归排序基准元素后面的子序列*/
	}

}

int main()
{
    int k[10]={2,5,6,3,7,8,1,9,12,0} , i;
    printf("The data array is\n") ;
    for(i=0;i<10;i++)                        	/*显示原序列之中的元素*/
        printf("%d ",k[i]);
	printf("\n");

    quicksort(k,0,9);                        	/*快速排序*/
    printf("\nThe result of quick sorting for the array is\n");
    for(i=0;i<10;i++)                        	 /*显示排序后的结果*/
        printf("%d ",k[i]);
	printf("\n");

	return 0;
}


