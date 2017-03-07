/* ************************************************************************
 *       Filename:  r_shm.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月18日 17时27分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{
    int i = 20000;
	key_t key;
	char *buf;

	key = ftok("./",66);

    while(i--) {
	int id = shmget(key,2048,IPC_CREAT | 0666);

	//printf("id = %d\n",id);

	buf = (char *)shmat(id,NULL,0);

    if((long)buf < 0) {
        printf("shmat failed: %s", strerror(errno));
        break;
    }
    else
        printf("i: %08d,  buf = %s\n",i, buf);
    }

	shmdt(buf);//将共享内存和当前进程分离

	return 0;
}




