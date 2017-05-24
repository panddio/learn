/*
 * Copyright (C) 2012 Ingenic Semiconductor Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/spinlock.h>
#include <linux/wakelock.h>
#include <linux/clk.h>
#include <linux/syscalls.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/gpio.h>
#include <linux/spinlock.h>
#include <linux/poll.h>
#include <linux/hrtimer.h>
#include <linux/wait.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/wiegand.h>

#ifdef CONFIG_BOARD_4775_ZMM220
#define WIEGANDOUTDRV_LIB_VERSION		"1.0.1 ZMM220"__DATE__	/* DRV LIB VERSION */
#endif

#ifdef CONFIG_BOARD_4775_ZMM210
#define WIEGANDOUTDRV_LIB_VERSION		"1.0.1 ZMM210"__DATE__	/* DRV LIB VERSION */
#endif

#ifdef CONFIG_BOARD_4775_ZMM200
#define WIEGANDOUTDRV_LIB_VERSION		"1.0.1 ZMM200"__DATE__	/* DRV LIB VERSION */
#endif

#ifdef CONFIG_BOARD_X1000_ZLM60
#define WIEGANDOUTDRV_LIB_VERSION		"1.0.1 ZLM60"__DATE__	/* DRV LIB VERSION */
#endif


#define WIEGAND_OUT0_DATA	'0'
#define WIEGAND_OUT1_DATA	'1'

#define PLUSE_WIDTH_STATE	0
#define PLUSE_INTVAL_STATE	1

#define MAX_WIEGAND_DATA_LEN	128

#define DEF_PULSE_WIDTH		100 //us
#define DEF_PULSE_INTERVAL	1000 //us
#define DEF_DATA_LENGTH		26 //bit

struct wiegand_out_dev {
	struct device		*dev;
	struct miscdevice	mdev;
	unsigned int		data0_pin;
	unsigned int		data1_pin;
	unsigned char		wiegand_out_data[MAX_WIEGAND_DATA_LEN];
	int			pos;
	int			data_length;
	int			pulse_width; //us
	int			pulse_intval; //us
	int 			state;
	spinlock_t		lock;
	int			use_count;
	struct hrtimer		timer;
	wait_queue_head_t	wq;
};

static void wiegand_out_data_reset(struct wiegand_out_dev *wiegand_out)
{
	gpio_direction_output(wiegand_out->data0_pin, 1);
	gpio_direction_output(wiegand_out->data1_pin, 1);
}

static void wiegand_out_set_start_state(struct wiegand_out_dev *wiegand_out)
{
	wiegand_out->state = PLUSE_INTVAL_STATE;
}

static void wiegand_out_set_current_state(struct wiegand_out_dev *wiegand_out)
{
	wiegand_out->state = (wiegand_out->state == PLUSE_WIDTH_STATE) ? PLUSE_INTVAL_STATE : PLUSE_WIDTH_STATE;
}

static void wiegand_out_start_pulse_width_timer(struct wiegand_out_dev *wiegand_out)
{
	int us = wiegand_out->pulse_width;
	int s = us / 1000000;
	ktime_t time = ktime_set(s, (us % 1000000) * 1000);
	hrtimer_start(&wiegand_out->timer, time, HRTIMER_MODE_REL);
}

static void wiegand_out_start_pulse_intval_timer(struct wiegand_out_dev *wiegand_out)
{
	int us = wiegand_out->pulse_intval;
	int s = us / 1000000;
	ktime_t time = ktime_set(s, (us % 1000000) * 1000);
	hrtimer_start(&wiegand_out->timer, time, HRTIMER_MODE_REL);
}

static void wiegand_out_start_write(struct wiegand_out_dev *wiegand_out)
{
	wiegand_out->pos = 0;
	wiegand_out_set_start_state(wiegand_out);
	wiegand_out_data_reset(wiegand_out);
	hrtimer_start(&wiegand_out->timer, ktime_set(0, 0), HRTIMER_MODE_REL);
}

static int wiegand_out_check_data(struct wiegand_out_dev *wiegand_out)
{
	int i;

	for (i = 0; i < wiegand_out->data_length; i++) {
		if (wiegand_out->wiegand_out_data[i] != WIEGAND_OUT0_DATA &&
			wiegand_out->wiegand_out_data[i] != WIEGAND_OUT1_DATA)
			return -1;
	}

	return 0;
}

