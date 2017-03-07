配置：
source build/envsetup.sh

编译uboot:
cd bootable/bootloader/uboot
make aw808_wisesquare_an51_msc0


cat build/smk.sh | grep  aw808
build/smk.sh --preset=aw808_v11_wisesquare_iwop -j32

======================================================================
m200 watch:
版级代码所在目录:
qiuweiwang@sw1:~/4.3/kernel/arch/mips/xburst/soc-m200/chip-m200/watch$

该目录下的common目录下的keyboard_gpio.c


/4.3/kernel/drivers/input/keyboard/gpio_keys.c
======================================================================

out/host/linux-x86/bin/mkbootimg --kernel kernel-3.10.14/arch/mips/boot/compressed/zImage  --ramdisk out/target/product/aw808/ramdisk.img --output out/target/product/aw808/boot.img

./out/host/linux-x86/bin/mkbootimg  --kernel ./kernel/arch/mips/boot/compressed/zImage --ramdisk ./out/target/product/aw808_iwop/ramdisk.img  --output ./out/target/product/aw808_iwop/boot.img

out/host/linux-x86/bin/mkbootimg --kernel kernel-3.10.14/arch/mips/boot/compressed/zImage --ramdisk out/target/product/aw808/ramdisk.img --output out/target/product/aw808/boot.img

/5.1/kernel-3.10.14/arch/mips/xburst/soc-m200/chip-m200/watch/common$ vi i2c_bus.c
======================================================================
烧录kernel:
adb push boot.img /data
cat boot.img > /dev/block/mmcblk0p1 

======================================================================
从历史命令中查看与sshfs相关的
history | grep sshfs
sshfs qiuweiwang@194.169.1.31:/home/qiuweiwang/ /home/qwwang/server

======================================================================
setenv bootargs mem=256M mem=768M@0x30000000 console=ttyS3,57600n8 ip=off root=/dev/mmcblk0p5 bk_root=/dev/mmcblk0p7 rw rootdelay=2 keep_bootcon


qwwang@qiuweiwang:/$ /etc/init.d/xinetd start
 * Starting internet superserver xinetd                                  [ OK ]

sudo /etc/init.d/tftpd-hpa start
ps -aux | grep 6847
sudo chmnod 777 /var/lib/tftpboot/
======================================================================
在内核中， sysfs 属性一般是由 __ATTR 系列的宏来声明的，如对设备的使用 DEVICE_ATTR ，对总线使用 BUS_ATTR ，对驱动使用 DRIVER_ATTR ，对类别(class)使用 CLASS_ATTR, 这四个高级的宏来自于 <include/linux/device.h>, 都是以更低层的来自 <include/linux/sysfs.h> 中的 __ATTR/__ATRR_RO 宏实现。这几个东东的区别就是，DEVICE_ATTR对应的文件在/sys/devices/目录中对应的device下面。而其他几个分别在driver，bus，class中对应的目录下

在documentation/driver-model/Device.txt中有对DEVICE_ATTR的详细介绍，这儿主要说明使用方法。

先看看DEVICE_ATTR的原型：
DEVICE_ATTR(_name, _mode, _show, _store)
_name：名称，也就是将在sys fs中生成的文件名称。
_mode：上述文件的访问权限，与普通文件相同，UGO的格式。
_show：显示函数，cat该文件时，此函数被调用。
_store：写函数，echo内容到该文件时，此函数被调用。

在终端查看到接口，当我们将数据 echo 到接口中时，在上层实际上完成了一次 write 操作，对应到 kernel ，调用了驱动中的 “store”。同理，当我们cat 一个 接口时则会调用 “show” 。

======================================================================
struct mmc_host是mmc core层与host层的接口，mmc_host.ops是控制host完成用户请求的接口函数集，其类型是struct mmc_host_ops，该结构体定义在include/linux/mmc/host.h文件中：

[cpp] view plaincopy在CODE上查看代码片派生到我的代码片
 83structmmc_host_ops {  

 88   int (*enable)(struct mmc_host *host);  
 89   int (*disable)(struct mmc_host *host);  
 
 98   void    (*post_req)(structmmc_host *host, struct mmc_request *req,  
 99                int err);  
100   void    (*pre_req)(struct mmc_host*host, struct mmc_request *req,  
101               bool is_first_req);  
102   void    (*request)(struct mmc_host*host, struct mmc_request *req);  
103   /* 
104    * Avoid calling these three functions too often or in a "fastpath", 
105    * since underlaying controller might implement them in an expensive 
106    * and/or slow way. 
107    * 
108    * Also note that these functions might sleep, so don't call them 
109    * in the atomic contexts! 
110    * 
111    * Return values for the get_ro callback should be: 
112    *   0 for a read/write card 
113    *   1 for a read-only card 
114    *   -ENOSYS when not supported(equal to NULL callback) 
115    *   or a negative errno value whensomething bad happened 
116    * 
117    * Return values for the get_cd callback should be: 
118    *   0 for a absent card 
119    *   1 for a present card 
120    *   -ENOSYS when not supported(equal to NULL callback) 
121    *   or a negative errno value whensomething bad happened 
122    */  
123   void    (*set_ios)(struct mmc_host*host, struct mmc_ios *ios);  
124   int (*get_ro)(struct mmc_host *host);  
125   int (*get_cd)(struct mmc_host *host);  
126  
127   void    (*enable_sdio_irq)(structmmc_host *host, int enable);  
128  
129   /* optional callback for HC quirks */  
130   void    (*init_card)(struct mmc_host*host, struct mmc_card *card);  
131  
132   int (*start_signal_voltage_switch)(struct mmc_host *host, struct mmc_ios*ios);  
133  
134   /* Check if the card is pulling dat[0:3] low */  
135   int (*card_busy)(struct mmc_host *host);  
136  
137   /* The tuning command opcode value is different for SD and eMMC cards */  
138   int (*execute_tuning)(struct mmc_host *host, u32 opcode);  
139   int (*select_drive_strength)(unsigned int max_dtr, int host_drv, intcard_drv);  
140   void    (*hw_reset)(struct mmc_host*host);  
141   void    (*card_event)(structmmc_host *host);  
142};  


request函数用于处理用户的请求。

set_ios函数用于设置SDI的控制参数，如时钟、总线宽度等等。

get_ro函数用于探测SD卡是否有写保护。

get_cd函数用于探测卡是否已插入插槽。

enable_sdio_irq函数用于启动或禁用SDI中断。

需要注意的是，为什么没有对MMC/SD进行读写的read和write函数呢？这是因为Linux块设备的读写操作是通过request函数完成的。

--------------------------------------------------------------------------
jz4775mmc 驱动

0) 两大招
grep -rn "xxx" ./
find ./ -name "xxx"

1) arch/mips/xburst/soc-4775/common/platform.c

179:    int jz_device_register(struct platform_device *pdev,void *pdata)
		{
			pdev->dev.platform_data = pdata;

			return platform_device_register(pdev);
		}
		
274:#define DEF_MSC(NO)		\
275:	static struct resource jz_msc##NO##_resources[] = {..}
287:    struct platform_device jz_msc##NO##_device = {..}

297:  DEF_MSC(0); 
	  这个宏展开 => static struct resource jz_msc0_resources[] = {..}  and 
			        static struct resource jz_msc0_device = {...}
			   
298:  DEF_MSC(1); // 同DEF_MSC(0)
299:  DEF_MSC(2); // 同DEF_MSC(0)


2) arch/mips/xburst/soc-4775/board/zmm220/zmm220-mmc.c

47:   struct jzmmc_platform_data inand_pdata = {..}
72:   struct jzmmc_platform_data tf_pdata = {..}
96:   struct jzmmc_platform_data tf_pdata = {..}
116:  struct jzmmc_platform_data sdio_pdata = {..}

3) arch/mips/xburst/soc-4775/board/zmm220/zmm220-misc.c:
>>> 以下注册设备
628:	jz_device_register(&jz_msc0_device, &inand_pdata); // MSC0 接的是存储
631:	jz_device_register(&jz_msc1_device, &sdio_pdata);  
634:	jz_device_register(&jz_msc2_device, &tf_pdata);    // 可能是wifi模块
638:	jz_device_register(&jz_msc0_device, &tf_pdata);
641:	jz_device_register(&jz_msc2_device, &sdio_pdata);

4) drivers/mmc/host/jz4775_mmc.c

1864:   static struct platform_driver jzmmc_driver = {..}

1877:   static int __init jzmmc_init(void)
		{
			return platform_driver_probe(&jzmmc_driver, jzmmc_probe);
		}
	
5) drivers/mmc/host/jz4775_mmc.c

1684:
static int __init jzmmc_probe(struct platform_device *pdev)
{
	...
	struct jzmmc_host *host = NULL;
	struct mmc_host *mmc;
	...

	mmc = mmc_alloc_host(sizeof(struct jzmmc_host), &pdev->dev); // 原型在core/host.c函数展开如下
		  {
		  	 /* 建立数据结构 */
			 struct mmc_host *host;
			 /*申请 sizeof(struct mmc_host) + sizeof(struct jzmmc_host) 大小空间
			  *struct mmc_host 
			  *{    ..
			  *		unsigned long  private[0] ____cacheline_aligned; //后面有这个长度为零的数组
			  *}
			  */这样 private 的位置正好是 struct jzmmc_host 的首地址
			 host = kzalloc(sizeof(struct mmc_host) + extra, GFP_KERNEL); 

			/* 建立kobject */
			 host->parent = dev;
			 host->class_dev.parent = dev;
			 host->class_dev.class = &mmc_host_class;
			 device_initialize(&host->class_dev);

			/* 初始化等待队列，工作队列 */
			 init_waitqueue_head(&host->wq);
			 INIT_DELAYED_WORK(&host->detect, mmc_rescan); // 初始化延时工作，指定工作函数
			                                               //注意这里的工作队列的延时时间delay为0，
			                                               //因为系统启动的时候不考虑插拔卡
			                                               //目的在系统初始化的时候就扫描查看是否存在卡
			/* 配置控制器 */
			 host->max_hw_segs = 1;
			 host->max_seg_size = PAGE_CACHE_SIZE;

			 host->max_req_size = PAGE_CACHE_SIZE;
			 host->max_blk_size = 512;
			 host->max_blk_count = PAGE_CACHE_SIZE / 512;

			 return host;	  
		  }
	
	host = mmc_priv(mmc); // host = mmc->private，即指向了struct jzmmc_host 结构
	...
	mmc_set_drvdata(pdev, host); //pdev->dev->p->driver_data = host，保存驱动的数据结构
	
	ret = jzmmc_msc_init(host); // 初始化 msc
	
	ret = jzmmc_gpio_init(host);// 初始化连接的IO口，申请中断等
	
	jzmmc_host_init(host, mmc); 
	{
		struct jzmmc_platform_data *pdata = host->pdata;
		
		mmc->ops = &jzmmc_ops; // !!!!

		...

		host->mmc = mmc;
		
		setup_timer(&host->request_timer, jzmmc_request_timeout,
				(unsigned long)host); // 设置mmc host 的定时器
				
		mmc_add_host(mmc); 
		{
			...
			device_add(&host->class_dev);
			...
 			mmc_start_host(host);
 			{
 				mmc_power_off(host);
				mmc_detect_change(host, 0);
 			}
		}
	}
	
	return 0;
	...
}

6) drivers/mmc/host/jz4775_mmc.c

struct mmc_host是mmc core层与host层的接口，mmc_host.ops是控制host完成用户请求的接口函数集，其类型是struct mmc_host_ops，该结构体定义在include/linux/mmc/host.h文件中。

1392:
static const struct mmc_host_ops jzmmc_ops = {
	.request		= jzmmc_request,
	.set_ios		= jzmmc_set_ios,
	.get_ro			= jzmmc_get_read_only,
	.get_cd			= jzmmc_get_card_detect,
	.enable_sdio_irq	= jzmmc_enable_sdio_irq,
};

request ：用于处理用户的请求。
set_ios ：用于设置SDI的控制参数，如时钟、总线宽度等等。
get_ro  ：用于探测SD卡是否有写保护。
get_cd  ：用于探测卡是否已插入插槽。
enable_sdio_irq ：用于启动或禁用SDI中断。

为什么没有对MMC/SD进行读写的read和write函数呢？这是因为Linux块设备的读写操作是通过request函数完成的。

934:
static void jzmmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	...
	
	jzmmc_command_start(host, host->cmd);  //实现命令的传输
	if (host->data)
		jzmmc_data_start(host, host->data);//实现数据的传输
	if (unlikely(test_and_clear_bit(JZMMC_CARD_NEED_INIT, &host->flags)))
		host->cmdat_def &= ~CMDAT_INIT;
}
======================================================================
/data/misc/bluetooth # cat bt_addr
su
echo 1 > /sys/power/wake_lock 

time busybox wget -P /data ftp://qwwang:123456@194.169.2.23//home/qwwang/test.mp3
======================================================================
gitk filename
git reset --hard 00c18a2d0c9b36aae147ad28e320842b3d7fe3de(哈希值)
kernel/sound/oss$ gitk --all &
kernel/arch/mips/xburst/soc-m200/chip-m200/watch/acrab$ gitk sound.c
kernel/arch/mips/xburst/soc-m200/chip-m200/watch/common$ gitk sound.c
======================================================================
zlm60 编译：
platform/
source tools/build/source.sh
make

development/device/device.mk :
U-BOOT-CONFIG := zlm60_v10_uImage_spi_nand
KERNEL-CONFIG := zlm60_linux_spinand_ubi_defconfig

out/target/product/zlm60/image/

>> 编译 system.ubifs :
cd out/target/product/zlm60  &&
./mkfs.ubifs -d system -e 0x1f000 -c 2048 -m 0x800 -o image/system.ubifs


解决在启动时不接串口会进入uboot命令行的问题，修改uboot如下：
include/configs/zlm60.h: 499 行添加
/*
* UART configuration
*/
#define	UART2_RXD_PORT  GPIO_PC(31)

