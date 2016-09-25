/* ************************************************************************
 *       Filename:  exec.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 11时07分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	execl("/bin/ls","ls","-l","-a","-h",NULL);
	return 0;
}


