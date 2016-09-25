/* ************************************************************************
 *       Filename:  test.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月06日 星期四 05時26分10秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>

int fun(int n)
{
	if(n > 1){
		return n*fun(n-1);
	}
	else{
		return 1;
	}
}

int mypow(int m, int n)
{
	if(n > 0){
		return m * mypow(m, n-1);
	}
	else if(n == 0){
		return 1;
	}

}
int main()
{

	int temp;

	temp = fun(6);

	printf("!5 = %d\n", temp);

	temp = mypow(3,5);
	printf("pow(3,5) = %d\n",temp);

	return 0;
}
