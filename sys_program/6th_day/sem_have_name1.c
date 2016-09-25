/* ************************************************************************
 *       Filename:  sem_have_name.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月20日 15时13分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>


void print(sem_t *psem1,sem_t *psem2)
{
	int i = 0;

	while(1)
	{
		sem_wait(psem1);
		printf("i = %d\n",i);
		i++;
		sleep(1);
		sem_post(psem2);
	}
}

int main(int argc, char *argv[])
{
	sem_t *ptr1,*ptr2;

	ptr1 = sem_open("sem_name1",O_CREAT,0777,1);
	if(ptr1 == SEM_FAILED)
	{
		printf("Failed:sem_name1\n");
	}
	ptr2 = sem_open("sem_name2",O_CREAT,0777,0);
	if(ptr2 == SEM_FAILED)
	{
		printf("Failed:sem_name2\n");
	}

	print(ptr1,ptr2);
	return 0;
}
