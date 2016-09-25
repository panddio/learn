/* ************************************************************************
 *       Filename:  getenv.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 11时59分01秒
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
	printf("USER =%s\n",getenv("USER"));
	printf("HOME =%s\n",getenv("HOME"));
	return 0;
}


