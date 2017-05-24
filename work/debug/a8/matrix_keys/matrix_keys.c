#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include <linux/slab.h>   // kmalloc() kfree()
#include <linux/delay.h>   // mdelya() msleep()
#include <asm/io.h>
#include <asm/uaccess.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>


#define DEVICE_NAME   "keys_drv"


static int keys_major = 0;
static struct class *keys_class = NULL;
static struct cdev *pcdev = NULL;



static int keys_drv_open(struct inode *pindo, struct file *filp)
{
	printk("%s:%d\n",__FUNCTION__,__LINE__);

	// ��������Ϊ���
	s3c_gpio_cfgpin(S5PV210_GPH3(0), S3C_GPIO_OUTPUT);
	s3c_gpio_cfgpin(S5PV210_GPH3(1), S3C_GPIO_OUTPUT);

	//s3c_gpio_setpin(S5PV210_GPH3(0), 0);
	gpio_set_value(S5PV210_GPH3(0), 0);
	gpio_set_value(S5PV210_GPH3(1), 1);

	s3c_gpio_cfgpin(S5PV210_GPH2(3), S3C_GPIO_INPUT);
	s3c_gpio_cfgpin(S5PV210_GPH2(4), S3C_GPIO_INPUT);
	s3c_gpio_cfgpin(S5PV210_GPH2(5), S3C_GPIO_INPUT);
	s3c_gpio_cfgpin(S5PV210_GPH2(6), S3C_GPIO_INPUT);
	s3c_gpio_cfgpin(S5PV210_GPH2(7), S3C_GPIO_INPUT);

	s3c_gpio_setpull(S5PV210_GPH2(3), S3C_GPIO_PULL_UP);
	s3c_gpio_setpull(S5PV210_GPH2(4), S3C_GPIO_PULL_UP);
	s3c_gpio_setpull(S5PV210_GPH2(5), S3C_GPIO_PULL_UP);
	s3c_gpio_setpull(S5PV210_GPH2(6), S3C_GPIO_PULL_UP);
	s3c_gpio_setpull(S5PV210_GPH2(7), S3C_GPIO_PULL_UP);


	printk("%s:%d\n",__FUNCTION__,__LINE__);
	return 0;
}


static ssize_t keys_drv_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	char data[] = {0};
	int i, keyval;
	int len, ret;

	volatile unsigned char *gph2dat = NULL;
	gph2dat = ioremap(0xe0200c44, 1); // 0xe0200c44 ��GPH2DAT �ĵ�ַ

	for(i=0; i<10; i++){ // ����ɨ��
		gpio_set_value(S5PV210_GPH3(0), 0);
		gpio_set_value(S5PV210_GPH3(1), 1);

		keyval = *gph2dat;
		keyval &= 0xf8;

		if(keyval != 0xf8){ //
			msleep(100);
			//mdelay(100); // ��ʱ����
			keyval = *gph2dat;
			keyval &= 0xf8;

			if(keyval != 0xf8){

				switch(keyval){

				case 0xf0: // key2
					data[0] = 2;
					goto out;
					break;

				case 0xe8: // key3
					data[0] = 3;
					goto out;
					break;

				case 0xd8: // key4
					data[0] = 4;
					goto out;
					break;

				case 0xb8: // key5
					data[0] = 5;
					goto out;
					break;

				case 0x78: // key6
					data[0] = 6;
					goto out;
					break;
				}
			}

			// �ȴ������ͷ�
			while(keyval != 0xf8){
				keyval = *gph2dat;
				keyval &= 0xf8;
			}
		}

		// ɨ��ڶ���
		gpio_set_value(S5PV210_GPH3(0), 1);
		gpio_set_value(S5PV210_GPH3(1), 0);

		keyval = *gph2dat;
		keyval &= 0xf0;

		if(keyval != 0xf0){ //
			msleep(100);
			//mdelay(100); // ��ʱ����
			keyval = *gph2dat;
			keyval &= 0xf0;

			if(keyval != 0xf0){

				switch(keyval){

				case 0xe0: // key8
					data[0] = 8;
					goto out;
					break;

				case 0xd0: // key9
					data[0] = 9;
					goto out;
					break;

				case 0xb0: // key10
					data[0] = 10;
					goto out;
					break;

				case 0x70: // key11
					data[0] = 11;
					goto out;
					break;
				}
			}

			// �ȴ������ͷ�
			while(keyval != 0xf0){
				keyval = *gph2dat;
				keyval &= 0xf0;
			}
		}
	}

	out:
	len = min(sizeof(data), count);
	ret = copy_to_user(buf, data, len); // ���ز��ܱ����Ƶ��ֽ���
	return len;
}

static int keys_drv_release(struct inode *pinode, struct file *filp)
{
	printk("%s:%d\n",__FUNCTION__,__LINE__);
	return 0;
}


static struct file_operations keys_drv_fops = {
	.owner   = THIS_MODULE,
	.open    = keys_drv_open,
	.read    = keys_drv_read,
	.release = keys_drv_release,
};

static void keys_setup_cdev(struct cdev *pcdev, int index)
{
	int err;

	dev_t devno = MKDEV(keys_major, index);

	cdev_init(pcdev, &keys_drv_fops);
	pcdev->owner = THIS_MODULE;
	pcdev->ops = &keys_drv_fops;

	err = cdev_add(pcdev, devno, 1);

	if(err){
		printk(KERN_NOTICE "Error %d adding keys cdev %d",err,index);
	}
}

int __init keys_drv_init(void)
{
    int ret;

	dev_t devno = MKDEV(keys_major, 0);

	if(!keys_major){ // ��̬��ȡ�豸��
		ret = alloc_chrdev_region(&devno, 0, 1, DEVICE_NAME);
		keys_major = MAJOR(devno);
	}
	else{
		ret = register_chrdev_region(devno, 1, DEVICE_NAME);
	}

	if(ret < 0){ // ע��ʧ��
		printk("register keys_driver failed!\n");
		return ret;
	}

	pcdev = kmalloc(sizeof(struct cdev), GFP_KERNEL);
	if(pcdev == NULL){
		printk("kmalloc failed!\n");
		ret = -ENOMEM;
		goto malloc_err;
	}

	memset(pcdev, 0, sizeof(struct cdev));
	keys_setup_cdev(pcdev, 0);

	// ע��һ����
	keys_class = class_create(THIS_MODULE, DEVICE_NAME);
	if(IS_ERR(keys_class)){
		printk("Err:failed in create keys class\n");
		goto class_err;
	}

	//����һ���豸�ڵ�
	device_create(keys_class, NULL, devno, NULL, DEVICE_NAME);
	printk("%s:%d\n",__FUNCTION__,__LINE__);
	return 0;

	class_err:
	cdev_del(pcdev);
	kfree(pcdev);

	malloc_err:
	unregister_chrdev_region(devno, 1);
	return ret;
}

void __exit keys_drv_exit(void)
{
	device_destroy(keys_class, MKDEV(keys_major, 0));// ɾ���豸�ڵ�
	class_destroy(keys_class); //ע����
	cdev_del(pcdev); // ע���豸
	kfree(pcdev);    // �����ڴ�
	unregister_chrdev_region(MKDEV(keys_major, 0), 1);// ע���豸��
	printk("%s:%d\n",__FUNCTION__,__LINE__);
}

module_init(keys_drv_init);
module_exit(keys_drv_exit);
MODULE_LICENSE("GPL");
