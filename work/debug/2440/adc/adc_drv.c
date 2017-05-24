/* ************************************************************************
 *       Filename:  adc_drv.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年10月30日 16时00分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <linux/kernel.h>  /* 提供prink等内核特有属性 */  
#include <linux/module.h>  /* 提供如MODULE_LICENSE()、EXPORT_SYMBOL() */  
#include <linux/init.h>    /* 设置段，如_init、_exit，设置初始化优先级，如__initcall */  
#include <linux/wait.h>    /* 等待队列wait_queue */  
#include <linux/interrupt.h> /* 中断方式，如IRQF_SHARED */  
#include <linux/fs.h>      /* file_operations操作接口等 */  
#include <linux/clk.h>     /* 时钟控制接口，如struct clk */  
#include <linux/miscdevice.h> /* 杂项设备 */  
#include <linux/sched.h>
#include <asm/io.h>        /* 提供readl、writel */  
#include <asm/irq.h>       /* 提供中断号，中断类型等，如IRQ_ADC中断号 */  
#include <asm/uaccess.h>   /* 提供copy_to_user等存储接口 */
#include <mach/hardware.h>
#include <mach/regs-gpio.h>
#include <mach/regs-irq.h>
#include <plat/regs-adc.h> /* 提供控制器的寄存器操作，如S3C2410_ADCCON */  


#define DEVICE_NAME   "adc"

 
static struct clk *adc_clock;   // 定义adc时钟，通过adc_clock接口获得adc输入时钟，adc转换器需要  
static void __iomem *base_addr; //定义虚拟地址访问硬件寄存器，__iomem只是用于表示指针将指向I/O内存  
static wait_queue_head_t adc_waitqueue; //定义一个等待队列adc_waitqueue，对ADC资源进行阻塞访问  

   
/* 定义并初始化信号量adc_lock，用于控制共享中断IRQ_ADC资源的使用 */  
DECLARE_MUTEX(adc_lock);  
EXPORT_SYMBOL(adc_lock);

static volatile int read_ok = 0; //定义等待队列的条件，当read_ok=1时，ADC转换完毕，数据可读 
static volatile int adc_data;    //定义ADC转换的数据内容


/*ADC中断服务程序，获取ADC转换后的数据 */  
static irqreturn_t adc_irq_callback(int irq, void *dev_id)
{
	// 仅当read_ok=0时才进行转换，防止多次中断
	if(!read_ok){
	    // 读取ADCCON[9:0]的值，0x3ff为只获取[9:0]位，ADCCON为转换后的数据 
        adc_data = readl(base_addr + S3C2410_ADCDAT0) & 0x3ff;  
  
        read_ok = 1; // 设置标识为1，唤醒读等待进程可以拷贝数据给用户空间了   
      	wake_up_interruptible(&adc_waitqueue);	
	}

	return IRQ_HANDLED;
}

static int adc_drv_open(struct inode *pinode, struct file *filp)
{
	int ret;

	// 由于IRQ_ADC为共享中断，因此中断类型选择IRQF_SHARED，最后一个参数需要设置NULL以外的值
	ret = request_irq(IRQ_ADC, adc_irq_callback, IRQF_SHARED, DEVICE_NAME, (void *)1);
    if(ret) {
        printk(KERN_ERR "Could notallocate ts IRQ_ADC !\n");
        return -EBUSY;
    }

    return ret;
}

static void adc_run(void)
{
	volatile unsigned int adccon;

	/* ADCCON的位[14]=1为使能A/D预分频器，位[13:6]=32表示设置的分频值，ADC的转换频率需要在2.5MHZ以下
     * 我们使用的ADC输入时钟为PCLK=50MHZ，50MHZ/32<2.5MHZ，满足条件
     * 位[5:3]=000，表示模拟输入通道选择AIN0
     */
	adccon = (1 << 14) | (32 << 6);
	writel(adccon, base_addr + S3C2410_ADCCON);

	// 位[0]=1表示使能ADC转换，当转换完毕后此位被ADC控制器自动清0
	adccon = readl(base_addr + S3C2410_ADCCON) | S3C2410_ADCCON_ENABLE_START;
	writel(adccon, base_addr + S3C2410_ADCCON);
}

static ssize_t adc_drv_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	int err;

    // 获取信号量，如果被占用，睡眠等待持有者调用up唤醒
    // 这样做的原因是，有可能其他进程抢占执行或是触摸屏驱动抢占执行
   	down_interruptible(&adc_lock);

    adc_run(); // 启动adc转换，调用中断处理函数adc_irq

	// 如果read_ok为假，则睡眠等待条件为真，由中断处理函数唤醒
    wait_event_interruptible(adc_waitqueue, read_ok);

	read_ok = 0; // 执行到此说明中断处理程序获得了ADC转换后的值，清除为0等待下一次的读

	// 将转换后的数据adc_data提交给用户
	err = copy_to_user(buf, (char *)&adc_data, min(sizeof(adc_data), count));

    up(&adc_lock); // 释放信号量，并唤醒因adc_lock而睡眠的进程

	return err ? -EFAULT : min(sizeof(adc_data), count);
}

static int adc_drv_close(struct inode *pinode, struct file *filp)
{
	// 释放中断
    free_irq(IRQ_ADC, (void *)1);

	return 0;
}


static struct file_operations adc_fops = { //字符设备操作接口
	.owner  = THIS_MODULE,
	.open   = adc_drv_open,
	.read   = adc_drv_read,
	.release= adc_drv_close,
};

static struct miscdevice adc_misc = {
	.minor = MISC_DYNAMIC_MINOR, // 动态获取次设备号
	.name  = DEVICE_NAME,        // 杂项设备名称
	.fops  = &adc_fops,          // 杂项设备子系统接口，指向adc_fops操作接口
};

static __init int adc_drv_init(void)
{
	int ret;

	// 获得adc的时钟源，通过arch/arm/mach-s3c2410/clock.c获得提供的时钟源为PCLK
	adc_clock = clk_get(NULL, "adc");
	if(!adc_clock){
		printk(KERN_ERR "failed to get adcclock source\n"); 
		return -ENOENT;
	}

    // 使能adc时钟源，ADC转换需要输入时钟
    clk_enable(adc_clock);  	

    // 使用ioremap获得操作ADC控制器的虚拟地址 
    // S3C2410_PA_ADC=ADCCON，是ADC控制器的基地址，寄存器组的长度=0x1c   
    base_addr = ioremap(S3C2410_PA_ADC, 0x1c);  
    if (base_addr == NULL){  
        printk(KERN_ERR "Failed to remapregister block\n");  
        ret = -ENOMEM;  
        goto fail1;  
    }	

	// 初始化等待队列
	init_waitqueue_head(&adc_waitqueue);  

	// 注册杂项设备
	ret = misc_register(&adc_misc);
	if(ret<0){
		printk(KERN_INFO " can't register adc_drv\n"); 
		goto fail2;
	}

fail2:
	iounmap(base_addr);
fail1:
	clk_disable(adc_clock); // 禁止ADC的时钟源 
    clk_put(adc_clock); 
	return ret;
}

static __exit void adc_drv_exit(void)
{
    /* 释放虚拟地址 */
    iounmap(base_addr);

    /* 禁止ADC的时钟源 */
    if (adc_clock)
    {
        clk_disable(adc_clock);
        clk_put(adc_clock);
        adc_clock = NULL;
    }

	misc_deregister(&adc_misc);
}

module_init(adc_drv_init);
module_exit(adc_drv_exit);
MODULE_LICENSE("GPL");
