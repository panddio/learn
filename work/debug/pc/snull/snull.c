#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/in.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/skbuff.h>
#include <linux/in6.h>
#include <asm/checksum.h>
#include "snull.h"

static int lockup = 0;
module_param(lockup, int, 0);
static int timeout = SNULL_TIMEOUT;
module_param(timeout, int, 0);
struct net_device snull_devs[2];

int snull_open(struct net_device *dev)
{
    //将硬件（MAC）从硬件设备复制到dev->dev_addr
    memcpy(dev->dev_addr, "\0SNUL0", ETH_ALEN);
    if(dev == snull_devs[1])
        dev->dev_addr[ETH_ALEN - 1]++; /* \0SNUL1 */

    netif_start_queue(dev);//启动接口的传输队列，允许接口接受传输包
    return 0;
}

int snull_release(struct net_device *dev)
{
    netif_stop_queue(dev);//在接口被关闭时，必须调用该函数，但该函数也可以用来临时停止传输。
    return 0;
}

int snull_config(struct net_device *dev, struct ifmap *map)
{
    if(dev->flags & IFF_UP)
        return -EBUSY;
    if(map->base_addr != dev->base_addr) {
        printk(KERN_WARNING "snull: Can't change I/O address\n");
        return -EOPNOTSUPP;
    }

    if(map->irq != dev->irq)
        dev->irq = map->irq;

    return 0;
}

void snull_rx(struct net_device *dev, int len, unsigned char *buf)
{
    struct sk_buff *skb;
    struct snull_priv *prvi = netdev_priv(dev);

    skb = dev_alloc_skb(len + 2);//分配一个保存数据包的缓冲区
    if(!skb) {
        printk("snull rx: low on mem - packet dropped\n");
        priv->stats.rx_dropped++;
        return;
    }

    skb_reserve(skb, 2);
    memcpy(skb_put(skb, len), buf, len);//skb_put函数刷新缓冲区内的数据末尾指针，并且返回新创建数据区的指针
    skb->dev = dev;
    skb->protocol = eth_type_trans(skb, dev);
    skb->ip_summed = CHECKSUM_UNNECESSARY;
    priv->stats.rx_packets++;
    priv->stats.rx_bytes += len;
    netif_rx(skb);//将套接字缓冲区传递给上层软件处理
    return;
}

void snull_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
    int statusword;
    struct net_device *dev = (struct net_device *)dev_id;
    struct snull_priv *priv = netdev_priv(dev);

    if(!dev)
        return;
    spin_lock(&priv->lock);
    statusword = priv->status;
    priv->status = 0;

    if(statusword & SNULL_RX_INTR)
        snull_rx(dev, priv->rx_packetlen, priv->rx_packetdata);

    if(statusword & SNULL_TX_INTR) {
        priv->stats.tx_packets++;
        priv->stats.tx_bytes += priv->tx_packetlen;
        dev_kfree_skb(priv->skb);
    }
    spin_unlock(&priv->lock);

    return;
}

void snull_tx_timeout(struct net_device *dev)
{
    struct snull_priv = netdev_priv(dev);
    printk(KERN_INFO"Transmit timeout at %ld, latency %ld\n", jiffies,jiffies - dev->trans_start);

    priv->status = SNULL_TX_INTR;
    snull_interrupt(0, dev, NULL); // 模拟一个传输中断
    priv->stats.tx_errors++;
    netif_wake_queue(dev);
    return;
}

void snull_hw_tx(char *buf, int len, struct net_device *dev)
{
    struct iphdr *ih;
    struct net_device *dest;
    struct snull_priv *priv = netdev_priv(dev);
    unsigned long *saddr, *daddr;

    if(len < sizeof(struct ethhdr) + sizeof(struct ipdhr)){
        printk("snull: Hmm... packet too short (%i octets)\n", len);
        return;
    }

    ih = (struct iphdr *)(buf + sizeof(struct iphdr));
    saddr = &ih->saddr;
    daddr = &ih->daddr;

    ((u8 *)saddr)[2] ^= 1;
    ((u8 *)daddr)[2] ^= 1;

    ih->check = 0;
    /* 重新计算ip校验和，正常情况下还应该重新计算tcp头校验和，icmp头检验和.. */
    ih->check = ip_fast_csum((u8 *)ih, ih->ihl);

    if(dev == snull_devs[0])
        printk(KERN_INFO"%08x:%05i --> %08x:%05i\n",
               ntohl(ih->saddr),ntohs(((struct tcphdr *)(ih+1))->source),
               ntohl(ih->daddr),ntohs(((struct tcphdr *)(ih+1))->dest));
    else
        printk(KERN_INFO"%08x:%05i <-- %08x:%05i\n",
               ntohl(ih->daddr),ntohs(((struct tcphdr *)(ih+1))->dest),
               ntohl(ih->saddr),ntohs(((struct tcphdr *)(ih+1))->source));

    dest = snull_devs[dev == snull_devs[0] ? 1 : 0];
    priv->status = SNULL_RX_INTR;
    priv->rx_packetlen = len;
    priv->rx_packetdata = buf;
    snull_interrupt(0, dest, NULL); // 产生中断--->接收

    priv->status = SNULL_TX_INTR;
    priv->tx_packetlen = len;
    priv->tx_packetdata = buf;

    if (lockup && ((priv->stats.tx_packets + 1) % lockup) == 0) {
        netif_stop_queue(dev);
        printk(KERN_INFO"Simulate lockup at %ld, txp %ld\n", jiffies,(unsigned long) priv->stats.tx_packets);
    }
    else
        snull_interrupt(0, dev, NULL);// 产生中断--->发送

    return;
}