arch/mips/cpu/xburst/x1000/soc.c: 76 行添加
gpio_enable_pull(GPIO_PC(31));
======================================================================
需要说明的是网卡芯片也有“软硬”之分，特别是对与主板板载(LOM)的网卡芯片来说更是如此，这是怎么回事呢?大家知道，以太网接口可分为协议层和物理层。
　　
　　协议层是由一个叫MAC(Media Access Layer，媒体访问层)控制器的单一模块实现。
　　
　　物理层由两部分组成，即PHY(Physical Layer，物理层)和传输器。
　　
　　常见的网卡芯片都是把MAC和PHY集成在一个芯片中，但目前很多主板的南桥芯片已包含了以太网MAC控制功能，只是未提供物理层接口，因此，需外接PHY芯片以提供以太网的接入通道。这类PHY网络芯片就是俗称的“软网卡芯片”，常见的PHY功能的芯片有RTL8201BL、VT6103等等。
　　
　　“软网卡”一般将网络控制芯片的运算部分交由处理器或南桥芯片处理，以简化线路设计，从而降低成本，但其多少会更多占用系统资源.
======================================================================
4.3/kernel/sound/oss:
grep  -nr "attibute_dac_l_gain"  ./

5.1/kernel-3.10.14/sound/soc/ingenic/icodec$:
grep  -nr "2c"  ./ 
grep  -nr "DLV_REG_GCR_DACL"  ./
gedit icdc_d1.c +472

5.1/kernel-3.10.14/:
grep  -nr "SOC_DOUBLE_R_TLV"  ./include/   | grep define
gedit ./include/sound/soc.h +123
======================================================================
0x00000000-0x00200000 : "NAND BOOT partition"   0    16
0x00200000-0x00500000 : "NAND KERNEL partition" 16   24
0x00500000-0x01900000 : "NAND ROOTFS partition" 40   160
0x01900000-0x08000000 : "NAND YAFFS partition"  200  1024-200

>>>
nerase 0 1024
fconfig 192.168.1.12 jdi.cfg
nprog 0 u-boot-nand.bin
fconfig 192.168.1.12 jdiyaffs.cfg
nprog 512 lconfig-normal.bin
fconfig 192.168.1.12 jdi.cfg
nprog 704 linuxlogo240x400.bin
nprog 1024 uImage_ZEM565-20120201

fconfig 192.168.1.12 jdiyaffs.cfg
nprog 2560 rootfsyaffs220151020
nprog 12800 mtdyaffs2tft300-20151022
======================================================================
error while loading shared libraries: libudev.so.0: cannot open shared object file: No such file or directory

locate udev.so
ln -s /lib/i386-linux-gnu/libudev.so.1 ./libudev.so.0
======================================================================
wiegand driver

device 资源定义和注册:
arch/mips/xburst/soc-x1000/chip-x1000/zlm60/common/board_base.c

driver 注册和实现：
driver/misc/wiegand_in.c
======================================================================	    
dd if=/dev/zero of=/dev/mtdblock5 bs=1024 count=3000
3072000 bytes (2.9MB) copied, 3.737917 seconds, 802.6KB/s

dd if=/dev/zero of=/dev/mtdblock5 bs=1M count=4
4194304 bytes (4.0MB) copied, 3.361232 seconds, 1.2MB/s

dd if=/dev/urandom of=/dev/mtdblock5 bs=1M count=4
4194304 bytes (4.0MB) copied, 6.387169 seconds, 641.3KB/s

dd if=/dev/urandom of=/dev/mtdblock5 bs=1024 count=3000
3072000 bytes (2.9MB) copied, 6.199825 seconds, 483.9KB/s
----------------------------------------------------------------------
dd if=/dev/zero of=/data/tt bs=16k count=6000 conv=fsync
98304000 bytes (93.8MB) copied, 17.804461 seconds, 5.3MB/s

dd if=/dev/zero of=/data/tt bs=16k count=6000 
98304000 bytes (93.8MB) copied, 5.389757 seconds, 17.4MB/s

dd if=/data/tt of=/dev/null bs=16k count=6000
98304000 bytes (93.8MB) copied, 4.672038 seconds, 20.1MB/s
----------------------------------------------------------------------
dd if=/dev/zero of=/data/mtdblock5 bs=16k count=6000 conv=fsync
98304000 bytes (93.8MB) copied, 17.743677 seconds, 5.3MB/s

dd if=/dev/zero of=/data/mtdblock5 bs=16k count=6000
98304000 bytes (93.8MB) copied, 5.501961 seconds, 17.0MB/s
======================================================================
linux sfcnand 驱动：
1) 设备资源

>> arch/mips/xburst/soc-x1000/common/platform.c:786
#ifdef CONFIG_JZ_SFC
static struct resource jz_sfc_resources[] = {
	[0] = {
		.flags = IORESOURCE_MEM, // SFC's registers map base address 0x13440000
		.start = SFC_IOBASE,
		.end = SFC_IOBASE + 0x10000 - 1,
	},
	[1] = {
		.flags = IORESOURCE_IRQ,
		.start = IRQ_SFC, //  SFC's IRQ
	},
	[2] = {
		.start = CONFIG_SFC_SPEED,
		.flags = IORESOURCE_BUS,
	}
};

struct platform_device jz_sfc_device = {
	.name = "jz-sfc",
	.id = 0,
	.resource = jz_sfc_resources,
	.num_resources = ARRAY_SIZE(jz_sfc_resources),
};
#endif

>> arch/mips/xburst/soc-x1000/common/board_base.c:19
struct jz_platform_device
{
	struct platform_device *pdevices;
	void *pdata;
	int size;
};

>> arch/mips/xburst/soc-x1000/common/board_base.c:54
定义 platform 设备资源数组
static struct jz_platform_device platform_devices_array[] __initdata = {
#define DEF_DEVICE(DEVICE, DATA, SIZE)  \
	{ .pdevices = DEVICE,   \
		.pdata = DATA, .size = SIZE,}

#ifdef	CONFIG_JZ_SFC
	DEF_DEVICE(&jz_sfc_device,&sfc_info_cfg, sizeof(struct jz_sfc_info)),
	展开如下：
	{
		.pdevices = &jz_sfc_device,
		.pdata    = &sfc_info_cfg,
		.size     = sizeof(struct jz_sfc_info),
	},
#endif
		
};

>> arch/mips/xburst/soc-x1000/include/mach/jzssi.h:187
struct jz_sfc_info {
	u8	chnl;				              /* the chanel of SSI controller */
	u16	bus_num;			             /* spi_master.bus_num */
	unsigned is_pllclk:1;			   /* source clock: 1---pllclk;0---exclk */
	unsigned long	board_size;  /* spi_master.num_chipselect */
	u32	 num_chipselect;
	u32	 allow_cs_same;
	void  *board_info;
	u32  board_info_size;
};

>> arch/mips/xburst/soc-x1000/common/spi_bus.c:485
#elif defined(CONFIG_JZ_SFCNAND)
struct jz_sfc_info sfc_info_cfg = {
	.chnl = 0,
	.bus_num = 0,
	.num_chipselect = 1,
	.board_info = &jz_spi_nand_data,
};
#endif

>> arch/mips/xburst/soc-x1000/common/spi_bus.c:210
struct jz_spi_nand_platform_data jz_spi_nand_data = {
	.jz_spi_support = jz_spi_nand_support_table,  // 程序所支持的nand，spi_bus.c:110
	.num_spi_flash	= ARRAY_SIZE(jz_spi_nand_support_table), // 
	.mtd_partition  = jz_mtd_spinand_partition, // nand 的分区情况，spi_bus.c:76
	.num_partitions = ARRAY_SIZE(jz_mtd_spinand_partition),   // 
};

jz_spi_nand_support_table=((struct jz_spi_nand_platform_data *)(flash->pdata->board_info))->jz_spi_support;
>> arch/mips/xburst/soc-x1000/common/board_base.c:281
注册设备资源：
static int __init board_base_init(void)
{
 	。。。
	pdevices_array_size = ARRAY_SIZE(platform_devices_array);
	for(i = 0; i < pdevices_array_size; i++) {
		if(platform_devices_array[i].size)
			platform_device_add_data(platform_devices_array[i].pdevices,
					platform_devices_array[i].pdata, platform_devices_array[i].size);
		platform_device_register(platform_devices_array[i].pdevices);
	}
	。。。
}
		
>> 执行以下函数之后
platform_device_add_data(platform_devices_array[i].pdevices,
	platform_devices_array[i].pdata, platform_devices_array[i].size);		

最终结果：		
platform_devices_array[i].pdevices->dev.platform_data = &sfc_info_cfg。


2) 驱动分析

>> drivers/mtd/nand/jz_sfcnand.c:1166
static int __init jz_sfc_probe(struct platform_device *pdev)
{
	struct jz_sfc_nand *flash; // 非常重要的结构！
	const char *jz_probe_types[] = {"cmdlinepart",NULL};
	struct jz_spi_support *spi_flash; // 存放nand flash 信息，比如：id 、块大小 、页大小 、Busytime等等

	int err = 0,ret = 0;
	struct nand_chip *chip;  // nand 操作的函数指针
	struct mtd_partition *mtd_sfcnand_partition;
	int num_partitions;
	struct jz_spi_nand_platform_data *param;
	int nand_magic= 0;

	chip = kzalloc(sizeof(struct nand_chip),GFP_KERNEL); // 分配 nand _ship 空间
	if(!chip)
		return -ENOMEM;
	
	flash = kzalloc(sizeof(struct jz_sfc_nand), GFP_KERNEL); // 分配 jz_sfc_nand 空间
	if (!flash) {
		kfree(chip);
		return -ENOMEM;
	}
	
	flash->dev = &pdev->dev;  // 保存 platform_device 中的struct device 结构指针
	flash->pdata = pdev->dev.platform_data; // 保存指向备的私有数据结构的指针， = &sfc_info_cfg  
	
	flash->threshold = THRESHOLD; // ？
	ret=sfc_nand_plat_resource_init(flash,pdev);  // 获取设备资源，初始化 jz_sfc_nand 部分成员
	if(ret) // 非0 则sfc_nand_plat_resource_init() 执行过程出错
	{
		....  // 出错处理
	}
	
	flash->chnl= flash->pdata->chnl; //the chanel of SSI controller， 这里是 0
	flash->tx_addr_plus = 0;
	flash->rx_addr_plus = 0;
	flash->use_dma = 0; // 
	err=0;
	
	/* find and map our resources */
	/* SFC controller initializations for SFC */
	jz_sfc_init_setup(flash); //  SFC controller initializations
	platform_set_drvdata(pdev, flash);
	init_completion(&flash->done);   // 初始化 jz_sfc_nand 中的完成量 struct completion done = 0
	spin_lock_init(&flash->lock_rxtx); //初始化 jz_sfc_nand 中的 spinlock_t		lock_rxtx;
	spin_lock_init(&flash->lock_status); // 初始化 jz_sfc_nand 中的 spinlock_t  lock_status
	
	err = request_irq(flash->irq, jz_sfc_irq, 0, pdev->name, flash); // flash->irq 在sfc_nand_plat_resource_init() 获得
	
	flash->column_cmdaddr_bits=24; // 
	
	jz_get_sfcnand_param(&param,flash,&nand_magic); // 获取烧录工具传下的参数
	if(nand_magic==0x6e616e64){   //如果0x6e616e64 则使用烧录工具传下来的一套参数
		(flash->pdata)->board_info = (void *)param;
	}else{
		param=(flash->pdata)->board_info; // 使用驱动定义的参数
	}
	
	mtd_sfcnand_partition=param->mtd_partition; // nand flash 的分区信息
	num_partitions=param->num_partitions;           // nand flash 的分区数量
	
	
	spi_flash = jz_sfc_nand_probe(flash);  // 匹配具体的 nand flash，并返回存放nand flash 信息的结构指针
	
	// 初始化jz_sfc_nand 中的 struct mtd_info mtd
	flash->mtd.name = "sfc_nand";
	flash->mtd.owner = THIS_MODULE;
	flash->mtd.type = MTD_NANDFLASH;
	flash->mtd.flags |= MTD_CAP_NANDFLASH;
	flash->mtd.erasesize = spi_flash->block_size;
	flash->mtd.writesize = spi_flash->page_size;
	flash->mtd.size = spi_flash->size;
	flash->mtd.oobsize = spi_flash->oobsize;
	flash->mtd.writebufsize = flash->mtd.writesize;
	flash->column_cmdaddr_bits = spi_flash->column_cmdaddr_bits;
	flash->tRD = spi_flash->tRD_maxbusy;
	flash->tPROG = spi_flash->tPROG_maxbusy;
	flash->tBERS = spi_flash->tBERS_maxbusy;
	flash->mtd.bitflip_threshold = flash->mtd.ecc_strength = 1;
	
	// 初始化 struct nand_chip chip
	chip->select_chip = NULL;
	chip->badblockbits = 8;
	chip->scan_bbt = nand_default_bbt;
	chip->block_bad = jz_sfcnand_block_bad_check;
	chip->block_markbad = jz_sfc_nandflash_block_markbad;
	//chip->ecc.layout= &gd5f_ecc_layout_128; // for erase ops
	chip->bbt_erase_shift = chip->phys_erase_shift = ffs(flash->mtd.erasesize) - 1;
	if (!(chip->options & NAND_OWN_BUFFERS))
		    chip->buffers = kmalloc(sizeof(*chip->buffers), GFP_KERNEL);

	/* Set the bad block position */
	if (flash->mtd.writesize > 512 || (chip->options & NAND_BUSWIDTH_16))
	chip->badblockpos = NAND_LARGE_BADBLOCK_POS;
	else
		    chip->badblockpos = NAND_SMALL_BADBLOCK_POS;
		    
	flash->mtd.priv = chip; //  初始化mtd 的私有数据指针

	flash->mtd._erase = jz_sfcnand_erase;
	flash->mtd._read = jz_sfcnand_read;
	flash->mtd._write = jz_sfcnand_write;
	flash->mtd._read_oob = jz_sfcnand_read_oob;
	flash->mtd._write_oob = jz_sfcnand_write_oob;
	flash->mtd._block_isbad = jz_sfcnand_block_isbab;
	flash->mtd._block_markbad = jz_sfcnand_block_markbad;
	
	chip->scan_bbt(&flash->mtd);  // ？
	// 注册mtd 设备
	ret = mtd_device_parse_register(&flash->mtd,jz_probe_types,NULL, mtd_sfcnand_partition, num_partitions);
	if (ret) {
		kfree(flash);
		return -ENODEV;
	}
}

