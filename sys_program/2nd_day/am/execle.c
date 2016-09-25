/* ************************************************************************
 *       Filename:  excele.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月14日 12时03分24秒
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
	char *env[] = {"USER=ME","COMGSI = sunplusapp.com"};

	execle("./getenv","getenv",NULL,env);
	return 0;
}


