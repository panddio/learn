#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/fb.h>
#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/div64.h>
#include <mach/regs-lcd.h>
#include <mach/regs-gpio.h>
#include <mach/fb.h>
#include <linux/pm.h>


#define DEVICE_NAME   "s3cfb"
#define PALETTE_BUFF_CLEAR (0x80000000) //用做清空调色板(颜色表)

struct fb_var
{
	int lcd_irq_no;           /*保存LCD中断号*/
	struct clk *lcd_clock;    /*保存从平台时钟队列中获取的LCD时钟*/
	struct resource *lcd_mem; /*LCD的IO空间*/
	void __iomem *lcd_base;   /*LCD的IO空间映射到虚拟地址*/
	struct device *dev;
	struct s3c2410fb_hw regs; /*表示5个LCD配置寄存器，s3c2410fb_hw定义在mach-s3c2410/include/mach/fb.h中*/

	/*定义一个数组来充当调色板。据数据手册描述，TFT屏色位模式为8BPP时，调色板(颜色表)的长度
	为256，调色板起始地址为0x4D000400*/
	u32 palette_buffer[256];
	u32 pseudo_pal[16];
	unsigned intpalette_ready; /*标识调色板是否准备好了*/	
};

static struct file_operations lcd_fb_fops = {



};

//该函数实现修改GPIO端口的值，第三个参数mask的
//作用是将要设置的寄存器值先清零
static inline void modify_gpio(void __iomem *reg,
			       unsigned long set, unsigned long mask)
{
	unsigned long tmp;

	tmp = readl(reg) & ~mask;
	writel(tmp | set, reg);
}

static void s3cfb_init_registers(struct fb_info *fbinfo) // LCD 相关寄存器的初始化
{
	unsigned long flags;
	void __iomem *tpal;
	void __iomem *lpcsel;	
	struct fb_var *fbvar = fbinfo->par;
	struct s3c2410fb_mach_info *mach_info = fbvar->dev->platform_data;

	//获得临时调色板寄存器基地址，S3C2410_TPAL宏定义在mach-s3c2410/include/mach/regs-lcd.h中
	//注意对于lpcsel这是一个针对三星TFT屏的一个专用寄存器，如果用的不是三星的TFT屏应该不用管它
	tpal   = fbvar->lcd_base + S3C2410_TPAL;
	lpcsel = fbvar->lcd_base + S3C2410_LPCSEL;

	//*在修改下面寄存器值之前先屏蔽中断，将中断状态保存到flags中
	local_irq_save(flags);

	//把IO端口C和D配置成LCD模式
	modify_gpio(S3C2410_GPCUP,  mach_info->gpcup,  mach_info->gpcup_mask);
	modify_gpio(S3C2410_GPCCON, mach_info->gpccon, mach_info->gpccon_mask);
	modify_gpio(S3C2410_GPDUP,  mach_info->gpdup,  mach_info->gpdup_mask);
	modify_gpio(S3C2410_GPDCON, mach_info->gpdcon, mach_info->gpdcon_mask);	

	
	local_irq_restore(flags);//恢复被屏蔽的中断
	
	writel(0x00,tpal); //临时调色板寄存器使能禁止
	writel(mach_info->lpcsel,lpcsel); //它是三星TFT屏的一个寄存器，这里可以不管
	return 0;	
	
}