x-loader sfcnand 驱动分析：
#define  SFC_SEND_COMMAND(sfc, a, b, c, d, e, f, g)   do{                       \
        ((struct jz_sfc *)sfc)->cmd = a;                                        \
        ((struct jz_sfc *)sfc)->len = b;                                        \
        ((struct jz_sfc *)sfc)->addr = c;                                       \
        ((struct jz_sfc *)sfc)->addr_len = d;                                   \
        ((struct jz_sfc *)sfc)->addr_plus = 0;                                  \
        ((struct jz_sfc *)sfc)->dummy_byte = e;                                 \
        ((struct jz_sfc *)sfc)->daten = f;                                      \
        SFC_MODE_GENERATE(sfc, a);                                              \
        sfc_send_cmd(sfc, g);                                                   \
} while(0)


git checkout --track ing/sz-master
======================================================================
uboot 的 spl（second program loader）
>> arch/mips/cpu/xburst/x1000/start.S：172
	j	board_init_f // 跳到board_init_f 函数，C代码

>> arch/mips/cpu/xburst/x1000/soc.c ：58
void board_init_f(ulong dummy)
{
	....
	gpio_init();
	enable_uart_clk();
	timer_init();
#ifndef CONFIG_FPGA
#ifdef CONFIG_SPL_CORE_VOLTAGE
	debug("Set core voltage:%dmv\n", CONFIG_SPL_CORE_VOLTAGE);
	spl_regulator_set_voltage(REGULATOR_CORE, CONFIG_SPL_CORE_VOLTAGE);
#endif
#ifdef CONFIG_SPL_MEM_VOLTAGE
	debug("Set mem voltage:%dmv\n", CONFIG_SPL_MEM_VOLTAGE);
	spl_regulator_set_voltage(REGULATOR_MEM, CONFIG_SPL_MEM_VOLTAGE);
#endif
#endif

	clk_prepare();
	pll_init(); // 锁相环
	clk_init(); // 时钟
	sdram_init(); // 内存
	board_init_r(NULL, 0); // 调用board_init_r
}

>> common/spl/spl.c：149
void board_init_r(gd_t *dummy1, ulong dummy2)
{	// 这个函数主要判断是从 nand、mmc、onenand、nor等设备加载uboot代码到初始化好的内存中
	....
	switch (boot_device) {
	             ....
	#ifdef CONFIG_SPL_SPI_NAND
	case BOOT_DEVICE_SPI_NAND:
		spl_spi_nand_load_image();
		break;
	#endif
	#ifdef CONFIG_SPL_SFC_NOR
	case BOOT_DEVICE_SFC_NOR:
		spl_sfc_nor_load_image();
		break;
	#endif
	#ifdef CONFIG_SPL_SFC_NAND
	case BOOT_DEVICE_SFC_NAND:
		spl_sfc_nand_load_image();
		break;
	#endif
		.....
	}
	
	jump_to_image_no_args(&spl_image);
}

mips-linux-gnu-objcopy --remove-section=.dynsym --gap-fill=0xff --pad-to=16384 \
			-I binary -O binary spl/u-boot-spl.bin spl/u-boot-spl-pad.bin
选项说明：
--remove-section=.dynsym：从输出文件中去除掉由sectionname指定的section，可以多次指定，不当会导致输出文件不可用
--gap-fill=0xff：在section之间的空隙中填充0xff	
--pad-to=16384	
-I binary：指定输入的文件，这里是 spl/u-boot-spl.bin
-O binary：指定输出的文件，这里是 spl/u-boot-spl-pad.bin

// 连接spl/u-boot-spl-pad.bin和u-boot.bin，生存最终烧录文件 u-boot-with-spl.bin
cat spl/u-boot-spl-pad.bin u-boot.bin > u-boot-with-spl.bin 
rm spl/u-boot-spl-pad.bin
======================================================================
网卡在物理上具有载波侦听的功能，当网络连接完成或者网络链接断开时，网卡芯片硬件会自动设置寄存器标志位来标识。

如网线链接断开的时候，会将LinkSts清位；重新链接网线，则硬件自动将此位置位。

这样，在网卡驱动中读写该位信息就可一判断网络是否链接通路。

网卡驱动程序通过netif_carrier_on/netif_carrier_off/netif_carrier_ok来和内核网络子系统传递信息。

1】netif_carrier_on【作用】告诉内核子系统网络链接完整。

2】netif_carrier_off【作用】告诉内核子系统网络断开。

3】netif_carrier_ok【作用】查询网络断开还是链接。

以上函数主要是改变net_device dev的state状态来告知内核链路状态的变化。
======================================================================
ubuntu下安装卸载 VMWare Player / WorkStation （.bundle文件）

比如下载下来的VMware Player文件名为
VMware-Player-3.1.0-261024.i386.bundle

在终端中转到文件放置的目录，执行
sudo sh VMware-Player-3.1.0-261024.i386.bundle

安装就开始了。

卸载方法：
在终端中输入
sudo vmware-installer -u vmware-player

就能卸载

卸载Workstation的方法相同，输入
sudo vmware-installer -u vmware-workstation
======================================================================
UBIFS 出错：
[    3.817188] VFS: Mounted root (ubifs filesystem) on device 0:9.
[    3.824409] Freeing unused kernel memory: 220K (80539000 - 80570000)
Starting mount /data parttion
[    3.944590] UBIFS: background thread "ubifs_bgt1_0" started, PID 53
[    4.009158] UBIFS error (pid 52): ubifs_check_node: bad CRC: calculated 0xe94bab05, read 0x869acbe8
[    4.018555] UBIFS error (pid 52): ubifs_check_node: bad node at LEB 253:82976

网上的一些见解：
UBIFS本身的机制导致它会出现这种错误，可以到http://www.linux-mtd.infradead.org/faq/ubifs.html，详细了解这个文件系统的特性和它的不足之处。
以下是我对你问题的一点理解。
1.你的根文件系统是UBIFS，可写读的。
2.在你运行Linux系统时，系统的一些服务，如日志等，可能会频繁的读写你的存储器。UBIFS对掉电的容忍性我觉得是比较差的，在异常掉电或重启后，下次重启后可能导致到UBIFS文件系统记录节点CRC和实际计算的不一致，导致你的根文件系统挂载不了。
所以我有了以下直观认识：
1.UBIFS挂载速度快，存储器寿命高。
2.UBIFS对异常掉电的容忍性差，容易出现CRC错误。

所以我以下建议：
1.将你的根文件系统设置为只读，另外建立一个可读写扩展文件系统系统分区，用于其他用途。
2.如果你坚持保留根文件系统分区为可读写，则每次通过linux命令执行关机操作，尽量避免直接切断电源。
3.或者向freescale官方咨询答案，到时候大家一起讨论共享。

针对你说的不能烧写和扩展文件系统，我有以下建议给你。
1.修改你的内核NAND flash分区，增加一个扩展文件系统分区。
2.然后通过ubifs文件系统工具将你的文件打包成ubifs固有的格式（为什么？）。
3.因为上面已经将文件打包成ubifs格式了，所以直接在uboot或类似uboot的引导程序中通过nand的命令如 nand erase、nand write等将打包后的文件直接写入对应的扩展分区中。
4.修改根文件系统，在初始化脚本中mount该扩展文件系统到根文件系统下即可

以上的正确性需要再验证
======================================================================
//没bug的分支
git checkout remotes/ingenic/ingenic-master-3.10.14
gitk pm_p0.c //相关文件

/work/m200/5.1/kernel-3.10.14/drivers/char/voice_wakeup
voice_wakeup_firmware.hex  复制出来覆盖 Indroid5.1-master 分支的

//要测试的分支
git checkout remotes/ingenic/Indroid5.1-master


//跟踪 4.3 的 remotes/ing/ingenic-master 分支关于深休的修改
remotes/ing/ingenic-master
======================================================================
MII_BMSR
phy_write(phy, MII_BMCR, ctl);
val = phy_read(phy, MII_BMCR);

======================================================================
测试Audio:
1) 播放，可查看音频文件格式信息：
aplay att.wav

2) 转化音频格式：
mpg123
mpg123 -r 8000 --8bit -m -n 50  -w road_8Khz_single_mono.wav road.mp3 
mpg123 -r 22050 --8bit -k 1000 -n 2000 -w 22Khz.wav paomo.mp3

3) 重要的概念：
通道数(channel)：该参数为1表示单声道，2则是立体声。
桢(frame)：桢记录了一个声音单元，一个时间点上所抓取的样本，其长度为样本长度与通道数的乘积。
采样率(rate)：每秒钟采样次数，该次数是针对桢而言。
周期(period)：音频设备一次处理所需要的桢数，对于音频设备的数据访问以及音频数据的存储，都是以此为单位。
======================================================================
efuse:

ret = jz_efuse_write(efuse->wr_info->seg_id, efuse->wr_info->data_length, efuse->wr_info->buf);


unsigned int  buf[32] = {0,1,2,3,4,5};
jz_efuse_write(USER_ID, 32, buf);
printk("===========================\n");
jz_efuse_read(USER_ID, 32, buf);
printk("PROTECT_SEG: byte1 = %u, byte2 = %u byte3 = %u, byte4 = %u\n", buf[0], buf[1],buf[2], buf[3]);
======================================================================
halley2
input: gpio-keys as /devices/platform/gpio-keys/input/input1
-----------------------------------------------------------------------------------------------
如何查看 /dev/input/eventx 对应的相关设备信息：
cat /proc/bus/input/devices
I: Bus=0019 Vendor=0000 Product=0000 Version=0000
N: Name="matrix-keypad"
P: Phys=
S: Sysfs=/devices/platform/matrix-keypad.0/input/input0
U: Uniq=
H: Handlers=event0 
B: PROP=0
B: EV=100013
B: KEY=40000800 1480 0 0 ffc
B: MSC=10

I: Bus=0019 Vendor=0001 Product=0001 Version=0100
N: Name="gpio-keys"
P: Phys=gpio-keys/input0
S: Sysfs=/devices/platform/gpio-keys/input/input1
U: Uniq=
H: Handlers=event1 
B: PROP=0
B: EV=3
B: KEY=200 0 0 0

在上面的H:中可以看到对应的eventx
-----------------------------------------------------------------------------------------------
/etc/mdev.conf

mdev.conf写的不对

加入下面的就可以：
# Move input devices to input directory
event.*	0:0	0660	@(mkdir -p input&&mv $MDEV input)
mice	0:0	0660	@(mkdir -p input&&mv $MDEV input)
mouse.*	0:0	0660	@(mkdir -p input&&mv $MDEV input)

关于 halley2 找不到/dev/input/event文件的解决方法，修改kernel的 halley2_nor 的配置文件，过程如下：
1) make halley2_nor_v10_linux_defconfig
2) make menuconfig
       A) 使能 Event interface
       Device Drivers  ---->
            Input device support  ---->
                    <*> Event interface

        B) 去掉支持 ext4 文件系统
        File systems  --->
                < >The Extended 4 (ext4) support
        说明： 去掉支持 ext4 文件系统的原因使编译的 uImage 小于3M，否则大于3M kernel 无法启动，因为uboot 只加载3M大小到内存。
3) make uImage
4) 烧录启动即可， ls /dev :

arch/mips/xburst/soc-x1000/chip-x1000/halley2/common/keyboard_gpio.c
arch/mips/xburst/soc-x1000/chip-x1000/halley2/halley2_v10/board.h


sudo apt-get install automake autoconf m4 libtool gettext
sudo apt-get install libncurses5-dev libslang2-dev libselinux1-dev debhelper lsb-release pkg-config po-debconf

objdump -t path-to-library.a | grep -e __isoc99_sscanf

======================================================================
halley 2 摄像头测试：

development/testsuit/camera_process/jpg_api
libjpeg.so
out/target/product/halley2/system/lib

platform/development/testsuit/grab_source/jpeg


./cimutils -I 0 -P -v -l -w 640 -h 480
./cimutils -I 0 -P -w 640 -h 480
./cimutils -I 0 -C -v -x 640 -y 480

======================================================================
halley2 蓝牙：
启动： bt_enable
hciconfig -a
hcitool scan
obex_test -b 30:45:1C:FC:03:11 1
======================================================================
linux下查看so文件的函数列表 :

方法一：
nm查看共享库so文件中导出函数列表

查看so文件中的导出函数表；
nm -D xxx.so
列出所有导出的函数，包括 xxx.so 静态链接的库中的那些导出函数。

方法二：
objdump -tT xxx.so
======================================================================
halley2_43438_cramfs_config: unconfig mozart_prepare product_canna_v2.0_ap6212_config \
		wifi_ap6212_config bt_ap6212_config bt_hci_dev_ttyS0_config \
		lcd_disable_config webrtc_aec_disable_config \
		audio_dev_x1000_config dmr_enable_config dms_disable_config \
		airplay_enable_config localplayer_enable_config song_supplyer_ximalaya_config \
		mplayer_float_config vr_speech_config vr_wakeup_key_shortpress_config \
		lapsule_enable_config adb_enable_config \
		rootfs_cramfs_config usrdata_jffs2_config flash_spi_gd25q128c_config
	@echo "Config complete sdk with cramfs for halley2 ap6212 board"
