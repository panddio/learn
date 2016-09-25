/* ************************************************************************
 *       Filename:  sem.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月20日 12时00分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1;

void print(char *str)
{
	sem_wait(&sem1);
	while(*str != '\0')
	{
		putchar(*str++);
		fflush(stdout);
		sleep(1);
	}
	putchar('\n');

	sem_post(&sem1);
}

void *fun1(void *arg)
{
	char *buf = "world";

	print(buf);
}

void *fun2(void *arg)
{
	char *buf = "hello";

	print(buf);
}

int main(int argc, char *argv[])
{
	int val = 0;
	pthread_t pth1,pth2;

	sem_init(&sem1,0,1);
	sem_getvalue(&sem1,&val);
	printf("sem_val = %d\n",val);


	pthread_create(&pth1,NULL,fun1,NULL);
	pthread_create(&pth2,NULL,fun2,NULL);

	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);

	val = sem_destroy(&sem1);
	if(val==0)
	{
		printf("delete sem succeed\n");
	}
	return 0;
}
