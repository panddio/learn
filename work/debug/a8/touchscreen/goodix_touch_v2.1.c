/* drivers/input/touchscreen/goodix_touch.c
 *
 * Copyright (C) 2010 Goodix, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/earlysuspend.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/irq.h>
#include "goodix_touch_v2.1.h"



#define debug_goodix(fmt, arg...)  printk(KERN_INFO fmt, ##arg);

/* other cpt touch can use this workqueue */
struct workqueue_struct *goodix_wq;

static const struct i2c_device_id goodix_ts_id[] = {
	{ GOODIX_I2C_NAME, 0 },
	{ }
};


int i2c_write_bytes(struct i2c_client *client,uint8_t *data,int len)
{
	/* just one i2c_msg OK. */
	int ret;
	struct i2c_msg msg;

	msg.addr  = client->addr; // 器件的地址
	msg.flags = !I2C_M_RD;    // !I2C_M_RD => 写
	msg.len = len;
	msg.buf = data;	         // 器件的寄存器地址

	ret =  i2c_transfer(client->adapter, &msg, 1);
	return ret;
}

int i2c_read_bytes(struct i2c_client *client, uint8_t *data, int len)
{
	/* u need two i2c_msg */
	int ret;
	struct i2c_msg msg[2];

	msg[0].addr  = client->addr;
	msg[0].flags = !I2C_M_RD;
	msg[0].len = 1;
	msg[0].buf = &data[0];

	msg[1].addr  = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = len - 1;
	msg[1].buf = &data[1];	// 保存读取数据的起始地址

	ret = i2c_transfer(client->adapter, msg, 2);
	return ret;
}


static int goodix_read_panel(struct goodix_priv *goodix, uint8_t *data, int size)
{
	return i2c_read_bytes(goodix->cli, data, size);
}

static int goodix_init_panel(struct goodix_priv *goodix)
{

	uint8_t config_info[54]={0x30,	0x19,0x05,0x05,0x28,0x02,0x14,0x14,0x10,0x32,0xF8,0x14,0x00,0x1E,0x00,0xED,0xCB,
									0xA9,0x87,0x65,0x43,0x21,0x01,0x00,0x00,0x35,0x2E,0x4D,0xC0,0x20,0x01,0x01,0x83,
									0x50,0x3C,0x1E,0x28,0x00,0x33,0x2C,0x01,0xEC,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,
									0x00,0x00,0x00,0x00,0x01};

	return i2c_write_bytes(goodix->cli, config_info, sizeof(config_info));
}

static void goodix_ts_work_func(struct work_struct *work)
{
	uint8_t  point_data[35]={ 0 };
	int ret = 0;
	int pos[MAX_FINGER_NUM][2];
	unsigned int pressure[MAX_FINGER_NUM];
	struct goodix_priv *goodix = container_of(work, struct goodix_priv, work);

	ret = goodix_read_panel(goodix, point_data, sizeof(point_data));

	ret = goodix_analysis_data(point_data, goodix, pos, pressure);

	if((point_data[1]&0x01) == 0x01)
	{
		input_report_abs(goodix->input_dev, ABS_X, (800-pos[0][0]));
		input_report_abs(goodix->input_dev, ABS_Y, pos[0][1]);
		input_report_abs(goodix->input_dev, ABS_PRESSURE, 1);
		input_report_key(goodix->input_dev, BTN_TOUCH, 1);
	}
	else
	{
		input_report_abs(goodix->input_dev, ABS_PRESSURE, 0);
		input_report_key(goodix->input_dev, BTN_TOUCH, 0);
	}
    input_sync(goodix->input_dev);

	return ;

}

static irqreturn_t goodix_ts_irq_handler(int irq, void *dev_id)
{
	struct goodix_priv *goodix = (struct goodix_priv *)dev_id;

	printk(KERN_CRIT "interrupt for guitar arrived.\n");

	queue_work(goodix_wq, &goodix->work);

	return IRQ_HANDLED;
}

