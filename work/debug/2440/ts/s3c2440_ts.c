/* ************************************************************************
 *       Filename:  s3c2440_ts.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年10月30日 20时43分30秒
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
#include <linux/fs.h>       /* file_operations操作接口等 */  
#include <linux/clk.h>      /* 时钟控制接口，如struct clk */ 
#include <linux/input.h>    /* 内核输入子系统操作接口 */  
#include <linux/slab.h>     /* kzalloc内存分配函数 */  
#include <linux/time.h>     /* do_gettimeofday时间函数 */  
#include <linux/timer.h>    /* timer定时器 */ 
#include <linux/miscdevice.h> /* 杂项设备 */ 
#include <linux/sched.h>
#include <linux/irq.h>
#include <asm/io.h>        /* 提供readl、writel */  
#include <asm/irq.h>       /* 提供中断号，中断类型等，如IRQ_ADC中断号 */  
#include <asm/uaccess.h>   /* 提供copy_to_user等存储接口 */
#include <plat/regs-adc.h> /* 提供控制器的寄存器操作，如S3C2410_ADCCON */  
#include <mach/hardware.h>
#include <mach/regs-gpio.h>
#include <mach/regs-irq.h>

#define __IRQT_FALEDGE IRQ_TYPE_EDGE_FALLING
#define __IRQT_RISEDGE IRQ_TYPE_EDGE_RISING
#define __IRQT_LOWLVL  IRQ_TYPE_LEVEL_LOW
#define __IRQT_HIGHLVL IRQ_TYPE_LEVEL_HIGH
#define IRQT_NOEDGE   (0)
#define IRQT_RISING   (__IRQT_RISEDGE)
#define IRQT_FALLING  (__IRQT_FALEDGE)
#define IRQT_BOTHEDGE (__IRQT_RISEDGE|__IRQT_FALEDGE)
#define IRQT_LOW      (__IRQT_LOWLVL)
#define IRQT_HIGH     (__IRQT_HIGHLVL)
#define IRQT_PROBE    IRQ_TYPE_PROBE

#define CONFIG_S3C2440_TOUCHSCREEN__DEBUG  1
#define DEVICE_NAME   "s3c2440ts"


// 定义一个宏WAIT4INT，用于对ADCTSC触摸屏控制寄存器进行操作
#define WAIT4INT(x)  (((x)<<8) | S3C2410_ADCTSC_YM_SEN | S3C2410_ADCTSC_YP_SEN | \
						S3C2410_ADCTSC_XP_SEN | S3C2410_ADCTSC_XY_PST(3))

// 定义一个宏AUTOPST，用于设置ADCTSC触摸屏控制寄存器为自动转换模式
#define AUTOPST  (S3C2410_ADCTSC_YM_SEN | S3C2410_ADCTSC_YP_SEN | S3C2410_ADCTSC_XP_SEN | \
				  S3C2410_ADCTSC_AUTO_PST | S3C2410_ADCTSC_XY_PST(0))

struct ts_event 
{
	short pressure;	/* 是否按下     */	
	short xp;		/*触摸屏x坐标值 */	
	short yp;		/*触摸屏y坐标值 */
};

struct s3c2440_ts 
{
	struct input_dev *input;/* 输入子系统设备结构体 */  
	struct timer_list timer;/* 定时器，用于ADC转换操作 */  
	struct ts_event tc;	    /* ADC转换的值的保存位置，也用于上报input子系统的数据 */  
	int pendown; 		    /* 判断是否有按下 */  
	int count;		        /* 用于驱动去抖的计数 */  
	int shift;			    /* 用于驱动去抖的基数 */	
};

struct s3c2440_ts *pts = NULL;

static void __iomem *base_addr;
static struct clk *adc_clock;
static struct semaphore adc_lock;