CONFIG_JZ_HIBERNATE

/home/qwwang/work/audio/org.x1000/mozart/output/host/usr/sbin/mkfs.cramfs /home/qwwang/work/audio/org.x1000/mozart/output/fs/appfs /home/qwwang/work/audio/org.x1000/mozart/output/target/appfs.cramfs  >> /home/qwwang/work/audio/org.x1000/mozart/output/target/fakeroot.fs
======================================================================
audio_recorder.cpp
webrtc_watch_aec.cpp

hardware/ingenic/audio/audio-alsa$ mm -B

out/target/product/aw808/system/lib/hw/audio.primary.watch.so

root@watch:/ # ps | grep me
media     118   1     69212  7284  ffffffff 76e82674 S /system/bin/mediaserver

logcat
logcat -v time 
======================================================================
adb shell 出现如下错误：
error: insufficient permissions for device

解决方法;
kill -9 <adb 进程id>
sudo adb shell
======================================================================
HUAWEI MU709s-6:
hardware/mobiled/src/modem/configure.cpp
kernel/drivers/usb/serial/option.c

编译：mobiled
cd hardware/mobiled
mm -B

代码提交：
git push ing HEAD:refs/for/分支

======================================================================
halley2 mozart:
源码获取：
repo init -u ssh://username@183.62.141.5:29418/mirror/sdk-x1000-v1.6/linux/manifest -b sz-master-mozart


 >> 重启adb
./usr/fs/etc/init.d/S99adbd.sh start


1. 打开/关闭无线网卡电源
iwconfig wlan0 txpower on
iwconfig wlan0 txpower off && ifconfig wlan0 down

linux以命令行下配置连接wlan无线网卡：
工作的大体思路如下：
用iwconfig开启无线网卡的电源，并查找区域内的无线网络
连接到相应的无线网络
通过ifconfig启用无线网卡，并获取IP（如果使用DHCP的话）
注意：
假设无线被识别为wlan0，如果您的网卡没有被识别为wlan0，可以在操作时做相应的修改。
具体过程
1. 打开无线网卡电源
iwconfig wlan0 txpower on
2. 列出区域内的无线网络
iwlist wlan0 scan
3. 假设要连接到网络MyHome（即essid为MyHome的网络），那么输入命令
iwconfig wlan0 essid "MyHome"
如果网络是加密的，密码是0123456789，那么就输入命令
iwconfig wlan0 essid "MyHome" key 0123-4567-89
4. 如果正常的话，输入
iwconfig wlan0
就可以看到连接正常的各项参数了。 5. 启用无线网卡
ifconfig wlan0 up
6. 如果是用DHCP获取IP的，那么用dhclient或dhcpcd获取ip
dhclient wlan0
或
dhcpcd wlan0
7. 现在无线网卡应该可以正常使用了
注意：一定要把NetworkManager服务停掉
======================================================================
X1000 SLCD Controller
SLCD Pins Description:
SLCD_DC: Command/Data Select Signal.     I/O: Output
SLCD_WR: Data Sample Signal.             I/O: Output
SLCD_RD: Smart LCD read signal.          I/O: Output
SLCD_CE: Smart LCD chip select.          I/O: Output
SLCD_TE: Smart LCD tearing effect signal I/O: Input
SLCD_DAT: The data of SLCD               I/O: Output

-----------------------------------------------
>>>> lcd-truly_tftp240240 屏:
arch/mips/xburst/soc-x1000/chip-x1000/halley2/common/lcd/lcd-truly_tftp240240_2_e.c:

struct lcd_platform_data truly_tft240240_pdata = {
	.reset    = truly_tft240240_power_reset,
	.power_on = truly_tft240240_power_on,
};

/* LCD Panel Device */
struct platform_device truly_tft240240_device = {
	.name		= "truly_tft240240_slcd",
	.dev		= {
		.platform_data	= &truly_tft240240_pdata,
	},
};

arch/mips/xburst/soc-x1000/chip-x1000/halley2/common/board_base.c:

static struct jz_platform_device platform_devices_array[] __initdata = {
#define DEF_DEVICE(DEVICE, DATA, SIZE)  \
	{ .pdevices = DEVICE,   \
		.pdata = DATA, .size = SIZE,}	

		。
		。
#ifdef CONFIG_LCD_TRULY_TFT240240_2_E
	DEF_DEVICE(&truly_tft240240_device, 0, 0),
#endif
		。
		。
}

>>>> 注册设备：
static int __init board_base_init(void)
{
	int pdevices_array_size, i;

	pdevices_array_size = ARRAY_SIZE(platform_devices_array);
	for(i = 0; i < pdevices_array_size; i++) {
		if(platform_devices_array[i].size)
			platform_device_add_data(platform_devices_array[i].pdevices,
					platform_devices_array[i].pdata, platform_devices_array[i].size);
		platform_device_register(platform_devices_array[i].pdevices);
	}
	。
	。
	return 0;
}

>>>> 对应的驱动：
drivers/video/backlight/truly_tft240240_2_e.c:
static struct platform_driver truly_tft240240_driver = {
	.driver		= {
		.name	= "truly_tft240240_slcd",
		.owner	= THIS_MODULE,
	},
	.probe		= truly_tft240240_probe,
	.remove		= truly_tft240240_remove,
	.suspend	= truly_tft240240_suspend,
	.resume		= truly_tft240240_resume,
};

static int __init truly_tft240240_init(void)
{
	return platform_driver_register(&truly_tft240240_driver);
}

-----------------------------------------------
>>>>>>> fb

arch/mips/xburst/soc-x1000/common/platform.c:
#ifdef CONFIG_FB_JZ_V13
static u64 jz_fb_dmamask = ~(u64) 0;
static struct resource jz_fb_resources[] = {
	[0] = {
		.start = LCDC_IOBASE,
		.end = LCDC_IOBASE + 0x1800 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_LCD,
		.end = IRQ_LCD,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device jz_fb_device = {
	.name = "jz-fb",
	.id = -1,
	.dev = {
		.dma_mask = &jz_fb_dmamask,
		.coherent_dma_mask = 0xffffffff,
	},
	.num_resources = ARRAY_SIZE(jz_fb_resources),
	.resource = jz_fb_resources,
};
#endif

arch/mips/xburst/soc-x1000/chip-x1000/halley2/common/board_base.c:
static struct jz_platform_device platform_devices_array[] __initdata = {
#define DEF_DEVICE(DEVICE, DATA, SIZE)  \
	{ .pdevices = DEVICE,   \
		.pdata = DATA, .size = SIZE,}	

		。
		。
#ifdef CONFIG_FB_JZ_V13
	DEF_DEVICE(&jz_fb_device, &jzfb_pdata, sizeof(struct jzfb_platform_data)),
#endif
		。
		。
}

>>>> 设备注册过程同上

>>>> 对应的 fb 驱动：
drivers/video/jz_fb_v13/jz_fb.c:
	。。。。
	
static struct platform_driver jzfb_driver = {
	.probe = jzfb_probe,
	.remove = jzfb_remove,
	.shutdown = jzfb_shutdown,
	.driver = {
		   .name = "jz-fb",
#ifdef CONFIG_PM
		   .pm = &jzfb_pm_ops,
#endif

		   },
};

static int __init jzfb_init(void)
{
	platform_driver_register(&jzfb_driver);
	return 0;
}
	。。。。

-----------------------------------------------
>>>>>>>>  backlight
arch/mips/xburst/soc-x1000/chip-x1000/halley2/common/lcd/lcd-truly_tftp240240_2_e.c:
static struct platform_pwm_backlight_data backlight_data = {
	.pwm_id		= 0,
	.max_brightness	= 255,
	.dft_brightness	= 80,
	.pwm_period_ns	= 30000,
	.init		= backlight_init,
	.exit		= backlight_exit,
	.notify		= backlight_notify,
};

struct platform_device backlight_device = {
	.name		= "pwm-backlight",
	.dev		= {
		.platform_data	= &backlight_data,
	},
};

arch/mips/xburst/soc-x1000/chip-x1000/halley2/common/board_base.c:
static struct jz_platform_device platform_devices_array[] __initdata = {
#define DEF_DEVICE(DEVICE, DATA, SIZE)  \
	{ .pdevices = DEVICE,   \
		.pdata = DATA, .size = SIZE,}	

		。
		。
#ifdef CONFIG_BACKLIGHT_PWM
	DEF_DEVICE(&backlight_device, 0, 0),
#endif
		。
		。
}

>>>> 设备注册过程同上

>>>> 对应的 backlight 驱动：
drivers/video/backlight/pwm_bl.c:
static struct platform_driver pwm_backlight_driver = {
	.driver		= {
		.name	= "pwm-backlight",
		.owner	= THIS_MODULE,
	},
	.probe		= pwm_backlight_probe,
	.remove		= pwm_backlight_remove,
	.suspend	= pwm_backlight_suspend,
	.resume		= pwm_backlight_resume,
};

static int __init pwm_backlight_init(void)
{
	return platform_driver_register(&pwm_backlight_driver);
}

======================================================================
LED 子系统

LED GPIO 的定义：
arch/mips/xburst/soc-x1000/chip-x1000/canna/common/misc.c：
static struct gpio_led gpio_leds[] = {
	{
		.name = "led-bt",   //名称，将在/sys/class/leds/目录下出现，代表一个LED
		.gpio = GPIO_PA(8), //LED 对应的GPIO
		.active_low = true, //是否对.default_state状态进行翻转，比如GPIO输出0.LED亮，而LEDS_GPIO_DEFSTATE_OFF正好等于0
		.default_state = LEDS_GPIO_DEFSTATE_OFF,
		.retain_state_suspended = true,
		.default_trigger = NULL, //触发模式：timer、ide-disk、heartbeat、backlight、gpio、default-on等
	},	
}

static struct gpio_led_platform_data gpio_led_info = {
        .leds = gpio_leds,
        .num_leds = ARRAY_SIZE(gpio_leds),
};

struct platform_device jz_leds_gpio = {
        .name = "leds-gpio",
        .id = -1,
        .dev = {
                .platform_data  = &gpio_led_info,
        },
};

struct gpio_led_platform_data {
	int 		num_leds;
	const struct gpio_led *leds;

#define GPIO_LED_NO_BLINK_LOW	0	/* No blink GPIO state low */
#define GPIO_LED_NO_BLINK_HIGH	1	/* No blink GPIO state high */
#define GPIO_LED_BLINK		2	/* Please, blink */
	int		(*gpio_blink_set)(unsigned gpio, int state,
					unsigned long *delay_on,
					unsigned long *delay_off);
};
----------------------------------------
LED 子系统的驱动：
drivers/leds/

主要文件:
# LED Core
obj-$(CONFIG_NEW_LEDS)                   +=led-core.o
obj-$(CONFIG_LEDS_CLASS)                 += led-class.o
obj-$(CONFIG_LEDS_TRIGGERS)              +=led-triggers.o
   
# LED PlatformDrivers  
obj-$(CONFIG_LEDS_GPIO)                  += leds-gpio.o
   
# LED Triggers
obj-$(CONFIG_LEDS_TRIGGER_TIMER)         +=ledtrig-timer.o
obj-$(CONFIG_LEDS_TRIGGER_IDE_DISK)      +=ledtrig-ide-disk.o
obj-$(CONFIG_LEDS_TRIGGER_HEARTBEAT)     +=ledtrig-heartbeat.o
obj-$(CONFIG_LEDS_TRIGGER_BACKLIGHT)     +=ledtrig-backlight.o
obj-$(CONFIG_LEDS_TRIGGER_GPIO)          +=ledtrig-gpio.o
obj-$(CONFIG_LEDS_TRIGGER_DEFAULT_ON)    += ledtrig-default-on.o


drivers/leds/leds-gpio.c:
static struct platform_driver gpio_led_driver = {
	.probe		= gpio_led_probe,
	.remove		= __devexit_p(gpio_led_remove),
	.driver		= {
		.name	= "leds-gpio",
		.owner	= THIS_MODULE,
		.of_match_table = of_gpio_leds_match,
	},
};

static int __init gpio_led_init(void)
{
	return platform_driver_register(&gpio_led_driver);
}

probe 函数主要流程：
static int __devinit gpio_led_probe(struct platform_device *pdev)
{
	struct gpio_led_platform_data *pdata = pdev->dev.platform_data;
	struct gpio_leds_priv *priv;
	int i, ret = 0;

	if (pdata && pdata->num_leds) {
		priv = kzalloc(sizeof_gpio_leds_priv(pdata->num_leds),
				GFP_KERNEL);
		if (!priv)
			return -ENOMEM;

		priv->num_leds = pdata->num_leds;
		for (i = 0; i < priv->num_leds; i++) {
			//create_gpio_led，注册GPIO LED
			ret = create_gpio_led(&pdata->leds[i],
					      &priv->leds[i],
					      &pdev->dev, pdata->gpio_blink_set);
			if (ret < 0) {
				/* On failure: unwind the led creations */
				for (i = i - 1; i >= 0; i--)
					delete_gpio_led(&priv->leds[i]);
				kfree(priv);
				return ret;
			}
		}
	} else {
		priv = gpio_leds_create_of(pdev);
		if (!priv)
			return -ENODEV;
	}

	platform_set_drvdata(pdev, priv);

}

create_gpio_led 函数主要流程：
static int __devinit create_gpio_led(const struct gpio_led *template,
	struct gpio_led_data *led_dat, struct device *parent,
	int (*blink_set)(unsigned, int, unsigned long *, unsigned long *))
{
	int ret, state;

	led_dat->gpio = -1;

	/* skip leds that aren't available */
	if (!gpio_is_valid(template->gpio)) {
		printk(KERN_INFO "Skipping unavailable LED gpio %d (%s)\n",
				template->gpio, template->name);
		return 0;
	}

	ret = gpio_request(template->gpio, template->name);
	if (ret < 0)
		return ret;

	// 初始化每个LED对应的 struct gpio_led_data 结构
	led_dat->cdev.name = template->name;
	led_dat->cdev.default_trigger = template->default_trigger;
	led_dat->gpio = template->gpio;
	led_dat->can_sleep = gpio_cansleep(template->gpio);
	led_dat->active_low = template->active_low;
	led_dat->blinking = 0;

	if (blink_set) { //blink_set = NULL, if语句不会执行
		led_dat->platform_gpio_blink_set = blink_set;
		led_dat->cdev.blink_set = gpio_blink_set;
	}
	
	led_dat->cdev.brightness_set = gpio_led_set; // 设定 LED 
	if (template->default_state == LEDS_GPIO_DEFSTATE_KEEP)
		state = !!gpio_get_value(led_dat->gpio) ^ led_dat->active_low;
	else
		state = (template->default_state == LEDS_GPIO_DEFSTATE_ON);

	led_dat->cdev.brightness = state ? LED_FULL : LED_OFF;
	if (!template->retain_state_suspended)
		led_dat->cdev.flags |= LED_CORE_SUSPENDRESUME;

	ret = gpio_direction_output(led_dat->gpio, led_dat->active_low ^ state); //设置GPIO LED 初始状态
	if (ret < 0)
		goto err;
		
	INIT_WORK(&led_dat->work, gpio_led_work);

	ret = led_classdev_register(parent, &led_dat->cdev); //创建classdev设备，也即leds类中实例化一个对象
	if (ret < 0)
		goto err;

	return 0;
err:
	gpio_free(led_dat->gpio);
	return ret;
}

led_classdev_register 函数主要流程：
1.加到leds_list链表中，
2.初始化blinktimer，
3.指定blink_timer的function和data，
4.设置trigger，
5.然后一个新的led设备就注册好了，就可以使用了。
int led_classdev_register(struct device *parent, struct led_classdev *led_cdev)
{
	led_cdev->dev = device_create(leds_class, parent, 0, led_cdev,
				      "%s", led_cdev->name);
	if (IS_ERR(led_cdev->dev))
		return PTR_ERR(led_cdev->dev);

#ifdef CONFIG_LEDS_TRIGGERS
	init_rwsem(&led_cdev->trigger_lock);
#endif
	/* add to the list of leds */
	down_write(&leds_list_lock);
	list_add_tail(&led_cdev->node, &leds_list);
	up_write(&leds_list_lock);

	if (!led_cdev->max_brightness)
		led_cdev->max_brightness = LED_FULL;

	led_update_brightness(led_cdev);

	init_timer(&led_cdev->blink_timer);
	led_cdev->blink_timer.function = led_timer_function;
	led_cdev->blink_timer.data = (unsigned long)led_cdev;

#ifdef CONFIG_LEDS_TRIGGERS
	led_trigger_set_default(led_cdev);
#endif

	printk(KERN_DEBUG "Registered led device: %s\n",
			led_cdev->name);

	return 0;
}

/*
 * PWM LED driver data - see drivers/leds/leds-pwm.c
 */
#ifndef __LINUX_LEDS_PWM_H
#define __LINUX_LEDS_PWM_H

struct led_pwm {
	const char	*name;
	const char	*default_trigger;
	unsigned	pwm_id;
	u8 		active_low;
	unsigned 	max_brightness;
	unsigned	pwm_period_ns;
};

struct led_pwm_platform_data {
	int			num_leds;
	struct led_pwm	*leds;
};

#endif
======================================================================
wifi 网络测试方法:
1. 使能wlan0
2. 增加网络热点
在文件中 增加新的内容/data/misc/wifi/wpa_supplicant.conf 如下
ctrl_interface=/data/misc/wifi/sockets
update_config=1
device_name=aw808
manufacturer=Ingenic
model_name=WATCH-RDK
model_number=WATCH-RDK
serial_number=
device_type=10-0050F204-5
config_methods=physical_display virtual_push_button
external_sim=1
#----------------------以下是新增加的热点密码及优先级 ----------------------
network={
    ssid="sw1"
    psk="#sz@sw1^"
    key_mgmt=WPA-PSK
    priority=27
}
3. reboot 或手动重启wpa_supplicant 服务
4. busybox ifconfig  即可看到分配的IP地址 

wpa_supplicant -Dnl80211 -iwlan0 -cwpa_supplicant.conf
udhcpc -i wlan0
======================================================================
ack的解决思路是：1)缺省就搜索子目录；2)对常用编程语言，ack里面写好了对应哪些文件扩展名，比如perl是.pl, .pm和.pod，那么你只要指定按perl这个语言搜就行了。于是上述命令可以简化为:
ack --perl pattern

