#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc, char *argv[])
{
	char cmd[] = 
	char ip[16] = "192.168.1.221";
	unsigned short port = 8080;

	if(argc > 1) {
		strcpy(ip, argv[1]);
	}
	//1.����һ������ͨ�ŵ�tcp�׽���
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//2.�����ƶ��ķ�����
	struct sockaddr_in s_addr;
	bzero(&s_addr, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(8080);
	s_addr.sin_addr.s_addr = inet_addr(ip);
	//3.����
	int ret = connect(sockfd, (struct sockaddr *)&s_addr, sizeof(s_addr));
	if(ret != 0)
	{
		perror("connect:");
		exit(-1);
	}

	while(1)
	{
		printf("cmd: ");
		fflush(stdout);

		cmd[strlen(cmd)- 1] = 0; // ȥ�� \n

		
	}
	return 0;
}

