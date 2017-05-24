#ifndef __SNULL_H__
#define __SNULL_H__

#define u8  unsigned short
#define u32 unsigned long

#define SNULL_RX_INTR 0x0001
#define SNULL_TX_INTR 0x0002
#define SNULL_TIMEOUT 5

struct snull_prib {
    int status;
    int rx_packetlen;
    int tx_packetlen;
    unsigned short *rx_packetdata;
    unsigned short *tx_packetdata;

    spinlock_t lock;
    struct sk_buff *skb;
    struct net_device *dev;
    struct net_device_stats stats;
};

#endif
