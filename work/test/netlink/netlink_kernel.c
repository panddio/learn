/*************************************************************************
	> File Name: netlink_kernel.c
	> Author: 
	> Mail: 
	> Created Time: Thu 01 Sep 2016 02:41:47 PM CST
 ************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/netlink.h>
#include <net/sock.h>

#define NETLINK_TEST  17
struct sock *nl_sk = NULL;

void nl_data_ready(struct sock *sk, int len)
{
    wake_up_interruptible(sk->sk_sleep);
}

void test_netlink(void)
{
    struct sk_buff *skb = NULL;
    struct nlmsghdr *nlh = NULL;
    int err;
    unsigned int pid;

    nl_sk = netlink_kernel_create(NETLINK_TEST, nl_data_ready);

    // wait for message coming down from user-space
    skb = skb_recv_datagram(nl_sk, 0, 0, &err);

    nlh = (struct nlmsghdr *)skb->data;
    printk("%s: received netlink message payload: %s\n", __FUNCTION__, (char *)NLMSG_DATA(nlh));

    pid = nlh->nlmsg_pid; // pid of sending process
    NETLINK_CB(skb).groups = 0; // not in mcast group
    NETLINK_CB(skb).pid = 0; //from kernel
    NETLINK_CB(skb).dst_pid = pid;
    NETLINK_CB(skb).dst_groups = 0; // unicast
    netlink_unicast(nl_sk, skb, pid, MSG_DONTWAIT);

    sock_release(nl_sk->sk_socket);
}

int init_module()
{
    test_netlink();
    return 0
}

void cleanup_module()
{

}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
