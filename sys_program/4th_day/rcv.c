/* ************************************************************************
 *       Filename:  rcv.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月18日 15时44分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>


typedef struct _msg
{
	long type;

	char mutex[100];
}MSG;

int main(int argc, char *argv[])
{
	key_t key;
	int id;
	MSG rcv1, rcv2;

	key = ftok("./", 23);

	id = msgget(key, IPC_CREAT | 0666);

	msgrcv(id, &rcv1,sizeof(rcv1)-4, 10, 0); //0：msgrcv调用阻塞直到接收消息成功为止；成功返回消息长度
	printf("rcv1 = %s\n",rcv1.mutex);

	msgrcv(id, &rcv2,sizeof(rcv2)-4, 1, 0);
	printf("rcv2 = %s\n",rcv2.mutex);

#ifdef P
	printf("this is a test\n");
#endif
	return 0;
}


