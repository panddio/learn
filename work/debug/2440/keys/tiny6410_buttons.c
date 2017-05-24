#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/irq.h>  // #define S3C_EINT(x) ((x) + S3C_IRQ_EINT_BASE)   #define IRQ_EINT(x) S3C_EINT(x)
#include<linux/mm.h>
#include<linux/sched.h>
#include<asm/system.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <mach/hardware.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <mach/map.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio-bank-n.h>
#include <mach/gpio-bank-l.h>  //#define S3C64XX_GPLDAT (S3C64XX_GPL_BASE + 0x08)

#define DEVICE_NAME "buttons"
 
struct fasync_struct *async_queue; /*异步结构体指针，用于读*/
 
struct button_irq_desc{
    int irq;
    int number;
    char *name;
};

static struct button_irq_desc button_irqs[] = {
    {IRQ_EINT(0),  0, "KEY0"},
    {IRQ_EINT(1),  1, "KEY1"},
    {IRQ_EINT(2),  2, "KEY2"},
    {IRQ_EINT(3),  3, "KEY3"},
    {IRQ_EINT(4),  4, "KEY4"},
    {IRQ_EINT(5),  5, "KEY5"},
    {IRQ_EINT(19), 6, "KEY6"},
    {IRQ_EINT(20), 7, "KEY7"},
};
static volatile char key_values[] = {'0', '0', '0', '0', '0', '0', '0', '0'};
 
static DECLARE_WAIT_QUEUE_HEAD(button_waitq); /*定义一个新的等待队列的头*/
static volatile int ev_press = 0;             /*判断是否有按键按下的标志位*/
 
static irqreturn_t buttons_interrupt(int irq, void *dev_id) /*中断处理函数*/
{                                                   /*(void *)&button_irqs[i]申请中断时传进来的参数*/
    struct button_irq_desc *button_irqs = (struct button_irq_desc *)dev_id;
    int down;
    int number;
    unsigned tmp;
    udelay(0);
    number = button_irqs->number;
    switch(number) {
        case 0: case 1: case 2: case 3: case 4: case 5:
            tmp = readl(S3C64XX_GPNDAT);  //  
            down = !(tmp & (1<<number));
            break;
        case 6: case 7:
            tmp = readl(S3C64XX_GPLDAT); /*（返回）从映射的I/O空间读取32位4字节的数值 */
            down = !(tmp & (1 << (number + 5)));
            break;
        default:
            down = 0;
    }
     if (down != (key_values[number] & 1)) {
        key_values[number] = '0' + down;
        ev_press = 1;
        wake_up_interruptible(&button_waitq);   /*唤醒阻塞（睡眠）的读等待队列*/

        /*产生异步读信号通知相关进程 把要发送的SIGIO 信号发送出去*/
        if(async_queue){
               kill_fasync(&async_queue, SIGIO, POLL_IN);
         #ifdef DEBUG
               printk("<0>%s kill SIGIO\n", __func__);
         #endif
        }
    }
    /*  //means that we did have a valid interrupt and handled it
     *  #define IRQ_RETVAL(x) ((x) != IRQ_NONE )   //这个宏只是返回0或非0
     */
    return IRQ_RETVAL(IRQ_HANDLED);
}
 
static int s3c64xx_buttons_open(struct inode *inode, struct file *file)
{
    int i;
    int err = 0;
    for (i = 0; i < sizeof(button_irqs)/sizeof(button_irqs[0]); i++) {
        if (button_irqs[i].irq < 0) {
            continue;
        }                 /*中断号            处理函数           双延触发*/
        err = request_irq(button_irqs[i].irq, buttons_interrupt, IRQ_TYPE_EDGE_BOTH,    /*申请中断*/
                button_irqs[i].name, (void *)&button_irqs[i]);
                /*在proc/interrupts中显示中断拥有者   void *dev_id*/
        if (err)
            break;
    }
    if (err) {  /*出错处理 把之前分配的中断释放掉*/
        i--;
        for (; i >= 0; i--) {
            if (button_irqs[i].irq < 0){
                continue;
            }
            disable_irq(button_irqs[i].irq);
            free_irq(button_irqs[i].irq, (void *)&button_irqs[i]);
        }
        return -EBUSY;
    }
    ev_press = 1;
    return 0;
}

static int s3c64xx_buttons_close(struct inode *inode, struct file *file)
{
    int i;
    for (i = 0; i < sizeof(button_irqs)/sizeof(button_irqs[0]); i++) {
        if (button_irqs[i].irq < 0) {
            continue;
        }
        free_irq(button_irqs[i].irq, (void *)&button_irqs[i]);
    }
    return 0;
}

static int s3c64xx_buttons_read(struct file *filp, char __user *buff, size_t count, loff_t *offp)
{
    unsigned long err;
    if (!ev_press) {
        if (filp->f_flags & O_NONBLOCK)
            return -EAGAIN;
        else{
            /*这个宏：使调用进程在等待队上睡眠，一直到修改了给定条件为止*/
            wait_event_interruptible(button_waitq, ev_press);  /*直到ev_press 为 1*/
        }
    }
    ev_press = 0;
    err = copy_to_user((void *)buff, (const void *)(&key_values), min(sizeof(key_values), count));
    return err ? -EFAULT : min(sizeof(key_values), count);
}
 
static unsigned int s3c64xx_buttons_poll( struct file *file, struct poll_table_struct *wait)
{
    unsigned int mask = 0;
    poll_wait(file, &button_waitq, wait);
	if (ev_press){
		mask |= POLLIN | POLLRDNORM; //有键按下 标示数据可以读取
    }
    ev_press = 0;
    return mask;
}
 
/*增加支持异步通知的函数 在release 函数中调用 */
static int misc_key_fasync(int fd, struct file *filp, int mode)
{
    /*将文件从异步通知列表（相关进程列表）中删除*/
     return fasync_helper(fd, filp, mode, &async_queue);
}

/*文件释放函数*/
int misc_key_release(struct inode *inode, struct file *filp)
{
    /*将文件从异步通知列表中删除*/
    misc_key_fasync(-1, filp, 0);
    return 0;
}
 
static struct file_operations dev_fops = {
    .owner   = THIS_MODULE,
    .open    = s3c64xx_buttons_open,
    .release = s3c64xx_buttons_close,
    .read    = s3c64xx_buttons_read,
    .poll    = s3c64xx_buttons_poll,
    .fasync = misc_key_fasync, /*不要忘了在这里也要加上 与内核联系的接口*/
    .release = misc_key_release,
};

static struct miscdevice misc = { /*杂项字符设备结构体*/
    .minor = MISC_DYNAMIC_MINOR,  /*次设备号 表示自动分配*/
    .name  = DEVICE_NAME,         /*设备名*/
    .fops  = &dev_fops,           /*设备操作*/
};
 
static int __init dev_init(void)
{
    int ret;
    ret = misc_register(&misc);             /*注册一个混杂设备 在加载模块时会自动创建设备文件， 为主设备号为10的字符设备*/
    printk(DEVICE_NAME"\tinitialized\n");   /*无需mknod指令创建设备文件。因为misc_register()会调用class_device_create()或者device_create()*/
    return ret;
}

static void __exit dev_exit(void)
{
    misc_deregister(&misc);                 /*注销混杂设备 自动删除设备文件*/
}
 
module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("FriendlyARM Inc.");