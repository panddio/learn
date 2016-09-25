/* ************************************************************************
 *       Filename:  area_circle.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月16日 星期四 11時46分42秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/



#include <stdio.h>


#define	PI 3.14
int main(int argc, char *argv[])
{
	float r = 0;
	float area = 0;
	printf("please input circle's radius\n");
	scanf("%f",&r);
	area =  PI * r * r;
	printf("area=%8.3f\n",area);
	return 0;
}
