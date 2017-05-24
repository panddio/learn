#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <asm/uaccess.h>



#define DEVICE_NAME  "virtualchar"
#define MEM_SIZE           0x400  // 1kb
#define VIRTUALCHAR_MAGIC  0x08
#define MEM_CLEAR    _IO(VIRTUALCHAR_MAGIC, 0) // 清零全局内存


static int major = 0;
static struct class *virtualchar_class = NULL;

struct virtualchar_dev
{
	struct cdev cdev;
	unsigned char mem[MEM_SIZE];
};

static struct virtualchar_dev *virtualchar_pdev = NULL; // 设备结构指针

static loff_t virtualchar_llseek(struct file *filp, loff_t offset, int orig)
{
	loff_t ret;

	switch(orig)
	{
		case SEEK_SET: // 从文件开头开始偏移
		{
			if(offset < 0){
				ret = -EINVAL;
				break;
			}
			else if((unsigned int)offset > MEM_SIZE){ // 越界
				ret = -EINVAL;
				break;
			}
			filp->f_pos = offset;
			ret = filp->f_pos;
			break;
		}
		case SEEK_CUR: // 从当前位置开始偏移
		{
			if(filp->f_pos + offset < 0){
				ret = -EINVAL;
				break;
			}
			else if(filp->f_pos + offset > MEM_SIZE){ // 越界
				ret = -EINVAL;
				break;
			}
			filp->f_pos += offset;
			ret = filp->f_pos;
			break;
		}
		case SEEK_END:
		{
			if(offset>0){
				ret = -EINVAL;
				break;
			}
			else if(MEM_SIZE + offset <0){
				ret = -EINVAL;
				break;
			}
			filp->f_pos = MEM_SIZE + offset;
			ret = filp->f_pos;
			break;			
		}
		default:
			ret = -EINVAL;		
	}

	return ret;
}

static int virtualchar_ioctl(struct inode *pinode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ret;
	struct virtualchar_dev *pdev = filp->private_data; // 获取设备结构指针
	
	switch(cmd)
	{
		case MEM_CLEAR:
		{	// 清空全局内存
			memset(pdev->mem, 0, MEM_SIZE);
			printk(KERN_INFO "Virtualchar memory is set to zero\n");
			break;
		}
		default:
			ret = -EINVAL; // 其他不支持命令
	}

	return ret;
}

static int virtualchar_open(struct inode *pinode, struct file *filp)
{
	struct virtualchar_dev *pdev =  NULL;

	pdev = container_of(pinode->i_cdev, struct virtualchar_dev, cdev); // 返回设备结构体的首地址
	// 将设备结构指针赋值给文件私有数据指针
	filp->private_data = pdev;	
	return 0;
}

static ssize_t virtualchar_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
	int ret;
	unsigned long count = size;
	unsigned long pos = *ppos;
	struct virtualchar_dev *pdev = filp->private_data;// 获取设备结构指针

	// 分析和获取有效的读长度
	if(pos >= MEM_SIZE){ // 要读的偏移位置越界
		return count? -ENXIO : 0;
	}
	else if(count > MEM_SIZE - pos){ // 要读的字节数过大
		count = MEM_SIZE - pos;
	}

	// 内核空间 -> 用户空间
	if(copy_to_user(buf, (void *)(pdev->mem + pos), count)){
		ret = -EFAULT;
	}
	else {
		*ppos += count;
		ret = count;

		printk(KERN_INFO "read %lu bytes from %lu\n", count, pos);
	}

	return ret;
}

static ssize_t virtualchar_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
	int ret;
	unsigned long count = size;
	unsigned long pos = *ppos;
	struct virtualchar_dev *pdev = filp->private_data;// 获取设备结构指针

	// 分析和获取有效的写长度
	if(pos >= MEM_SIZE){ // 要写的偏移位置越界
		return count? -ENXIO : 0;
	}
	else if(count > MEM_SIZE - pos){ // 要写的字节数过大
		count = MEM_SIZE - pos;
	}

	// 用户空间 -> 内核空间
	if(copy_from_user((void *)(pdev->mem + pos), buf, count)){
		ret = -EFAULT;
	}
	else {
		*ppos += count;
		ret = count;
		printk(KERN_INFO "written %lu bytes from %lu\n", count, pos);
	}

	return ret;
}

