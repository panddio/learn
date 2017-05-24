#include <linux/module.h>	/* module_init */
#include <linux/fs.h>	/* file_operations */
#include <linux/device.h>	/* class device */
#include <asm/io.h>	/* writel() */
#include <plat/gpio-cfg.h>	/* s3c_gpio_cfgpin */
#include <mach/gpio.h>	/* gpio_set_value */
#include <linux/uaccess.h> /* copy_to_user() */
#include <linux/interrupt.h> /* request_irq() */
#include <linux/irq.h> /* IRQ_TYPE_EDGE_FALLING() */
#include <linux/delay.h> /* mdelay() */
#include <linux/kfifo.h> /* kfifo */
#include <linux/poll.h> /* poll */
#include <linux/kthread.h> /* kthread */
#include <linux/miscdevice.h> /* struct miscdevice */
#include <linux/cdev.h> /* cdev_init */
#include <linux/proc_fs.h>	/* proc_dir_entry */
#include <linux/platform_device.h> /* platform_driver_register() */
#include <linux/ioport.h>	/* resource */
#include <linux/input.h>
#include <linux/gpio_keys.h> 



#define DEVICE_NAME   "s5pv210_buttons"
#define DOWN          0    //按键按下
#define UP            1    //按键松开

#define GPH2_7  _IO('g',7)
#define GPH2_6	_IO('g',6)
#define GPH2_5	_IO('g',5)
#define GPH2_4	_IO('g',4)



static struct task_struct *kthread_ops = NULL;
static struct input_dev *input_buttons = NULL;
static struct workqueue_struct *buttons_workqueue = NULL;
static struct work_struct buttons_work;
static struct kfifo buttons_fifo;
static struct completion buttons_compet;
static struct timer_list buttons_timer;

static spinlock_t buttons_spinlock;
static atomic_t open_flag = ATOMIC_INIT(0);

struct gpio_buttons {
	u8 status; /* up=0, down=1 */
	u8 type;   /* short=0, long=1 */
	u32 code;
};

struct gpio_buttons button = {
	.status = 0,
	.type   = 0,
	.code   = 0,
};

static struct gpio_keys_platform_data *pbuttons = NULL;

static int nbuttons = 0; // 记录按键个数
static int key_id   = 0; // 记录哪个按键被按下


static struct gpio_keys_button s5pv210_gpio_buttons[] = {
	// KEY2
	{
		.code    = KEY_UP,
		.gpio    = S5PV210_GPH2(3),
		.desc    = "key-up",
		.type    = EV_KEY,
	},
	// KEY4
	{
		.code    = KEY_DOWN,
		.gpio    = S5PV210_GPH2(5),
		.desc    = "key-down",
		.type    = EV_KEY,
	},
	// KEY6
	{
		.code    = KEY_LEFT,
		.gpio    = S5PV210_GPH2(7),
		.desc    = "key-left",
		.type    = EV_KEY,
	},
	// KEY5
	{
		.code    = KEY_RIGHT,
		.gpio    = S5PV210_GPH2(6),
		.desc    = "key-right",
		.type    = EV_KEY,
	},
};

static struct resource s5pv210_gpio_resource[] = {
	[0] = {
		.start = S5PV210_GPH3(0),
		.end = S5PV210_GPH3(0),
		.name = "GPH3_0",
		.flags = IORESOURCE_IO,
	},
	[1] = {
		.start = S5PV210_GPH0(3),
		.end = S5PV210_GPH0(3),
		.name = "GPH0_3",
		.flags = IORESOURCE_IO,
	}
};

static struct gpio_keys_platform_data s5pv210_buttons_info = {
	.buttons  = s5pv210_gpio_buttons,
	.nbuttons = ARRAY_SIZE(s5pv210_gpio_buttons),
};


static void	s5pv210_buttons_release(struct device *pdev)
{
	printk(KERN_WARNING "%s\n",__FUNCTION__);
	return;
}


static struct platform_device s5pv210_buttons_dev = {
	.name  = "s5pv210_buttons",
	.id    = -1,
	.num_resources = ARRAY_SIZE(s5pv210_gpio_resource),
	.resource = s5pv210_gpio_resource,
	.dev = {
		.platform_data = &s5pv210_buttons_info,
		.release       = s5pv210_buttons_release,
	},
};

static int input_buttons_open(struct input_dev *dev)
{
	int i;
	printk(KERN_WARNING "%s\n",__FUNCTION__);

	if(atomic_read(&open_flag) == 0){
		for(i=0;i<nbuttons;i++)
			enable_irq(gpio_to_irq(pbuttons->buttons[i].gpio));
	}
	atomic_inc(&open_flag);
	return 0;
}

static void input_buttons_close(struct input_dev *dev)
{
	int i;
	printk(KERN_WARNING "%s\n",__FUNCTION__);
	del_timer_sync(&buttons_timer);

	atomic_dec(&open_flag);
	if(atomic_read(&open_flag) == 0){
		for(i=0;i<nbuttons;i++)
			disable_irq(gpio_to_irq(pbuttons->buttons[i].gpio));
	}
}

