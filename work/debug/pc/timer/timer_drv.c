/* ************************************************************************
 *       Filename:  timer.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月07日 19时28分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/timer.h> /*包括timer.h头文件*/
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>

#define DEVICE_NAME "timer_drv"

struct timer_dev
{
	struct cdev timer_cdev;	
	struct timer_list s_timer;
	atomic_t counter;
};

struct timer_dev *p_tdev = NULL;
//dev_t devno; //设备号
//static int majno = 0; //主设备号



//定时器到达expires 时间后，这个函数被调用
static void this_timer_handle(unsigned long arg) 
{
	mod_timer(&p_tdev->s_timer,jiffies + HZ); //更新定时器
	atomic_inc(&p_tdev->counter); //使counter自增
	printk(KERN_NOTICE "current jiffies is %ld\n",jiffies);
}

int this_timer_release(struct inode *inode, struct file *filp)
{
	del_timer(&p_tdev->s_timer);
	return 0;
}

static int timer_open(struct inode *inode, struct file *filp)
{
	//初始化定时器，主要对定时器的下一定时器的地址和此定时器所在结构体进行初始化
	init_timer(&p_tdev->s_timer);
	p_tdev->s_timer.function = this_timer_handle; //设置定时器超时后调度的超时处理函数
	//设置定时器超时的时间，jiffies为当前滴答数，HZ为一秒的滴答数
	p_tdev->s_timer.expires = jiffies + HZ;

	add_timer(&p_tdev->s_timer);    //把定时器添加到定时器链表中
	atomic_set(&p_tdev->counter,0); //计数清零

	return 0;
}

static ssize_t timer_read(struct file *filp,char __user *buf, size_t count,loff_t *ppos)
{
	int counter;
	counter = atomic_read(&p_tdev->counter); //
	if(put_user(counter,(int*)buf))
		return -EFAULT;
	else
		return(sizeof(unsigned int));
}

static struct file_operations timer_fops =
{
	.owner = THIS_MODULE,
	.open = timer_open,
	.read = timer_read,
	.release = this_timer_release,

};

static void timer_setup_cdev(struct timer_dev *dev, int index)
{
	int err;
	//dev_t devno = MKDEV(majno,0);

	cdev_init(&dev->timer_cdev,&timer_fops);
	dev->timer_cdev.owner = THIS_MODULE;
	dev->timer_cdev.ops = &timer_fops;

	//err = cdev_add(&dev->timer_cdev,devno,1);
	err = cdev_add(&dev->timer_cdev,10,1);

	if(err)
	{
		printk(KERN_NOTICE "Error %d adding timer %d",err,index);
	}
}

static struct miscdevice misc =
{
     .minor = MISC_DYNAMIC_MINOR, //表示动态分配次设备号
     .name = DEVICE_NAME,
     .fops = &timer_fops,
};

static int __init timerdrv_init(void)
{
	int ret;

	ret = misc_register(&misc);

	if(ret<0)
	{
        printk(KERN_INFO " can't register timer_drv\n");
        return ret;
	}

	p_tdev = kmalloc(sizeof(struct timer_dev), GFP_KERNEL);

	if(!p_tdev)
	{
		ret = -ENOMEM;
		goto fail_malloc;
	}

	memset(p_tdev, 0, sizeof(struct timer_dev));

	timer_setup_cdev(p_tdev,0);

	printk(KERN_INFO "timer_drv initialized\n");
    return 0;

	fail_malloc:
	misc_deregister(&misc);
	return -1;
}

static void __exit timerdrv_exit(void)
{
	cdev_del(&p_tdev->timer_cdev);//注销cdev
	kfree(p_tdev); //回收设备结构的内存

    misc_deregister(&misc);
    printk(KERN_INFO "timer_drv exited!\n");
}


#if 0
static void timer_setup_cdev(struct timer_dev *dev, int index)
{
	int err;
	dev_t devno = MKDEV(majno,0);

	cdev_init(&dev->timer_cdev,&timer_fops);
	dev->timer_cdev.owner = THIS_MODULE;
	dev->timer_cdev.ops = &timer_fops;

	err = cdev_add(&dev->timer_cdev,devno,1);

	if(err)
	{
		printk(KERN_NOTICE "Error %d adding timer %d",err,index);
	}
}

static int __init timerdev_init(void)
{
	int ret;

	dev_t devno = MKDEV(majno,0);

	if(!majno) //动态申请主设备号
	{
		ret = alloc_chrdev_region(&devno,0,1,DEVICE_NAME);
		majno = MAJOR(devno);
	}
	else
	{
		ret = register_chrdev_region(devno,1,DEVICE_NAME);	
	}
	
	if(ret < 0) return ret;//失败
	
	
	p_tdev = kmalloc(sizeof(struct timer_dev), GFP_KERNEL);
	
	if(!p_tdev)
	{
		ret = -ENOMEM;
		goto fail_malloc;
	}
	
	memset(p_tdev, 0, sizeof(struct timer_dev));
	
	timer_setup_cdev(p_tdev,0);
	
	//注册一个类
	timer_class = class_create(THIS_MODULE, DEVICE_NAME);//要包含#include <linux/device.h>

	if(IS_ERR(timer_class))
	{
		printk("Err:failed in create leds class\n");
		goto fail_add_class;
	}
	//创建一个设备节点
	//device_create(timer_class, NULL, MKDEV(majno, 0), NULL, DEVICE_NAME);
	device_create(timer_class, NULL, devno, NULL, DEVICE_NAME);
	return 0;
	
	fail_malloc:
	unregister_chrdev_region(devno,1);
	return -1;
	
	fail_add_class:
	cdev_del(&p_tdev->timer_cdev);
	kfree(p_tdev);
	unregister_chrdev_region(devno,1);
	return -1;		
}
#endif

module_init(timerdrv_init);
module_exit(timerdrv_exit);

/* 描述驱动程序的一些信息，不是必须的 */
MODULE_AUTHOR("Dawei");                 // 驱动程序的作者
MODULE_DESCRIPTION("A Timer Driver");   // 一些描述信息
MODULE_LICENSE("GPL");                  // 遵循的协议
