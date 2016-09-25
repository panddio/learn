/*************************************************************************
	> File Name: TCPEchoClient.c
	> Author: 
	> Mail: 
	> Created Time: Fri 06 May 2016 11:12:30 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "Practical.h"

int main(int argc, char *argv[])
{
    if(argc < 3 || argc > 4) //Test for correct number of arguments
        DieWithUserMessage("Paramter(s)", "<Server Address/Name> <Echo Word> [<Server Port/Service]");

    char *server = argv[1];  //First arg: server address/name
    char *echoString = argv[2]; //Second arg: string to echo
    char *service = (argc == 4)?argv[3]:"echo"; //Third arg (optional): server port/service


    //Create a connected TCP socket
    int sock  = SetupTCPClientSocket(server, service);
    if(sock < 0)
        DieWithUserMessage("SetupTCPClientSocket() failed","unable to connect");

    size_t echoStringLen = strlen(echoString);
    
    //Send the string to the server
    ssize_t numBytes = send(sock, echoString, echoStringLen, 0);
    if(numBytes < 0)
        DieWithSystemMessage("send() failed");
    else if(numBytes != echoStringLen)
        DieWithUserMessage("send()", "sent unexpected number of bytes");

    //Recevice the same string back from the server
    unsigned int totalBytesRcvd = 0; //Count of total bytes receviced
    fputs("Receviced: ", stdout);
    while(totalBytesRcvd < echoStringLen) {
        char buffer[BUFSIZE];
        numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
        if(numBytes < 0)
            DieWithSystemMessage("recv() failed");
        else if(numBytes == 0)
            DieWithUserMessage("recv()", "connection closed prematurely");

        totalBytesRcvd += numBytes; //Keep tally of total bytes
        buffer[numBytes] = 0;       //Terminate the string
        fputs(buffer, stdout);      //Print the buffer
    }

    fputc('\n',stdout);
    close(sock);
    exit(0);
}
