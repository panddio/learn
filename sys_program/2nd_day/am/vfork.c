/* ************************************************************************
 *       Filename:  vfork.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 10时28分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  王秋伟, 
 *        Company:  
 * ************************************************************************/
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int gnum = 0;

int main(int argc, char *argv[])
{
	pid_t pid;
	int num = 1;

	//pid = fork();
	pid = vfork();

	if(pid < 0) perror("");

	else if(pid == 0)
	{
		int i;

		for(i=0;i<3;i++)
		{
			printf("in son process\n");
			gnum++;
			num++;
			sleep(1);
		}
		printf("in #son process\n");
		execl("/bin/ls","ls","-l","-h",NULL); //当调用exec函数后，用vfork创建的子进程也会有自己的地址空间，
											  //并且exec启动的程序会把，该地址空间的数据段、代码段和堆栈段覆盖掉
											  //所以就导致后面的printf打印不出信息
											  //当遇到exec函数，用vfork创建子进程的父进程将不再等待子进程执行完
											  //所以这里会先看到父进程for循环中打印出一条信息，然后再有 ls 执行的打印信息

		printf("in son# process\n"); //加了execl函数后，并没有把这条信息打印到屏幕

		//exit(2);// 退出子进程，并返回2，会刷新缓冲区
		//return 0;//加了这句，会弹栈，因为这里的子进程跟父进程共用同一地址空间，
		           //导致父进程找不到栈原来的内容，则出错，
				   //比如这里，返回后，父进程中访问num的值为0，而实际在子进程return前num ！= 0
	}
	else
	{
		int i;
		int status = 0;

		for(i=0;i<3;i++)
		{
			printf("in father process\n");
			printf("gnum = %d  num = %d\n",gnum,num);
			sleep(1);
		}
				
		//wait(&status);
		waitpid(-1,&status,0); // 这里跟 wait(&status) 一样

		if(WIFEXITED(status) != 0) //判断返回状态 ，存在status的低8位
		{
			printf("return = %d\n",WEXITSTATUS(status)); //取返回值，存在status的8~16位
		}
	}

	return 0;
}
