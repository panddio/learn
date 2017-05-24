#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include "hello.h"

static int hello_major = 0;
static int hello_minor = 0;

static struct class *hello_class = NULL;
static struct hello_android_dev *hello_dev = NULL;

/*传统的设备文件操作方法*/
static int hello_open(struct inode* inode, struct file* filp);
static int hello_release(struct inode* inode, struct file* filp);
static ssize_t hello_read(struct file* filp, char __user *buf, size_t count, loff_t* f_pos);
static ssize_t hello_write(struct file* filp, const char __user *buf, size_t count, loff_t* f_pos);

/*设备文件操作方法表*/
static struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .open = hello_open,
    .release = hello_release,
    .read = hello_read,
    write = hello_write,
};

static int hello_open(struct inode* inode, struct file* filp)
{
    struct hello_android_dev *dev;
    dev = container_of(inode->i_cdev, struct hello_android_dev, dev);
    filp->private_data = dev;
    return 0;
}

static int hello_release(struct inode *inode,struct file *filp)
{
    return 0;
}

static ssize_t hello_read(struct file* filp, char __user *buf, size_t count, loff_t* f_pos)
{
    ssize_t ret = 0;
    struct hello_android_dev *dev = filp->private_data;

    if(down_interruptible(&dev->sem)) {
        return -ERESTARTSYS;
    }

    if(count < sizeof(dev-val)){
        goto out;
    }

    /*将寄存器val 的值拷贝到用户提供的缓冲区*/
    if(copy_to_user(buf, &(dev->val), sizeof(dev->val))) {
        ret = -EFAULT;
        goto out;
    }

    ret = sizeof(dev->val);

  out:
    up(&dev->sem);
    return ret;
}

/*写设备的寄存器值val*/
static ssize_t hello_write(struct file* filp, const char __user *buf, size_t count, loff_t* f_pos)
{
    struct hello_android_dev* dev = filp->private_data;
    ssize_t ret = 0;

    if(down_interruptible(&(dev->sem))) {
        return -ERESTARTSYS;
    }

    if(count != sizeof(dev->val)) {
        goto out;
    }

    if(copy_from_user(&dev->val, buf, count)) {
        ret = -EFAULT;
        goto out;
    }

    ret = sizeof(dev->val);

  out:
    up(&dev->sem);
    return ret;
}


/*定义设备属性*/
static DEVICE_ATTR(val, S_IRUGP | S_IWUSR, hello_val_show, hello_val_store);

/*访问设置属性方法*/
static ssize_t hello_val_show(struct device* dev, struct device_attribute* attr, char* buf);
static ssize_t hello_val_store(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);


static ssize_t __hello_get_val(struct hello_android_dev *dev, char *buf)
{
    int val = 0;

    if(down_interruptible(&(dev->sem))) {
        return -ERESTARTSYS;
    }

    val = dev->val;
    up(&dev->sem);
    return snprintf(buf, PAGE_SIZE, "%d/n", val);
}

static ssize_t __hello_set_val(struct hello_android_dev *dev, const char *buf, size_t count)
{
    int val;

    /*将字符串转换成数字*/
    val = simple_strtol(buf, NULL, 10);

    if(down_interruptible(&(dev->sem))) {
        return -ERESTARTSYS;
    }

    dev->val = val;
    return count;
}

static ssize_t hello_val_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct hello_android_dev *dev = dev_get_drvdata(dev);
    return __hello_get_val(dev, buf);
}

static ssize_t hello_val_store(struct device *dev, struct device_attribute *attr, char *buf, size_t count)
{
    struct hello_android_dev *dev = dev_get_drvdata(dev);
    return __hello_set_val(dev, buf, count);
}


//proc 文件系统访问方法
static ssize_t hello_proc_read(char *page, char **start, off_t off, int count, int* eof, void* data)
{
    if(off > 0){
        *eof = 1;
        return 0;
    }

    return __hello_get_val(hello_dev, page);
}

