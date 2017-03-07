/* ************************************************************************
 *       Filename:  pthread.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月19日 11时01分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct _play
{
	int count;
	int playflag;
	sem_t sem1;
	sem_t sem2;
}Play;

int num;

#if 0
void *fun1(void *arg)
{
	int i = (int)arg;
	printf("i = %d\n",i);

	for(;i>=0;i--)
	{
		printf("in pth1 num = %d\n",num);
		sleep(1);
	}
}

void *fun2(void *arg)
{
	char *pbuf = (char *)arg;

	printf("%s\n",pbuf);

	while(1)
	{
		num++;
		printf("in pth2\n");
		sleep(1);
	}
}
#endif

void *fun1(void *arg)
{
	Play *p = (Play *)arg;

	while(1)
	{
		if(p->playflag == 1)
		{
			sem_wait(&p->sem1);
			p->count++;
			sleep(1);
			sem_post(&p->sem2);
		}
	}
}

void *fun2(void *arg)
{
	Play *p = (Play *)arg;

	while(1)
	{
		sem_wait(&p->sem2);
		printf("count = %d\n",p->count);
		sem_post(&p->sem1);
	}
}

int main(int argc, char *argv[])
{
	int a = 5;
	char buf[] = "hello";
	Play play;
	play.count = 0;
	play.playflag = 1;
	pthread_t pth1, pth2;

	sem_init(&play.sem1, 0, 1);
	sem_init(&play.sem2, 0, 0);

	pthread_create(&pth1,NULL,fun1,(void *)&play);
	//sleep(1);
	pthread_create(&pth2,NULL,fun2,(void *)&play);

	while(1)
	{
		sleep(4);
		play.playflag = 0;
	}
	return 0;
}


