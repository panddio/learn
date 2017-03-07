/* ************************************************************************
 *       Filename:  msg.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月18日 14时53分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <sys/types.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <string.h>

typedef struct _msg
{
	long type;

	char mutex[100];
}MSG;

int main(int argc, char *argv[])
{
	key_t key;
	int id;
	MSG sed;
	MSG sed2;

	sed.type = 10;
	strcpy(sed.mutex, "hello world");

	sed2.type = 1;
	strcpy(sed2.mutex, "I love you");


	key = ftok("./",23);
	id = msgget(key, IPC_CREAT | 0666);

	msgsnd(id,&sed,sizeof(sed)-4 ,0); //参数0，表示msgsnd调用阻塞直到条件满足为止
	msgsnd(id,&sed2,sizeof(sed2)-4 ,0);
	return 0;
}

