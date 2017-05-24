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
#define PALETTE_BUFF_CLEAR (0x80000000) //������յ�ɫ��(��ɫ��)

struct fb_var
{
	int lcd_irq_no;           /*����LCD�жϺ�*/
	struct clk *lcd_clock;    /*�����ƽ̨ʱ�Ӷ����л�ȡ��LCDʱ��*/
	struct resource *lcd_mem; /*LCD��IO�ռ�*/
	void __iomem *lcd_base;   /*LCD��IO�ռ�ӳ�䵽�����ַ*/
	struct device *dev;
	struct s3c2410fb_hw regs; /*��ʾ5��LCD���üĴ�����s3c2410fb_hw������mach-s3c2410/include/mach/fb.h��*/

	/*����һ���������䵱��ɫ�塣�������ֲ�������TFT��ɫλģʽΪ8BPPʱ����ɫ��(��ɫ��)�ĳ���
	Ϊ256����ɫ����ʼ��ַΪ0x4D000400*/
	u32 palette_buffer[256];
	u32 pseudo_pal[16];
	unsigned intpalette_ready; /*��ʶ��ɫ���Ƿ�׼������*/	
};

static struct file_operations lcd_fb_fops = {



};

//�ú���ʵ���޸�GPIO�˿ڵ�ֵ������������mask��
//�����ǽ�Ҫ���õļĴ���ֵ������
static inline void modify_gpio(void __iomem *reg,
			       unsigned long set, unsigned long mask)
{
	unsigned long tmp;

	tmp = readl(reg) & ~mask;
	writel(tmp | set, reg);
}

static void s3cfb_init_registers(struct fb_info *fbinfo) // LCD ��ؼĴ����ĳ�ʼ��
{
	unsigned long flags;
	void __iomem *tpal;
	void __iomem *lpcsel;	
	struct fb_var *fbvar = fbinfo->par;
	struct s3c2410fb_mach_info *mach_info = fbvar->dev->platform_data;

	//�����ʱ��ɫ��Ĵ�������ַ��S3C2410_TPAL�궨����mach-s3c2410/include/mach/regs-lcd.h��
	//ע�����lpcsel����һ���������TFT����һ��ר�üĴ���������õĲ������ǵ�TFT��Ӧ�ò��ù���
	tpal   = fbvar->lcd_base + S3C2410_TPAL;
	lpcsel = fbvar->lcd_base + S3C2410_LPCSEL;

	//*���޸�����Ĵ���ֵ֮ǰ�������жϣ����ж�״̬���浽flags��
	local_irq_save(flags);

	//��IO�˿�C��D���ó�LCDģʽ
	modify_gpio(S3C2410_GPCUP,  mach_info->gpcup,  mach_info->gpcup_mask);
	modify_gpio(S3C2410_GPCCON, mach_info->gpccon, mach_info->gpccon_mask);
	modify_gpio(S3C2410_GPDUP,  mach_info->gpdup,  mach_info->gpdup_mask);
	modify_gpio(S3C2410_GPDCON, mach_info->gpdcon, mach_info->gpdcon_mask);	

	
	local_irq_restore(flags);//�ָ������ε��ж�
	
	writel(0x00,tpal); //��ʱ��ɫ��Ĵ���ʹ�ܽ�ֹ
	writel(mach_info->lpcsel,lpcsel); //��������TFT����һ���Ĵ�����������Բ���
	return 0;	
	
}

