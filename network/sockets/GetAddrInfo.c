/*************************************************************************
	> File Name: GetAddrInfo.c
	> Author: 
	> Mail: 
	> Created Time: Fri 06 May 2016 09:20:10 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include "Practical.h"

int main(int argc, char *argv[])
{

    if(argc != 3)
        DieWithUserMessage("Parameter(s)","<Address/Name> <Port/Service");

    char *addrString = argv[1];
    char *portString = argv[2];

    //Tell the system what kind(s) of address info we want
    struct addrinfo addrCriterial;
    memset(&addrCriterial, 0, sizeof(addrCriterial));
    addrCriterial.ai_family = AF_UNSPEC;
    addrCriterial.ai_socktype = SOCK_STREAM;
    addrCriterial.ai_protocol = IPPROTO_TCP;

    //Get address(es) associated with the specified name/Service
    struct addrinfo *addrList;
    int rtnVal = getaddrinfo(addrString, portString, &addrCriterial, &addrList);
    if(rtnVal != 0)
        DieWithUserMessage("getaddrinfo() failed",gai_strerror(rtnVal));

    //Display returned addresses
    struct addrinfo *addr;
    for(addr = addrList; addr != NULL; addr = addr->ai_next) {
        PrintSocketAddress(addr->ai_addr, stdout);
        fputc('\n', stdout);
    }

    freeaddrinfo(addrList); //Free addrinfo allocated in getaddrinfo()
    exit(0);
}