static void touch_timer_callback(unsigned long data)
{
	unsigned long data0;
	unsigned long data1;

	// 禁止中断，处理完数据再打开中断
	set_irq_type(IRQ_TC, IRQT_NOEDGE);
	set_irq_type(IRQ_ADC,IRQT_NOEDGE);

	// 读取ADCDAT0和ADCDAT1寄存器，提取ADC转换的x，y坐标值
	data0 = readl(base_addr + S3C2410_ADCDAT0);
	data1 = readl(base_addr + S3C2410_ADCDAT1);

	// 判断ADCDAT0和ADCDAT1中的[15]位，[15]位为等待中断模式下用于判断笔尖是否有抬起或落下，0=落下
	pts->pendown = (!(data0 &S3C2410_ADCDAT0_UPDOWN)) && (!(data1 & S3C2410_ADCDAT0_UPDOWN));

	// 当触摸屏处于被按下状态，执行下面代码
	if(pts->pendown){
		/* count不为0，说明正在转换，xp和yp往右移动shift(2)位是为了去抖 
		 * 需要结合stylus_action中断函数来看，当count=4时，才能认为转换结束， 
		 * 即最后所得的xp和yp是累加了4次的，最终上报时需要除以4，因此这里预先 
		 * 右移2位，相当于除以4 
		 */ 
		if(pts->count != 0){
			pts->tc.xp >>= pts->shift; // pts->tc.xp = pts->tc.xp >> pts->shift
			pts->tc.yp >>= pts->shift;

			// 终端打印调试信息  
			#ifdef CONFIG_S3C2440_TOUCHSCREEN__DEBUG  
			{  
				struct timeval tv;  
				do_gettimeofday(&tv);  
				printk(KERN_INFO"T: %06d, X: %03x, Y: %03x\n", (int)tv.tv_usec, pts->tc.xp, pts->tc.yp);  
			}  
			#endif

			// 报告X、Y的绝对坐标值
			input_report_abs(pts->input, ABS_X, pts->tc.xp);
			input_report_abs(pts->input, ABS_Y, pts->tc.yp);
			input_report_abs(pts->input, ABS_PRESSURE, pts->tc.pressure);// 报告触摸屏的状态，1表明触摸屏被按下
			input_report_key(pts->input, BTN_TOUCH,pts->pendown);// 报告按键事件，键值为1(代表触摸屏对应的按键被按下)
			input_sync(pts->input);// 等待接收方受到数据后回复确认，用于同步
		}

		// count=0执行这里面的代码，ADC还没有开始转换
		pts->tc.xp = 0;
		pts->tc.yp = 0;
		pts->tc.xp = 0;
		pts->tc.pressure= 0;
		pts->count = 0;

    	// 因为触摸屏是按下状态，ADC还没有转换，需要启动ADC开始转换 
        // 本句代码是设置触摸屏为自动转换模式 
        writel(S3C2410_ADCTSC_PULL_UP_DISABLE | AUTOPST, base_addr + S3C2410_ADCTSC);	

		// 启动ADC转换
		writel(readl(base_addr +S3C2410_ADCCON) | S3C2410_ADCCON_ENABLE_START, base_addr + S3C2410_ADCCON);	

	}
	else {
		// 执行到这里说明按键没有被按下或按键抬起，count清0
		pts->count = 0;

		input_report_key(pts->input, BTN_TOUCH, 0);   // 报告按键事件，给0值说明按键抬起	
		input_report_abs(pts->input, ABS_PRESSURE, 0);// 报告按键事件，给0值说明按键抬起
		input_sync(pts->input); 

		writel(WAIT4INT(0), base_addr +S3C2410_ADCTSC);// 将触摸屏重新设置为等待中断状态，等待触摸屏被按下

		del_timer_sync(&pts->timer); // 删除定时器，在定时器时间到前停止一个已注册的定时器
		up(&adc_lock);               // 触摸屏抬起了，可以释放信号量了 
	}

	// 使能中断触发条件，IRQT_BOTHEDGE为使能上升沿和下降沿触发  
	set_irq_type(IRQ_TC, IRQT_BOTHEDGE);  
	set_irq_type(IRQ_ADC,IRQT_BOTHEDGE); 	

}