static __devinit int goodix_ts_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct goodix_priv *goodix;
	int ret;

    /*allocate memory for goodix — kmalloc*/
	goodix = (struct goodix_priv *)kmalloc(sizeof(struct goodix_priv), GFP_KERNEL);
	if(goodix == NULL){
		printk("%s: kmalloc failed!\n", __FUNCTION__);
		ret = -ENOMEM;
		goto out;
	}
	memset(goodix, 0, sizeof(struct goodix_priv));

	ret = gpio_request(SHUTDOWN_PORT, "GOODIX_TS SHUTDOWN PORT");
	if (ret < 0) {
		dev_err(&client->dev, "Failed to request GPIO:%d, ERRNO:%d\n",(int)SHUTDOWN_PORT,ret);
		goto err1;
	}

	/* set gpio output & 0; goodix step into normal mode */
	gpio_direction_output(SHUTDOWN_PORT, 0);

	ret = i2c_check_functionality(client->adapter, I2C_FUNC_I2C);
	if (ret == 0) {
		dev_err(&client->dev, "Soc no I2C function, ERRNO:%d\n", ret);
		goto err2;
	}

	msleep(16);//step into normal mode, need 16ms

	dev_info(&client->dev, "chip goodix work...\t i2c connecttion work...\t now we request irq and input_dev\n");

	/*init goodix variable*/
	goodix->cli = client;
	goodix->privata_data = client->dev.platform_data;
	i2c_set_clientdata(client, goodix);

	/* init work of workqueue*/
	//goodix_wq = create_workqueue("goodix_wq");     // 创建工作队列
	INIT_WORK(&goodix->work, goodix_ts_work_func); // 初始化工作(工作和工作函数建立关联)

	/* input dev init and register */
	goodix->input_dev = input_allocate_device(); // 给input设备分配空间

	if(IS_ERR(goodix->input_dev)){
		ret = PTR_ERR(goodix->input_dev);
		goto err2;
	}
	goodix->input_dev->name = GOODIX_I2C_NAME;
	goodix->input_dev->phys = "Goodix-TS";
	goodix->input_dev->id.bustype = BUS_HOST;
	goodix->input_dev->id.vendor  = 0x0001;
	goodix->input_dev->id.product = 0x0001;
	goodix->input_dev->id.version = 0x0001;
	goodix->input_dev->evbit[0] = BIT_MASK(EV_SYN) | BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) ;
	goodix->input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	goodix->input_dev->absbit[0] = BIT(ABS_X) | BIT(ABS_Y); // for android
	set_bit(ABS_PRESSURE, goodix->input_dev->absbit);

	input_set_abs_params(goodix->input_dev, ABS_X, 0, SCREEN_MAX_HEIGHT, 0, 0);
	input_set_abs_params(goodix->input_dev, ABS_Y, 0, SCREEN_MAX_WIDTH, 0, 0);
	input_set_abs_params(goodix->input_dev, ABS_PRESSURE, 0 , 255, 0, 0);

	//goodix->input_dev->open  = input_goodix_open;  // 在input_register_device成功后被调用
	//goodix->input_dev->close = input_goodix_close; // 在input_unregister_device成功后被调用
	ret = input_register_device(goodix->input_dev);
	if(ret) goto err3;

	/* request_irq */
	ret = gpio_request(INT_PORT, "GOODIX_TS INT_PORT");
	if(ret < 0){
		dev_err(&client->dev, "Failed to request GPIO:%d, ERRNO:%d\n",(int)INT_PORT, ret);
		goto err3;
	}

	ret = request_irq(INT_FUNC, goodix_ts_irq_handler, IRQ_TYPE_EDGE_RISING, GOODIX_I2C_NAME, (void *)goodix);
	if(ret){
		dev_err(&client->dev,"Can't allocate touchscreen's interrupt!ERRNO:%d\n", ret);
		gpio_free(INT_PORT);
		goto err4;
	}

	/* init hardware*/
	goodix_init_panel(goodix);

	return 0;

	err4:
	gpio_free(INT_PORT);
	input_unregister_device(goodix->input_dev);
	err3:
	input_free_device(goodix->input_dev);
	err2:
	gpio_direction_input(SHUTDOWN_PORT);
	gpio_free(SHUTDOWN_PORT);
	err1:
	kfree(goodix);
	out:
	return ret;

}

static __devexit int goodix_ts_remove(struct i2c_client *client)
{
	struct goodix_priv *goodix = i2c_get_clientdata(client);

	gpio_direction_input(SHUTDOWN_PORT);
	gpio_free(SHUTDOWN_PORT);

	disable_irq(INT_FUNC);
	free_irq(INT_FUNC, (void *)goodix);
	gpio_free(INT_PORT);

	input_unregister_device(goodix->input_dev);
	input_free_device(goodix->input_dev);

	i2c_set_clientdata(client, NULL);
	if(goodix->input_dev)
		kfree(goodix->input_dev);
	kfree(goodix);
	return 0;
}

static struct i2c_driver goodix_ts_driver = {
	.probe		= goodix_ts_probe,
	.remove		= goodix_ts_remove,
	.id_table	= goodix_ts_id,
	.driver = {
		.name	= GOODIX_I2C_NAME,
		.owner = THIS_MODULE,
	},
};

static int __init cpt_ts_init(void)
{
	int ret;
	printk(KERN_INFO "Touchscreen driver of guitar is installing...\n");
	goodix_wq = create_workqueue("goodix_wq");//success means not null
	if (!goodix_wq) {
		printk(KERN_ALERT "creat workqueue faiked\n");
		return -ENOMEM;

	}
	ret=i2c_add_driver(&goodix_ts_driver);
	return ret;
}

static void __exit cpt_ts_exit(void)
{
	printk(KERN_INFO "Touchscreen driver of guitar is exiting...\n");
	i2c_del_driver(&goodix_ts_driver);
	if (goodix_wq)
		destroy_workqueue(goodix_wq);
	return ;
}

module_init(cpt_ts_init);
module_exit(cpt_ts_exit);

MODULE_DESCRIPTION("Goodix Touchscreen Driver");
MODULE_LICENSE("GPL");