static enum hrtimer_restart wiegand_out_timeout(struct hrtimer *timer)
{
	struct wiegand_out_dev *wiegand_out = container_of(timer, struct wiegand_out_dev, timer);

	wiegand_out_set_current_state(wiegand_out);

	if (wiegand_out->state == PLUSE_WIDTH_STATE) {
		if (wiegand_out->pos == wiegand_out->data_length) {
			if(waitqueue_active(&wiegand_out->wq))
				wake_up_interruptible(&wiegand_out->wq);
			
			return HRTIMER_NORESTART;
		}
		
		if (wiegand_out->wiegand_out_data[wiegand_out->pos] == WIEGAND_OUT0_DATA)
			gpio_direction_output(wiegand_out->data0_pin, 0);
		else
			gpio_direction_output(wiegand_out->data1_pin, 0);
		
		wiegand_out->pos++;
		wiegand_out_start_pulse_width_timer(wiegand_out);
	}
	else {
		gpio_direction_output(wiegand_out->data0_pin, 1);
		gpio_direction_output(wiegand_out->data1_pin, 1);
		wiegand_out_start_pulse_intval_timer(wiegand_out);
	}

	return HRTIMER_NORESTART;
}

static int wiegand_out_open(struct inode *inode, struct file *filp)
{
	struct miscdevice *dev = filp->private_data;
	struct wiegand_out_dev *wiegand_out = container_of(dev, struct wiegand_out_dev, mdev);

	spin_lock(&wiegand_out->lock);
	if (wiegand_out->use_count > 0) {
		spin_unlock(&wiegand_out->lock);
		return -EBUSY;
	}
	wiegand_out->use_count++;		
	spin_unlock(&wiegand_out->lock);

	wiegand_out_data_reset(wiegand_out);
	return 0;
}

static int wiegand_out_release(struct inode *inode, struct file *filp)
{
	struct miscdevice *dev = filp->private_data;
	struct wiegand_out_dev *wiegand_out = container_of(dev, struct wiegand_out_dev, mdev);

	spin_lock(&wiegand_out->lock);
	wiegand_out->use_count--;		
	spin_unlock(&wiegand_out->lock);

	return 0;
}

static ssize_t wiegand_out_write(struct file *filp, const char __user *buf, size_t size, loff_t *l)
{
	int ret;
	int us;
	int s;
	struct miscdevice *dev = filp->private_data;
	struct wiegand_out_dev *wiegand_out = container_of(dev, struct wiegand_out_dev, mdev);

	if (filp->f_flags & O_NONBLOCK)
		return -EAGAIN;

	if (size > MAX_WIEGAND_DATA_LEN) {
		printk("ERROR: wiegand out data length error, max is %d, please check.\n", MAX_WIEGAND_DATA_LEN);
		return -EFAULT;
	}

	if (copy_from_user(wiegand_out->wiegand_out_data, buf, size))
		return -EFAULT;

	wiegand_out->data_length = size;
	ret = wiegand_out_check_data(wiegand_out);
	if (ret) {
		printk("ERROR: wiegand out data format error, must be '0' or '1', please check.\n");
		return -EFAULT;
	}

	wiegand_out_start_write(wiegand_out);

	us = (wiegand_out->pulse_width + wiegand_out->pulse_intval)
			* wiegand_out->data_length;
	s = us / 1000000;
	ret = interruptible_sleep_on_timeout(&wiegand_out->wq, (s + 2) * HZ);
	if (!ret) {
		printk("wiegand write timeout\n");
		return -EIO;
	}

	return 0;
}

static long wiegand_out_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct miscdevice *dev = filp->private_data;
	struct wiegand_out_dev *wiegand_out = container_of(dev, struct wiegand_out_dev, mdev);
	int cs;

	switch (cmd) {
	case WIEGAND_PULSE_WIDTH:
	{
		if(get_user(cs, (unsigned int *)arg))
			return -EINVAL;
		wiegand_out->pulse_width = cs;
		break;
	}

	case WIEGAND_PULSE_INTERVAL:
	{
		if(get_user(cs, (unsigned int *)arg))
			return -EINVAL;
		wiegand_out->pulse_intval = cs;
		break;
	}

	default:
		return -EINVAL;
	}

	return 0;
}

