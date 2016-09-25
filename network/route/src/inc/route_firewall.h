/******************************************************************************
  �� �� ��   : route_firewall.h
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��14��
  ����޸�   :
  ��������   : route_firewall.c ��ͷ�ļ�
******************************************************************************/
#ifndef __ROUTE_FIREWALL_H__
#define __ROUTE_FIREWALL_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

//static Boolean check_input_rules();
static int firewall_filt_ip(TYPE_Route *rt, MSG_Info *pinfo);
static int firewall_filt_mac(TYPE_Route *rt, MSG_Info *pinfo);
static int firewall_filt_port(TYPE_Route *rt, MSG_Info *pinfo);
static int firewall_filt_protocol(TYPE_Route *rt, MSG_Info *pinfo);

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/
extern void firewall_rule_set_help(void);
extern void firewall_build_rule(TYPE_Route *rt, const char *rule, char flag);
extern void delete_firewall_rule(TYPE_Route *rt, const char *rule);
extern int firewall_filt(TYPE_Route *rt, MSG_Info *pinfo);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

/*****************************************************************************
                      >>>  ����ǽ���������ʽ  <<<
ip src 10.221.2.1
ip dst 10.221.2.1
ip host 10.221.2.1

mac src 01:02:03:04:05:06
mac dst 01:02:03:04:05:06
mac host 01:02:03:04:05:06

port src 8000
port dst 8000
port 8000

tcp ip src 10.221.2.1
tcp port dst 8000
tcp port 8000

arp
tcp 
udp 
icmp
igmp
http
tftp
*****************************************************************************/

#endif /* __ROUTE_FIREWALL_H__ */
