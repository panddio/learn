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
	char *ptr[] = {"ls","-l","-h",NULL};

	execv("/bin/ls",ptr);
	return 0;
}


