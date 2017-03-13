#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/ether.h>

int main(int argc,char *argv[])
{
	unsigned char buf[1024] = "";
	int sock_raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	while(1)
	{
		unsigned char src_mac[18] = "";
		unsigned char dst_mac[18] = "";
		unsigned char src_ip[16] = "";
		unsigned char dst_ip[16] = "";

		bzero(buf,1024);
		//获取链路层的数据帧
		recvfrom(sock_raw_fd, buf, sizeof(buf),0,NULL,NULL);
		//从buf里提取目的mac、源mac
		sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x", \
		buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
		sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x", \
		buf[6], buf[7], buf[8], buf[9], buf[10], buf[11]);

		//
		sprintf(src_ip, "%u.%u.%u.%u", buf[28],buf[29],buf[30],buf[31]);
		sprintf(dst_ip, "%u.%u.%u.%u", buf[38],buf[39],buf[40],buf[41]);

		//打印源MAC、目的MAC
		printf("MAC:%s >> %s\n", src_mac, dst_mac);
		printf("IP :%s >> %s\n", src_ip, dst_ip);
	}

	return 0;
}