static void s3cfb_check_var(struct fb_info *fbinfo)
{
	unsigned int i;

	//从lcd_fb_probe探测函数设置的平台数据中再获得LCD相关信息的数据
	struct fb_var_screeninfo *var = &fbinfo->var;//fb_info中的LCD可变参数
	struct fb_var *fbvar = fbinfo->par; //在lcd_fb_probe探测函数中设置的私有结构体数据
	struct s3c2410fb_mach_info *mach_info = fbvar->dev->platform_data; //从LCD平台设备资源 取出LCD的配置结构体数据
	struct s3c2410fb_display *display = NULL;
	struct s3c2410fb_display *default_display = mach_info->displays + mach_info->default_display;
	int type = default_display->type; //LCD的类型

	//验证X/Y解析度
	if (var->yres == default_display->yres &&
		var->xres == default_display->xres &&
		var->bits_per_pixel == default_display->bpp)
	{
		display =default_display;
	}
	else
	{
		for (i =0;i <mach_info->num_displays;i++)
		{
			if (type == mach_info->displays[i].type &&
				var->yres == mach_info->displays[i].yres &&
				var->xres == mach_info->displays[i].xres &&
				var->bits_per_pixel == mach_info->displays[i].bpp)
			{
				display = mach_info->displays + i;
				break;
			}
		}
	}

	if (!display)
		return -EINVAL;

	//配置LCD配置寄存器1中的5-6位(配置成TFT类型)和配置LCD配置寄存器5
	fbvar->regs.lcdcon1 = display->type;
	fbvar->regs.lcdcon5 = display->lcdcon5;

	//设置屏幕的虚拟解析像素和高度宽度
	var->xres_virtual = display->xres;
	var->yres_virtual = display->yres;
	var->height = display->height;
	var->width = display->width;

	//设置时钟像素，行、帧切换值，水平同步、垂直同步长度值
	var->pixclock = display->pixclock;
	var->left_margin = display->left_margin;
	var->right_margin = display->right_margin;
	var->upper_margin = display->upper_margin;
	var->lower_margin = display->lower_margin;
	var->vsync_len = display->vsync_len;
	var->hsync_len = display->hsync_len;

	//设置透明度
	var->transp.offset = 0;
	var->transp.length = 0;

	//根据色位模式(BPP)来设置可变参数中R、G、B的颜色位域
	//对于这些参数值的设置请参考CPU数据
	switch (var->bits_per_pixel)
	{
		case 1:
		case 2:
		case 4:
			var->red.offset = 0;
			var->red.length = var->bits_per_pixel;
			var->green      = var->red;
			var->blue       = var->red;
			break;
		case 8:/* 8 bpp 332 */
			if (display->type != S3C2410_LCDCON1_TFT)
			{
				var->red.length   = 3;
				var->red.offset   = 5;
				var->green.length = 3;
				var->green.offset = 2;
				var->blue.length  = 2;
				var->blue.offset  = 0;
			}
			else
			{
				var->red.offset   = 0;
				var->red.length   = 8;
				var->green        = var->red;
				var->blue         = var->red;
			}
			break;
	case 12:/* 12 bpp 444 */
		var->red.length     = 4;
		var->red.offset     = 8;
		var->green.length   = 4;
		var->green.offset   = 4;
		var->blue.length    = 4;
		var->blue.offset    = 0;
		break;
	case 16:/* 16 bpp */
		if (display->lcdcon5 &S3C2410_LCDCON5_FRM565)
		{
			/* 565 format */
			var->red.offset   = 11;
			var->green.offset = 5; 
			var->blue.offset  = 0;
			var->red.length   = 5;
			var->green.length = 6;
			var->blue.length  = 5;
		} 
		else 
		{
			/* 5551 format */
			var->red.offset    = 11;
			var->green.offset  = 6;
			var->blue.offset   = 1;
			var->red.length    = 5;
			var->green.length  = 5;
			var->blue.length   = 5;
		}
		break;
	case 32:/* 24 bpp 888 and 8 dummy */
		var->red.length    = 8;
		var->red.offset    = 16;
		var->green.length  = 8;
		var->green.offset  = 8;
		var->blue.length   = 8;
		var->blue.offset   = 0;
		break;
	}

	return 0;
}

//申请帧缓冲设备fb_info的显示缓冲区空间
static int __init s3cfb_map_video_memory(struct fb_info *fbinfo)
{
	dma_addr_t map_dma; //用于保存DMA缓冲区总线地址
	struct fb_var *fbvar = fbinfo->par;//获得在lcd_fb_probe探测函数中设置的私有结构体数据
	unsigned map_size = PAGE_ALIGN(fbinfo->fix.smem_len);//获得FrameBuffer缓存的大小, PAGE_ALIGN定义在mm.h中

	//分配的一个写合并DMA缓存区设置为LCD屏幕的虚拟地址
	//dma_alloc_writecombine定义在arch/arm/mm/dma-mapping.c中
	fbinfo->screen_base = dma_alloc_writecombine(fbvar->dev, map_size, &map_dma, GFP_KERNEL);
	if(fbinfo->screen_base)
	{
		//设置这片DMA缓存区的内容为空
		memset(fbinfo->sreen_base, 0x00, map_size);
		
		//将DMA缓冲区总线地址设成fb_info不可变参数中framebuffer缓存的开始位置
		fbinfo->fix.smem_start = map_dma;
	}

	return fbinfo->screen_base ? 0 : -ENOMEM;
}

//释放帧缓冲设备fb_info的显示缓冲区空间
static int inline s3cfb_unmap_video_memory(struct fb_info *fbinfo)
{
	struct fb_var *fbvar = fbinfo->par;
	unsigned map_size = PAGE_ALIGN(fbinfo->fix.smem_len);
	
	//释放写合并DMA缓存区，跟申请DMA的地方想对应
	dma_free_writecombine(fbvar->dev,map_size,fbinfo->screen_base,fbinfo->fix.smem_start);
}


