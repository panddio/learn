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
#include <linux/module.h>

#define WIEGANDINDRV_LIB_VERSION		"1.0.1 ZLM60"__DATE__	/* DRV LIB VERSION */

#define DEF_PULSE_WIDTH		100 //us
#define DEF_PULSE_INTERVAL	1000 //us
#define DEF_DATA_LENGTH		26 //bit
#define DEVIATION		100 //us

struct wiegand_in_dev {
	struct device		*dev;
	struct miscdevice	mdev;
	unsigned int		data0_pin;
	unsigned int		data1_pin;
	unsigned int		current_data[2];
	unsigned int		wiegand_in_data[2];
	int			data_length;
	int			recvd_length;
	int			pulse_width;
	int			pulse_intval;
	int			error;
	spinlock_t		lock;
	int			use_count;
	struct hrtimer		timer;
	wait_queue_head_t	wq;
	struct timeval 		latest;
	struct timeval 		now;
};

static void wiegand_in_data_reset(struct wiegand_in_dev *wiegand_in)
{
	wiegand_in->recvd_length = -1;
	wiegand_in->current_data[0] = 0;
	wiegand_in->current_data[1] = 0;
	wiegand_in->wiegand_in_data[0] = 0;
	wiegand_in->wiegand_in_data[1] = 0;
	wiegand_in->error = 0;
}

static int wiegand_in_open(struct inode *inode, struct file *filp)
{
	struct miscdevice *dev = filp->private_data;
	struct wiegand_in_dev *wiegand_in = container_of(dev, struct wiegand_in_dev, mdev);

	spin_lock(&wiegand_in->lock);
	if (wiegand_in->use_count > 0) {
		spin_unlock(&wiegand_in->lock);
		return -EBUSY;
	}
	wiegand_in->use_count++;
	spin_unlock(&wiegand_in->lock);

	wiegand_in_data_reset(wiegand_in);
	enable_irq(gpio_to_irq(wiegand_in->data0_pin));
	enable_irq(gpio_to_irq(wiegand_in->data1_pin));
	return 0;
}

static int wiegand_in_release(struct inode *inode, struct file *filp)
{
	struct miscdevice *dev = filp->private_data;
	struct wiegand_in_dev *wiegand_in = container_of(dev, struct wiegand_in_dev, mdev);

	disable_irq(gpio_to_irq(wiegand_in->data0_pin));
	disable_irq(gpio_to_irq(wiegand_in->data1_pin));
	spin_lock(&wiegand_in->lock);
	wiegand_in->use_count--;
	spin_unlock(&wiegand_in->lock);

	return 0;
}

static ssize_t wiegand_in_read(struct file *filp, char *buf, size_t size, loff_t *l)
{
	struct miscdevice *dev = filp->private_data;
	struct wiegand_in_dev *wiegand_in = container_of(dev, struct wiegand_in_dev, mdev);

	if (filp->f_flags & O_NONBLOCK)
		return -EAGAIN;

	if (wait_event_interruptible(wiegand_in->wq,
		(wiegand_in->wiegand_in_data[0] > 0) || (wiegand_in->error)))
		return -ERESTARTSYS;

	if(wiegand_in->wiegand_in_data[0] > 0) {
		if(copy_to_user(buf, wiegand_in->wiegand_in_data,
			sizeof(wiegand_in->wiegand_in_data)))
			return -EFAULT;
		wiegand_in->wiegand_in_data[0] = 0;
		wiegand_in->wiegand_in_data[1] = 0;

		return sizeof(wiegand_in->wiegand_in_data);
	}
	wiegand_in->error = 0;

	return 0;
}

static unsigned int wiegand_in_poll(struct file *filp, poll_table *wait)
{
	unsigned int mask = 0;

	struct miscdevice *dev = filp->private_data;
	struct wiegand_in_dev *wiegand_in = container_of(dev, struct wiegand_in_dev, mdev);
	poll_wait(filp, &wiegand_in->wq, wait);

	if( wiegand_in->wiegand_in_data[0] )
		mask |= POLLIN | POLLRDNORM;

	return mask;
}

static long wiegand_in_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct miscdevice *dev = filp->private_data;
	struct wiegand_in_dev *wiegand_in = container_of(dev, struct wiegand_in_dev, mdev);
	int cs;

	switch (cmd) {
	case WIEGAND_PULSE_WIDTH:
	{
		if(get_user(cs, (unsigned int *)arg))
			return -EINVAL;
		wiegand_in->pulse_width = cs;
		break;
	}

	case WIEGAND_PULSE_INTERVAL:
	{
		if(get_user(cs, (unsigned int *)arg))
			return -EINVAL;
		wiegand_in->pulse_intval = cs;
		break;
	}

	case WIEGAND_FORMAT:
	{
		if(get_user(cs, (unsigned int *)arg))
			return -EINVAL;
		wiegand_in->data_length = cs;
		break;
	}

	case WIEGAND_READ:
	{
		if(wiegand_in->wiegand_in_data[0]) {
			if( copy_to_user((unsigned int *)arg,
				wiegand_in->wiegand_in_data, sizeof(wiegand_in->wiegand_in_data)))
				return -EFAULT;
			wiegand_in->wiegand_in_data[0] = 0;
			wiegand_in->wiegand_in_data[1] = 0;
		}
		break;
	}

	case WIEGAND_STATUS:
	{
		if(wiegand_in->wiegand_in_data[0] == 0)
			cs = 0;
		else
			cs = 1;
		if(put_user(cs, (unsigned int *)arg))
			return -EINVAL;
		break;
	}

	default:
		return -EINVAL;
	}

	return 0;
}

