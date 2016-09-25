/* ************************************************************************
 *       Filename:  libnet_test.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月10日 10时13分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libnet.h>


int main(int argc, char *argv[])
{
	char msg[1024] = "1_lbt6_56#128#7427EAB366CA#0#0#0#4000#9:666666:szb05:SZ-B05:32:";
	char buf[1024] = "";
	char err_buf[100] = "";
	unsigned char dst_mac[6] = {0xec,0xa8,0x6b,0xac,0xcf,0xf9};
	unsigned char src_mac[6] = {0x00,0x0c,0x29,0xe4,0xd3,0xd6};
	char *dst_ip_str = "10.221.2.12";
	char *src_ip_str = "10.221.2.221";

	unsigned long dst_ip, src_ip;
	libnet_t *plib_hdr = NULL;
	libnet_ptag_t ptag1 = 0, ptag2 = 0, ptag3 = 0;

	fgets(buf, sizeof(buf), stdin);
	int len = strlen(buf);
	buf[--len] = 0;
	strcat(msg,buf);
	len = strlen(msg);

	plib_hdr = libnet_init(LIBNET_LINK_ADV, "eth0", err_buf);
	if(NULL == plib_hdr)
	{
		perror("");
		exit(-1);
	}
	src_ip = libnet_name2addr4(plib_hdr, src_ip_str, LIBNET_RESOLVE);
	dst_ip = libnet_name2addr4(plib_hdr, dst_ip_str, LIBNET_RESOLVE);

	ptag1 = libnet_build_udp(2425, 2425, 8+len, 0, msg, len, plib_hdr, 0);
	ptag2 = libnet_build_ipv4(20+8+len,0,0,0,128,17,0,src_ip,dst_ip,NULL,0,plib_hdr,0);
	ptag3 = libnet_build_ethernet((u_int8_t *)dst_mac,(u_int8_t *)src_mac,ETHERTYPE_IP,NULL,0,plib_hdr,0);

	libnet_write(plib_hdr);
	libnet_destroy(plib_hdr);

	return 0;
}