// ADC中断服务程序，ADC启动转换后被执行
static irqreturn_t stylus_action(int irq, void *dev_id)
{
	unsigned long data0;
	unsigned long data1;

#ifdef CONFIG_S3C2440_TOUCHSCREEN__DEBUG  
	printk(KERN_ERR "%s() No.%dline:\n\r",__FUNCTION__,__LINE__);  
#endif

	// 获取触摸屏的x，y坐标值
	data0 = readl(base_addr + S3C2410_ADCDAT0);
	data1 = readl(base_addr + S3C2410_ADCDAT1);

	pts->tc.xp += data0 & S3C2410_ADCDAT0_XPDATA_MASK;
	pts->tc.yp += data1 & S3C2410_ADCDAT1_YPDATA_MASK;
	pts->tc.pressure = 1;
	pts->count++;
	
	// 如果count小于4，需要重启设置自动转换模式，并进行ADC转换，用于去抖
	if((pts->count) < (1 << pts->shift)){
		writel(S3C2410_ADCTSC_PULL_UP_DISABLE | AUTOPST, base_addr + S3C2410_ADCTSC);
		writel(readl(base_addr + S3C2410_ADCCON) | S3C2410_ADCCON_ENABLE_START, base_addr + S3C2410_ADCCON);
	}
	else {
		// pts->count=4，启动定时器去执行touch_timer_callback函数上报按键和触摸事件
		mod_timer(&pts->timer, jiffies + HZ/100);

		// 检测触摸屏抬起的中断信号
		writel(WAIT4INT(1),base_addr + S3C2410_ADCTSC);
	}

	return IRQ_HANDLED;
}

// 触摸屏中断服务程序，触摸屏按下或抬起时触发执行
static irqreturn_t stylus_updown(int irq, void *dev_id)
{
	unsigned long data0;
	unsigned long data1;

	// 由于是中断程序，所以不能使用down和down_interruptible，会导致睡眠
	if(down_trylock(&adc_lock) == 0){
		// 读取ADCDAT0和ADCDAT1，用于判断触摸屏是否被按下
		data0 = readl(base_addr + S3C2410_ADCDAT0);
		data1 = readl(base_addr + S3C2410_ADCDAT1);

		pts->pendown = (!(data0 & S3C2410_ADCDAT0_UPDOWN)) && (!(data1 & S3C2410_ADCDAT1_UPDOWN));
		if(pts->pendown){
			// 启动ADC转换，设置ADCCON寄存器的bit[0]为1，bit[0]在启动ADC转换后自动清零
			writel(readl(base_addr + S3C2410_ADCCON) | S3C2410_ADCCON_ENABLE_START, base_addr + S3C2410_ADCCON);
		}
	}
	
	return IRQ_RETVAL(IRQ_HANDLED);
}


static void adc_init(void) 
{
    // S3C2410_ADCCON_PRSCEN设置ADCCON的位[14]=1为使能A/D预分频器 
    // S3C2410_ADCCON_PRSCVL设置ADCCON的位[13:6]=32表示设置的分频值， 
    // ADC的转换频率需要在2.5MHZ以下，我们使用的ADC输入时钟为PCLK=50MHZ，50MHZ/(49+1)=1MHZ，满足条件  
	writel(S3C2410_ADCCON_PRSCEN |S3C2410_ADCCON_PRSCVL(49), base_addr + S3C2410_ADCCON);

    // 初始化ADC启动或延时寄存器，ADC转换启动延时值设置为0xffff  
    writel(0xffff, base_addr + S3C2410_ADCDLY);	

   /* 初始化ADC触摸屏控制寄存器ADCTSC， 
    * WAIT4INT(0)在上面定义，引脚YM、YP、XM、XP的使能位在ADCTSC的[7:4]位， 
    * 设置触摸屏的工作状态在[1:0]位，WAIT4INT(0)=11010011， 
    * 1101代表笔尖按下时发生触摸屏中断信号IRQ_TS给CPU，0011表示XP上拉使能， 
    * 使用正常ADC转换，转换的方式为等待中断模式 
    */  
    writel(WAIT4INT(0), base_addr + S3C2410_ADCTSC); 	
}

