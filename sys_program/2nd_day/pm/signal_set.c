/* ************************************************************************
 *       Filename:  signal_set.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 17时01分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <signal.h>
#include <stdio.h>



int main(int argc, char *argv[])
{
	sigset_t set;
	int ret = 0;

	sigemptyset(&set);

	ret = sigismember(&set,SIGINT);

	if(ret == 0)
		printf("SIG is not a member of sigpromask \nret = %d\n",ret);

	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGQUIT);

	ret = sigismember(&set,SIGINT);

	if(ret == 1)
		printf("SIG is a member of sigpromask \nret = %d\n",ret);

	return 0;
}