static struct file_operations virtualchar_fops = {
	.owner  = THIS_MODULE,
	.llseek = virtualchar_llseek,
	.ioctl  = virtualchar_ioctl,
	.open   = virtualchar_open,
	.read   = virtualchar_read,
	.write  = virtualchar_write,
};

#if 1
void virtualchar_setup_cdev(struct virtualchar_dev *pdev, int minor)
{
	int err, devno;

	devno = MKDEV(major, minor);

	cdev_init(&pdev->cdev, &virtualchar_fops);
	pdev->cdev.owner = THIS_MODULE;
	pdev->cdev.ops = &virtualchar_fops;

	err = cdev_add(&pdev->cdev, devno, 1);
	if(err){
		printk(KERN_NOTICE "Error %d adding globmem\n", err);
	}
}
#else
void virtualchar_setup_cdev(void)
{
	int err, devno;

	devno = MKDEV(major, 0);

	cdev_init(&virtualchar_dev.cdev, &virtualchar_fops);
	virtualchar_dev.cdev.owner = THIS_MODULE;
	virtualchar_dev.cdev.ops = &virtualchar_fops;

	err = cdev_add(&virtualchar_dev.cdev, devno, 1);
	if(err){
		printk(KERN_NOTICE "Error %d adding globmem\n", err);
	}
}
#endif
int __init virtualchar_init(void)
{
	int ret ,i;
	struct device *virtualchar_device;
	dev_t devno = MKDEV(major, 0);
	if(major){
		ret = register_chrdev_region(devno, 2, DEVICE_NAME);
	}
	else{ // 动态获取设备号
		ret = alloc_chrdev_region(&devno, 0, 2, DEVICE_NAME);
		major = MAJOR(devno);
	}

	if(ret < 0){
		printk("register keys_driver failed!\n");
		return ret;		
	}

	/* 动态申请两个设备结构体的内存 */
	virtualchar_pdev = (struct virtualchar_dev *)kmalloc(2*sizeof(struct virtualchar_dev), GFP_KERNEL);
	if(!virtualchar_pdev){ // 申请失败
		ret = -ENOMEM;
		goto malloc_err;
	}
	
	virtualchar_setup_cdev(&virtualchar_pdev[0], 0);
	virtualchar_setup_cdev(&virtualchar_pdev[1], 1);

	// 注册一个类
	virtualchar_class = class_create(THIS_MODULE, DEVICE_NAME);
	if(IS_ERR(virtualchar_class)){
		printk("Err:failed in create keys class!\n");
		ret = PTR_ERR(virtualchar_class);
		goto class_err;	
	}	

	//创建设备节点
	for(i=0;i<2;i++){
		virtualchar_device = device_create(virtualchar_class, NULL, MKDEV(major, i), NULL, "virtualchar%d", i);
		if(IS_ERR(virtualchar_device)){
			printk("Err:failed in create keys device!\n");
			ret = PTR_ERR(virtualchar_device);
			goto device_err;
		}
	}
	printk("%s:%d\n",__FUNCTION__,__LINE__);
	return 0;

	device_err:
	while(i--){
		device_destroy(virtualchar_class, MKDEV(major, i));
	}
	class_destroy(virtualchar_class);
	class_err:
	cdev_del(&virtualchar_pdev[0].cdev);
	cdev_del(&virtualchar_pdev[1].cdev);
	kfree(virtualchar_pdev);

	malloc_err:
	unregister_chrdev_region(devno, 2);
	return ret;
}

void __exit virtualchar_exit(void)
{
	int i;
	//删除设备节点
	for(i=0;i<2;i++)
		device_destroy(virtualchar_class,MKDEV(major, i));
	
	//注销类
	class_destroy(virtualchar_class); 	
	
	// 删除cdev结构
	cdev_del(&(virtualchar_pdev[0].cdev)); 
	cdev_del(&(virtualchar_pdev[1].cdev));
	kfree(virtualchar_pdev); // 释放设备结构体的内存

	// 注销设备号
	unregister_chrdev_region(MKDEV(major, 0), 2);
	printk("%s:%d\n",__FUNCTION__,__LINE__);
}

module_init(virtualchar_init);
module_exit(virtualchar_exit);
MODULE_LICENSE("GPL");
