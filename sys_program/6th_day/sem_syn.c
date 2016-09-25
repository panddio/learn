/* ************************************************************************
 *       Filename:  sem_syn.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月20日 14时38分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1, sem2;
char ch = 'a';

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
	while(1)
	{
		sem_wait(&sem1);
		ch++;
		sleep(1);
		sem_post(&sem2);
	}

}

void *fun2(void *arg)
{
	while(1)
	{
		sem_wait(&sem2);
		printf("%c",ch);
		fflush(stdout);
		sem_post(&sem1);
	}

}

int main(int argc, char *argv[])
{
	int val = 0;
	pthread_t pth1,pth2;

	sem_init(&sem1,0,0);
	sem_init(&sem2,0,1);


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