static void s3cfb_write_palette(struct fb_var *fbvar)
{
	unsigned int i;
	void __iomem *regs = fbvar->lcd_base;
	fbvar->palette_ready =0;

	for(i = 0 ; i <256 ; i++)
	{
	    unsigned long ent = fbvar->palette_buffer[i];
		if(ent == PALETTE_BUFF_CLEAR)
			continue;
		writel(ent, regs + S3C2410_TFTPAL(i));
		if(readw(regs + S3C2410_TFTPAL(i)) == ent)
			fbvar->palette_buffer[i] =PALETTE_BUFF_CLEAR;
		else
			fbvar->palette_ready = 1;				
	}
}

static irqreturn_t lcd_fb_irq(void *dev_id)
{
	struct fb_var *fbvar = dev_id;
	void __iomem *lcd_irq_base;
	unsigned long lcdirq;
	
	lcd_irq_base = fbvar->lcd_base + S3C2410_LCDINTBASE;//LCD中断寄存器基地址
	lcdirq = readl(lcd_irq_base + S3C24XX_LCDINTPND);   //读取LCD中断挂起寄存器的值
	
	//判断是否为中断挂起状态
	if(lcdirq & S3C2410_LCDINT_FRSYNC)
	{
		//填充调色板
		if (fbvar->palette_ready)
			s3cfb_write_palette(fbvar);

		//清除帧中断请求标志
		writel(S3C2410_LCDINT_FRSYNC, lcd_irq_base + S3C24XX_LCDINTPND);
		writel(S3C2410_LCDINT_FRSYNC, lcd_irq_base + S3C24XX_LCDSRCPND);
	}
		
	return IRQ_HANDLED;
}

static void s3cfb_lcd_enable(struct fb_var *fbvar, int enable)
{
	unsigned long flags;

	//在修改下面寄存器值之前先屏蔽中断，将中断状态保存到flags中
	local_irq_save(flags);
	
	if(enable)
	{
		fbvar->regs.lcdcon1 |= S3C2410_LCDCON1_ENVID;
	}
	else
	{
		fbvar->regs.lcdcon1 &= ~S3C2410_LCDCON1_ENVID;
	}
	writel(fbvar->regs.lcdcon1, fbvar->lcd_base + S3C2410_LCDCON1);

	//恢复被屏蔽的中断
	local_irq_restore(flags);
}

//有两个地方会调用到：一个是设备注销时，一个是驱动注销时
static __devexit int lcd_fb_remove(struct platform_device *pdev)
{
	struct fb_info *fbinfo = platform_get_drvdata(pdev);
	struct fb_var *fbvar = fbinfo->par;


	//从系统中注销帧缓冲设备
	unregister_framebuffer(fbinfo);

	//停止LCD控制器的工作
	s3cfb_lcd_enable(fbvar,0);
	msleep(1); // 延迟一段时间，因为停止LCD控制器需要一点时间

	//释放帧缓冲设备fb_info的显示缓冲区空间
	s3cfb_unmap_video_memory(fbinfo);

	//将LCD平台数据清空和释放fb_info空间资源
	platform_set_drvdata(pdev, NULL);
	framebuffer_release(fbinfo);

	//释放中断资源
	free_irq(fbvar->lcd_irq_no,fbvar);

	//释放时钟资源
	if (fbvar->lcd_clock)
	{
		clk_disable(fbvar->lcd_clock);
		clk_put(fbvar->lcd_clock);
		fbvar->lcd_clock = NULL;
	}

	//释放LCD IO空间映射的虚拟内存空间
	iounmap(fbvar->lcd_base);
	
	//释放申请的LCD IO端口所占用的IO空间
	release_resource(fbvar->lcd_mem); 

	return 0;
	
}

