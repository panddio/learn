/* ************************************************************************
 *       Filename:  sort.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月28日 星期二 10時51分47秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>

typedef struct stu
{
	int num;
	char name[30];
	float score;
}STU;

void sort(STU stu[],int n)
{
	STU temp;
	int i,j;

	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++)
		{
			if(stu[i].score < stu[j].score)
			{
				temp = stu[i];
				stu[i] = stu[j];
				stu[j] = temp;
			}
		}
}
int main(int argc, char *argv[])
{
	STU stu[5];
	int i;
	float ave = 0;

	for(i=0;i<5;i++)
	{
		printf("请输入第%d位学生的学号、姓名、成绩：\n",i+1);
		scanf("%d %s %f",&stu[i].num,stu[i].name,&stu[i].score);
	}

	sort(stu,5);

	for(i=0;i<5;i++)
	{
		ave += stu[i].score;
		printf("学号：%-4d 姓名：%-8s 成绩：%-4.1f 排第%d名\n",stu[i].num,stu[i].name,stu[i].score,i+1); 
	}

	ave /=5;

	printf("\n平均成绩 %.1f\n",ave);
	return 0;
}


