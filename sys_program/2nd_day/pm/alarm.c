/* ************************************************************************
 *       Filename:  alarm.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 15时20分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	int ret = 0;
	ret = alarm(6);
	printf("ret 1 = %d\n",ret);

	sleep(4);

	ret = alarm(5);

	printf("ret 2 = %d\n",ret);

	while(1)
	{
		printf("alarm\n");
		sleep(1);
	}
	return 0;
}


