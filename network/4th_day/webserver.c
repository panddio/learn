/* ************************************************************************
 *       Filename:  webserver.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月06日 11时36分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

char const err[] = "HTTP/1.1 404 Not Fount\n\
					Server:Apache Tomcat/5.0.12\n\
					Content-Type:text/html\n\
					Content-Length:43\n\
					<HTML><BODY>File not Fount</BODY></HTML>";

char const *ack[] ={"HTTP/1.1 200 OK\r\n",
				    "Server:Apache Tomcat/5.0.12\r\n",
				    "Content-Type:text/html\r\n",
				    "Content-Length:",
					"\r\n"
				   };

void *server_fun(void *arg)
{
	FILE *fp = NULL;
	int connfd = *(int *)arg;
	int len = 0;
	char msg[512] = "";
	char html[256]= "";
	char path[256]= "./html/";

	bzero(msg, sizeof(msg));
	len = recv(connfd, msg, sizeof(msg),0);
	sscanf(msg,"GET /%[^ ]",html);
	//printf("html = ###%s###\n",html);
	//printf("msg = %s\n", msg);

	strcat(path,html);
	printf("path = %s\n",path);
	fp = fopen(path,"rb");
	if(fp == NULL)
	{
		printf("Not fount file\n");
		send(connfd, err, sizeof(err), 0);
		close(connfd);
		pthread_exit(NULL);//退出线程
	}

	//fseek(fp,0,SEEK_END);
	//len = ftell(fp); //获取文件的大小
	//sprintf(msg, "%s%d%s", ack[4],len,"\r\n");
	//printf("msg = %s\n",msg);

	send(connfd,ack[0],strlen(ack[0]),0);
	//send(connfd,ack[1],strlen(ack[1]),0);
	send(connfd,ack[2],strlen(ack[2]),0);
	//send(connfd,ack[3],strlen(ack[3]),0);
	send(connfd,ack[4],strlen(ack[4]),0); //要加上这一句，否则网页的图片无法显示

	while(1)
	{
		bzero(msg,sizeof(msg));
		len = fread(msg, 1, 512, fp);

		if(len == 0) break;
		send(connfd, msg, len, 0);
		//printf("_len=%d\n",len);
	}

	fclose(fp);
	close(connfd);
	return NULL;
}

int main(int argc, char *argv[])
{
	unsigned short port = 8033;

	//创建一个监听套接字
	int sockfd  = socket(AF_INET, SOCK_STREAM, 0);

	if(argc > 1)
	{
		port = atoi(argv[1]);
	}

	//让服务器绑定IP和端口
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret != 0)
	{
		perror("bind:");
		exit(-1);
	}

	listen(sockfd, 10);//创建监听队列

	struct sockaddr_in c_addr;
	socklen_t c_addr_len = sizeof(c_addr);

	while(1)
	{
		int connfd = accept(sockfd, (struct sockaddr *)&c_addr, &c_addr_len);
		pthread_t pth;
		pthread_create(&pth, NULL, (void *)server_fun, (void *)&connfd);
		pthread_detach(pth);
	}

	close(sockfd);
	return 0;
}


