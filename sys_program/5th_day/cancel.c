/* ************************************************************************
 *       Filename:  cancel.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月19日 14时42分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_t pth1,pth2;

void up_fun1(void *arg)
{
	printf("push fun1\n");
}

void up_fun2(void *arg)
{
	printf("push fun2\n");
}
void up_fun3(void *arg)
{
	printf("push fun3\n");
}
void *fun1(void *arg)
{
	int i=0;

	//pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

	pthread_cleanup_push(up_fun1,NULL);
	pthread_cleanup_push(up_fun2,NULL);
	pthread_cleanup_push(up_fun3,NULL);
	pthread_cleanup_pop(0);
	//for(i=0;i<20;i++)
	while(1)
	{
		printf("in pth1\n");
		sleep(1);
		//pthread_testcancel();//
		i++;
		if(i == 2)
		{
			return 0;
		}
	}

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(1);

	return;
}

void *fun2(void *arg)
{
	int i=0;

	for(i=0;i<10;i++)
	{
		printf("in pth2\n");
		sleep(1);

		if(i==5)
		{
			pthread_exit(NULL);
		}

		if(i==2)
		{
			pthread_cancel(pth1);
		}
	}

	return;
}

int main(int argc, char *argv[])
{

	pthread_create(&pth1,NULL,fun1,NULL);
	//pthread_create(&pth2,NULL,fun2,NULL);

	sleep(5);
	pthread_cancel(pth1);

	pthread_join(pth1,NULL);
	//pthread_join(pth2,NULL);


	return 0;
}


