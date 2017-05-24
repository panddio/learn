/* ************************************************************************
 *       Filename:  leds_drv.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月09日 22时26分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/delay.h> 
#include <linux/ioctl.h> 
#include <linux/cdev.h> 
#include <linux/gpio.h>
#include <linux/device.h>
#include <asm/irq.h> 
#include <mach/regs-gpio.h> 
#include <mach/hardware.h>

#define DEVICE_NAME "leds_drv"

#define LED_ON   0
#define LED_OFF  1


static int majno = 0; //
static struct cdev *p_cdev = NULL;
static struct class *leds_class = NULL;

static unsigned long led_table[] = {
	S3C2410_GPB(5), 
	S3C2410_GPB(6), 
	S3C2410_GPB(7), 
	S3C2410_GPB(8), 
};

static unsigned int led_cfg_table[] =
{
	S3C2410_GPIO_OUTPUT, 
	S3C2410_GPIO_OUTPUT,
	S3C2410_GPIO_OUTPUT,
	S3C2410_GPIO_OUTPUT,
	//S3C2410_GPB5_OUTP,
	//S3C2410_GPB6_OUTP, 
	//S3C2410_GPB7_OUTP, 
	//S3C2410_GPB8_OUTP, 	
};

static int leds_open(struct inode *inode, struct file *filp)
{
	int i;
	
	for(i=0;i<4;i++)
	{
		s3c2410_gpio_cfgpin(led_table[i], led_cfg_table[i]); //要添加#include <linux/gpio.h>
	}
	
	return 0;
}

static int leds_ioctl(struct inode * inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	
	if(arg >= 4)
	{
		return -EINVAL;
	}
	
	switch(cmd)
	{
		case LED_ON:
		{
			s3c2410_gpio_setpin(led_table[arg], 0);
			return 0;
		}
		case LED_OFF:
		{
			s3c2410_gpio_setpin(led_table[arg], 1);
			return 0;
		}
		default:
			return -EINVAL;
	}
}


static struct file_operations leds_fops = 
{
	.owner = THIS_MODULE,
	.open  = leds_open,
	.ioctl = leds_ioctl,
};

static void leds_setup_cdev(struct cdev *dev,int index)
{
	int err;
	dev_t devno = MKDEV(majno, index);
	
	cdev_init(dev, &leds_fops);
	
	dev->owner = THIS_MODULE;
	dev->ops = &leds_fops;	
	
	err = cdev_add(dev, devno, 1);
	
	if(err)
	{
		printk(KERN_NOTICE "Error %d adding leds cdev %d",err,index);
	}	
}
/*
 * 设备初始化函数，在设备加载到内核时调用
 */
static int __init leds_drv_init(void)
{
	int ret;
	dev_t devno = MKDEV(majno,0);
	
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
	
	leds_setup_cdev(p_cdev,0);

	//注册一个类
	leds_class = class_create(THIS_MODULE, DEVICE_NAME);//要添加#include <linux/device.h>

	if(IS_ERR(leds_class))
	{
		printk("Err:failed in create leds class\n");
		goto fail_add_class;
	}
	//创建一个设备节点
	device_create(leds_class,NULL,MKDEV(devno,0),NULL,DEVICE_NAME);	
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
static void __exit leds_drv_exit(void)
{
	cdev_del(p_cdev);
	kfree(p_cdev);  //回收设备结构的内存
	
	device_destroy(leds_class,MKDEV(majno,0));  //删除设备节点
	class_destroy(leds_class); //注销类	
	unregister_chrdev_region(MKDEV(majno,0),1); //释放设备号	
}

module_init(leds_drv_init);
module_exit(leds_drv_exit);

/* 描述驱动程序的一些信息，不是必须的 */
MODULE_AUTHOR("Dawei");                 // 驱动程序的作者
MODULE_DESCRIPTION("A Leds Driver");    // 一些描述信息
MODULE_LICENSE("GPL");                  // 遵循的协议
