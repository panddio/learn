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

sem_t semp, semc;
int totol_num = 3;


void *producter(void *arg)
{
	while(1)
	{
		sem_wait(&semp);

		sleep(1);
		totol_num++;
		printf("push into  >>totol_num = %d\n",totol_num);

		sem_post(&semc);
	}
}

void *consumer(void *arg)
{
	while(1)
	{
		sem_wait(&semc);

		sleep(2);
		totol_num--;
		printf("pop out    >>totol_num = %d\n",totol_num);

		sem_post(&semp);
	}
}

int main(int argc, char *argv[])
{
	pthread_t pth1,pth2;

	sem_init(&semp,0,7);
	sem_init(&semc,0,3);

	pthread_create(&pth1,NULL,producter,NULL);
	pthread_create(&pth2,NULL,consumer,NULL);

	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);

	sem_destroy(&semp);
	sem_destroy(&semc);

	return 0;
}
