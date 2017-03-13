/*************************************************************************
	> File Name: tcp_server.c
	> Author:
	> Mail:
	> Created Time: Mon 17 Oct 2016 10:53:42 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int create_tcp_server(unsigned short port)
{
	int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in s_addr;

	bzero(&s_addr, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(port);
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(listen_sock, (struct sockaddr *)&s_addr, sizeof(s_addr));
	if(ret != 0) {
		perror("bind():");
		return -1;
	}

	listen(listen_sock, 10);

	return listen_sock;
}

int recv_client_data(int listen_sock)
{
	fd_set rfds;
	struct timeval tv = {0, 100*1000};
	static int client = -1;
	int max, ret, index = -1;

	FD_ZERO(&rfds);
	FD_SET(listen_sock, &rfds);

	if(client != -1)
		FD_SET(client, &rfds);

	max = listen_sock > client ? listen_sock : client;
	ret = select(max+1, &rfds, NULL, NULL, &tv);

	if(ret > 0) {
		if(FD_ISSET(listen_sock, &rfds)) {
            struct sockaddr_in c_addr;
            socklen_t addr_len = sizeof(c_addr);
            bzero(&c_addr, addr_len);

			if(client != -1)
				close(client);

			client = accept(listen_sock, (struct sockaddr *)&c_addr, &addr_len);
		}

		if(client != -1 && FD_ISSET(client, &rfds)) {
			ret = read(client, &index, sizeof(index));
			if(ret != sizeof(index)) {
				close(client);
				client = -1;
				index = -1;
			}
		}
	}

	return index;
}