static __init int s3c2440_ts_init(void)
{
	int ret;
	struct input_dev *input_dev;

	pts = kzalloc(sizeof(struct s3c2440_ts), GFP_KERNEL);

	input_dev = input_allocate_device(); //给输入设备申请空间
	if(!pts || !input_dev){
		goto fail1;
	}
	
	adc_clock = clk_get(NULL, "adc");    //获得adc的时钟源
	if(!adc_clock){
		printk(KERN_ERR "failed to get adc clock source\n");  
		ret =  -ENOENT;  
		goto fail1;
	}
	clk_enable(adc_clock); // 使能adc时钟源，ADC转换需要输入时钟

    // 使用ioremap获得操作ADC控制器的虚拟地址 
    // S3C2410_PA_ADC=ADCCON，是ADC控制器的基地址，寄存器组的长度=0x1c   
    base_addr = ioremap(S3C2410_PA_ADC, 0x1c); 	

    if (base_addr == NULL) {  
        printk(KERN_ERR "Failed to remapregister block\n");  
        ret = -ENOMEM;  
        goto fail2;  
    } 	

	adc_init();              // 初始化ADC控制寄存器和ADC触摸屏控制寄存器
	sema_init(&adc_lock, 1); // 初始化信号量的值为1
	pts->shift = 2;          // 设置驱动去抖基数

	// 申请ADC中断，AD转换完成后触发。这里使用共享中断IRQF_SHARED是因为该中断号在ADC驱动中也使用了， 
	// 最后一个参数用于区分共享中断，如果设为NULL，中断申请失败 
	ret = request_irq(IRQ_ADC, stylus_action, IRQF_SHARED | IRQF_SAMPLE_RANDOM, DEVICE_NAME, (void *)pts);
	if(ret){
		ret = -EBUSY;
		goto fail3;
	}

	// 申请触摸屏中断，对触摸屏按下或提笔时触发  
	ret = request_irq(IRQ_TC, stylus_updown, IRQF_SAMPLE_RANDOM, DEVICE_NAME, (void *)pts);
	if(ret){
		ret = -EBUSY;
		goto fail4;
	}
	// 设置中断触发条件，IRQT_BOTHEDGE为使能上升沿和下降沿触发	
	set_irq_type(IRQ_TC, IRQT_BOTHEDGE);  
	set_irq_type(IRQ_ADC,IRQT_BOTHEDGE);

	// 初始化定时器 
	init_timer(&pts->timer);  
	pts->timer.data = 1;  
	pts->timer.function = touch_timer_callback;

	/* 设置触摸屏输入设备的标志，注册输入设备成功进入根文件系统，可以cat /proc/bus/input/devices查看其内容*/
	input_dev->name 	  = DEVICE_NAME;
	input_dev->phys 	  = "s3c2440ts/input0";
	input_dev->id.bustype = BUS_HOST;  /*总线类型 */	 
	input_dev->id.vendor  = 0x1;	   /*经销商ID */  
	input_dev->id.product = 0x2;	   /*产品ID */	
	input_dev->id.version = 0x0100;    /*版本ID */ 

	// evbit字段用于描述支持的事件，这里支持同步事件、按键事件、绝对坐标事件
	input_dev->evbit[0] = BIT_MASK(EV_SYN) |BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH); // keybit字段用于描述按键的类型，BTN_TOUCH表示触摸屏的点击
	
	//对于触摸屏来说，使用的是绝对坐标系统。这里设置该坐标系统中X和Y坐标的最小值和最大值(0-1023范围) 
	//ABS_X和ABS_Y就表示X坐标和Y坐标，ABS_PRESSURE就表示触摸屏是按下还是抬起状态  
	input_set_abs_params(input_dev, ABS_X, 0,0x3FF, 0, 0);	
	input_set_abs_params(input_dev, ABS_Y, 0,0x3FF, 0, 0);	
	input_set_abs_params(input_dev, ABS_PRESSURE, 0, 1, 0, 0); 

	pts->input = input_dev;
	ret = input_register_device(pts->input); // 注册输入子系统
	if(ret) 
		goto fail5;

	return 0;

fail5:
	free_irq(IRQ_TC, (void *)pts);
	disable_irq(IRQ_TC);
fail4:
	free_irq(IRQ_ADC, (void *)pts);
	disable_irq(IRQ_ADC);
fail3:
	iounmap(base_addr);
fail2:
	clk_disable(adc_clock); // 禁止ADC的时钟源     
	clk_put(adc_clock); 
fail1:
	input_free_device(input_dev);
	kfree(pts);
	return ret;
}

static __exit void s3c2440_ts_exit(void)
{
	// 屏蔽并释放中断
	disable_irq(IRQ_TC);
	disable_irq(IRQ_ADC);
	free_irq(IRQ_TC, (void *)pts);
	free_irq(IRQ_ADC, (void *)pts);

	// 注销定时器
	del_timer_sync(&pts->timer);

	// 屏蔽和禁止adc时钟
	if(adc_clock) {
		clk_disable(adc_clock);
		clk_put(adc_clock);
		adc_clock = NULL;
	}

	// 注销触摸屏输入子系统
	input_unregister_device(pts->input);

	// 释放虚拟地址
	iounmap(base_addr);

	// 释放触摸屏设备结构体
	kfree(pts);
}

module_init(s3c2440_ts_init);
module_exit(s3c2440_ts_exit);
MODULE_LICENSE("GPL");
