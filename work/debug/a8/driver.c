
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>

#define LED_INPUT	    _IO('i',1)
#define LED_OUTPUT   	_IO('o',2)

static int demo_major = 0;
static struct class *my_class;

static int demo_open(struct inode *pinode, struct file *pfile)
{
	printk("%s:%d\n",__FUNCTION__,__LINE__);
	printk("major:%d,minor:%d\n",imajor(pinode),iminor(pinode));

	return 0;
}
static ssize_t demo_read(struct file *pfile, char __user *buffer, size_t count, loff_t *offset)
{
	char data[] = "this is driver!";
	int ret;
	int len = min(strlen(data),count);
	printk("%s:%d\n",__FUNCTION__,__LINE__);

	ret = copy_to_user(buffer,data,len);
	return len;
}
static ssize_t demo_write(struct file *pfile, const char __user *buffer, size_t count, loff_t *offset)
{
	char data[20];
	int ret;
	int len = min(strlen(data),count);
	printk("%s:%d\n",__FUNCTION__,__LINE__);

	ret = copy_from_user(data,buffer,len);
	printk("%s\n",data);

	if(data[0] == '1'){
		gpio_set_value(S5PV210_GPH0(0), 1); // ¶ÔÓ¦º¯Êý: gpio_get_value(S5PV210_GPH0(0));
		gpio_set_value(S5PV210_GPH0(1), 1);
		gpio_set_value(S5PV210_GPH0(2), 1);
		gpio_set_value(S5PV210_GPH0(3), 1);
	}
	else{
		gpio_set_value(S5PV210_GPH0(0), 0);
		gpio_set_value(S5PV210_GPH0(1), 0);
		gpio_set_value(S5PV210_GPH0(2), 0);
		gpio_set_value(S5PV210_GPH0(3), 0);
	}
	return len;
}
static int demo_release(struct inode *pinode, struct file *pfile)
{
	printk("%s:%d\n",__FUNCTION__,__LINE__);
	return 0;
}
static long demo_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg)
{
	switch(cmd){
	case LED_INPUT:
		s3c_gpio_cfgpin(S5PV210_GPH0(arg),S3C_GPIO_INPUT);
		break;
	case LED_OUTPUT:
		s3c_gpio_cfgpin(S5PV210_GPH0(arg),S3C_GPIO_OUTPUT);
		break;
	default:
		break;
	}
	
	return 0;
}
static struct file_operations demo_fops = {
	.owner = THIS_MODULE,
	.open = demo_open,
	.read = demo_read,
	.write = demo_write,
	.release = demo_release,
	.unlocked_ioctl = demo_ioctl,
};

int __init demo_module_init(void)
{
	int i;
	printk("%s:%d\n",__FUNCTION__,__LINE__);
	demo_major = register_chrdev(demo_major,"char_dev",&demo_fops);
	my_class = class_create(THIS_MODULE,"demo_class");
	for(i=0;i<6;i++)
		device_create(my_class,NULL,MKDEV(demo_major,i),NULL,"demo_char%d",i);
	return 0;
}
void __exit demo_module_exit(void)
{
	int i;
	printk("%s:%d\n",__FUNCTION__,__LINE__);
	for(i=0;i<6;i++)
		device_destroy(my_class,MKDEV(demo_major,i));
	class_destroy(my_class);
	unregister_chrdev(demo_major,"char_dev");
}
module_init(demo_module_init);
module_exit(demo_module_exit);
MODULE_LICENSE("GPL");