static void buttons_timerhandler(unsigned long data)
{
	int ret = 0;
	unsigned long irqflag;

	printk(KERN_WARNING "[msg]:  %s\n",__FUNCTION__);
	spin_lock_irqsave(&buttons_spinlock, irqflag);
	button.type = 1;	 // 等0，表示短按，等1，表示长按
	ret = kfifo_in(&buttons_fifo,&button, sizeof(button));
	spin_unlock_irqrestore(&buttons_spinlock, irqflag);

	if(ret != sizeof(button))
		printk(KERN_WARNING "kfifo_in fail!\n");

	mod_timer(&buttons_timer,jiffies+20);/* 5ms*20=100ms */
}

static void buttons_workhandler(struct work_struct *work)
{
	int ret;
	unsigned long irqflag;

	if(button.status == 0){
		s3c_gpio_cfgpin(pbuttons->buttons[key_id].gpio, S3C_GPIO_INPUT);	// 配置引脚为输入，S3C_GPIO_INPUT 可以替换成S3C_GPIO_SFN(0x1)
		mdelay(30);	// 延时消抖
		ret = gpio_get_value(pbuttons->buttons[key_id].gpio);
		s3c_gpio_cfgpin(pbuttons->buttons[key_id].gpio, S3C_GPIO_SFN(0xf)); // S3C_GPIO_SFN(0xf)复用功能选择，0xf对应引脚中断功能,

		if( ret != 0)
			return;
		if(kfifo_is_full(&buttons_fifo))
			return;

		spin_lock_irqsave(&buttons_spinlock, irqflag);
		button.status = 1;
		button.type = 0;	 // 等0，表示短按，等1，表示长按
		button.code = pbuttons->buttons[key_id].code;
		kfifo_in(&buttons_fifo,&button, sizeof(button));
		spin_unlock_irqrestore(&buttons_spinlock, irqflag);

		if(!timer_pending(&buttons_timer)){	      // 查看定时器是否正被调度
			buttons_timer.expires = jiffies+1*HZ; // 设置定时器的定时时间为1秒
			add_timer(&buttons_timer);	          // 注册定时器
		}
	}
	else { // 按键抬起 不用去抖动
		del_timer_sync(&buttons_timer); // 删除定时器，在定时器时间到前停止一个已注册的定时器

		if(kfifo_is_full(&buttons_fifo))
			return;

		spin_lock_irqsave(&buttons_spinlock, irqflag);
		button.status = 0;
		button.code = pbuttons->buttons[key_id].code;
		kfifo_in(&buttons_fifo,&button, sizeof(button));
		spin_unlock_irqrestore(&buttons_spinlock, irqflag);
	}

}

static irqreturn_t s5pv210_buttons_irqhandler(int irq, void *dev_id)
{
	//printk(KERN_WARNING "%s\n",__FUNCTION__);

	key_id = (int)dev_id;
	queue_work(buttons_workqueue, &buttons_work);

	return IRQ_HANDLED;
}

static int kthread_ops_buttons(void *data)
{
	int ret;
	unsigned long irqflag;
	struct gpio_buttons buttons_read;

	for(;;)
	{
		if(kthread_should_stop()) break; // 是否终止
		if(!kfifo_is_empty(&buttons_fifo)){
			spin_lock_irqsave(&buttons_spinlock, irqflag);
			ret = kfifo_out(&buttons_fifo, &buttons_read, sizeof(buttons_read));
			spin_unlock_irqrestore(&buttons_spinlock, irqflag);

			if(ret == sizeof(buttons_read)){
				input_report_key(input_buttons, buttons_read.code, buttons_read.status); //
				input_sync(input_buttons);
				//printk(KERN_WARNING "%s\n",__FUNCTION__);
			}
		}
		schedule_timeout(HZ); // 让出CPU，并告诉内核不要超过HZ时间不调‘我’
	}
	complete_and_exit(&buttons_compet, 0);
	return 0;
}