static struct file_operations wiegand_out_misc_fops = {
	.open		= wiegand_out_open,
	.release	= wiegand_out_release,
	.write		= wiegand_out_write,
	.unlocked_ioctl	= wiegand_out_ioctl,
};

static int wiegand_out_probe(struct platform_device *pdev)
{
	int ret = -1;
	struct wiegand_out_dev *wiegand_out;
	struct wiegand_platform_data *pdata;

	printk(" WIEGAND OUT VERSION =  %s  \n",WIEGANDOUTDRV_LIB_VERSION);

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata) {
		dev_err(&pdev->dev, "Failed to get platform_data %s %d.\n", __FUNCTION__, __LINE__);
		return -ENXIO;
	}

	wiegand_out = kzalloc(sizeof(struct wiegand_out_dev), GFP_KERNEL);
	if (!wiegand_out) {
		printk("%s: alloc mem failed.\n", __FUNCTION__);
		ret = -ENOMEM;
	}
	wiegand_out->data0_pin = pdata->data0_pin;
	wiegand_out->data1_pin = pdata->data1_pin;

	if (gpio_is_valid(wiegand_out->data0_pin)) {
		ret = gpio_request(wiegand_out->data0_pin, "WIEGAND_OUT_DATA0");
		if (ret < 0) {
			printk("ERROR: request wiegand_out_data0 gpio failed.\n");
			goto err_gpio_request0;
		}
	}
	else {
		printk("ERROR: wiegand_out_data0 gpio is invalid.\n");
		goto err_gpio_request0;
	}

	if (gpio_is_valid(wiegand_out->data1_pin)) {
		ret = gpio_request(wiegand_out->data1_pin, "WIEGAND_OUT_DATA1");
		if (ret < 0) {
			printk("ERROR: request wiegand_out_data1 gpio failed.\n");
			goto err_gpio_request1;
		}
	}
	else {
		printk("ERROR: wiegand_out_data1 gpio is invalid.\n");
		goto err_gpio_request1;
	}

	wiegand_out->dev = &pdev->dev;
	wiegand_out->mdev.minor = MISC_DYNAMIC_MINOR;
	wiegand_out->mdev.name =  "dummy";
	wiegand_out->mdev.fops = &wiegand_out_misc_fops;

	wiegand_out_data_reset(wiegand_out);
	wiegand_out->pulse_width = DEF_PULSE_WIDTH;
	wiegand_out->pulse_intval = DEF_PULSE_INTERVAL;
	wiegand_out->data_length = DEF_DATA_LENGTH;

	spin_lock_init(&wiegand_out->lock);
	init_waitqueue_head(&wiegand_out->wq);
	hrtimer_init(&wiegand_out->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	wiegand_out->timer.function = wiegand_out_timeout;

	ret = misc_register(&wiegand_out->mdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "misc_register failed %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
		goto err_registe_misc;
	}

	platform_set_drvdata(pdev, wiegand_out);
	printk("Weigand out driver register success.\n");

	return 0;

err_registe_misc:
	gpio_free(wiegand_out->data1_pin);
err_gpio_request1:
	gpio_free(wiegand_out->data0_pin);
err_gpio_request0:
	kfree(wiegand_out);
	return ret;
}

static int wiegand_out_remove(struct platform_device *dev)
{
	struct wiegand_out_dev *wiegand_out = platform_get_drvdata(dev);
	misc_deregister(&wiegand_out->mdev);
	gpio_free(wiegand_out->data0_pin);
	gpio_free(wiegand_out->data1_pin);
	kfree(wiegand_out);

	return 0;
}

static struct platform_driver wiegand_out_driver = {
	.probe		= wiegand_out_probe,
	.remove		= wiegand_out_remove,
	.driver		= {
		.name	= "dummy",
	},
};

static int __init wiegand_out_init(void)
{
	return platform_driver_register(&wiegand_out_driver);
}

static void __exit wiegand_out_exit(void)
{
	platform_driver_unregister(&wiegand_out_driver);
}

module_init(wiegand_out_init);
module_exit(wiegand_out_exit);