如果只想排除perl类型的文件，则可以用:
ack --noperl pattern

你可以--type-add TYPE=.ext[,ext2[,...]]或者--type-set TYPE=.ext[,ext2[,...]]来临时定制文件类型（如果要长期使用，可以修改~/.ackrc。

同时，也许你已经注意到了，其实ack也可以用来替代那一大堆find命令，用来搜索指定类型的文件本身(而不是文件内容)，ack当然也支持，只需要添加-f 选项就行了:
ack -f --perl
----------------------------------------------------------------------
glark

与ack关注点不一样的是，glark跟关注文件里面的内容，举两个例子说一下:

% glark --and=2 printStackTrace catch *.java
这表示在java代码中搜索printStackTrace和catch这两个词，要求这两个词出现的位置相差不超过2行；

 
% glark --or catch throw *.java
这表示要求搜出包含catch或者throw的行；

% glark --and=5 cout --or double float *.c
这表示要求某行包含double或者float，然后在其上下5行内有cout出现。
======================================================================
#define PXPIN		0x00   /* PIN Level Register */
#define PXINT		0x10   /* Port Interrupt Register */
#define PXINTS		0x14   /* Port Interrupt Set Register */
#define PXINTC		0x18   /* Port Interrupt Clear Register */
#define PXMSK		0x20   /* Port Interrupt Mask Reg */
#define PXMSKS		0x24   /* Port Interrupt Mask Set Reg */
#define PXMSKC		0x28   /* Port Interrupt Mask Clear Reg */
#define PXPAT1		0x30   /* Port Pattern 1 Set Reg. */
#define PXPAT1S		0x34   /* Port Pattern 1 Set Reg. */
#define PXPAT1C		0x38   /* Port Pattern 1 Clear Reg. */
#define PXPAT0		0x40   /* Port Pattern 0 Register */
#define PXPAT0S		0x44   /* Port Pattern 0 Set Register */
#define PXPAT0C		0x48   /* Port Pattern 0 Clear Register */
#define PXFLG		0x50   /* Port Flag Register */
#define PXFLGC		0x58   /* Port Flag clear Register */
#define PXOENS		0x64   /* Port Output Disable Set Register */
#define PXOENC		0x68   /* Port Output Disable Clear Register */
#define PXPEN		0x70   /* Port Pull Disable Register */
#define PXPENS		0x74   /* Port Pull Disable Set Register */
#define PXPENC		0x78   /* Port Pull Disable Clear Register */
#define PXDSS		0x84   /* Port Drive Strength set Register */
#define PXDSC		0x88   /* Port Drive Strength clear Register */
#define PZGID2LD	0xF0   /* GPIOZ Group ID to load */

#define GPIO_BASE   0xb0010000

#define GPIO_PXPIN(n)   (GPIO_BASE + (PXPIN + (n)*0x100)) /* PIN Level Register */
#define GPIO_PXINT(n)   (GPIO_BASE + (PXINT + (n)*0x100)) /* Port Interrupt Register */
#define GPIO_PXINTS(n)  (GPIO_BASE + (PXINTS + (n)*0x100)) /* Port Interrupt Set Register */
#define GPIO_PXINTC(n)  (GPIO_BASE + (PXINTC + (n)*0x100)) /* Port Interrupt Clear Register */
#define GPIO_PXMSK(n)   (GPIO_BASE + (PXMSK + (n)*0x100)) /* Port Interrupt Mask Register */
#define GPIO_PXMSKS(n)  (GPIO_BASE + (PXMSKS + (n)*0x100)) /* Port Interrupt Mask Set Reg */
#define GPIO_PXMSKC(n)  (GPIO_BASE + (PXMSKC + (n)*0x100)) /* Port Interrupt Mask Clear Reg */
#define GPIO_PXPAT1(n)  (GPIO_BASE + (PXPAT1 + (n)*0x100)) /* Port Pattern 1 Register */
#define GPIO_PXPAT1S(n) (GPIO_BASE + (PXPAT1S + (n)*0x100)) /* Port Pattern 1 Set Reg. */
#define GPIO_PXPAT1C(n) (GPIO_BASE + (PXPAT1C + (n)*0x100)) /* Port Pattern 1 Clear Reg. */
#define GPIO_PXPAT0(n)  (GPIO_BASE + (PXPAT0 + (n)*0x100)) /* Port Pattern 0 Register */
#define GPIO_PXPAT0S(n) (GPIO_BASE + (PXPAT0S + (n)*0x100)) /* Port Pattern 0 Set Register */
#define GPIO_PXPAT0C(n) (GPIO_BASE + (PXPAT0C + (n)*0x100)) /* Port Pattern 0 Clear Register */
#define GPIO_PXFLG(n)   (GPIO_BASE + (PXFLG + (n)*0x100)) /* Port Flag Register */
#define GPIO_PXFLGC(n)  (GPIO_BASE + (PXFLGC + (n)*0x100)) /* Port Flag clear Register */
#define GPIO_PXPE(n)    (GPIO_BASE + (PXPE + (n)*0x100)) /* Port Pull Disable Register */
#define GPIO_PXPES(n)   (GPIO_BASE + (PXPES + (n)*0x100)) /* Port Pull Disable Set Register */
#define GPIO_PXPEC(n)   (GPIO_BASE + (PXPEC + (n)*0x100)) /* Port Pull Disable Clear Register */

#define GPIO_PA(n)      (0*32 + n)
#define GPIO_PB(n)      (1*32 + n)
#define GPIO_PC(n)      (2*32 + n)
#define GPIO_PD(n)      (3*32 + n)

static void gpio_direction_output(unsigned int gpio, unsigned int value)
{
	unsigned int port = gpio/32;
	unsigned int pin = gpio%32;

    *(volatile unsigned int *)GPIO_PXINTC(port) = 1 << pin;
    *(volatile unsigned int *)GPIO_PXMSKS(port) = 1 << pin;
    *(volatile unsigned int *)GPIO_PXPAT1C(port) = 1 << pin;

    if(value)
        *(volatile unsigned int *)GPIO_PXPAT0S(port) = 1 << pin;
    else
        *(volatile unsigned int *)GPIO_PXPAT0C(port) = 1 << pin;
}

void dump_gpio_status (unsigned int port, unsigned int pin)
{
    unsigned pxpin =  *(volatile unsigned int *) (GPIO_BASE + port * 0x100 );
    unsigned pxint =  *(volatile unsigned int *) (GPIO_BASE + port * 0x100  + 0x10);
    unsigned pxmsk  =  *(volatile unsigned int *) (GPIO_BASE + port * 0x100  + 0x20);
    unsigned pxpat1 =  *(volatile unsigned int *) (GPIO_BASE + port * 0x100  + 0x30);
    unsigned pxpat0 =  *(volatile unsigned int *) (GPIO_BASE + port * 0x100  + 0x40);
    //unsigned pxpen =  *(volatile unsigned int *) (GPIO_BASE + port * 0x100  + 0x70);

    int int_f, mask_f, pat0_f, pat1_f, pen_f;
    int_f = pxint & (1<<pin);
    mask_f = pxmsk & (1<<pin);
    pat0_f = pxpat0 & (1<<pin);
    pat1_f = pxpat1 & (1<<pin); 

    if (!int_f && mask_f && !pat1_f && !pat0_f)
        printf(">>> port: %d, pin: %d -- output 0 <<<\n", port, pin);
    else if (!int_f && mask_f && !pat1_f && pat0_f)
        printf(">>> port: %d, pin: %d -- output 1 <<<\n", port, pin);
    else
        printf(">>> port: %d, pin: %d -- unkown status <<<\n", port, pin);
}
======================================================================
sz-mozart 摄像头 cim_core

设备：
1) arch/mips/xburst/soc-x1000/include/mach/platform.h:
#define CIM_PORTA							\
	{ .name = "cim",    .port = GPIO_PORT_A,  .func = GPIO_FUNC_2, .pins = 0xfff << 8, }

2) arch/mips/xburst/soc-x1000/chip-x1000/halley2/common/board_base.c:

struct jz_gpio_func_def platform_devio_array[] = {
	.
	.
#if defined(CONFIG_VIDEO_JZ_CIM_HOST) || defined (CONFIG_JZ_CIM_CORE)
	CIM_PORTA,
#endif
	.	
}


#if defined(CONFIG_VIDEO_JZ_CIM_HOST) || defined(CONFIG_JZ_CIM_CORE)
static struct resource jz_cim_resources[] = {
	[0] = {
		.flags = IORESOURCE_MEM,
		.start = CIM_IOBASE,
		.end = CIM_IOBASE + 0x10000 - 1,
	},
	[1] = {
		.flags = IORESOURCE_IRQ,
		.start = IRQ_CIM,
	}
};

struct platform_device jz_cim_device = {
	.name = "jz-cim",
	.id = 0,
	.resource = jz_cim_resources,
	.num_resources = ARRAY_SIZE(jz_cim_resources),
};
#endif

3) arch/mips/xburst/soc-x1000/chip-x1000/halley2/common/board_base.c:
static struct jz_platform_device platform_devices_array[] __initdata = {
#define DEF_DEVICE(DEVICE, DATA, SIZE)  \
	{ .pdevices = DEVICE,   \
		.pdata = DATA, .size = SIZE,}
		
#ifdef CONFIG_JZ_CIM_CORE
    DEF_DEVICE(&jz_cim_device, 0, 0),
#endif
		
}

