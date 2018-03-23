/*************************************************************************
	> Filename: pthread_cancel.c
	>   Author: Wang Qiuwei
	>    Email: qiuwei.wang@ingenic.com / panddio@163.com
	> Datatime: Thu 13 Jul 2017 09:21:30 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void cleanup(void *agr)
{
	printf("%s: L%d\n", __FUNCTION__, __LINE__);
	pthread_mutex_unlock(&mutex);
}

void *pthread_fun1(void *arg)
{
	int count = 0;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); //允许退出线程
	//pthread_setcanceltype(PTHREAD_CANCEL_DISABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	//pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL); //设置立即取消
	while(1) {
		pthread_cleanup_push(cleanup, NULL);
		pthread_mutex_lock(&mutex);
		printf("%s: L%d count=%d\n", __FUNCTION__, __LINE__, count);
		count++;
		usleep(1000*1000);
		pthread_mutex_unlock(&mutex);
		pthread_cleanup_pop(0);
	}
}

int main(int argc, char *argv)
{
	pthread_t thrd;

//	pthread_attr_t attr;
//	pthread_attr_init(&attr);
//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thrd, NULL, pthread_fun1, NULL);
//	pthread_detach(thrd);
	sleep(5);
	pthread_cancel(thrd);
	pthread_join(thrd, NULL);
//	while(1);
	return 0;
}
