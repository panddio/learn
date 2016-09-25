/* ************************************************************************
 *       Filename:  mutex.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月20日 10时34分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
//PTHREAD_MUTEX_INITIALIZER;


void print(char *str)
{
	pthread_mutex_lock(&mutex);

	while(*str != '\0')
	{
		putchar(*str++);
		fflush(stdout);
		sleep(1);
	}
	putchar('\n');

	pthread_mutex_unlock(&mutex);
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
	pthread_t pth1,pth2;

	pthread_mutex_init(&mutex,NULL);

	pthread_create(&pth1,NULL,fun1,NULL);
	pthread_create(&pth2,NULL,fun2,NULL);

	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);

	pthread_mutex_destroy(&mutex);
	return 0;
}