sensor-gc2155:
1) arch/mips/xburst/soc-x1000/chip-x1000/halley2/halley2_v20/board.h
#ifdef CONFIG_JZ_CAMERA_SENSOR
#define FRONT_CAMERA_INDEX  0
#define BACK_CAMERA_INDEX   1

#define CAMERA_SENSOR_RESET GPIO_PD(5)
#define CAMERA_FRONT_SENSOR_PWDN  GPIO_PD(4)
#define CAMERA_VDD_EN  GPIO_PD(3)
#endif

2) arch/mips/xburst/soc-x1000/chip-x1000/halley2/common/i2c_bus.c
#ifdef CONFIG_JZ_CAMERA_SENSOR
static int sensor_gc2155_early_init(void)
{
    int ret = -1;

    if (!gpio_is_valid(CAMERA_VDD_EN)) {
        pr_err("%s %d: GPIO CAMERA_VDD_EN is invalid\n", __func__, __LINE__);
        return -1;
    }

    ret = gpio_request(CAMERA_VDD_EN, "gc2155_vdd_en");
    if (ret < 0) {
        pr_err("%s %d: CAMERA_VDD_EN request failed\n", __func__, __LINE__);
        return -1;
    }

    if (!gpio_is_valid(CAMERA_FRONT_SENSOR_PWDN)) {
        pr_err("%s %d: GPIO CAMERA_FRONT_SENSOR_PWDN is invalid\n", __func__, __LINE__);
        return -1;
    }

    ret = gpio_request(CAMERA_FRONT_SENSOR_PWDN, "gc2155_front_power_pwdn");
    if (ret < 0) {
        pr_err("%s %d: CAMERA_FRONT_SENSOR_PWDN request failed\n", __func__, __LINE__);
        return -1;
    }

    if (!gpio_is_valid(CAMERA_SENSOR_RESET)) {
        pr_err("%s %d: GPIO CAMERA_SENSOR_RESET is invalid\n", __func__, __LINE__);
        return -1;
    }

    ret = gpio_request(CAMERA_SENSOR_RESET, "gc2155_sensor_reset");
    if (ret < 0) {
        pr_err("%s %d: CAMERA_SENSOR_RESET request failed\n", __func__, __LINE__);
        return -1;
    }

    return 0;
}

static void sensor_gc2155_reset(void)
{
    gpio_direction_output(CAMERA_VDD_EN, 1);

    gpio_direction_output(CAMERA_SENSOR_RESET, 0);
    mdelay(250);
    gpio_direction_output(CAMERA_SENSOR_RESET, 1);
    mdelay(250);
}

static void sensor_gc2155_power_on(int value)
{
    gpio_direction_output(CAMERA_VDD_EN, value);

    /* enable or disable the camera */
    gpio_direction_output(CAMERA_FRONT_SENSOR_PWDN, value ? 0 : 1);
    mdelay(150);
}

static struct cim_sensor_plat_data gc2155_pdata = {
    .name = "sensor-gc2155",
    .gpio_en = CAMERA_VDD_EN,
    .init = sensor_gc2155_early_init,
    .reset = sensor_gc2155_reset,
    .power_on = sensor_gc2155_power_on,
};
#endif

#if (defined(CONFIG_SOFT_I2C0_GPIO_V12_JZ) || defined(CONFIG_I2C0_V12_JZ))
struct i2c_board_info jz_i2c0_devs[] __initdata = {
	....
#ifdef CONFIG_JZ_CAMERA_SENSOR
    {
        I2C_BOARD_INFO("sensor", 0x3c),
        .platform_data  = &gc2155_pdata,
    },
#endif
};
int jz_i2c0_devs_size = ARRAY_SIZE(jz_i2c0_devs);
#endif

3) arch/mips/xburst/soc-x1000/chip-x1000/halley2/common/board_base.c
static int __init board_base_init(void)
{
	int pdevices_array_size, i;

	。。。。

#if (defined(CONFIG_SOFT_I2C0_GPIO_V12_JZ) || defined(CONFIG_I2C0_V12_JZ))
	i2c_register_board_info(0, jz_i2c0_devs, jz_i2c0_devs_size);
#endif
	return 0;
}

驱动：
1) drivers/char/jz_cim_core.c:

======================================================================
sz-halley2 camera

sensor-ov7740
1) 
#ifdef CONFIG_VIDEO_JZ_CIM_HOST_V13
#define FRONT_CAMERA_INDEX  0
#define BACK_CAMERA_INDEX   1

#define CAMERA_SENSOR_RESET GPIO_PD(5)
#define CAMERA_FRONT_SENSOR_PWDN  GPIO_PD(4)
#define CAMERA_VDD_EN  GPIO_PD(3)
#endif


struct soc_camera_desc icdesc_front = {
	.host_desc = {
		.bus_id = CIM0,
		.board_info	= &jz_i2c0_devs[FRONT_CAMERA_INDEX],
		.i2c_adapter_id	= 0,
	},
	.subdev_desc = {
		.power = front_camera_sensor_power,
		.reset = camera_sensor_reset_front,
		.drv_priv = &ov772x_priv_front,
	},
};


3) 摄像头初始化时，没有将数据写入I2C，一般问题会出现在哪里？
SENSOR的各路电源是否接好，
CMCLK是否正确
RESET sensor
I2C总线上拉电阻是否匹配正确，
访问sensor时使用的 device ID是否正确， (注意7位地址和8位地址)
I2C的时钟CLK速率是否太高，
两次I2C连续读写之间是否有spec规定的delay时间
CAMERA POWER UP 时序是否符合 SPEC。

4) 编写测试代码过程中常见的问题

● 摄像头寄存器的配置

因为摄像头有很多寄存器，可能一下无法理解里面所有的配置含义，所以开始时希望得到一份可用的配置。但往往从别人的测试代码中拿到配置后，仍然无法使用。我这里列出几个可能的原因：
（a）摄像头中的图像输出格式和你在camera控制器中设置的不一致，同一个摄像头可以设置多种输入格式，如：YCbYCr或CbYCrY。
（b）图像输出的一些时序和你的camera控制器设置不一致，摄像头可以设置一些时序，如：图像数据在CAMPCLK的上升沿有效还是下降沿有效。
（c）注意输出图像的格式和Framebuffer控制器的匹配，如字节顺序等问题
（d）图像属性设置，比如宽高是否超范围或是否为4/8 整数倍。
（e）查看图像，RGB格式的数据，可以直接丢到LCD显示，验证图像效果。YUV可以用专门的YUV工具查看，或者用Photoshop查看。
（f）camera控制器中，隔行，逐行的控制位设置。 


5) Camera 测试
a)照相：cimutils -I 0 -C -v -x 320 -y 240、 cimutils -I 0 -C -v -x 640 -y 480
b)预览：cimutils -I 0 -P -w 320 -h 240
c)预览并照相：/cimutils -I 0 -P -v -l -w 320 -h 240
d)获取帮助：cimutils --help
======================================================================
VIM Ack基本使用
常用参数：
-i         忽略大小写
-v        显示不匹配行
-w        强制匹配整个单词
-l         打印匹配的文件名
-L        打印不匹配的文件名
-m       在每个文件中最多匹配多少行就停止搜索
-c        显示匹配的总行数

然后在Vim中输入 :Ack test_blah 便可以在当前项目代码中搜索 "test_blah" 了
常用快捷键如下：
?           帮助，显示所有快捷键
Enter/o     打开文件
O           打开文件并关闭Quickfix
go          预览文件，焦点仍然在Quickfix
t           新标签页打开文件
q           关闭Quickfix


可以在 ~/.vimrc 中为 :Ack 设置一个快捷键：
map <c-u> :Ack<space>
以后在普通模式下输入 Ctrl+U 便可以自动输入 :Ack 了

配置个热键：
    参考 http://vim.wikia.com/wiki/Word_under_cursor_for_command
    :map <F8> "zyw:exe "Ack ".@z.""<CR>
不配热键也可以：
:Ack <Ctrl + R + W> 就能把光标下的当前单词放进VIM命令行了


" 映射成<Ctrl-TAB>打开下一个TAB, <Alt-1>打开第一个TAB, <Alt-2>打开第二个, ...

if has("gui_running") 
     :map <silent> <C-S> :if expand("%") == ""<CR>:browse confirm w<CR>:else<CR>:confirm w<CR>:endif<CR> 
     noremap <M-1> 1gt 
     noremap <M-2> 2gt 
     noremap <M-3> 3gt 
     noremap <M-4> 4gt 
     noremap <M-5> 5gt 
     noremap <M-6> 6gt 
     noremap <M-7> 7gt 
     noremap <M-8> 8gt 
     noremap <M-9> 9gt 
     noremap <M-0> 10gt 
     noremap <C-TAB> gt 
     noremap <C-F4> <ESC>:bd<CR> 
     noremap qt <ESC>:bd<CR> 
     au BufEnter * simalt ~x "maximum the initial window 
else 
     colorscheme desert"torte 
endif

1.NERDTree与右边编辑区的Tabbar切换focus为 ctrl+w+h   ctr+w+l
2.也可以直接ctr+w 多次切换
3.Tabbar切换tab esc+[Number]
4.关闭tab :bd 回车清除内容，再回车关闭tab
5.关闭所有tab :qa! 
6.NERDTree与右边编辑区的Tabbar切换focus为 ctrl+h   ctr+l
7.Tabbar切换 ctrl+tab 上一下，下一个tab的切换，直接鼠标双击切换tab，直接跳转到[Number]的tab上，还没有找到。。。
8.关闭同上

ctags:
找到 tag：1/3 或更多

在跳转到一个函数或者一个变量的定义处时，经常有多处地方定义了相同名字，需要定位正确的定义地方。
:ts 或 tselect 查看有相同地方的定义
:tn或tnext   查找下一个定义地方。
:tp   查找上一个地方。
:tfirst  到第一个匹配
:tlast 到最后一个匹配
:tags 查看到达当前位置所经过的标签路径
ta xxx 跳转到标签 xxx 定义的地方
:stag xxx 在分割窗口中查看包含 xxx 的文件
======================================================================
获取31服务器上的Manhhatan/halley2代码:
repo init -u ssh://wangqiuwei@194.169.1.31:29418/mirror/Manhhatan/halley2/platform/manifest.git -b ingenic-linux-kernel3.10.14-halley2-v2.0-20160411 -m boards/halley2.xml

----------------------------------------------------------------------
获取31服务器上的mozart代码:
repo init -u ssh://wangqiuwei@194.169.1.31:29418/mirror/sdk-x1000-v1.6/linux/manifest -b sz-master-mozart
repo init -u ssh://wangqiuwei@194.169.1.31:29418/mirror/sdk-x1000-v1.6/linux/manifest -b speaker-master-x1000
repo init -u ssh://wangqiuwei@194.169.1.31:29418/mirror/sdk-x1000-v1.6/linux/manifest -b speaker-master-x1000 -m master.xml

网盘下载：
链接: http://pan.baidu.com/s/1c0Dae0g 密码: syf8

kernel:
./git/config:
[core]
	repositoryformatversion = 0
	filemode = true
[remote "ing"]
	url = ssh://wangqiuwei@194.169.1.31:29418/mirror/sdk-x1000-v1.6/android/kernel/kernel-3.0.8
	review = https://review.ingenic.cn/
	projectname = android/kernel/kernel-3.0.8
	fetch = +refs/heads/*:refs/remotes/ing/*
[remote "bj"]
    url = ssh://qwwang_sz@192.168.1.26:29418/android/kernel/kernel-3.0.8
	review = https://review.ingenic.cn/
	projectname = android/kernel/kernel-3.0.8
	fetch = +refs/heads/*:refs/remotes/ing/*
	push = HEAD:refs/for/speaker-master-x1000

uboot:
.git/config:
[core]
	repositoryformatversion = 0
	filemode = true
[remote "ing"]
	url = ssh://wangqiuwei@194.169.1.31:29418/mirror/sdk-x1000-v1.6/bootloader/u-boot
	review = https://review.ingenic.cn/
	projectname = bootloader/u-boot
	fetch = +refs/heads/*:refs/remotes/ing/*

[remote "bj"]
    url = ssh://qwwang_sz@192.168.1.26:29418/bootloader/u-boot
	review = https://review.ingenic.cn/
	projectname = bootloader/u-boot
	fetch = +refs/heads/*:refs/remotes/ing/*
    push = HEAD:refs/for/speaker-master-x1000
----------------------------------------------------------------------
#define CONFIG_BOOTCOMMAND          "bootx sfc 0x80f00000 0xd00000" 这一行（大概在159行），

   0xd00000 这个值没有修改正确，计算方法：updater分区大小 + appfs 分区起始地址
   
----------------------------------------------------------------------
grep 设置默认跳过的目录和文件的方法:
修改:~/.profile,添加如下一行:
export GREP_OPTIONS="--exclude-dir=\.git --exclude=.tags* --exclude=tags"
----------------------------------------------------------------------
Makefile有三个非常有用的变量。分别是$@，$^，$<代表的意义分别是：
$@--目标文件，$^--所有的依赖文件，$<--第一个依赖文件。

======================================================================
应用层：
open("/dev/dsp3", O_RDONLY);
驱动：
xb_snd_dsp_open
xb_snd_dsp_ioctl

应用层：
open("/dev/mixer3", O_RDONLY);
驱动：
xb_snd_mixer_open
xb_snd_mixer_ioctl
======================================================================
交叉编译opencv

报错解决：
Linking CXX shared library ../../lib/libopencv_core.so
/opt/toolchains/mips-gcc472-glibc216/bin/../lib/gcc/mips-linux-gnu/4.7.2/../../../../mips-linux-gnu/bin/ld: ../../3rdparty/lib/libzlib.a(gzclose.c.obj): relocation R_MIPS_26 against `gzclose_w' can not be used when making a shared object; recompile with -fPIC
../../3rdparty/lib/libzlib.a: error adding symbols: Bad value
collect2: error: ld returned 1 exit status
make[2]: *** [lib/libopencv_core.so] 错误 1

解决方法，修改build/CmakeCache.txt， 如下：

1) CMAKE_CXX_FLAGS:STRING=-fPIC，大概163行
2) CMAKE_C_FLAGS:STRING=-fPIC ， 大概183行

运行运用找不到库的问题：
error while loading shared libraries: ../../lib/libopencv_core.so的解决方法

readelf -d libopencv_highgui.so

Dynamic section at offset 0x50580 contains 30 entries:
  Tag Type Name/Value
 0x00000001 (NEEDED) Shared library: [../../lib/libopencv_core.so]
 0x00000001 (NEEDED) Shared library: [../../lib/libopencv_imgproc.so]
 0x00000001 (NEEDED) Shared library: [libstdc++.so.6]
 0x00000001 (NEEDED) Shared library: [libm.so.6]
 0x00000001 (NEEDED) Shared library: [libgcc_s.so.1]
 0x00000001 (NEEDED) Shared library: [libc.so.6]
 0x0000000c (INIT) 0xa410
 0x0000000d (FINI) 0x49ed4
 0x00000019 (INIT_ARRAY) 0x50000
 0x0000001b (INIT_ARRAYSZ) 12 (bytes)
 0x0000001a (FINI_ARRAY) 0x5000c
......

解决方法：
1) vi toolchain.cmake, 内容如下：
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR mips)
set(CMAKE_C_COMPILER mipsel-linux-gcc)
set(CMAKE_CXX_COMPILER mipsel-linux-g++)
set(CMAKE_FIND_ROOT_PATH "/opt/toolchains/mipsel-buildroot-linux-gnu/usr")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

2) cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake ../opencv-2.4.13/
3) ccmake .
======================================================================
/*#define CONFIG_LCD*/

