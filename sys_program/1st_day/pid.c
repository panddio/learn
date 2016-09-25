/* ************************************************************************
 *       Filename:  pid.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月13日 15时12分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char *argv[])
{

	pid_t pid, ppid, pgid;

	pid = getpid();
	ppid = getppid();
	pgid = getpgid(0);

	printf("pid = %d\n",pid);  //获取本进程号
	printf("ppid = %d\n",ppid);//获取此进程的父进程
	printf("pgid = %d\n",pgid);//获取组进程号，参数为0是返回当前的PGID

	return 0;
}
