#include "stdio.h"

//��С�����������
insertsort(int k[],int n)         	/*ֱ�Ӳ�������*/
{
    int i,j;
	int temp;

    for(i=1;i<n;i++)
    {
        temp = k[i];				//��Ҫ�Ƚϵ�ֵ��練���������һ����λ�������ƶ�
        j = i - 1;
        while(j>=0 && k[j]>temp)    //�Ƚ�ֱ�����ֱ�temp���ֵ������ǰ�ҵ�ͷ
        {
			k[j+1] = k[j];			//��ǰ���ֵ������
			j--;
		}
        k[j+1] = temp;             	//����a[j]�ĺ���
    }
}

int main()
{
    int i,a[10] = {2,5,6,3,7,8,0,9,12,1};        /*��ʼ�����У�a[0]����������*/
    printf("The data array is:\n") ;
    for(i=0;i<10;i++)                       	 /*�������ǰ������*/
        printf("%d ",a[i]);

    insertsort(a,10);                            /*��������*/
	
    printf("\nThe result of insertion sorting for the array is:\n");
    for(i=0;i<10;i++)
        printf("%d ",a[i]);                      /*�������������*/
	printf("\n");
	return 0;
}