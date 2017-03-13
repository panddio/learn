/*************************************************************************
	> File Name: socket_server.c
	> Author: 
	> Mail: 
	> Created Time: Tue 17 May 2016 11:28:50 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


int main(int argc, char ** argv) {
    int listenfd;
    struct sockaddr_in servaddr;
    pid_t pid;
    char temp[100];
    int n = 0;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, n);
    for(;;) {
        struct sockaddr_in local;
        int connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
        if((pid = fork()) == 0) {
            struct sockaddr_in serv, guest;
            char serv_ip[20];
            char guest_ip[20];
            int serv_len = sizeof(serv);
            int guest_len = sizeof(guest);
            getsockname(connfd, (struct sockaddr *)&serv, &serv_len);
            getpeername(connfd, (struct sockaddr *)&guest, &guest_len);
            inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));
            inet_ntop(AF_INET, &guest.sin_addr, guest_ip, sizeof(guest_ip));
            printf("host %s:%d guest %s:%d\n", serv_ip, ntohs(serv.sin_port), guest_ip, ntohs(guest.sin_port));
            char buf[] = "hello world";
            write(connfd, buf, strlen(buf));
            close(connfd);
            exit(0);

        }
        close(connfd);
    }
}
