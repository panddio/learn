#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/slab.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/gpio_keys.h>
#include <linux/gpio.h>
#include <linux/miscdevice.h> /* struct miscdevice */
#include <jz_notifier.h>

#define PE10_PORT    (GPIO_PE(10))
#define DEVICE_NAME  "pe10_gpio"

#define PE10_IOC_MAGIC     'p'
#define PE10_SET_ON_TIMER  _IO(PE10_IOC_MAGIC, 1) 
#define PE10_SET_OFF_TIMER _IO(PE10_IOC_MAGIC, 2) 



static int flag = 0;
static int on_time = 180 * HZ;
static int off_time = 3 * HZ;

static struct timer_list pe10_timer;

static void pe10_timer_handle(unsigned long arg)
{
	if(flag == 0) {	
		flag = 1;
		gpio_direction_output(PE10_PORT, 0); 
		mod_timer(&pe10_timer,jiffies+off_time);
		printk(KERN_WARNING "[msg]:  output 0 %s\n",__FUNCTION__);
	}
	else {
		flag = 0;
		gpio_direction_output(PE10_PORT, 1); 
		mod_timer(&pe10_timer,jiffies+on_time);	
		printk(KERN_WARNING "[msg]:  output 1 %s\n",__FUNCTION__);
	}

	//printk(KERN_WARNING "[msg]:  %s\n",__FUNCTION__);
}

static int pe10_drv_open(struct inode *inode, struct file *filp)
{
	//pe10_timer.expires = jiffies+on_time;  // 设置定时器的定时时间为on_time秒		
	//add_timer(&pe10_timer);			 // 注册定时器 
	printk(KERN_WARNING "[msg]:  %s\n",__FUNCTION__);
	return 0;
}

static long pe10_drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	
	printk(KERN_WARNING "[msg]:  %s\n",__FUNCTION__);
	
	switch(cmd) {
		case PE10_SET_ON_TIMER:
			if(arg < 1 || arg > 2000)
				ret = EINVAL;
			else {
				on_time = arg * HZ;
				mod_timer(&pe10_timer,jiffies+on_time);
			}
			break;
		case PE10_SET_OFF_TIMER:
			if(arg < 1 || arg > 60)
				ret = EINVAL;
			else {
				off_time = arg * HZ;
				mod_timer(&pe10_timer,jiffies+off_time);
			}
			break;
		default:
			ret = -EINVAL;
	}

	return ret;
}

static int pe10_drv_release(struct inode *inode, struct file *filp)
{	
	//del_timer(&pe10_timer);	
	printk(KERN_WARNING "[msg]:  %s\n",__FUNCTION__);
	return 0;
}

static struct file_operations pe10_fops = {
	.owner   = THIS_MODULE,
	.open    = pe10_drv_open,
	.release = pe10_drv_release,
	.unlocked_ioctl = pe10_drv_ioctl,
};

static struct miscdevice pe10_misc = {
	.minor = MISC_DYNAMIC_MINOR,	
	.name  = DEVICE_NAME,
	.fops  = &pe10_fops,
};

static __init int pe10_drv_init(void)
{
	int ret;

	ret = misc_register(&pe10_misc);	
	
	init_timer(&pe10_timer); 
	pe10_timer.data = 0;                
	pe10_timer.function = pe10_timer_handle;

	// GPIO 申请及初始化
	ret = gpio_request(PE10_PORT, "PE10_DRV PORT");	
	if (ret < 0)  {		
		printk("Failed to request GPIO:%d, ERRNO:%d\n",(int)PE10_PORT, ret);		
		goto err1;	
	}
	gpio_direction_output(PE10_PORT, 1); 
	
	pe10_timer.expires = jiffies+on_time; 	
	add_timer(&pe10_timer);			    
	printk (DEVICE_NAME"\tinitialized\n");
	return 0;
	
err1:
	misc_deregister(&pe10_misc);
	return ret;
}

static __exit void pe10_drv_exit(void)
{
	del_timer_sync(&pe10_timer);
	misc_deregister(&pe10_misc);
	printk(KERN_WARNING "[msg]:  %s\n",__FUNCTION__);
}

module_init(pe10_drv_init);
module_exit(pe10_drv_exit);
MODULE_LICENSE("GPL");

