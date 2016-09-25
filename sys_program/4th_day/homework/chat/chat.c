/* ************************************************************************
 *       Filename:  chat.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月18日 17时47分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  王秋伟 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>

#if defined   (P)
char name[] = "Peter";
#elif defined (L)
char name[] = "Lucy";
#elif defined (B)
char name[] = "Bob";
#endif

typedef struct _msg
{
	long type;
	char msg[256];
}MSG;

int main(int argc, char *argv[])
{
	key_t key;
	pid_t pid;
	MSG snd,rcv;
	int id;
	
	key = ftok("./",23);                //获取key 值
	id = msgget(key, IPC_CREAT | 0666); //打开或创建消息队列
	if(id == -1)  //出错退出
	{
		perror("");
		exit(-1);
	}

	printf("Hi, I am %s\n",name);

	pid = fork(); //创建子进程	
	if(pid < 0)   //出错退出
	{
		perror("");
		exit(-1);
	}		
	else if(pid == 0) //子进程
	{
		int len = 0, i;
		char buf[256] = "";
		
		while(1)
		{
			printf("%s: ",name);
			fflush(stdout);

			fgets(buf,sizeof(buf),stdin);
			len = strlen(buf);

			if(len > 3)
			{
				char msg[256] = "";
				buf[len-1] = '\0';
				
				for(i=0;i < len-1;i++)
				{
					if(buf[i] == 'P' || buf[i] == 'L' || buf[i] == 'B' && buf[i+1] == ' ')
					{
						if(buf[i] == name[0]) //判断是不是给自己发信息
						{
							break; //给自己发信息直接退出，不写入消息队列
						}
						snd.type = buf[i];
						buf[i] = ':';
						
						strcat(msg,name);
						strcat(msg, buf+i);
						strcpy(snd.msg, msg); 
				
						msgsnd(id, &snd, sizeof(snd) - sizeof(long) , 0);
						break;
					}
				}
			}			
		}
	}
	else //父进程
	{
		
		while(1)
		{
			bzero(rcv.msg, sizeof(rcv.msg));
									
		#if defined   (P)
			msgrcv(id, &rcv,sizeof(rcv) - sizeof(long), (long)('P'), 0);
		#elif defined (L)
			msgrcv(id, &rcv,sizeof(rcv) - sizeof(long), (long)('L'), 0);
		#elif defined (B)
			msgrcv(id, &rcv,sizeof(rcv) - sizeof(long), (long)('B'), 0);
		#endif							
			printf("\r%s\n",rcv.msg);
			printf("%s: ",name);
			fflush(stdout);			
		}
	}
	//printf("name = %s\n",name);
	return 0;
}