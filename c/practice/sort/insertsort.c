#include "stdio.h"

//从小到大进行排序
insertsort(int k[],int n)         	/*直接插入排序*/
{
    int i,j;
	int temp;

    for(i=1;i<n;i++)
    {
        temp = k[i];				//将要比较的值先绶存起来留出一个空位，方便移动
        j = i - 1;
        while(j>=0 && k[j]>temp)    //比较直到出现比temp大的值，或向前找到头
        {
			k[j+1] = k[j];			//将前面的值往后移
			j--;
		}
        k[j+1] = temp;             	//插在a[j]的后面
    }
}

int main()
{
    int i,a[10] = {2,5,6,3,7,8,0,9,12,1};        /*初始化序列，a[0]可任意置数*/
    printf("The data array is:\n") ;
    for(i=0;i<10;i++)                       	 /*输出排序前的数据*/
        printf("%d ",a[i]);

    insertsort(a,10);                            /*插入排序*/
	
    printf("\nThe result of insertion sorting for the array is:\n");
    for(i=0;i<10;i++)
        printf("%d ",a[i]);                      /*输出排序后的数据*/
	printf("\n");
	return 0;
}