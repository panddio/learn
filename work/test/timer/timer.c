/*************************************************************************
	> Filename: timer.c
	>   Author:
	>    Email: qiuwei.wang@ingenic.com / paddio@163.com
	> Datatime: Wed 04 Jan 2017 02:22:26 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/timerfd.h>


#if 1
/*
 * POSIX Timer
 */
static int counter = 0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void print_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    printf("Current time: %ld.%ld\n",tv.tv_sec, tv.tv_usec);
}

void timer_thread(union sigval sgv)
{
    pthread_mutex_lock(&mutex);
    if (++counter >= 8)
        pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    pid_t tid = (pid_t)syscall(SYS_gettid);
    printf("Timer %d in PID:[%d], TID:[%d]\n", *((int *)(sgv.sival_ptr)), getpid(), tid);
    print_time();
}

int main(int argc, char *argv[])
{
    timer_t timerid1, timerid2;
    struct sigevent evp1, evp2;
    struct itimerspec its1, its2;

    /*
     * create timer
     */
    bzero(&evp1, sizeof(evp1));
    evp1.sigev_notify = SIGEV_THREAD;
    evp1.sigev_value.sival_ptr = &timerid1;
    evp1.sigev_notify_function = timer_thread;
    evp1.sigev_notify_attributes = NULL;
    if (timer_create(CLOCK_MONOTONIC, &evp1, &timerid1) < 0) {
        printf("Failed to create timer1: %s", strerror(errno));
        return -1;
    }

    bzero(&evp2, sizeof(evp2));
    evp2.sigev_notify = SIGEV_THREAD;
    evp2.sigev_value.sival_ptr = &timerid2;
    evp2.sigev_notify_function = timer_thread;
    evp2.sigev_notify_attributes = NULL;
    if (timer_create(CLOCK_MONOTONIC, &evp2, &timerid2) < 0) {
        printf("Failed to create timer2: %s", strerror(errno));
        return -1;
    }

    /*
     * start timer
     */
    its1.it_interval.tv_sec = 2;
    its1.it_interval.tv_nsec = 0;
    its1.it_value.tv_sec = 3;
    its1.it_value.tv_nsec = 0;
    if (timer_settime(timerid1, 0, &its1, NULL) < 0) {
        printf("Failed to set timer1: %s\n", strerror(errno));
        return -1;
    }

    its2.it_interval.tv_sec = 1;
    its2.it_interval.tv_nsec = 0;
    its2.it_value.tv_sec = 5;
    its2.it_value.tv_nsec = 0;
    if (timer_settime(timerid2, 0, &its2, NULL) < 0) {
        printf("Failed to set timer2: %s\n", strerror(errno));
        return -1;
    }

    print_time();
    while(counter < 8)
        pthread_cond_wait(&cond, &mutex);

    return 0;
}
#elif 0
/*
 * setitimer
 */
static int cnt = 0;

void print_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    printf("Current time: %ld.%ld, cnt = %d\n",tv.tv_sec, tv.tv_usec, cnt);
}

void sighandler(int signo)
{
    switch(signo) {
    case SIGALRM:
        printf("Timer fired, signo: %s\n", "SIGALRM");
        break;
    case SIGVTALRM:
        printf("Timer fired, signo: %s\n", "SIGVTALRM");
        break;
    case SIGPROF:
        printf("Timer fired, signo: %s\n", "SIGPROF");
        break;
    }

    cnt++;
    print_time();
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    struct itimerval val;

    /*
     * init sigaction
     */
    act.sa_handler = sighandler;
    act.sa_flags = 0;                           //见注 3)
    //act.sa_flags = SA_RESETHAND | SA_NODEFER; //见注 2)
    //sigaddset(&act.sa_mask, SIGQUIT);         //见注 1)
    sigemptyset(&act.sa_mask);
    sigaction(SIGPROF, &act, NULL);

    /*
     * init timer
     */
    val.it_value.tv_sec = 5;
    val.it_value.tv_usec = 0;
    val.it_interval.tv_sec = 3;
    val.it_interval.tv_usec = 0;
    setitimer(ITIMER_PROF, &val, NULL);

    print_time();

    while(cnt < 4)
        usleep(100);

    return 0;
}

/**
 * 注：
 * 1) 如果在信号SIGINT(Ctrl + c)的信号处理函数show_handler执行过程中，本进程收到信号SIGQUIT(Crt+\)，将阻塞该信号，直到show_handler执行结束才会处理信号SIGQUIT。
 *
 * 2) SA_NODEFER  :一般情况下，当信号处理函数运行时，内核将阻塞<该给定信号:SIGINT>。但是如果设置了SA_NODEFER标记，那么在该信号处理函数运行时，内核将不会阻塞该
 *                 信号。SA_NODEFER是这个标记的正式的POSIX名字(还有一个名字SA_NOMASK，为了软件的可移植性，一般不用这个名字)
 *
 *    SA_RESETHAND:当调用信号处理函数时，将信号的处理函数重置为缺省值。 SA_RESETHAND是这个标记的正式的POSIX名字(还有一个名字SA_ONESHOT，为了软件的可移植性，一般不用这个名字)
 *
 * 3) 如果不需要重置该给定信号的处理函数为缺省值；并且不需要阻塞该给定信号(无须设置sa_flags标志)，那么必须将sa_flags清零，否则运行将会产生段错误。但是sa_flags清零后可能会造成信号丢失！
 */
#endif
