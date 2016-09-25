/*************************************************************************
	> File Name: UDPEchoClient.c
	> Author: 
	> Mail: 
	> Created Time: Mon 16 May 2016 04:50:18 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "Practical.h"

int main(int argc, char *argv[])
{
    if(argc < 3 || argc > 4)
        DieWithUserMessage("Parameter(s)",
            "<Server Address/Name> <Echo Word> [<Server Port/Service]");

    char *server = argv[1];
    char *echoString = argv[2];

    size_t echoStringLen = strlen(echoString);
    if(echoStringLen > MAXSTRINGLENGTH) //Check input length
        DieWithUserMessage(echoString, "string too long");

    //Thrid arg(optional): server port/service
    char *servPort = argv[3];

    //Tell the system what kind(s) of address info we want
    struct addrinfo addrCriteria;
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC;
    addrCriteria.ai_socktype = SOCK_DGRAM;  //Only datagram sockets
    addrCriteria.ai_protocol = IPPROTO_UDP; //Onlu UDP protocol

   //Get address(es)
   struct addrinfo *servAddr;
   int rtnVal = getaddrinfo(server, servPort, &addrCriteria, &servAddr);
   if(rtnVal != 0)
       DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));

   //Create a datagram/UDP socket
   int sock = socket(servAddr->ai_family, servAddr->ai_socktype, servAddr->ai_protocol);

   if(sock < 0)
       DieWithSystemMessage("socket() failed");

   //Send the string to server
   ssize_t numBytes = sendto(sock, echoString, echoStringLen, 0,
           servAddr->ai_addr, servAddr->ai_addrlen);

   if(numBytes < 0)
       DieWithSystemMessage("sendto() failed");
   else if(numBytes != echoStringLen)
       DieWithUserMessage("sendto() error", "sent unexpected number of bytes");

   //Receive a response
   struct sockaddr_storage fromAddr; //Source address of server
   socklen_t fromAddrLen = sizeof(fromAddr);
   char buffer[MAXSTRINGLENGTH + 1] = {0};
   numBytes = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0,
                (struct sockaddr *)&fromAddr, &fromAddrLen);

   if(numBytes < 0)
       DieWithSystemMessage("recvfrom() failed");
   else if(numBytes != echoStringLen)
       DieWithUserMessage("recvfrom() error", "received unexpected number of bytes");

   //Verify reception from expected source
   if(!SockAddrsEqual(servAddr->ai_addr, (struct sockaddr *)&fromAddr))
       DieWithUserMessage("recvfrom()","received a packet from unknown source");

   freeaddrinfo(servAddr);
   buffer[MAXSTRINGLENGTH] = '\n';
   printf("Received: %s\n", buffer);

   close(sock);
   return 0;
}
