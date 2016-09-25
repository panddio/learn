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
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>



int main(int argc, char *argv[])
{
	key_t key;
	char *buf;

	key = ftok("./",66);

	int id = shmget(key,2048,IPC_CREAT | 0666);

	printf("id = %d\n",id);

	buf = (char *)shmat(id,NULL,0);
	shmdt(buf);//将共享内存和当前进程分离

	printf("buf = %s\n",buf);	
	return 0;
}