#define CONFIG_GPIO_PWR_WAKE		GPIO_PB(31)
#define CONFIG_GPIO_PWR_WAKE_ENLEVEL	0

#ifdef CONFIG_LCD
#define LCD_BPP     5
#define SOC_X1000
#define CONFIG_JZ_PWM
#define CONFIG_GPIO_LCD_PWM     GPIO_PC(25)
#define CONFIG_LCD_GPIO_FUNC1_SLCD

#define CONFIG_JZ_LCD_V13
#define CONFIG_SYS_WHITE_ON_BLACK
#define CONFIG_SYS_PWM_PERIOD       10000 /* Pwm period in ns */
#define CONFIG_SYS_PWM_CHN          0     /* Pwm channel ok */
#define CONFIG_SYS_PWM_FULL         255
#define CONFIG_SYS_BACKLIGHT_LEVEL  80    /* Backlight brightness is (80 / 256) */

#define CONFIG_SYS_CONSOLE_INFO_QUIET
#define CONFIG_SYS_CONSOLE_IS_IN_ENV

#define CONFIG_VIDEO_TRULY_TFT240240_2_E

#ifdef CONFIG_VIDEO_TRULY_TFT240240_2_E
#define CONFIG_GPIO_LCD_RD  GPIO_PB(16)
#define CONFIG_GPIO_LCD_RST GPIO_PD(0)
#define CONFIG_GPIO_LCD_CS  GPIO_PB(18)
#define CONFIG_GPIO_LCD_BL  GPIO_PD(1)
#endif	/* CONFIG_VIDEO_TRULY_TFT240240_2_E */

/*#define CONFIG_LCD_LOGO*/
/*#define CONFIG_RLE_LCD_LOGO*/
/*#define CONFIG_LCD_INFO_BELOW_LOGO*/  /*display the console info on lcd panel for debugg*/
#ifdef CONFIG_RLE_LCD_LOGO
#define CONFIG_CMD_BATTERYDET           /*detect battery and show charge logo*/
#define CONFIG_CMD_LOGO_RLE             /*display the logo using rle command*/
#endif

#endif /* CONFIG_LCD */
======================================================================
#ifndef CONFIG_LCD_DK_ST7789H2
#define SLCDC_PORTAB_8BIT						\
	{ .name = "slcd", .port = GPIO_PORT_A, .func = GPIO_FUNC_1, .pins = 0xff, }, \
	{ .name = "slcd", .port = GPIO_PORT_B, .func = GPIO_FUNC_1, .pins = 0x1a << 16, } 
#else
#define SLCDC_PORTAB_8BIT						\
	{ .name = "slcd", .port = GPIO_PORT_A, .func = GPIO_FUNC_1, .pins = 0xff, }, \
	{ .name = "slcd", .port = GPIO_PORT_B, .func = GPIO_FUNC_1, .pins = 0x12 << 16, } 
#endif
======================================================================
tar.xz 文件压缩与解压:

1) xz压缩文件方法或命令:
xz -z 要压缩的文件
如果要保留被压缩的文件加上参数 -k ，如果要设置压缩率加入参数 -0 到 -9调节压缩率。如果不设置，默认压缩等级是6.

2) xz解压文件方法或命令:
xz -d 要解压的文件
同样使用 -k 参数来保留被解压缩的文件。

3)创建或解压tar.xz文件的方法:
习惯了 tar czvf 或 tar xzvf 的人可能碰到 tar.xz也会想用单一命令搞定解压或压缩。
其实不行 tar里面没有征对 xz格式的参数, 比如 z是针对 gzip，j是针对 bzip2。

创建tar.xz文件：只要先 tar cvf xxx.tar xxx/ 这样创建xxx.tar文件先，然后使用 xz -z xxx.tar 来将 xxx.tar压缩成为 xxx.tar.xz
解压tar.xz文件：先 xz -d xxx.tar.xz 将 xxx.tar.xz解压成 xxx.tar 然后，再用 tar xvf xxx.tar来解包
======================================================================
根文件系统，网络已经连接，并且 网关、DNS 已经配置可以 ping通 域名的IP， 无法 ping通 域名的解决方法：
问题原因：
因为缺少几个必要的库和配置文件：/etc/nsswitch.conf, /lib/libnss_dns*, /lib/libnss_files*, and /lib/libresolv*
实测： /etc/nsswitch.conf 可以没有
======================================================================
配置编译strace
1) 配置：
./configure ARCH=mips CROSS_COMPILE=mips-linux-gnu- --prefix=`pwd` --host=mipsel-linux CC=mips-linux-gnu-gcc LD=mips-linux-gnu-ld CFLAGS="-EL -mabi=32 -mhard-float -march=mips32r2 -Os"

2) 编译：
make LDLIBS="-Wl -EL -W1 -start-group -lc -lnss_file -lnss_dns -lresolv -W1 -end-group"

3) 去掉符号信息
mips-linux-gnu-strip strace
======================================================================
shell 判断字符串为空
主要有以下几种方法：

echo “$str”|awk '{print length($0)}'
expr length “$str”
echo “$str”|wc -c
但是第三种得出的值会多1，可能是把结束符也计算在内了

判断字符串为空的方法有三种：
if [ "$str" =  "" ]
if [ x"$str" = x ]
if [ -z "$str" ] （-n 为非空）
注意：变量都要带双引号，否则有些命令会报错，养成好习惯吧！

test或[ ]的注意事项
1、在中括号 [] 内的每个组件都需要有空白键来分隔
2、在中括号内的变量，最好都以双引号括号起来
3、在中括号内的常数，最好都以单或双引号括号起来
======================================================================
printk("### %s: %s -- %d ###\n",__FILE__, __FUNCTION__, __LINE__);

# echo 250 > brightness 
[   97.473346] ### drivers/leds/led-class.c: led_brightness_store -- 51 ###
[   97.480682] ### brightness = 250, period = 30000, max = 255 duty = 29411 pwm->flags = 6 ###
[   97.489358] ### drivers/leds/leds-pwm.c: __led_pwm_set -- 46 111
[   97.495550] ### drivers/pwm/core.c: pwm_config -- 407 ###
[   97.501156] ### drivers/pwm/pwm-jz.c: jz_pwm_config -- 100  pwm_id = 4 ###
[   97.508240] ### tcu_device->pwm_flag = 6 ###
[   97.512665] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_as_timer_config -- 266 ###
[   97.520931] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_set_start_state -- 141 ###
[   97.529196] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_set_pwm_shutdown -- 130 ###
[   97.537534] ### arch/mips/xburst/soc-x1000/common/tcu.c: set_tcu_full_half_value -- 122 ###
[   97.546157] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_select_division_ratio -- 153 ###
[   97.554961] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_pwm_output_enable -- 76 ###
[   97.563317] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_select_clk -- 170 ###
[   97.571134] ### drivers/pwm/pwm-jz.c: jz_pwm_config -- 156 OK
[   97.577054] ### drivers/leds/leds-pwm.c: __led_pwm_set -- 54 enable
[   97.583528] ### drivers/pwm/pwm-jz.c: jz_pwm_disable -- 176 ###
[   97.589643] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_disable -- 357 ###
[   97.597175] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_shutdown_counter -- 97 ###
[   97.605437] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_pwm_output_disable -- 90 ###
[   97.613880] ### drivers/pwm/core.c: pwm_enable -- 440 aaa
[   97.619456] ### drivers/pwm/pwm-jz.c: jz_pwm_enable -- 165 ###
[   97.625467] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_enable -- 338 ###
[   97.632925] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_pwm_output_enable -- 76 ###
[   97.641277] ### arch/mips/xburst/soc-x1000/common/tcu.c: tcu_enable -- 346 ###
--------------------------------------------------------------------------------------------
tcu_as_timer_config() {
	tcu_set_start_state() {
		stop conuting up;
		The clock supplies to timer x is supplied;
		set TCSRx = 0;

		tcu_set_pwm_shutdown() {
			set TCSRx.SD;
		}
	}

	set TCNTx = 0; //Timer counter regiter
	
	set_tcu_full_half_value() {
		set TDFRx = period;
		set TDHRx = duty;
	}

	tcu_select_division_ratio() {
		tmp = regr(TCSRx);
		regw((tmp | CSR_DIVx), TCSRx)
	}

	tcu_pwm_output_enable(id) {
		if (id > 4) {
			pr_err("TCU %d is not support PWM output\n", id);
			dump_stack();
			return -ENXIO;
		}
		tmp = regr(CH_TCSR(id));
		regw((tmp | TCSR_PWM_EN), CH_TCSR(id));
	}

	tcu_select_clk(int id, int clock) {
		int tmp;

		tmp = regr(CH_TCSR(id));
		switch (clock) {
		case EXT_EN:  regw((tmp | CSR_EXT_EN), CH_TCSR(id)); break;
		case RTC_EN:  regw((tmp | CSR_RTC_EN), CH_TCSR(id)); break;
		case PCLK_EN: regw((tmp | CSR_PCK_EN), CH_TCSR(id)); break;
		case CLK_MASK:
			regw((tmp & (~CSR_CLK_MSK)), CH_TCSR(id));
		}
	}
}

pwm-beeper ===>>
#if defined(CONFIG_INPUT_PWM_BEEPER) && defined(PWM_BEEPER_PORT)
struct platform_device pwm_beeper_device = {
    .name   = "pwm-beeper",
    .dev    = {
        .platform_data = (unsigned long *)PWM_BEEPER_PORT,
    },
};
#endif
	/* tcu->half_num = tcu->full_num, indicated duty = 0 */
	if (tcu->half_num == tcu->full_num) {
		if (tcu->io_func != (tcu->init_level ? GPIO_OUTPUT1 : GPIO_OUTPUT0)) {
			tcu->io_func = tcu->init_level ? GPIO_OUTPUT1 : GPIO_OUTPUT0;
			jzgpio_set_func(tcu->gpio_def->port, tcu->io_func, tcu->gpio_def->pins);
			pr_debug("%s -- line = %d, tcu->io_func = %s\n", __FUNCTION__, __LINE__, \
				tcu->io_func == GPIO_OUTPUT1 ? "GPIO_OUTPUT1" : "GPIO_OUTPUT0");
		}
	} else if (tcu->half_num == 0) {  /* tcu->half_num = 0, indicated duty = 100% */
		if (tcu->io_func != (tcu->init_level ? GPIO_OUTPUT0 : GPIO_OUTPUT1)) {
			tcu->io_func = tcu->init_level ? GPIO_OUTPUT0 : GPIO_OUTPUT1;
			jzgpio_set_func(tcu->gpio_def->port, tcu->io_func, tcu->gpio_def->pins);
			pr_debug("%s -- line = %d, tcu->io_func = %s\n", __FUNCTION__, __LINE__, \
				tcu->io_func == GPIO_OUTPUT0 ? "GPIO_OUTPUT0" : "GPIO_OUTPUT1");
		}
	} else {
		if (tcu->io_func != tcu->gpio_def->func) {
			tcu->io_func = tcu->gpio_def->func;
			jzgpio_set_func(tcu->gpio_def->port, tcu->io_func, tcu->gpio_def->pins);
		}
	}
======================================================================
#include <soc/cpm.h>
#include <soc/base.h>
 
#define CPM_CLKGR_CIM          (1 << 22)

unsigned int reg_clkgr = cpm_inl(CPM_CLKGR);
unsigned int gate = CPM_CLKGR_CIM;
reg_clkgr |= gate;
cpm_outl(reg_clkgr, CPM_CLKGR);
printk("CPM_CLKGR  = 0x%08x\n", cpm_inl(CPM_CLKGR));

