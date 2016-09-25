/* ************************************************************************
 *       Filename:  pcap_test.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月09日 16时13分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <pcap.h>

#if 0
void my_callback(u_char *user, const struct pcap_pkthdr *hdr, const u_char *msg)
{
	printf("user=%s\n", user);

	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",\
			msg[6],msg[7],msg[8],msg[9],msg[10],msg[11]);

	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",\
			msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
}

int main(int argc, char *argv[])
{
	char err_buf[100] = "";
	//1.打开网络句柄
	pcap_t *p_fd = pcap_open_live("eth0",2048,0,0,err_buf);

	//2.过滤网络数据
	//2.1编译过滤规则
	//struct bpf_program bpf_p;
	//pcap_compile(p_fd,&bpf_p,"udp port 8000", 0, 0xffffff00);

	//2.2设置过滤规则
	//pcap_setfilter(p_fd, &bpf_p);

	struct pcap_pkthdr p_hdr;
	const u_char *msg = NULL;

	pcap_loop(p_fd, -1, my_callback, (u_char *)"haha");

	pcap_close(p_fd);

	return 0;
}
#elif 0
void my_callback(u_char *msg, const struct pcap_pkthdr *hdr, const u_char *user)
{
	printf("user=%s\n", user);

	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",\
			msg[6],msg[7],msg[8],msg[9],msg[10],msg[11]);

	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",\
			msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
}

int main(int argc, char *argv[])
{
	char err_buf[100] = "";
	//打开网络句柄
	pcap_t *p_fd = pcap_open_live("eth0",2048,0,0,err_buf);

	struct pcap_pkthdr p_hdr;
	const u_char *msg = NULL;

	pcap_loop(p_fd, -1, my_callback, (u_char *)"haha");

	pcap_close(p_fd);

	return 0;
}
#elif 1

int main(int argc, char *argv[])
{
	char err_buf[100] = "";

	pcap_t *p_fd = pcap_open_live("eth0",2048,0,0,err_buf);

	struct pcap_pkthdr p_hdr;
	const u_char *msg = NULL;
	msg = pcap_next(p_fd, &p_hdr);

	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",\
			msg[6],msg[7],msg[8],msg[9],msg[10],msg[11]);

	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",\
			msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);

	pcap_close(p_fd);
	return 0;
}
#elif 0
int main(int argc, char *argv[])
{
	char err_buf[100] = "";
	char *dev = NULL;

	dev = pcap_lookupdev(err_buf);

	printf("dev=%s\n",dev);

	return 0;
}
#endif
