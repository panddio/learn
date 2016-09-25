#include <stdio.h>



float fun(int n)
{
	float res = 0.0;
	int temp = 0, i = n;
	
	if(n==1) return 1;
	
	while(i>0)
	{
		temp += i;
		i--;
	}
	
	res = 1.0/temp;
	
	return (res + fun(n-1));	
}

void main(void)
{
	float res = 0.0;
	
	
	res = fun(11);
	
	printf("res = %f\n",res);
}