static __devinit int s5pv210_buttons_probe(struct platform_device *pdev)
{
	int ret, i;

	printk(KERN_WARNING "%s\n",__FUNCTION__);

	// 初始化按键公共端接口输出低电平
	s3c_gpio_cfgpin(pdev->resource[0].start, S3C_GPIO_OUTPUT);
	gpio_set_value(pdev->resource[0].start, 0);

	ret = kfifo_alloc(&buttons_fifo, 128, GFP_KERNEL);
	if(ret)  goto out;

	buttons_workqueue = create_workqueue("buttons_workqueue");	// 创建工作队列
	INIT_WORK(&buttons_work,buttons_workhandler); // 初始化工作(工作和工作函数建立关联)

	spin_lock_init(&buttons_spinlock); // 初始化自旋锁
	init_timer(&buttons_timer);
	buttons_timer.data = 0;	 // 设置传给回调函数的参数为0
	buttons_timer.function = buttons_timerhandler; // 设置定时器到时回调函数

	pbuttons = pdev->dev.platform_data;
	nbuttons = pbuttons->nbuttons; // 获取按键个数

	for(i=0;i<nbuttons;i++){

		s3c_gpio_setpull(pbuttons->buttons[i].gpio, S3C_GPIO_PULL_UP); // 设置引脚上拉使能

		// 注册中断
		ret = request_irq(gpio_to_irq(pbuttons->buttons[i].gpio), s5pv210_buttons_irqhandler,\
						 IRQ_TYPE_EDGE_BOTH, pbuttons->buttons[i].desc, (void *)i);
		disable_irq(gpio_to_irq(pbuttons->buttons[i].gpio));
		if(ret){       //返回非0，中断申请失败
			while(i--) //释放注册成功的中断
				free_irq(gpio_to_irq(pbuttons->buttons[i].gpio), (void *)i);
			goto request_irq_err;
		}
	}

	//input 子系统
	input_buttons = input_allocate_device(); // 给input设备分配空间
	if(IS_ERR(input_buttons)){
		ret = PTR_ERR(input_buttons);
		goto input_allocate_err;
	}
	input_buttons->name = DEVICE_NAME;
	input_buttons->phys = "inputkey";
	input_buttons->id.bustype = BUS_HOST;
	input_buttons->id.vendor = 0x0001;
	input_buttons->evbit[0] = BIT(EV_KEY)|BIT(EV_REP)|BIT(EV_SYN); // 支持事件类型: 按键+重复按键+同步事件
	for(i=0;i<nbuttons;i++){
		set_bit(pbuttons->buttons[i].type, input_buttons->evbit);
		set_bit(pbuttons->buttons[i].code, input_buttons->keybit);
		//input_buttons->keybit[BIT_WORD(pbuttons->buttons[i].code)] |= BIT_MASK(pbuttons->buttons[i].code);
	}
	input_buttons->open  = input_buttons_open;  // 在input_register_device成功后被调用
	input_buttons->close = input_buttons_close; // 在input_unregister_device成功后被调用

	ret = input_register_device(input_buttons); // 注册input子系统
	if(ret) goto input_register_err;

	// completion是一种轻量级的机制，它允许一个线程告诉另一个线程工作已经完成
	init_completion(&buttons_compet);// 可以利用宏静态创建completion: DECLARE_COMPLETION(my_completion);

	// 创建内核线程
	kthread_ops = kthread_create(kthread_ops_buttons, NULL, "buttons_ops");
	if(IS_ERR(kthread_ops)){
		complete(&buttons_compet);
		ret = PTR_ERR(kthread_ops);
		goto kthread_create_err;
	}
	wake_up_process(kthread_ops); // 启动内核进程

	printk(KERN_WARNING "%s\n",__FUNCTION__);
	return 0;

	// 出错退出处理
	kthread_create_err:
	input_unregister_device(input_buttons);

	input_register_err:
	input_free_device(input_buttons);

	input_allocate_err:
	for(i=0; i<nbuttons; i++){
		free_irq(gpio_to_irq(pbuttons->buttons[i].gpio), (void *)i);
	}
	request_irq_err:
	destroy_workqueue(buttons_workqueue);
	out:
	kfifo_free(&buttons_fifo);
	return ret;
}

static __devexit int s5pv210_buttons_remove(struct platform_device *pdev)
{
	int i;
	kthread_stop(kthread_ops);
	wait_for_completion(&buttons_compet);
	destroy_workqueue(buttons_workqueue);
	input_unregister_device(input_buttons);
	input_free_device(input_buttons);
	kfifo_free(&buttons_fifo);

	for(i=0; i<nbuttons; i++){
		disable_irq(gpio_to_irq(pbuttons->buttons[i].gpio));
		free_irq(gpio_to_irq(pbuttons->buttons[i].gpio), (void *)i);
	}

	printk(KERN_WARNING "%s\n",__FUNCTION__);
	return 0;
}

static struct platform_driver s5pv210_buttons_drv = {
	.probe  = s5pv210_buttons_probe,  // 匹配后的回调函数
	.remove = s5pv210_buttons_remove, // 在设备注销时或是驱动注销时调用
	.driver = {
		.owner = THIS_MODULE,
		.name  = "s5pv210_buttons",
	},
};

static __init int s5pv210_buttons_driver_init(void)
{
	int ret;

	ret = platform_device_register(&s5pv210_buttons_dev);
	if(ret){
		printk(KERN_ERR "%s: register device failed\n", __FUNCTION__);
		goto fail0;
	}

	ret = platform_driver_register(&s5pv210_buttons_drv);
	if(ret){
		printk(KERN_ERR "%s: register driver failed\n", __FUNCTION__);
		goto fail1;
	}

	return 0;
	fail1:
	platform_device_unregister(&s5pv210_buttons_dev);
	fail0:
	return ret;
}

static __exit void s5pv210_buttons_driver_exit(void)
{
	platform_driver_unregister(&s5pv210_buttons_drv);
	platform_device_unregister(&s5pv210_buttons_dev);
	printk(KERN_WARNING "%s\n",__FUNCTION__);
	return;
}

module_init(s5pv210_buttons_driver_init);
module_exit(s5pv210_buttons_driver_exit);
MODULE_LICENSE("GPL");
