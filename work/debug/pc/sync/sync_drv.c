/* ************************************************************************
 *       Filename:  sync_drv.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年11月11日 10时57分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/poll.h>
#include <linux/fcntl.h>
#include <linux/signal.h> //for SIGIO,POLL_IN
#include <linux/timer.h>
#include <linux/jiffies.h>

#define DEVICE_NAME  "sync"

static struct timer_list sync_timer;
static struct fasync_struct *sync_queue;


static void sync_timerhandler(unsigned long arg)
{
	//发送信号到用户空间，通知相关进程
	kill_fasync(&sync_queue, SIGIO, POLL_IN);
	mod_timer(&sync_timer,jiffies + HZ); //更新定时器，不更新的话，定时器处理函数只执行一次
}
	
static int sync_open(struct inode *pinode, struct file *filp)
{
	init_timer(&sync_timer); // 初始化定时器
	sync_timer.data = 0;     // 传递给定时器处理函数的参数
	sync_timer.function = sync_timerhandler; // 定时器处理函数
	sync_timer.expires = jiffies + HZ;
	add_timer(&sync_timer); // 启动定时器
	return 0;
}

static int sync_fasync(int fd, struct file *filp, int mode)
{
	//根据用户空间的需要，获取或设置相应的属性
	return fasync_helper(fd, filp, mode, &sync_queue);
}

static int sync_close(struct inode *pinode, struct file *filp)
{
	del_timer_sync(&sync_timer); // 删除定时器，在定时器时间到前停止一个已注册的定时器
    sync_fasync(-1, filp, 0);    // 将文件从异步通知列表中删除
	return 0;
}

static struct file_operations sync_fops = {
	.owner   = THIS_MODULE,
	.open    = sync_open,
	.fasync  = sync_fasync,
	.release = sync_close,
};

static struct miscdevice sync_misc = { /*杂项字符设备结构体*/
    .minor = MISC_DYNAMIC_MINOR,       /*次设备号 表示自动分配*/
    .name  = DEVICE_NAME,              /*设备名*/
    .fops  = &sync_fops,               /*设备操作*/
};

static __init int sync_init(void)
{
	int ret;

	ret = misc_register(&sync_misc);
	if(ret < 0)
		printk(DEVICE_NAME "can't register\n");
	else
		printk(DEVICE_NAME "register successful\n");
	return ret;
}

static __exit void sync_exit(void)
{
	misc_deregister(&sync_misc);
	printk("unregister success \n");
}

module_init(sync_init);
module_exit(sync_exit);
MODULE_LICENSE("GPL");