static struct file_operations wiegand_in_misc_fops = {
	.open		= wiegand_in_open,
	.release	= wiegand_in_release,
	.read		= wiegand_in_read,
	.unlocked_ioctl	= wiegand_in_ioctl,
	.poll    	= wiegand_in_poll,
};

static void wiegand_in_check_data(struct wiegand_in_dev *wiegand_in)
{
	if (wiegand_in->recvd_length == wiegand_in->data_length - 1) {
		memcpy(wiegand_in->wiegand_in_data, wiegand_in->current_data, sizeof(wiegand_in->current_data));
		wiegand_in->recvd_length = -1;
		wiegand_in->current_data[0] = 0;
		wiegand_in->current_data[1] = 0;
		wake_up_interruptible(&wiegand_in->wq);
	} else {
		printk("recvd data error: received length = %d, required length = %d\n",
			wiegand_in->recvd_length, wiegand_in->data_length);
		wiegand_in_data_reset(wiegand_in);
		wiegand_in->error = 1;
		wake_up_interruptible(&wiegand_in->wq);
	}
}

static enum hrtimer_restart wiegand_in_timeout(struct hrtimer * timer)
{
	struct wiegand_in_dev *wiegand_in = container_of(timer, struct wiegand_in_dev, timer);
	wiegand_in_check_data(wiegand_in);
	return HRTIMER_NORESTART;
}

static void wiegand_in_reset_timer(struct wiegand_in_dev *wiegand_in)
{
	int us = (wiegand_in->pulse_width + wiegand_in->pulse_intval)
		* wiegand_in->data_length;
	int s = us / 1000000;
	ktime_t time = ktime_set(s, (us % 1000000) * 1000);
	hrtimer_start(&wiegand_in->timer, time, HRTIMER_MODE_REL);
}

static int wiegand_in_check_irq(struct wiegand_in_dev *wiegand_in)
{
	int diff;

	if (wiegand_in->recvd_length < 0) {
		do_gettimeofday(&wiegand_in->latest);
		return 0;
	}

	/* Check how much time we have used already */
	do_gettimeofday(&wiegand_in->now);
	diff = wiegand_in->now.tv_usec - wiegand_in->latest.tv_usec;

	/* check fake interrupt */
	if (diff < wiegand_in->pulse_width )//+ wiegand_in->pulse_intval - DEVIATION)
		return -1;
	/*
	 * if intarval is greater than DEVIATION,
	 * then cheet it as beginning of another scan
	 * and discard current data
	 */
	else if (diff > wiegand_in->pulse_width + wiegand_in->pulse_intval
					+ ((wiegand_in->pulse_width + wiegand_in->pulse_intval)<<1)) {
		hrtimer_cancel(&wiegand_in->timer);
		wiegand_in_data_reset(wiegand_in);
		return -1;
	}

	wiegand_in->latest.tv_sec = wiegand_in->now.tv_sec;
	wiegand_in->latest.tv_usec = wiegand_in->now.tv_usec;
	return 0;
}

static irqreturn_t wiegand_in_interrupt(int irq, void *dev_id)
{
	struct wiegand_in_dev *wiegand_in = (struct wiegand_in_dev *)dev_id;

	if (wiegand_in_check_irq(wiegand_in))
		return IRQ_HANDLED;

	if (wiegand_in->recvd_length < 0)
		wiegand_in_reset_timer(wiegand_in);

	wiegand_in->recvd_length++;
	wiegand_in->current_data[1] <<= 1;
	wiegand_in->current_data[1] |= ((wiegand_in->current_data[0] >> 31) & 0x01);
	wiegand_in->current_data[0] <<= 1;
	if (irq == gpio_to_irq(wiegand_in->data1_pin))
		wiegand_in->current_data[0] |= 1;
	return IRQ_HANDLED;
}

static int wiegand_in_probe(struct platform_device *pdev)
{
	int ret;
	struct wiegand_in_dev *wiegand_in;
	struct wiegand_platform_data *pdata;

	printk(" WIEGAND IN VERSION =  %s  \n",WIEGANDINDRV_LIB_VERSION);

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata) {
		dev_err(&pdev->dev, "Failed to get platform_data %s %d.\n", __FUNCTION__, __LINE__);
		return -ENXIO;
	}

	wiegand_in = kzalloc(sizeof(struct wiegand_in_dev), GFP_KERNEL);
	if (!wiegand_in) {
		printk("%s: alloc mem failed.\n", __FUNCTION__);
		ret = -ENOMEM;
	}

