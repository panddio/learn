int main(int argc,char *argv[])
{
  //1.创建一个原始套接字
  int raw_fd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
  unsigned char msg[2048]="";
  //1.封装mac头
  unsigned char dst_mac[6]={0x00,0x0c,0x29,0xef,0x4d,0x3d};
  unsigned char src_mac[6]={0x00,0x0c,0x29,0xf5,0xc6,0x39};
  struct ether_header *eth_hdr = NULL;
  eth_hdr = (struct ether_header *)msg;
  memcpy(eth_hdr->ether_dhost,6);
  memcpy(eth_hdr->ether_shost,6);
  ether_hdr->ether_type = htons(0x0800);

  //2.封装ip头
  struct iphdr *ip_hdr =NULL;
  ip_hdr = (struct iphdr *)(msg+14);
  ip_hdr->version =4;
  ip_hdr->ihl=5;
  ip_hdr->tos=0;
  ip_hdr->tot_len = htons(20+ip_data_len);//两个字节的 要htons
  ip_hdr->saddr = inet_addr("10.221.2.16");
  ip_hdr->daddr = inet_addr("");
  ip_hdr->check = htons(0);//????????
  //2.封装udp头部
  struct udphdr *udp_hdr;
  udp_hdr = (struct udphdr *)(msg+14+20);
  udp_hdr->source = htons(8000);
  udp_hdr->dest = htons(8000);
  udp_hdr->len = htons(8+udp_data_len);
  udp_hdr->check=htons(0);//??

  //3.udp数据
  memcpy(msg +14 +20+8,"hehe",strlen("hehe"));
  //4.ip首部校验
  ip->check = htons(checksum(msg+14),20/2);
  //5.0 udp校验
  unsigned char wei_udp[1024]={
        10.221.2.66//源ip
		10.221.2.16//目的ip
		0,17,0,0//长度需要对其赋值&
  }
  *(unsigned short *)(wei_udp+10) = htons(8+strlen("hehe"));//&
  memcpy(wei_udp+12,msg+12+20,8+strlen("hehe"));
  udp_hdr->check = htons(checksum(wei_udp,(12+8+strlen("hehe"))/2));

  sendto();

}
