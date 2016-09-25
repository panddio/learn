/*************************************************************************
	> File Name: UDPEchoServer.c
	> Author: 
	> Mail: 
	> Created Time: Mon 16 May 2016 06:09:10 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "Practical.h"

int main(int argc, char *argv[])
{
   if(argc != 2)
       DieWithUserMessage("Parameter(s)", "<Server Port/Service>");

   char *service = argv[1];


}

