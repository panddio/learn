#include <linux/module.h>
#include <linux/ioport.h>	/* resource */
#include <linux/irq.h>	    /* IRQ_EINT(23) */
#include <linux/gpio.h>	    /* S5PV210_GPH3(0) */
#include <linux/platform_device.h> /* platform_device_register() */
#include <linux/gpio_keys.h>  /* gpio_keys_button */
#include <linux/input.h>


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


static void	s5pv210_buttons_device_release(struct device *pdev)
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
		.release       = s5pv210_buttons_device_release,
	},
};

static int __init s5pv210_buttons_device_init(void)
{
	return platform_device_register(&s5pv210_buttons_dev);
}

static void __exit s5pv210_buttons_device_exit(void)
{
	platform_device_unregister(&s5pv210_buttons_dev);
	return;
}

module_init(s5pv210_buttons_device_init);
module_exit(s5pv210_buttons_device_exit);
MODULE_LICENSE("GPL");