======================================================================
解压cpio文件
cpio -idmv < filename.cpio
同样可以解压img文件：
cpio -idmv < filename.img
cpio 备份命令
备份：cpio -covB > [file|device] 将数据备份到文件或设备上
还原：cpio -icduv < [file|device} 将数据还原到系统中
常用参数：
-o   ：将数据copy到文件或设备上
-i    ：将数据从文件或设备上还原到系统中
-t    ：查看cpio建立的文件或设备内容
-c   ：一种比较新的portable format方式存储
-v   ：在屏幕上显示备份过程中的文件名
-B   ：让预设的blocks可以增加到5120bytes，默认是512bytes，这样可以使备份速度加快
-d   ：自动建立目录，这样还原时才不会出现找不到路径的问题
-u   ：更新，用较新的文件覆盖旧的文件
cpio常与find 配合使用 
======================================================================
ov5640 sysclock registers:
0x3034:
	Bit[7]:   Debug mode
	Bit[6:4]: PLL charge pump control
	Bit[3:0]:
			  MIPI bit mode
			  0x8: 8-bit mode
			  0xA: 10-bit mode
			  Others: Debug mode

0x3035:
	Bit[7:4]: System clock divider
			  Slow down all clocks
	Bit[3:0]: Scale divider for MIPI
			  MIPI PCLK/SERCLK can be slowed down

0x3036:
	Bit[7:0]: PLL multiplier (4~252)
			  Can be any integer from 4~127
			  and only even integers from 128~252
			  
0x3067:
	Bit[7:5]: Debug mode
	Bit[4]:   PLL root divider
			  0: Bypass
			  1: Divided by 2
	Bit[3:0]: PLL pre-divider
			  1,2,3,4,6,8

0x3108:
	Pad Clock Divider for SCCB Clock
	Bit[7:6]: Debug mode
	Bit[5:4]: PCLK root divider
			  00: PCLK = pll_clki
			  01: PCLK = pll_clki/2
			  10: PCLK = pll_clki/4
			  11: PCLK = pll_clki/8
	Bit[3:2]: sclk2x root divider
			  00: SCLK2x = pll_clki
			  01: SCLK2x = pll_clki/2
			  10: SCLK2x = pll_clki/4
			  11: SCLK2x = pll_clki/8
	Bit[1:0]: SCLK root divider
			  00: SCLK = pll_clki
			  01: SCLK = pll_clki/2
			  10: SCLK = pll_clki/4
			  11: sclk = pll_clki/8
======================================================================
linux spi应用程序编写步骤:
第一：open
第二：ioctl ，ioctl有九种cmd，分别对应不同的arg
a、设置或获取SPI工作模式
SPI_IOC_RD_MODE     //读 模式 
SPI_IOC_WR_MODE     //写 模式 
以上两种cmd对用arg是spi_device.mode
spi_device.mode有以下几种类型
#define SPI_MODE_0 (0|0) //SCLK空闲时为低电平，串行同步时钟的前沿（上升）数据被采样
#define SPI_MODE_1 (0|SPI_CPHA)//SCLK空闲时为高电平，串行同步时钟的前沿（下降）数据被采样
#define SPI_MODE_2 (SPI_CPOL|0)//SCLK空闲时为低电平，串行同步时钟的后沿（上升）数据被采样
#define SPI_MODE_3 (SPI_CPOL|SPI_CPHA)//SCLK空闲时为高电平，串行同步时钟的后沿（下降）数据被采样
#define SPI_CS_HIGH 0x04//片选为高
#define SPI_LSB_FIRST 0x08//低位数据先传输
#define SPI_3WIRE 0x10//三线式，输入输出数据线为一条线
#define SPI_LOOP 0x20//回环模式
#define SPI_NO_CS 0x40//没有片选信号
#define SPI_READY 0x80//
用法：
mode = SPI_MODE_0 | SPI_CS_HIGH | SPI_LSB_FIRST | SPI_LOOP
ioctl(fd, SPI_IOC_WR_MODE, &mode)；
注意：前面四种是对SCK时钟信号空闲时的电平，和采样时刻的选择，四个只能选择其中一种，后面的五种可以用或的形式选择任意几个，使用方法如上

b、设置或获取SPI读写是从高位还是低位开始
SPI_IOC_RD_LSB_FIRST    //读 LSB 
SPI_IOC_WR_LSB_FIRST    //写 LSB 
以上两种cmd对用arg是spi_device.mode
用法：同上，但是mode类型只有SPI_LSB_FIRST一种

c、设置或获取SPI读写数据位数
SPI_IOC_RD_BITS_PER_WORD    //读 每字多少位 
SPI_IOC_WR_BITS_PER_WORD    //写 每字多少位
以上两种cmd对用arg是spi_device.bits_per_word
用法：
bits = 8；
ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);

d、设置或获取SPI读写的最大频率
SPI_IOC_RD_MAX_SPEED_HZ //读 最大速率 
SPI_IOC_WR_MAX_SPEED_HZ //写 最大速率 
以上两种cmd对用arg是spi_device.max_speed_hz
用法：
speed = 50*1000；
ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

e、传输数据
SPI_IOC_MESSAGE(n)      //传输n个数据包 
以上一种cmd对用arg是spi_ioc_transfer
用法：全双工传输数据
struct spi_ioc_transfer tr = {
    .tx_buf = (unsigned long)tx,
    .rx_buf = (unsigned long)rx,
    .len = ARRAY_SIZE(tx),
    .delay_usecs = delay,
    .speed_hz = speed,
    .bits_per_word = bits,
};
ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);

第三：read或write
用法：和大多数的设备read函数一样的用法，但是每次读或者写的大小不能大于4096Byte。
char* buf[n];
read(fd,buf,sizeof(buf));或者write(fd,buf,sizeof(buf));

第四：close
======================================================================
Linux下Beyond Compare4的破解使用 
1.官网下载最新版 Beyond Compare 4 并安装

http://www.scootersoftware.com/download.php
2.安装后进入到bcompare目录下，输入命令破解

进入目录：
cd /usr/lib/beyondcompare/

更改权限：
sudo chmod 755 BCompare

输入破解命令:
sudo sed -i "s/keexjEP3t4Mue23hrnuPtY4TdcsqNiJL-5174TsUdLmJSIXKfG2NGPwBL6vnRPddT7tH29qpkneX63DO9ECSPE9rzY1zhThHERg8lHM9IBFT+rVuiY823aQJuqzxCKIE1bcDqM4wgW01FH6oCBP1G4ub01xmb4BGSUG6ZrjxWHJyNLyIlGvOhoY2HAYzEtzYGwxFZn2JZ66o4RONkXjX0DF9EzsdUef3UAS+JQ+fCYReLawdjEe6tXCv88GKaaPKWxCeaUL9PejICQgRQOLGOZtZQkLgAelrOtehxz5ANOOqCaJgy2mJLQVLM5SJ9Dli909c5ybvEhVmIC0dc9dWH+/N9KmiLVlKMU7RJqnE+WXEEPI1SgglmfmLc1yVH7dqBb9ehOoKG9UE+HAE1YvH1XX2XVGeEqYUY-Tsk7YBTz0WpSpoYyPgx6Iki5KLtQ5G-aKP9eysnkuOAkrvHU8bLbGtZteGwJarev03PhfCioJL4OSqsmQGEvDbHFEbNl1qJtdwEriR+VNZts9vNNLk7UGfeNwIiqpxjk4Mn09nmSd8FhM4ifvcaIbNCRoMPGl6KU12iseSe+w+1kFsLhX+OhQM8WXcWV10cGqBzQE9OqOLUcg9n0krrR3KrohstS9smTwEx9olyLYppvC0p5i7dAx2deWvM1ZxKNs0BvcXGukR+/g" BCompare

3.此时BCompare文件已被破解，打开软件会提示Trial Mode Error！表示成功，输入Team ZWT生成的密钥即可注册成功

提供Team ZWT生成密钥一枚：
--- BEGIN LICENSE KEY ---
GXN1eh9FbDiX1ACdd7XKMV7hL7x0ClBJLUJ-zFfKofjaj2yxE53xauIfkqZ8FoLpcZ0Ux6McTyNmODDSvSIHLYhg1QkTxjCeSCk6ARz0ABJcnUmd3dZYJNWFyJun14rmGByRnVPL49QH+Rs0kjRGKCB-cb8IT4Gf0Ue9WMQ1A6t31MO9jmjoYUeoUmbeAQSofvuK8GN1rLRv7WXfUJ0uyvYlGLqzq1ZoJAJDyo0Kdr4ThF-IXcv2cxVyWVW1SaMq8GFosDEGThnY7C-SgNXW30jqAOgiRjKKRX9RuNeDMFqgP2cuf0NMvyMrMScnM1ZyiAaJJtzbxqN5hZOMClUTE+++
--- END LICENSE KEY -----
======================================================================
0x400     1K
0x1000    4K
0x10000   64K
0x80000   512K/0.5M
0x100000  1M
======================================================================
config WKUP_PIN_RST
	depends on MACH_XBURST
	bool "support reset chip by press the WKUP pin judge time"
	default n

config JUDGE_TIME
	int "judge time lenght in second"
	range 1 16
	default 5
	depends on WKUP_PIN_RST
======================================================================
建 repo管理的 git库
服务器：
01) cd review_site/git/mirror/
02) mkdir lrc
03) git clone qwwang@194.169.2.23:/home/qwwang/work/github/tt/lrc --mirror
04) mkdir manifest
05) cp ../QRcode/manifest/default.xml manifest/
06) cd manifest && vim default.xml, 修改 default.xml 为:
<?xml version="1.0" encoding="UTF-8"?>
<manifest>
  <remote  name="linux"
           fetch="."
           review="https://review.ingenic.cn/" />
  <default revision="master"
           remote="linux"
           sync-j="1" />

   <project path="lrc" name="lrc" />
</manifest>
07) git init; git add .; git commit -m "init"
08) cd ..; git clone manifest/ --mirror
09) git clone qwwang@194.169.2.23:/home/qwwang/work/github/tt/route --mirror
10) cd manifest && vim default.xml, 添加一行: <project path="route" name="route" />
11) git add .; git commit -m "add route"; git push, 如果出错继续执行下面步骤
    a) cp default.xml ../; cd ..
    b) rm manifest/ -rf
    c) git clone manifest.git/
    d) cp default.xml manifest/; cd manifest/
    e) git add .; git commit -m "add route"; git push origin

客户机：
1) mkdir test; cd test
2) repo init -u ssh://wangqiuwei@194.169.1.31:29418/mirror/lrc/manifest
3) repo sync

建单独的git库
服务器：
1)git init --bare test （test为新建库的名称）

客户机：
1)git clone ssh://wangqiuwei@194.169.1.31:29418/test

Gerrit 添加一个已经有的git工程到gerrit服务器
1) ssh -p 29418 user@localhost gerrit create-project --name demo-project
2) git push ssh://user@localhost:29418/demo-project *:*

添加用户方法
服务器：
添加用户 "aaa": htpasswd etc/passwords aaa
======================================================================
BF3703
0x03 VHREF
VREF and HREF control.
Bit[7:6]: VREF end low 2 Bits(high 8 Bit at VSTOP[7:0])
Bit[5:4]: VREF start low 2 Bits(high 8 Bit at VSTART[7:0])
Bit[3:2]: HREF end 2 LSB(high 8 MSB at register HSTOP)
Bit[1:0]: HREF start 2 LSB(high 8 MSB at register HSTART)

0x17 HSTART
Output Format-Horizontal Frame(HREF column)start high
8-Bit(low 2Bits are at VHREF[1:0])

0x18 HSTOP
Output Format-Horizontal Frame(HREF column)end high
8-Bit(low 2 Bits are at VHREF[3:2])

0x19 VSTART 
Output Format-Vertical Frame(row)start high 8-Bit(low 2 Bits are at VHREF[5:4])

0x1a VSTOP
Output Format-Vertical Frame(row)end high 8-Bit(low 2 Bits are at VHREF[7:6])
======================================================================
获取文件大小的方法：
stat -c%s filename
======================================================================
sed 是stream editor的简称，也就是流编辑器。它一次处理一行内容，处理时，把当前处理的行存储在临时缓冲区中，
称为“模式空间”（pattern space），接着用sed命令处理缓冲区中的内容，处理完成后，把缓冲区的内容送往屏幕。接
着处理下一行，这样不断重复，直到文件末尾。文件内容并没有 改变，除非你使用重定向存储输出。

sed 命令行格式为：
  sed [-nefri] ‘command’ 输入文本

常用选项：
  -n ∶ 使用安静(silent)模式。在一般 sed 的用法中，所有来自 STDIN的资料一般都会被列出到萤幕上。
       但如果加上 -n 参数后，则只有经过 sed 特殊处理的那一行(或者动作)才会被列出来。
  -e ∶ 直接在指令列模式上进行 sed 的动作编辑；
  -f ∶ 直接将 sed 的动作写在一个档案内， -f filename 则可以执行 filename 内的sed 动作；
  -r ∶ sed 的动作支援的是延伸型正规表示法的语法。(预设是基础正规表示法语法)
  -i ∶ 直接修改读取的档案内容，而不是由萤幕输出。       

常用命令：
  a ∶ 新增，a 的后面可以接字串，而这些字串会在新的一行出现(目前的下一行)
  c ∶ 取代，c 的后面可以接字串，这些字串可以取代 n1,n2 之间的行！
  d ∶ 删除，因为是删除啊，所以 d 后面通常不接任何咚咚；
  i ∶ 插入，i 的后面可以接字串，而这些字串会在新的一行出现(目前的上一行)
  p ∶ 列印，亦即将某个选择的资料印出。通常 p 会与参数 sed -n 一起运作～
  s ∶ 取代，可以直接进行取代的工作哩！通常这个 s 的动作可以搭配正规表示法！例如 1,20s/old/new/g 就是啦！

sed -i 's/.\/$(LOADER_NAME)[ ]\+[0-9a-z]\+[ ]\+[0-9]\+/.\/$(LOADER_NAME) $(APP_OFFSET) $(APP_SIZE)/' $(APP_SCRIPT); \

======================================================================
git clone ssh://wangqiuwei@194.169.1.31:29418/linux-recovery