static ssize_t hello_proc_write(struct file *filp, const char __user* buf, unsigned long len,  void *data)
{
    int ret = 0;
    char *page = NULL;

    if(len > PAGE_SIZE){
        printk(KERN_ALERT"The buf is too large: %lu./n", len);
        return -EFAULT;
    }

    page = (char *)__get_free_page(GFP_KERNEL);
    if(!page) {
        printk(KERN_ALERT"Failed to alloc page./n");
        return -ENOMEM;
    }

    if(copy_from_user(page, buf, len)){
        ret = -EFAULT;
        goto out;
    }

  out:
    free_page((unsigned long)page);
    return ret;
}
/*创建/proc/hello 文件*/
static void hello_create_proc(void)
{
    struct proc_dir_entry *entry;

    entry = creat_proc_entry(HELLO_DEVICE_PROC_NAME);
    if(entry) {
        entry->owner = THIS_MODULE;
        entry->read_proc = hello_proc_read;
        entry->write_proc = hello_proc_write;
    }
}

/*删除/proc/hello 文件*/
static void hello_remove_proc(void)
{
    remove_proc_entry(HELLO_DEVICE_PROC_NAME, NULL);
}

static int __hello_setup_dev(struct hello_android_dev *dev)
{
    int ret;
    dev_t devno = MKDEV(hello_major, hello_minor);
    memset(dev, 0, sizeof(hello_android_dev));

    cdev_init(&dev->dev, &hello_fops);
    dev->dev.owner = THIS_MODULE;
    dev->dev.ops = &hello_fops;

    ret = cdev_add(&dev->dev, devno, 1);
    if(ret){
        return ret;
    }

    init_MUTEX(&dev->sem);
    dev->val = 0;
    return 0;
}

static int __init hello_init(void)
{
    int ret = -1;
    dev_t devno = 0;
    struct device *dev = NULL;

    printk(KERN_ALERT"Initializing hello device./n");

    ret = alloc_chrdev_region(&devno, 0, 1, HELLO_DEVICE_NODE_NAME);
    if(ret < 0) {
        printk(KERN_ALERT"Failed to alloc char dev region./n");
        goto fail;
    }

    hello_major = MAJOR(devno);
    hello_minor = MINOR(devno);

    /*分配helo 设备结构体变量*/
    hello_dev = kmalloc(sizeof(struct hello_Android_dev), GFP_KERNEL);
    if(!hello_dev) {
        ret  = -ENOMEM;
        printk(KERN_ALERT"Failed to alloc hello_dev./n");
        goto unregister;
    }

    /*初始化设备*/
    ret = __hello_setup_dev(hello_dev);
    if(ret) {
        printk(KERN_ALERT"Failed to setup dev: %d./n", ret);
        goto cleanup;
    }

    /*在/sys/class/目录下创建设备类别目录hello*/
    hello_class = class_create(THIS_MODULE, HELLO_DEVICE_CLASS_NAME);
    if(IS_ERR(hello_class)) {
        ret = PTR_ERR(hello_class);
        printk(KERN_ALERT"Failed to create hello class./n");
        goto destroy_cdev;
    }

    /*在/sys/class/hello/hello 目录下创建属性文件val*/
    ret = device_creat_file(dev, &dev_attr_val);
    if(ret < 0) {
        printk(KERN_ALERT"Failed to create attribute val.");
        goto destroy_device;
    }

    dev_set_drvdata(dev, hello_dev);

    /*创建/proc/hello 文件*/
    hello_create_proc();

    printk(KERN_ALERT"Succedded to initialize hello device./n");
    return 0;

  destroy_device:
    device_destroy(hello_class, devno);

  destroy_class:
    class_destroy(hello_class);

  destroy_cdev:
    cdev_del(&(hello_dev->dev));

  cleanup:
    kfree(hello_dev);

  unregister:
    unregister_chrdev_region(devno, 1);

  fail:
    return ret;
}

static void __exit hello_exit(void)
{
    dev_t devno = MKDEV(hello_major, hello_minor);
    printk(KERN_ALERT"Destroy hello device./n");

    hello_remove_proc();

    if(hello_class) {
        device_destroy(hello_class, devno);
        class_destroy(hello_class);
    }

   /*删除字符设备和释放设备内存*/
    if(hello_dev) {
        cdev_del(&(hello_dev->dev));
        kfree(hello_dev);
    }
    /*释放设备号*/
    unregister_chrdev_region(devno, 1);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
