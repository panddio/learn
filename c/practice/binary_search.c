/*=========================================================================
  工程名称：	练习  
  组成文件：	main.c
  功能描述： 	在一个排好序的数据中用二分查找法，找出需要的数据
  程序分析：	首先得从小到大排好序，二分再比较，不等则继续二分，直到高低碰头遍历结束
  维护记录：	2010-09-11 v1.1
=========================================================================*/
#include <stdio.h>

//二分法对以排好序的数据进行查找
int binary_search(int array[],int value,int size)
{
	int low=0,high=size-1,mid;

	while(low<=high)				//只要高低不碰头就继续二分查找
	{
		mid=(low+high)/2;
		if(value==array[mid])		//比较是不是与中间元素相等
			return mid;
		else if(value > array[mid])	//每查找一次，就判断一次所要查找变量所在范围，并继续二分
			low=mid + 1; 				//如果大小中间值，下限移到中间的后一个位，上限不变，往高方向二分
		else
			high=mid - 1; 			    //上限移到中间的前一个位，往低方向二分
	}
	return -1;
}

int main(void)
{
	int value;
	int a[10]={0,1,2,3,4,5,6,7,8,9};
	int n;

	while(1)
	{
		printf("\n请输入你要查找的数字:\n");
		scanf("%d",&value);
		n = binary_search(a,value,10);
		if(n==-1)
			printf("数字没找到!\n");
		else
			printf("查找数据的下标是：%d\n",n);
	}
}
