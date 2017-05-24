#include <linux/module.h>
#include <linux/ioport.h>	/* resource */
#include <linux/irq.h>	/* IRQ_EINT(23) */
#include <linux/gpio.h>	/* S5PV210_GPH3(0) */
#include <linux/platform_device.h> /* platform_device_register() */
#include <linux/gpio_keys.h>
#include <linux/input.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>


#define BMA150_ADDR			0x38
#define BMA150_WRITE			0x00
#define BMA150_READ			0x01

#define clk_out()		s3c_gpio_cfgpin(S5PV210_GPD1(5),S3C_GPIO_OUTPUT)
#define dat_out()		s3c_gpio_cfgpin(S5PV210_GPD1(4),S3C_GPIO_OUTPUT)
#define dat_in()		s3c_gpio_cfgpin(S5PV210_GPD1(4),S3C_GPIO_INPUT)
#define clk_clear()	gpio_set_value(S5PV210_GPD1(5), 0)
#define clk_set()		gpio_set_value(S5PV210_GPD1(5), 1)
#define dat_clear()	gpio_set_value(S5PV210_GPD1(4), 0)
#define dat_set()		gpio_set_value(S5PV210_GPD1(4), 1)
#define get_data_in()	gpio_get_value(S5PV210_GPD1(4))
#define demo_i2c_delay()		udelay(50)

static void demo_i2c_send_byte(unsigned char data)
{
	signed char i;

	dat_out();
	clk_clear();
	for(i=7;i>=0;i--){
		if(data&(1<<i))
			dat_set();
		else
			dat_clear();
		demo_i2c_delay();
		clk_set();
		demo_i2c_delay();/* 对方读取数据 */
		clk_clear();
	}
}
static unsigned char demo_i2c_receive_byte(void)
{
	signed char i;
	unsigned char data = 0;

	dat_in();
	clk_clear();
	for(i=7;i>=0;i--){
		demo_i2c_delay();
		clk_set();
		demo_i2c_delay();
	//	data = data<<1;
		data |= get_data_in()<<i;
		clk_clear();
	}
	return data;
}
static void demo_i2c_send_ack(unsigned char ack)
{
	dat_out();
	clk_clear();
	if(ack)
		dat_set();
	else
		dat_clear();
	demo_i2c_delay();
	clk_set();
	demo_i2c_delay();/* 对方读取应答 */
	clk_clear();
}
static unsigned char demo_i2c_receive_ack(void)
{
	unsigned char ack = 0;

	dat_in();
	clk_clear();
	demo_i2c_delay();
	clk_set();
	demo_i2c_delay();
	ack = get_data_in();
	clk_clear();
	return ack;
}
static void demo_i2c_start(void)
{
	dat_out();
	dat_set();
	clk_set();
	demo_i2c_delay();
	dat_clear();
	demo_i2c_delay();
	clk_clear();	
}
static void demo_i2c_stop(void)
{
	dat_out();
	dat_clear();
	clk_set();
	demo_i2c_delay();
	dat_set();
	demo_i2c_delay();
	clk_clear();	
}

static void demo_i2c_init(void)
{
	clk_out();
	dat_out();
	clk_clear();
	dat_clear();
}
static void demo_i2c_send(unsigned char reg,unsigned char *buff,int len)
{
	int i = 0;
	demo_i2c_start();
	demo_i2c_send_byte((BMA150_ADDR<<1)|BMA150_WRITE);/* 发送地址 */
	demo_i2c_receive_ack();
	demo_i2c_send_byte(reg);
	demo_i2c_receive_ack();
	
	while(len--){
		demo_i2c_send_byte(buff[i++]);
		demo_i2c_receive_ack();
	}
	demo_i2c_stop();
}
static void demo_i2c_receive(unsigned char reg,unsigned char *buff,int len)
{
	int i = 0;
	demo_i2c_start();
	demo_i2c_send_byte((BMA150_ADDR<<1)|BMA150_WRITE);/* 发送地址 */
	demo_i2c_receive_ack();
	demo_i2c_send_byte(reg);
	demo_i2c_receive_ack();
	demo_i2c_stop();
	
	demo_i2c_start();
	demo_i2c_send_byte((BMA150_ADDR<<1)|BMA150_READ);/* 发送地址 */
	demo_i2c_receive_ack();
	while(len--){
		buff[i++] = demo_i2c_receive_byte();
		if(len == 0)
			demo_i2c_send_ack(1);
		else
			demo_i2c_send_ack(0);
	}
	demo_i2c_stop();
}
static int demo_bma150_open(struct inode *pinode, struct file *pfile)
{
	unsigned char chip_id;
	demo_i2c_receive(0x00,&chip_id,1);
	printk("%s,%d,id = %d\n",__FUNCTION__,__LINE__,chip_id);
	
	return 0;
}
static ssize_t demo_bma150_read(struct file *pfile, char __user *buffer, size_t count, loff_t *offset)
{
	unsigned char data[6];
	signed short x,y,z;
	
	demo_i2c_receive(0x02,data,6);
	x = (data[0]>>6)|(data[1]<<2);
	y = (data[2]>>6)|(data[3]<<2);
	z = (data[4]>>6)|(data[5]<<2);
	
	x = (signed short)(x<<6)>>6;/* 符号位扩展 */
	y = (signed short)(y<<6)>>6;
	z = (signed short)(z<<6)>>6;
	printk("x=%d,y=%d,z=%d\n",x,y,z);
	return 1;
}
static struct file_operations bma150_fops = {
	.owner = THIS_MODULE,
	.open = demo_bma150_open,
	.read = demo_bma150_read,
};
static struct miscdevice bma150_ops = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "bma150_dev",
	.fops = &bma150_fops,
};
static int __init demo_bma150_init(void)
{
	printk("%s,%d\n",__FUNCTION__,__LINE__);
	demo_i2c_init();
	return misc_register(&bma150_ops);
}
static void __exit demo_bma150_exit(void)
{
	printk("%s,%d\n",__FUNCTION__,__LINE__);
	misc_deregister(&bma150_ops);
}

module_init(demo_bma150_init);
module_exit(demo_bma150_exit);
MODULE_LICENSE("GPL");