static __devinit int lcd_fb_probe(struct platform_device *pdev)
{
	int ret, i;

	struct resource *res; //保存从LCD平台设备中获取的LCD资源
	struct fb_info *fbinfo;//FrameBuffer驱动所对应的fb_info结构
	struct s3c2410fb_mach_info *mach_info;//保存从内核中获取的平台设备数据
	struct fb_var *fbvar; //上面定义的驱动程序全局变量结构体
	struct s3c2410fb_display *display; //LCD屏的配置信息结构体，该结构体定义在mach-s3c2410/include/mach/fb.h中

	//获取LCD硬件相关信息数据，在mach-s3c2440.c中
    //s3c24xx_fb_set_platdata()函数将LCD的硬件相关信息保存到LCD平台数据中 
	mach_info = pdev->dev.platform_data;
	if(mach_info == NULL)
	{
		/*判断获取数据是否成功*/
		dev_err(&pdev->dev, "no platform data for lcd\n");
		return -EINVAL;
	}	
	//获得在mach-s3c2440.c中定义的FrameBuffer平台设备的LCD配置信息
	display = mach_info->displays + mach_info->default_display;
	
	//申请一段大小为sizeof(fb_info)+sizeof(fb_var)的空间，fb_var是这个设备的私有数据结构
	//并初始化fb_info->par = &fb_var, fb_info->device = &pdev->dev,
	//目的是在其他接口函数中通过fb_info结构取出这些成员
	//返回这段空间的首地址
	fbinfo = framebuffer_alloc(sizeof(fb_var), &pdev->dev);
	if(!fbinfo)
	{
		dev_err(&pdev->dev, "framebuffer alloc of registers failed\n");
		ret = -ENOMEM;
		goto err_noirq;
	}
	//重新将LCD平台设备数据设置为fbinfo，好在后面的一些函数中来使用
	platform_set_drvdata(pdev, fbinfo);

	//fbinfo->par 在framebuffer_alloc()函数中赋值，指向了fb_var私有数据结构
	//这里从fbinfo->par获取到fb_var私有数据结构的地址，进行成员的初始化
	fbvar = fbinfo->par;
	fbvar->dev = &pdev->dev;//保存pdev->dev到私有数据结构，这样在其他函数可以通过fbva私有数据结构取出LCD平台设备资源

	//从LCD平台设备资源中获取LCD中断号,platform_get_irq定义在platform_device.h中
	fbvar->lcd_irq_no =platform_get_irq(pdev, 0);
	if(fbvar->lcd_irq_no <0)
	{
		/*判断获取中断号是否成功*/
		dev_err(&pdev->dev, "no lcd irq for platform\n");
		return -ENOENT;
	}

	//获取LCD平台设备所使用的IO端口资源，注意这个IORESOURCE_MEM
	//标志和LCD平台设备定义中的一致
	res =platform_get_resource(pdev,IORESOURCE_MEM,0);
	if(res == NULL)
	{
		/*判断获取资源是否成功*/
		dev_err(&pdev->dev, "failed to get memory region resource\n");
		return -ENOENT;
	}

	//申请LCD IO端口所占用的IO空间(注意理解IO空间和内存空间的
	//区别),request_mem_region定义在ioport.h中
	fbvar->lcd_mem =request_mem_region(res->start, res->end - res->start + 1,pdev->name);
	if(fbvar->lcd_mem == NULL)	
	{
		/*判断申请IO空间是否成功*/
		dev_err(&pdev->dev, "failed to reserve memory region\n");
		return -ENOENT;
	}

	//从平台时钟队列中获取LCD的时钟，这里为什么要取得这个时钟，
	//从LCD屏的时序图上看，各种控制信号的延迟都跟LCD的时钟有关
	fbvar->lcd_clock =clk_get(NULL, "lcd");
	if(!fbvar->lcd_clock)
	{
		/*判断获取时钟是否成功*/
		dev_err(&pdev->dev, "failed to find lcd clock source\n"); 
		ret = -ENOENT;
		goto err_nomap;
	}

	//时钟获取后要使能后才可以使用，clk_enable定义在arch/arm/plat-s3c/clock.c中
	clk_enable(fbvar->lcd_clock);	

	//申请LCD中断服务，上面获取的中断号lcd_fb_irq，使用快速中断方式:IRQF_DISABLED
	ret =request_irq(fbvar->lcd_irq_no, lcd_fb_irq, IRQF_DISABLED, pdev->name, fbvar)
	if(ret)
	{
		/*判断申请中断服务是否成功*/
		dev_err(&pdev->dev, "IRQ%d error %d\n",fbvar->lcd_irq_no,ret);
		ret = -EBUSY;
		goto err_noclk;		
	}
	/*以上是对要使用的资源进行了获取和设置。下面就开始初始化填充fb_info结构体*/

	/*首先初始化fb_info中代表LCD固定参数的结构体fb_fix_screeninfo*/
	/*像素值与显示内存的映射关系有5种，定义在fb.h中。现在采用FB_TYPE_PACKED_PIXELS方式，
	在该方式下，像素值与内存直接对应，比如在显示内存某单元写入一个"1"时，该单元对应的像
	素值也将是"1"，这使得应用层把显示内存映射到用户空间变得非常方便。Linux中当LCD为TFT
	屏时，显示驱动管理显示内存就是基于这种方式*/
	strcpy(fbinfo->fix.id, DEVICE_NAME); // 字符串形式的标识符
	fbinfo.fix.type = FB_TYPE_PACKED_PIXELS;
	fbinfo->fix.type_aux  = 0;//以下这些根据fb_fix_screeninfo定义中的描述，当没有硬件是都设为0
	fbinfo->fix.xpanstep  = 0;
	fbinfo->fix.ypanstep  = 0;
	fbinfo->fix.ywrapstep = 0;
	fbinfo->fix.accel     = FB_ACCEL_NONE;	
	//接着，再初始化fb_info中代表LCD可变参数的结构体fb_var_screeninfo
	fbinfo->var.nonstd			= 0;
	fbinfo->var.activate		= FB_ACTIVATE_NOW;
	fbinfo->var.accel_flags 	= 0;
	fbinfo->var.vmode			= FB_VMODE_NONINTERLACED;
	fbinfo->var.xres			= display->xres;
	fbinfo->var.yres			= display->yres;
	fbinfo->var.bits_per_pixel	= display->bpp;
	//指定对底层硬件操作的函数指针, 因内容较多故其定义在第3步中再讲
	fbinfo->fbops				= &lcd_fb_fops;
	fbinfo->flags				= FBINFO_FLAG_DEFAULT;
	fbinfo->pseudo_palette	    = &fbvar->pseudo_pal;

	//初始化色调色板(颜色表)为空
	for(i=0;i<256;i++)
		fbvar->palette_buffer[i] = PALETTE_BUFF_CLEAR;

	for ( i = 0 ; i < mach_info->num_displays; i++ )
	{
	    //计算FrameBuffer缓存的最大大小，这里右移3位(即除以8)
		//是因为色位模式BPP是以位为单位
		unsigned long smem_len = (mach_info->displays[i].xres * \
								  mach_info->displays[i].xres * \
								  mach_info->displays[i].bpp) >> 3;

		if(fbinfo->fix.smem_len < smem_len)
			fbinfo->fix.smem_len = smem_len;	
	}

	msleep(1); //初始化LCD控制器之前要延迟一段时间
	
	
	s3cfb_init_registers(fbinfo);//初始化完fb_info后，开始对LCD各寄存器进行初始化
	s3cfb_check_var(fbinfo);     //初始化完寄存器后，开始检查fb_info中的可变参数
	ret = s3cfb_map_video_memory(fbinfo);//申请帧缓冲设备fb_info的显示缓冲区空间
	if (ret)
	{
		dev_err(&pdev->dev, "failed to allocate video RAM: %d\n",ret);
		ret = -ENOMEM;
		goto err_nofb;
	}

	//最后，注册这个帧缓冲设备fb_info到系统中, 
	//register_framebuffer定义在fb.h中在fbmem.c中
	ret =register_framebuffer(fbinfo);
	if (ret <0)
	{
		dev_err(&pdev->dev, "failed to register framebuffer device: %d\n",ret);
		goto err_video_nomem;
	}

	//对设备文件系统的支持创建frambuffer设备文件，
	//device_create_file定义在linux/device.h中
	ret =device_create_file(&pdev->dev, &dev_attr_debug);
	if (ret)
	{
		dev_err(&pdev->dev, "failed to add debug attribute\n");
	} 
	printk(KERN_WARNING "%s\n",__FUNCTION__);
	return 0;

	//以下是出错处理
err_video_nomem:	
	s3cfb_unmap_video_memory(fbinfo);	
err_nofb:
	platform_set_drvdata(pdev, NULL);
	framebuffer_release(fbinfo);	
err_noirq:
	free_irq(fbvar->lcd_irq_no, fbvar);
err_noclk:
	clk_disable(fbvar->lcd_clock);
	clk_put(fbvar->lcd_clock);
err_nomap:
	iounmap(fbvar->lcd_base);
err_nomem:
	release_resource(fbvar->lcd_mem);
	kfree(fbvar->lcd_mem);

	return ret;
}


static struct platform_driver lcd_fb_driver = {
	.probe  = lcd_fb_probe,


	.driver = {
		.name  = "s3c2410-lcd",
		.owner = THIS_MODULE,
	}

};

static __init int lcd_fb_init(void)
{   
	// Linux中，帧缓冲设备被看做是平台设备
	platform_driver_register(&lcd_fb_driver);
}

static __exit void lcd_fb_exit(void)
{
	// 注销设备
	platform_driver_unregister(&lcd_fb_driver);
}

module_init(lcd_fb_init);
module_exit(lcd_fb_exit);
MODULE_LICENSE("GPL");
