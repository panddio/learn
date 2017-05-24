/* ************************************************************************
 *       Filename:  buttons_drv.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月16日 18时40分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/sched.h>
#include <linux/gpio.h>
#include <linux/timer.h>
#include <asm/irq.h>
#include <asm/uaccess.h>
#include <mach/regs-gpio.h>
#include <mach/hardware.h>

#define DEVICE_NAME          "buttons_drv"
#define TIME_DELAY_20MS      (HZ/50)         //按键按下去抖延时
#define TIME_DELAY_50MS      (HZ/20)         //按键松开去抖延时
#define KEY_DOWN             0               //按键按下
#define KEY_UP               1               //按键松开
#define KEY_UNCERTAIN        2               //按键不确定
#define KEY_COUNT            6

static volatile int ev_press = 0;             //按键按下状态标志
static volatile int key_status[KEY_COUNT];    //记录按键的状态
static struct timer_list key_timers[KEY_COUNT];//定义6个按键去抖定时器
static DECLARE_WAIT_QUEUE_HEAD(buttons_waitq);//定义并初始化等待队列

static int majno = 0; //主设备号
static struct cdev *p_cdev = NULL;
static struct class *keys_class = NULL;

struct key_irq_desc
{
	int irqno;   //中断号
	int pin;     //引脚
	int pin_cfg; //引脚配置
	char *name;  //中断设备名称
};

static struct key_irq_desc keys_irq[] =
{
    {IRQ_EINT8 , S3C2410_GPG(0) ,  S3C2410_GPG0_EINT8  , "KEY0"},
    {IRQ_EINT11, S3C2410_GPG(3) ,  S3C2410_GPG3_EINT11 , "KEY1"},
    {IRQ_EINT13, S3C2410_GPG(5) ,  S3C2410_GPG5_EINT13 , "KEY2"},
    {IRQ_EINT14, S3C2410_GPG(6) ,  S3C2410_GPG6_EINT14 , "KEY3"},
    {IRQ_EINT15, S3C2410_GPG(7) ,  S3C2410_GPG7_EINT15 , "KEY4"},
    {IRQ_EINT19, S3C2410_GPG(11),  S3C2410_GPG11_EINT19, "KEY5"},
};


static irqreturn_t key_interrupt(int irq, void *dev_id)
{
	//获取哪个按键被按下
	int key_id = (int)dev_id;

	if(key_status[key_id] == KEY_UP)
	{
		key_status[key_id] = KEY_UNCERTAIN; //设置当前按键状态为不确定

		//设置去抖延时时间为20MS，并启动定时器
		key_timers[key_id].expires = jiffies + TIME_DELAY_20MS;
		add_timer(&key_timers[key_id]); //定时器到时之后会调用定时器的回调函数进一步处理
	}

	return IRQ_RETVAL(IRQ_HANDLED);
}

static void timer_callback(unsigned long arg)
{
	//获取哪个按键被按下
	int key_id = arg;
	int status = s3c2410_gpio_getpin(keys_irq[key_id].pin); //获取按键状态

	if( !status ) //低电平， 按键按下
	{
		if(key_status[key_id] == KEY_UNCERTAIN)
		{
			key_status[key_id] = KEY_DOWN;

			s3c2410_gpio_setpin(keys_irq[key_id].pin, 1);
			ev_press = 1; //确定有按键被按下
			wake_up_interruptible(&buttons_waitq);//唤醒等待队列
		}

		//设置按键抬起去抖延时
		key_timers[key_id].expires = jiffies + TIME_DELAY_50MS;
		add_timer(&key_timers[key_id]);
	}
}

static int buttons_open(struct inode *inode, struct file *file)
{
	int i, ret;

	for(i=0;i<KEY_COUNT;i++)
	{
		//配置I/O的模式为中断
		s3c2410_gpio_cfgpin(keys_irq[i].pin, keys_irq[i].pin_cfg);

		//配置下降沿触发中断
		set_irq_type(keys_irq[i].pin, IRQ_TYPE_EDGE_FALLING);

		ret = request_irq(keys_irq[i].irqno, key_interrupt, IRQF_DISABLED, keys_irq[i].name, (void *)i);

		if(ret)	break; //申请中断成功返回 0

		key_status[i] = KEY_UP;

		//初始化并设置各个按键的去抖定时器
		key_timers[i].function = timer_callback;  //注册定时器的到时处理函数
		key_timers[i].data = i;                   //传递给到时处理函数的参数
		init_timer(&key_timers[i]);                //初始化定时器
	}

	if(ret) //中断申请失败
	{
		i--;

		for(; i >= 0; i--)
		{   //释放注册成功的中断
			disable_irq(keys_irq[i].irqno);
			free_irq(keys_irq[i].irqno, (void *)i);
		}

		return -EBUSY;
	}

	return 0;
}

static ssize_t buttons_read(struct file *filp,char __user *buf, size_t count,loff_t *ppos)
{
	unsigned long ret;

	if(!ev_press) //没有按键被按下
	{
		if(filp->f_flags & O_NONBLOCK)
		{
			//若应用程序采用非阻塞方式读取，则返回
			return -EAGAIN; //提示用户再尝试读
		}
		else
		{
			//以阻塞方式读取且按键没被按下，则让等待队列进入休眠
			wait_event_interruptible(buttons_waitq, ev_press);
		}
	}

	ev_press = 0; //已有按键按下，重置此标志

	ret = copy_to_user(buf, (void *)key_status, min(sizeof(key_status), count));

	memset((void *)key_status, 0, sizeof(key_status));

	return ret ? -EFAULT :  min(sizeof(key_status), count); //返回用户成功读取的字节数
}

static int buttons_close(struct inode *inode,struct file *file)
{
	int i;

	//释放定时器和中断
	for(i=0; i < KEY_COUNT; i++)
	{
		del_timer(&key_timers[i]);

		disable_irq(keys_irq[i].irqno);
		free_irq(keys_irq[i].irqno, (void *)i);
	}
	return 0;
}

static unsigned int buttons_poll(struct file *file, struct poll_table_struct *wait)
{
	unsigned int mask = 0;

	//添加 等待队列 到 等待队列表中
	poll_wait(file, &buttons_waitq, wait);

	if(ev_press) //按键被按下
	{
		mask |= POLLIN | POLLRDNORM; //表示数据可以获取
	}

	return mask;
}

static struct file_operations buttons_fops =
{
	.owner   = THIS_MODULE,
	.open    = buttons_open,
	.read    = buttons_read,
	.release = buttons_close,
	.poll    = buttons_poll,
};

static void buttons_setup_cdev(struct cdev *dev,int index)
{
	int err;
	dev_t devno = MKDEV(majno, index);

	cdev_init(dev, &buttons_fops);

	dev->owner = THIS_MODULE;
	dev->ops = &buttons_fops;

	err = cdev_add(dev, devno, 1);

	if(err)
	{
		printk(KERN_NOTICE "Error %d adding keys cdev %d",err,index);
	}
}

static int __init buttons_init(void)
{
	int ret;
	dev_t devno = MKDEV(majno,0);

	//初始化硬件I/O

	if(!majno)
	{
		ret = alloc_chrdev_region(&devno,0,1,DEVICE_NAME);
		majno = MAJOR(devno);
	}
	else
	{
		ret = register_chrdev_region(devno,1,DEVICE_NAME);
	}

	if(ret < 0)
	{
		return ret;
	}

	p_cdev = kmalloc(sizeof(struct cdev), GFP_KERNEL);

	if(!p_cdev)
	{
		ret = -ENOMEM;
		goto fail_malloc;
	}

	memset(p_cdev, 0, sizeof(struct cdev));

	buttons_setup_cdev(p_cdev,0);

	//注册一个类
	keys_class = class_create(THIS_MODULE, DEVICE_NAME);//要添加#include <linux/device.h>

	if(IS_ERR(keys_class))
	{
		printk("Err:failed in create keys class\n");
		goto fail_add_class;
	}
	//创建一个设备节点
	device_create(keys_class,NULL,MKDEV(devno,0),NULL,DEVICE_NAME);
	return 0;

	fail_malloc:
	unregister_chrdev_region(devno,1);
	return -1;

	fail_add_class:
	cdev_del(p_cdev);
	kfree(p_cdev);
	unregister_chrdev_region(devno,1);
	return -1;
}
/*
 * 设备的注销函数，在设备从内核卸载时调用
 *
 */
static void __exit buttons_exit(void)
{
	device_destroy(keys_class,MKDEV(majno,0));  //删除设备节点
	class_destroy(keys_class); //注销类
	cdev_del(p_cdev);
	kfree(p_cdev);  //回收设备结构的内存
	unregister_chrdev_region(MKDEV(majno,0),1); //释放设备号
}

module_init(buttons_init);
module_exit(buttons_exit);

/* 描述驱动程序的一些信息，不是必须的 */
MODULE_AUTHOR("Dawei");                 // 驱动程序的作者
MODULE_DESCRIPTION("A buttons Driver");   // 一些描述信息
MODULE_LICENSE("GPL");                  // 遵循的协议