#if 1
	wiegand_in->data0_pin = pdata->data1_pin;
	wiegand_in->data1_pin = pdata->data0_pin;
#else
	wiegand_in->data0_pin = pdata->data0_pin;
	wiegand_in->data1_pin = pdata->data1_pin;
#endif

	if (gpio_is_valid(wiegand_in->data0_pin)) {
		ret = gpio_request(wiegand_in->data0_pin, "WIEGAND_IN_DATA0");
		gpio_direction_input(wiegand_in->data0_pin);
		if (ret < 0) {
			printk("ERROR: request wiegand_in_data0 gpio failed.\n");
			goto err_gpio_request0;
		}
	}
	else {
		printk("ERROR: wiegand_in_data0 gpio is invalid.\n");
		goto err_gpio_request0;
	}
	if (gpio_is_valid(wiegand_in->data1_pin)) {
		ret = gpio_request(wiegand_in->data1_pin, "WIEGAND_IN_DATA1");
		gpio_direction_input(wiegand_in->data1_pin);
		if (ret < 0) {
			printk("ERROR: request wiegand_in_data1 gpio failed.\n");
			goto err_gpio_request1;
		}
	}
	else {
		printk("ERROR: wiegand_in_data1 gpio is invalid.\n");
		goto err_gpio_request1;
	}

	ret = request_irq(gpio_to_irq(wiegand_in->data0_pin),
		wiegand_in_interrupt,
		IRQF_DISABLED |
		IRQF_TRIGGER_FALLING,
		"wiegand_in_data0", wiegand_in);
	if (ret < 0) {
		printk("ERROR: request wiegand_in_data0 irq failed.\n");
		goto err_request_irq0;
	}
	disable_irq(gpio_to_irq(wiegand_in->data0_pin));
	ret = request_irq(gpio_to_irq(wiegand_in->data1_pin),
		wiegand_in_interrupt,
		IRQF_DISABLED |
		IRQF_TRIGGER_FALLING,
		"wiegand_in_data1", wiegand_in);
	if (ret < 0) {
		printk("ERROR: request wiegand_in_data1 irq failed.\n");
		goto err_request_irq1;
	}
	disable_irq(gpio_to_irq(wiegand_in->data1_pin));

	wiegand_in->dev = &pdev->dev;
	wiegand_in->mdev.minor = MISC_DYNAMIC_MINOR;
	wiegand_in->mdev.name =  "wiegand_in";
	wiegand_in->mdev.fops = &wiegand_in_misc_fops;

	wiegand_in_data_reset(wiegand_in);
	wiegand_in->pulse_width = DEF_PULSE_WIDTH;
	wiegand_in->pulse_intval = DEF_PULSE_INTERVAL;
	wiegand_in->data_length = DEF_DATA_LENGTH;

	spin_lock_init(&wiegand_in->lock);
	init_waitqueue_head(&wiegand_in->wq);
	hrtimer_init(&wiegand_in->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	wiegand_in->timer.function = wiegand_in_timeout;

	ret = misc_register(&wiegand_in->mdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "misc_register failed %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
		goto err_registe_misc;
	}

	platform_set_drvdata(pdev, wiegand_in);
	printk("Weigand in driver register success.\n");

	return 0;

err_registe_misc:
	free_irq(gpio_to_irq(wiegand_in->data1_pin), NULL);
err_request_irq1:
	free_irq(gpio_to_irq(wiegand_in->data0_pin), NULL);
err_request_irq0:
	gpio_free(wiegand_in->data1_pin);
err_gpio_request1:
	gpio_free(wiegand_in->data0_pin);
err_gpio_request0:
	kfree(wiegand_in);
	return ret;
}

static int wiegand_in_remove(struct platform_device *dev)
{
	struct wiegand_in_dev *wiegand_in = platform_get_drvdata(dev);
	misc_deregister(&wiegand_in->mdev);
	free_irq(gpio_to_irq(wiegand_in->data0_pin), wiegand_in);
	free_irq(gpio_to_irq(wiegand_in->data1_pin), wiegand_in);
	gpio_free(wiegand_in->data0_pin);
	gpio_free(wiegand_in->data1_pin);
	kfree(wiegand_in);

	return 0;
}

static struct platform_driver wiegand_in_driver = {
	.probe		= wiegand_in_probe,
	.remove		= wiegand_in_remove,
	.driver		= {
		.name	= "wiegand_in",
	},
};

static int __init wiegand_in_init(void)
{
	return platform_driver_register(&wiegand_in_driver);
}

static void __exit wiegand_in_exit(void)
{
	platform_driver_unregister(&wiegand_in_driver);
}

module_init(wiegand_in_init);
module_exit(wiegand_in_exit);
MODULE_LICENSE("GPL");

