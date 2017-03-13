/*************************************************************************
	> File Name: socket_client.c
	> Author: 
	> Mail: 
	> Created Time: Tue 17 May 2016 11:34:19 AM CST
 ************************************************************************/

#include <stdio.h>
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
    int sockfd, n;
    int my;
    char buf[100];
    struct sockaddr_in servaddr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("create socket error\n");
        exit(1);

    }

    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));

    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0) {
        printf("inet_pton error\n");
        exit(1);

    }

    if((my = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0) {
        printf("connect error\n");
        exit(1);

    }

    struct sockaddr_in serv, guest;
    int serv_len = sizeof(serv);
    int guest_len = sizeof(guest);
    char serv_ip[20], guest_ip[20];

    getsockname(sockfd, (struct sockaddr *)&guest, &guest_len);
    getpeername(sockfd, (struct sockaddr *)&serv, &serv_len);

    inet_ntop(AF_INET, &guest.sin_addr, guest_ip, sizeof(guest_ip));
    inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));

    printf("host %s:%d, guest %s:%d\n", serv_ip, ntohs(serv.sin_port), guest_ip, ntohs(guest.sin_port));

    n = read(sockfd, buf, 100);
    buf[n] = '\0';

    printf("%s\n", buf);
    getchar();
    close(sockfd);
    exit(0);
}