int snull_tx(struct sk_buff *skb, struct net_device *dev)
{
    int len;
    chat *data, shortpkt[ETH_ZLEN];
    struct snull_priv *priv = netdev_priv(dev);

    data = skb->data;
    len =skb->len;
    if(len < ETH_ZLEN) {
        memset(shortpkt, 0, ETH_ZLEN);
        memcpy(shortpkt, skb->data, len);
        data = shortpkt;
    }

    dev->trans_start = jiffies; //保存时间
    priv->sbk = skb;            //记住skb，以便释放
    snull_hw_tx(data, len, dev);//硬件相关的传输函数

    return 0;
}

int snull_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
    return 0;
}

struct net_device_stats *snull_stats(struct net_device *dev)
{
    struct snull_priv = netdev_priv(dev);
    return &priv->stats;
}

int snull_rebuild_header(struct sk_buff *skb)
{
    struct ethhdr *eth = (struct ethhdr *)skb->data;
    struct net_device *dev = skb->dev;

    memcpy(eth->h_source, dev->dev_addr, dev->addr_len);
    memcpy(eth->h_dest, dev->dev_addr, dev->addr_len);
    eth->h_dest[ETH_ALEN - 1] ^= 0x01;
    return 0;
}

int snull_header(struct sk_buff *skb, struct net_device *dev,
                 unsigned short type, const void *daddr, const void *saddr,
                 unsigned int len)
{
    struct ethhdr *eth = (struct ethhdr *)skb_push(skb, ETH_HLEN);

    eth->h_proto = htons(type);
    memcpy(eth->h_source, saddr?saddr:dev->dev_addr, dev->addr_len);
    memcpy(eth->h_dest, daddr?daddr:dev->dev_addr, dev->addr_len);
    eth->h_dest[ETH_ALEN - 1] ^= 0x01;

    return (dev->hard_harder_len);
}

int snull_change_mtu(struct net_device *dev, int new_mtu)
{
    unsigned long flags;
    struct snull_priv *priv = netdev_priv(dev);
    spinlock_t *lock = &priv->lock;

    if((new_mtu < 68) || (new_mtu > 1500)) //以太网的MTU是1500个octet（ETH_DATA_LEN）
        return -EINVAL;
    spin_lock_irqsave(lock, flags);
    dev->mtu = new_mtu;
    spin_unlock_irqsave(lock, flags);
    return 0;
}

//以下两个结构是相关接口函数的初始化
static const struct net_device_ops snull_dev_ops = {
    .ndo_open       = snull_open,
    .ndo_stop       = snull_release,
    .ndo_set_config = snull_config,
    .ndo_start_xmit = snull_tx,
    .ndo_do_ioctl   = snull_ioctl,
    .ndo_get_stats  = snull_stats,
    .ndo_change_mtu = snull_change_mtu,
    .ndo_tx_timeout = snull_tx_timeout,
};

static const struct header_ops snull_header_ops = {
    .creat   = snull_header,
    .rebuild = snull_rebuild_header,
    .cache   = NULL,
};

static void snull_init_netdev(struct net_device *dev)
{
    struct snull_priv *priv = NULL;

    ether_setup(dev);//对某些成员作一些初始化
    dev->netdev_ops = &snull_dev_ops;
    dev->header_ops = &snull_header_ops;
    dev->watchdog_timeo = timeout;
    dev->flags |= IFF_NOARP;    //禁止ARP
    dev->features |= NETIF_F_NO_CSUM;

    priv = netdev_priv(dev);//priv是net_device中的一个成员，它与net_device一起被分配，当需要访问私有成员priv时使用该函数
    memset(priv, 0, sizeof(struct snull_priv));
    priv->dev = dev;
    spin_lock_init(&priv->lock);
    return;
}

static __init int snull_init(void)
{
    int ret, i;

    snull_devs[0] = alloc_netdev(sizeof(struct snull_priv), "sn%d", snull_init_netdev);
    snull_devs[1] = alloc_netdev(sizeof(struct snull_priv), "sn%d", snull_init_netdev);

    if(snull_devs[0] == NULL || snull_devs[1] == NULL) {
        for(i = 0; i < 2; i++) {
            if(snull_devs[i] != NULL)
                free_netdev(snull_devs[i]);    //将net_device结构返还给系统
        }
        goto fail0;
    }

    for(i = 0; i < 2; i++) {
        //注册设备，必须在初始化一切事情后再注册
        ret = register_netdev(snull_devs[i]);
        if(ret) {
            printk("snull: error %i registering device \"%s\"\n",result, snull_devs[i]->name);
            break;
        }
    }

    if(i != 2) {
         while(i >= 0)
            unregister_netdev(snull_devs[i]);    //从系统中删除接口
         goto fail1
    }

    return 0;
fail1:
    free_netdev(snull_devs[0]);
    free_netdev(snull_devs[1]);
fail0:
    return -ENODEV;
}

static __exit void snull_exit(void)
{
    int i;
    for(i=0; i<2;i++) {
        if(snull_devs[i]) {
            unregister_netdev(snull_devs[i]); //从系统中删除接口
            free_netdev(snull_devs[i]); //将net_device结构返还给系统
        }
    }
    return;
}

module_init(snull_init);
module_exit(snull_exit);

MODULE_VERSION("snull_v1.0");
MODULE_LICENSE("GPL");