static void s3cfb_check_var(struct fb_info *fbinfo)
{
	unsigned int i;

	//��lcd_fb_probe̽�⺯�����õ�ƽ̨�������ٻ��LCD�����Ϣ������
	struct fb_var_screeninfo *var = &fbinfo->var;//fb_info�е�LCD�ɱ����
	struct fb_var *fbvar = fbinfo->par; //��lcd_fb_probe̽�⺯�������õ�˽�нṹ������
	struct s3c2410fb_mach_info *mach_info = fbvar->dev->platform_data; //��LCDƽ̨�豸��Դ ȡ��LCD�����ýṹ������
	struct s3c2410fb_display *display = NULL;
	struct s3c2410fb_display *default_display = mach_info->displays + mach_info->default_display;
	int type = default_display->type; //LCD������

	//��֤X/Y������
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

	//����LCD���üĴ���1�е�5-6λ(���ó�TFT����)������LCD���üĴ���5
	fbvar->regs.lcdcon1 = display->type;
	fbvar->regs.lcdcon5 = display->lcdcon5;

	//������Ļ������������غ͸߶ȿ��
	var->xres_virtual = display->xres;
	var->yres_virtual = display->yres;
	var->height = display->height;
	var->width = display->width;

	//����ʱ�����أ��С�֡�л�ֵ��ˮƽͬ������ֱͬ������ֵ
	var->pixclock = display->pixclock;
	var->left_margin = display->left_margin;
	var->right_margin = display->right_margin;
	var->upper_margin = display->upper_margin;
	var->lower_margin = display->lower_margin;
	var->vsync_len = display->vsync_len;
	var->hsync_len = display->hsync_len;

	//����͸����
	var->transp.offset = 0;
	var->transp.length = 0;

	//����ɫλģʽ(BPP)�����ÿɱ������R��G��B����ɫλ��
	//������Щ����ֵ��������ο�CPU����
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

//����֡�����豸fb_info����ʾ�������ռ�
static int __init s3cfb_map_video_memory(struct fb_info *fbinfo)
{
	dma_addr_t map_dma; //���ڱ���DMA���������ߵ�ַ
	struct fb_var *fbvar = fbinfo->par;//�����lcd_fb_probe̽�⺯�������õ�˽�нṹ������
	unsigned map_size = PAGE_ALIGN(fbinfo->fix.smem_len);//���FrameBuffer����Ĵ�С, PAGE_ALIGN������mm.h��

	//�����һ��д�ϲ�DMA����������ΪLCD��Ļ�������ַ
	//dma_alloc_writecombine������arch/arm/mm/dma-mapping.c��
	fbinfo->screen_base = dma_alloc_writecombine(fbvar->dev, map_size, &map_dma, GFP_KERNEL);
	if(fbinfo->screen_base)
	{
		//������ƬDMA������������Ϊ��
		memset(fbinfo->sreen_base, 0x00, map_size);
		
		//��DMA���������ߵ�ַ���fb_info���ɱ������framebuffer����Ŀ�ʼλ��
		fbinfo->fix.smem_start = map_dma;
	}

	return fbinfo->screen_base ? 0 : -ENOMEM;
}

//�ͷ�֡�����豸fb_info����ʾ�������ռ�
static int inline s3cfb_unmap_video_memory(struct fb_info *fbinfo)
{
	struct fb_var *fbvar = fbinfo->par;
	unsigned map_size = PAGE_ALIGN(fbinfo->fix.smem_len);
	
	//�ͷ�д�ϲ�DMA��������������DMA�ĵط����Ӧ
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
	
	lcd_irq_base = fbvar->lcd_base + S3C2410_LCDINTBASE;//LCD�жϼĴ�������ַ
	lcdirq = readl(lcd_irq_base + S3C24XX_LCDINTPND);   //��ȡLCD�жϹ���Ĵ�����ֵ
	
	//�ж��Ƿ�Ϊ�жϹ���״̬
	if(lcdirq & S3C2410_LCDINT_FRSYNC)
	{
		//����ɫ��
		if (fbvar->palette_ready)
			s3cfb_write_palette(fbvar);

		//���֡�ж������־
		writel(S3C2410_LCDINT_FRSYNC, lcd_irq_base + S3C24XX_LCDINTPND);
		writel(S3C2410_LCDINT_FRSYNC, lcd_irq_base + S3C24XX_LCDSRCPND);
	}
		
	return IRQ_HANDLED;
}

static void s3cfb_lcd_enable(struct fb_var *fbvar, int enable)
{
	unsigned long flags;

	//���޸�����Ĵ���ֵ֮ǰ�������жϣ����ж�״̬���浽flags��
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

	//�ָ������ε��ж�
	local_irq_restore(flags);
}

//�������ط�����õ���һ�����豸ע��ʱ��һ��������ע��ʱ
static __devexit int lcd_fb_remove(struct platform_device *pdev)
{
	struct fb_info *fbinfo = platform_get_drvdata(pdev);
	struct fb_var *fbvar = fbinfo->par;


	//��ϵͳ��ע��֡�����豸
	unregister_framebuffer(fbinfo);

	//ֹͣLCD�������Ĺ���
	s3cfb_lcd_enable(fbvar,0);
	msleep(1); // �ӳ�һ��ʱ�䣬��ΪֹͣLCD��������Ҫһ��ʱ��

	//�ͷ�֡�����豸fb_info����ʾ�������ռ�
	s3cfb_unmap_video_memory(fbinfo);

	//��LCDƽ̨������պ��ͷ�fb_info�ռ���Դ
	platform_set_drvdata(pdev, NULL);
	framebuffer_release(fbinfo);

	//�ͷ��ж���Դ
	free_irq(fbvar->lcd_irq_no,fbvar);

	//�ͷ�ʱ����Դ
	if (fbvar->lcd_clock)
	{
		clk_disable(fbvar->lcd_clock);
		clk_put(fbvar->lcd_clock);
		fbvar->lcd_clock = NULL;
	}

	//�ͷ�LCD IO�ռ�ӳ��������ڴ�ռ�
	iounmap(fbvar->lcd_base);
	
	//�ͷ������LCD IO�˿���ռ�õ�IO�ռ�
	release_resource(fbvar->lcd_mem); 

	return 0;
	
}

static __devinit int lcd_fb_probe(struct platform_device *pdev)
{
	int ret, i;

	struct resource *res; //�����LCDƽ̨�豸�л�ȡ��LCD��Դ
	struct fb_info *fbinfo;//FrameBuffer��������Ӧ��fb_info�ṹ
	struct s3c2410fb_mach_info *mach_info;//������ں��л�ȡ��ƽ̨�豸����
	struct fb_var *fbvar; //���涨�����������ȫ�ֱ����ṹ��
	struct s3c2410fb_display *display; //LCD����������Ϣ�ṹ�壬�ýṹ�嶨����mach-s3c2410/include/mach/fb.h��

	//��ȡLCDӲ�������Ϣ���ݣ���mach-s3c2440.c��
    //s3c24xx_fb_set_platdata()������LCD��Ӳ�������Ϣ���浽LCDƽ̨������ 
	mach_info = pdev->dev.platform_data;
	if(mach_info == NULL)
	{
		/*�жϻ�ȡ�����Ƿ�ɹ�*/
		dev_err(&pdev->dev, "no platform data for lcd\n");
		return -EINVAL;
	}	
	//�����mach-s3c2440.c�ж����FrameBufferƽ̨�豸��LCD������Ϣ
	display = mach_info->displays + mach_info->default_display;
	
	//����һ�δ�СΪsizeof(fb_info)+sizeof(fb_var)�Ŀռ䣬fb_var������豸��˽�����ݽṹ
	//����ʼ��fb_info->par = &fb_var, fb_info->device = &pdev->dev,
	//Ŀ�����������ӿں�����ͨ��fb_info�ṹȡ����Щ��Ա
	//������οռ���׵�ַ
	fbinfo = framebuffer_alloc(sizeof(fb_var), &pdev->dev);
	if(!fbinfo)
	{
		dev_err(&pdev->dev, "framebuffer alloc of registers failed\n");
		ret = -ENOMEM;
		goto err_noirq;
	}
	//���½�LCDƽ̨�豸��������Ϊfbinfo�����ں����һЩ��������ʹ��
	platform_set_drvdata(pdev, fbinfo);

	//fbinfo->par ��framebuffer_alloc()�����и�ֵ��ָ����fb_var˽�����ݽṹ
	//�����fbinfo->par��ȡ��fb_var˽�����ݽṹ�ĵ�ַ�����г�Ա�ĳ�ʼ��
	fbvar = fbinfo->par;
	fbvar->dev = &pdev->dev;//����pdev->dev��˽�����ݽṹ��������������������ͨ��fbva˽�����ݽṹȡ��LCDƽ̨�豸��Դ

	//��LCDƽ̨�豸��Դ�л�ȡLCD�жϺ�,platform_get_irq������platform_device.h��
	fbvar->lcd_irq_no =platform_get_irq(pdev, 0);
	if(fbvar->lcd_irq_no <0)
	{
		/*�жϻ�ȡ�жϺ��Ƿ�ɹ�*/
		dev_err(&pdev->dev, "no lcd irq for platform\n");
		return -ENOENT;
	}

	//��ȡLCDƽ̨�豸��ʹ�õ�IO�˿���Դ��ע�����IORESOURCE_MEM
	//��־��LCDƽ̨�豸�����е�һ��
	res =platform_get_resource(pdev,IORESOURCE_MEM,0);
	if(res == NULL)
	{
		/*�жϻ�ȡ��Դ�Ƿ�ɹ�*/
		dev_err(&pdev->dev, "failed to get memory region resource\n");
		return -ENOENT;
	}

	//����LCD IO�˿���ռ�õ�IO�ռ�(ע�����IO�ռ���ڴ�ռ��
	//����),request_mem_region������ioport.h��
	fbvar->lcd_mem =request_mem_region(res->start, res->end - res->start + 1,pdev->name);
	if(fbvar->lcd_mem == NULL)	
	{
		/*�ж�����IO�ռ��Ƿ�ɹ�*/
		dev_err(&pdev->dev, "failed to reserve memory region\n");
		return -ENOENT;
	}

	//��ƽ̨ʱ�Ӷ����л�ȡLCD��ʱ�ӣ�����ΪʲôҪȡ�����ʱ�ӣ�
	//��LCD����ʱ��ͼ�Ͽ������ֿ����źŵ��ӳٶ���LCD��ʱ���й�
	fbvar->lcd_clock =clk_get(NULL, "lcd");
	if(!fbvar->lcd_clock)
	{
		/*�жϻ�ȡʱ���Ƿ�ɹ�*/
		dev_err(&pdev->dev, "failed to find lcd clock source\n"); 
		ret = -ENOENT;
		goto err_nomap;
	}

	//ʱ�ӻ�ȡ��Ҫʹ�ܺ�ſ���ʹ�ã�clk_enable������arch/arm/plat-s3c/clock.c��
	clk_enable(fbvar->lcd_clock);	

	//����LCD�жϷ��������ȡ���жϺ�lcd_fb_irq��ʹ�ÿ����жϷ�ʽ:IRQF_DISABLED
	ret =request_irq(fbvar->lcd_irq_no, lcd_fb_irq, IRQF_DISABLED, pdev->name, fbvar)
	if(ret)
	{
		/*�ж������жϷ����Ƿ�ɹ�*/
		dev_err(&pdev->dev, "IRQ%d error %d\n",fbvar->lcd_irq_no,ret);
		ret = -EBUSY;
		goto err_noclk;		
	}
	/*�����Ƕ�Ҫʹ�õ���Դ�����˻�ȡ�����á�����Ϳ�ʼ��ʼ�����fb_info�ṹ��*/

	/*���ȳ�ʼ��fb_info�д���LCD�̶������Ľṹ��fb_fix_screeninfo*/
	/*����ֵ����ʾ�ڴ��ӳ���ϵ��5�֣�������fb.h�С����ڲ���FB_TYPE_PACKED_PIXELS��ʽ��
	�ڸ÷�ʽ�£�����ֵ���ڴ�ֱ�Ӷ�Ӧ����������ʾ�ڴ�ĳ��Ԫд��һ��"1"ʱ���õ�Ԫ��Ӧ����
	��ֵҲ����"1"����ʹ��Ӧ�ò����ʾ�ڴ�ӳ�䵽�û��ռ��÷ǳ����㡣Linux�е�LCDΪTFT
	��ʱ����ʾ����������ʾ�ڴ���ǻ������ַ�ʽ*/
	strcpy(fbinfo->fix.id, DEVICE_NAME); // �ַ�����ʽ�ı�ʶ��
	fbinfo.fix.type = FB_TYPE_PACKED_PIXELS;
	fbinfo->fix.type_aux  = 0;//������Щ����fb_fix_screeninfo�����е���������û��Ӳ���Ƕ���Ϊ0
	fbinfo->fix.xpanstep  = 0;
	fbinfo->fix.ypanstep  = 0;
	fbinfo->fix.ywrapstep = 0;
	fbinfo->fix.accel     = FB_ACCEL_NONE;	
	//���ţ��ٳ�ʼ��fb_info�д���LCD�ɱ�����Ľṹ��fb_var_screeninfo
	fbinfo->var.nonstd			= 0;
	fbinfo->var.activate		= FB_ACTIVATE_NOW;
	fbinfo->var.accel_flags 	= 0;
	fbinfo->var.vmode			= FB_VMODE_NONINTERLACED;
	fbinfo->var.xres			= display->xres;
	fbinfo->var.yres			= display->yres;
	fbinfo->var.bits_per_pixel	= display->bpp;
	//ָ���Եײ�Ӳ�������ĺ���ָ��, �����ݽ϶���䶨���ڵ�3�����ٽ�
	fbinfo->fbops				= &lcd_fb_fops;
	fbinfo->flags				= FBINFO_FLAG_DEFAULT;
	fbinfo->pseudo_palette	    = &fbvar->pseudo_pal;

	//��ʼ��ɫ��ɫ��(��ɫ��)Ϊ��
	for(i=0;i<256;i++)
		fbvar->palette_buffer[i] = PALETTE_BUFF_CLEAR;

	for ( i = 0 ; i < mach_info->num_displays; i++ )
	{
	    //����FrameBuffer���������С����������3λ(������8)
		//����ΪɫλģʽBPP����λΪ��λ
		unsigned long smem_len = (mach_info->displays[i].xres * \
								  mach_info->displays[i].xres * \
								  mach_info->displays[i].bpp) >> 3;

		if(fbinfo->fix.smem_len < smem_len)
			fbinfo->fix.smem_len = smem_len;	
	}

	msleep(1); //��ʼ��LCD������֮ǰҪ�ӳ�һ��ʱ��
	
	
	s3cfb_init_registers(fbinfo);//��ʼ����fb_info�󣬿�ʼ��LCD���Ĵ������г�ʼ��
	s3cfb_check_var(fbinfo);     //��ʼ����Ĵ����󣬿�ʼ���fb_info�еĿɱ����
	ret = s3cfb_map_video_memory(fbinfo);//����֡�����豸fb_info����ʾ�������ռ�
	if (ret)
	{
		dev_err(&pdev->dev, "failed to allocate video RAM: %d\n",ret);
		ret = -ENOMEM;
		goto err_nofb;
	}

	//���ע�����֡�����豸fb_info��ϵͳ��, 
	//register_framebuffer������fb.h����fbmem.c��
	ret =register_framebuffer(fbinfo);
	if (ret <0)
	{
		dev_err(&pdev->dev, "failed to register framebuffer device: %d\n",ret);
		goto err_video_nomem;
	}

	//���豸�ļ�ϵͳ��֧�ִ���frambuffer�豸�ļ���
	//device_create_file������linux/device.h��
	ret =device_create_file(&pdev->dev, &dev_attr_debug);
	if (ret)
	{
		dev_err(&pdev->dev, "failed to add debug attribute\n");
	} 
	printk(KERN_WARNING "%s\n",__FUNCTION__);
	return 0;

	//�����ǳ�����
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
	// Linux�У�֡�����豸��������ƽ̨�豸
	platform_driver_register(&lcd_fb_driver);
}

static __exit void lcd_fb_exit(void)
{
	// ע���豸
	platform_driver_unregister(&lcd_fb_driver);
}

module_init(lcd_fb_init);
module_exit(lcd_fb_exit);
MODULE_LICENSE("GPL");
