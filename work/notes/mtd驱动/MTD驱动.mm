<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1523938100578" ID="ID_1195767320" MODIFIED="1523938184178" TEXT="MTD&#x9a71;&#x52a8;">
<font NAME="SansSerif" SIZE="18"/>
<node CREATED="1523938174574" ID="ID_1241092888" MODIFIED="1523938414768" POSITION="right" TEXT="&#x8bbe;&#x5907;&#x90e8;&#x5206;">
<node CREATED="1523938496204" ID="ID_63186431" MODIFIED="1524025426276">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      platform.c&#25991;&#20214;:
    </p>
    <p>
      <font color="#f87312">/** </font>
    </p>
    <p>
      <font color="#f87312">&#160;* resource &#32467;&#26500;&#22635;SFC&#25511;&#21046;&#22120;&#30340;&#30828;&#20214;&#36164;&#28304;&#65292;&#21253;&#25324;&#65306; </font>
    </p>
    <p>
      <font color="#f87312">&#160;* &#23492;&#23384;&#22120;&#22320;&#22336;&#31354;&#38388;&#12289;&#20013;&#26029;&#21495;&#20197;&#21450;&#20018;&#34892;&#26102;&#38047;&#39057;&#29575; </font>
    </p>
    <p>
      <font color="#f87312">&#160;*/</font>
    </p>
    <p>
      static struct resource jz_sfc_resources[] = {
    </p>
    <p>
      &#160;&#160;&#160;&#160;[0] = {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.flags = IORESOURCE_MEM,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.start = <font color="#dd0d0d">SFC_IOBASE</font>,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.end = SFC_IOBASE + 0x10000 - 1,
    </p>
    <p>
      &#160;&#160;&#160;&#160;},
    </p>
    <p>
      &#160;&#160;&#160;&#160;[1] = {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.flags = IORESOURCE_IRQ,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.start = <font color="#e31818">IRQ_SFC</font>,
    </p>
    <p>
      &#160;&#160;&#160;&#160;},
    </p>
    <p>
      &#160;&#160;&#160;&#160;[2] = {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.start = <font color="#ec0b0b">CONFIG_SFC_SPEED</font>,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.flags = IORESOURCE_BUS,
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      };
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f37e1f">/** </font>
    </p>
    <p>
      <font color="#f37e1f">&#160;* platform&#35774;&#22791;&#32467;&#26500;&#65292;&#21253;&#21547;&#19978;&#38754;&#30828;&#20214;&#36164;&#28304;&#65292;&#23558;&#22312; </font>
    </p>
    <p>
      <font color="#f37e1f">&#160;* board_bash.c&#20013;&#32487;&#32493;&#22635;&#34917;platform_data&#24182;&#27880;&#20876; </font>
    </p>
    <p>
      <font color="#f37e1f">&#160;*/</font>
    </p>
    <p>
      struct platform_device jz_sfc_device = {
    </p>
    <p>
      &#160;&#160;&#160;&#160;.name = &quot;<font color="#f11a1a">jz-sfc</font>&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;.id = 0,
    </p>
    <p>
      &#160;&#160;&#160;&#160;.resource = jz_sfc_resources,
    </p>
    <p>
      &#160;&#160;&#160;&#160;.num_resources = ARRAY_SIZE(jz_sfc_resources),
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1523938498617" ID="ID_1580542219" MODIFIED="1524025451548">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      sfc_bus.c&#25991;&#20214;&#65306;
    </p>
    <p>
      #ifdef CONFIG_JZ_SFC_FLASH_POWER_CTRL
    </p>
    <p>
      struct flash_power_ctrl <font color="#1647e7">power_ctrl</font>&#160;= {
    </p>
    <p>
      &#160;&#160;&#160;&#160;.power_pin = GPIO_FLASH_POWER,
    </p>
    <p>
      &#160;&#160;&#160;&#160;.power_en_level = GPIO_FLASH_POWER_EN_LEVEL,
    </p>
    <p>
      &#160;&#160;&#160;&#160;.power_on_delay_ms = FLASH_POWER_ON_DELAY,
    </p>
    <p>
      };
    </p>
    <p>
      #endif /* CONFIG_JZ_SFC_FLASH_POWER_CTRL */
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f67d07">/** </font>
    </p>
    <p>
      <font color="#f67d07">&#160;* flash&#35774;&#22791;&#20449;&#24687;&#32467;&#26500;&#20307;&#65292;&#21253;&#21547;flash&#30340;&#21442;&#25968;&#12289;&#20998;&#21306;&#34920;&#21450;&#20854;&#20998;&#21306;&#20010;&#25968;&#31561;&#20449;&#24687;&#65292; </font>
    </p>
    <p>
      <font color="#f67d07">&#160;* &#23558;&#34987;&#22635;&#20805;&#21040;struct platform_device&#32467;&#26500;&#30340;platform_data&#25351;&#21521;&#30340;&#31354;&#38388;&#12290; </font>
    </p>
    <p>
      <font color="#f67d07">&#160;*/</font>
    </p>
    <p>
      struct jz_sfc_info <font color="#1448e4">sfc_info_cfg</font>&#160;= {
    </p>
    <p>
      &#160;&#160;&#160;&#160;.use_board_info = 0, <font color="#e98e0f">/* 0:&#20998;&#21306;&#34920;&#26159;&#20174;flash&#20013;&#35835;&#21462;&#65292;&#38750;0: &#20998;&#21306;&#34920;&#30001;flash_partition&#25351;&#23450; */</font>
    </p>
    <p>
      
    </p>
    <p>
      #if defined(CONFIG_JZ_SFC_NOR)
    </p>
    <p>
      &#160;&#160;&#160;&#160;.flash_param = &amp;spi_nor_info_table[SPINOR_INFO_NUM],&#160;&#160;//please check nor params before use
    </p>
    <p>
      &#160;&#160;&#160;&#160;.flash_partition = <font color="#e51a1a">sfc_nor_partition</font>,
    </p>
    <p>
      &#160;&#160;&#160;&#160;.num_partition = ARRAY_SIZE(sfc_nor_partition),
    </p>
    <p>
      &#160;&#160;&#160;&#160;.other_args = &amp;nor_pri_data,
    </p>
    <p>
      #elif defined(CONFIG_JZ_SFCNAND)
    </p>
    <p>
      &#160;&#160;&#160;&#160;.flash_param = NULL,
    </p>
    <p>
      &#160;&#160;&#160;&#160;.flash_partition = <font color="#df0f0f">spinand_partition</font>,
    </p>
    <p>
      &#160;&#160;&#160;&#160;.num_partition = ARRAY_SIZE(spinand_partition),
    </p>
    <p>
      &#160;&#160;&#160;&#160;.other_args = NULL,
    </p>
    <p>
      #endif
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_JZ_SFC_FLASH_POWER_CTRL
    </p>
    <p>
      &#160;&#160;&#160;&#160;.flash_power_ctrl = &amp;power_ctrl, <font color="#f59006">/* &#20241;&#30496;&#21796;&#37266;&#26102;flash&#25481;&#30005;&#25511;&#21046; */</font>
    </p>
    <p>
      #endif
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1523938427615" ID="ID_502407364" MODIFIED="1524130198811" TEXT="norflash">
<node CREATED="1523946727841" ID="ID_1896994965" MODIFIED="1523946781851">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      #include &quot;sfc_nor_table.h&quot;
    </p>
    <p>
      #define SPINOR_UBOOT_OFF&#160;&#160;&#160;&#160;0
    </p>
    <p>
      #define SPINOR_UBOOT_SIZE&#160;&#160;&#160;0x40000
    </p>
    <p>
      #define SPINOR_KERNEL_OFF&#160;&#160;&#160;(SPINOR_UBOOT_OFF + SPINOR_UBOOT_SIZE)
    </p>
    <p>
      #define SPINOR_KERNEL_SIZE&#160;&#160;0x300000
    </p>
    <p>
      #define SPINOR_ROOTFS_OFF&#160;&#160;&#160;0x360000
    </p>
    <p>
      #define SPINOR_ROOTFS_SIZE&#160;&#160;MAX_PART_SIZE
    </p>
    <p>
      #define MAX_PART_SIZE&#160;&#160;&#160;-1
    </p>
    <p>
      
    </p>
    <p>
      #define SPINOR_INFO_NUM 0
    </p>
    <p>
      #define SPINOR_FS_ERASE_32K 32768
    </p>
    <p>
      #define SPINOR_FS_ERASE_64K 65536
    </p>
    <p>
      #define SPINOR_QUAD_MODE&#160;&#160;&#160;&#160;1
    </p>
    <p>
      #define SPINOR_STANDARD_MODE&#160;&#160;&#160;&#160;0
    </p>
    <p>
      
    </p>
    <p>
      /**
    </p>
    <p>
      &#160;* norflash&#20998;&#21306;&#34920;&#65292;&#22312;struct jz_sfc_info&#30340;use_board_info=1&#30340;&#26102;&#20505;&#25165;&#34987;&#20351;&#29992;
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      struct nor_partition sfc_nor_partition[] = {
    </p>
    <p>
      &#160;&#160;&#160;&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.name = &quot;uboot&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.offset = SPINOR_UBOOT_OFF,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.size = SPINOR_UBOOT_SIZE,
    </p>
    <p>
      &#160;&#160;&#160;&#160;},
    </p>
    <p>
      &#160;&#160;&#160;&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.name = &quot;kernel&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.offset = SPINOR_KERNEL_OFF,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.size = SPINOR_KERNEL_SIZE,
    </p>
    <p>
      &#160;&#160;&#160;&#160;},
    </p>
    <p>
      &#160;&#160;&#160;&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.name = &quot;rootfs&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.offset = SPINOR_ROOTFS_OFF,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.size = SPINOR_ROOTFS_SIZE,
    </p>
    <p>
      &#160;&#160;&#160;&#160;},
    </p>
    <p>
      };
    </p>
    <p>
      
    </p>
    <p>
      
    </p>
    <p>
      struct nor_private_data nor_pri_data = {
    </p>
    <p>
      &#160;&#160;&#160;&#160;.fs_erase_size = SPINOR_FS_ERASE_32K,
    </p>
    <p>
      &#160;&#160;&#160;&#160;.uk_quad = SPINOR_QUAD_MODE,
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1523938425298" ID="ID_959130865" MODIFIED="1524130200660" TEXT="nandflash">
<node CREATED="1523938462915" ID="ID_1370700675" MODIFIED="1523946682213">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      #define SPINAND_UBOOT_OFFSET&#160;&#160;&#160;&#160;0x0
    </p>
    <p>
      #define SPINAND_UBOOT_SIZE&#160;&#160;0x100000
    </p>
    <p>
      #define SPINAND_KERNEL_OFFSET&#160;&#160;&#160;(SPINAND_UBOOT_OFFSET + SPINAND_UBOOT_SIZE)
    </p>
    <p>
      #define SPINAND_KERNEL_SIZE 0x800000
    </p>
    <p>
      #define SPINAND_ROOTFS_OFFSET&#160;&#160;&#160;(SPINAND_KERNEL_OFFSET + SPINAND_KERNEL_SIZE)
    </p>
    <p>
      #define SPINAND_ROOTFS_SIZE 0x2800000
    </p>
    <p>
      #define SPINAND_DATA_OFFSET (SPINAND_ROOTFS_OFFSET + SPINAND_ROOTFS_SIZE)
    </p>
    <p>
      #define SPINAND_DATA_SIZE&#160;&#160;&#160;0x0
    </p>
    <p>
      #define SPINAND_MASK_FLAGS&#160;&#160;0x0
    </p>
    <p>
      
    </p>
    <p>
      /**
    </p>
    <p>
      &#160;* nandflash&#20998;&#21306;&#34920;&#65292;&#22312;struct jz_sfc_info&#30340;use_board_info=1&#30340;&#26102;&#20505;&#25165;&#34987;&#20351;&#29992;
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      struct jz_sfcnand_partition spinand_partition[] = {
    </p>
    <p>
      &#160;&#160;&#160;&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.name = &quot;uboot&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.offset = SPINAND_UBOOT_OFFSET,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.size = SPINAND_UBOOT_SIZE,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.mask_flags = SPINAND_MASK_FLAGS,
    </p>
    <p>
      &#160;&#160;&#160;&#160;},
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.name = &quot;kernel&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.offset = SPINAND_KERNEL_OFFSET,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.size = SPINAND_KERNEL_SIZE,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.mask_flags = SPINAND_MASK_FLAGS,
    </p>
    <p>
      &#160;&#160;&#160;&#160;},
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.name = &quot;rootfs&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.offset = SPINAND_ROOTFS_OFFSET,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.size = SPINAND_ROOTFS_SIZE,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.mask_flags = SPINAND_MASK_FLAGS,
    </p>
    <p>
      &#160;&#160;&#160;&#160;},
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.name = &quot;data&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.offset = SPINAND_DATA_OFFSET,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.size = SPINAND_DATA_SIZE,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;.mask_flags = SPINAND_MASK_FLAGS,
    </p>
    <p>
      &#160;&#160;&#160;&#160;},
    </p>
    <p>
      };
    </p>
    <p>
      #endif
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
</node>
<node CREATED="1523938174902" ID="ID_771931888" MODIFIED="1523938419457" POSITION="right" TEXT="&#x9a71;&#x52a8;&#x90e8;&#x5206;">
<node CREATED="1523947293912" ID="ID_1491447723" MODIFIED="1523947304175" TEXT="nandflash">
<node CREATED="1523947321544" ID="ID_1472919091" MODIFIED="1523950845160" TEXT="&#x8bbe;&#x5907;&#x9a71;&#x52a8;&#xff1a;drivers/mtd/devices/jz_sfc_nand.c"/>
<node CREATED="1523947324037" ID="ID_1312419218" MODIFIED="1523951009301" TEXT="jz_sfcnand_probe()&#x8fc7;&#x7a0b;&#x5206;&#x6790;">
<node CREATED="1523950994657" ID="ID_1433214417" MODIFIED="1524040755352" TEXT="&#x91cd;&#x8981;&#x7ed3;&#x6784;&#x4f53;">
<node CREATED="1523951048065" ID="ID_1538266556" MODIFIED="1524025391395">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#fa7612">/** </font>
    </p>
    <p>
      <font color="#fa7612">&#160;* &#36825;&#20010;&#32467;&#26500;&#26159;&#36143;&#31359;&#25972;&#20010;sfcnand&#39537;&#21160;&#30340;&#38750;&#24120;&#37325;&#35201;&#30340;&#32467;&#26500;&#65292;&#21253;&#21547;: </font>
    </p>
    <p>
      <font color="#fa7612">&#160;* SFC&#25511;&#21046;&#22120;&#30828;&#20214;&#36164;&#28304;&#32467;&#26500;sfc </font>
    </p>
    <p>
      <font color="#fa7612">&#160;* &#25351;&#21521;&#20445;&#23384;flash&#20449;&#24687;&#30340;flash_info&#65292;&#22312;probe&#20989;&#25968;&#20013;&#35774;&#32622;&#25351;&#21521;&#32467;&#26500;jz_sfcnand_flashinfo </font>
    </p>
    <p>
      <font color="#fa7612">&#160;* &#20445;&#23384;platform_device&#20013;dev&#25351;&#38024; </font>
    </p>
    <p>
      <font color="#fa7612">&#160;* MTD&#21407;&#22987;&#35774;&#22791;&#30340;&#25968;&#25454;&#32467;&#26500;&#26159;mtd_info </font>
    </p>
    <p>
      <font color="#fa7612">&#160;* &#20114;&#26021;&#38145; </font>
    </p>
    <p>
      <font color="#fa7612">&#160;*/</font>
    </p>
    <p>
      struct sfc_flash {
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#174de9">struct sfc</font>&#160;*sfc;&#160;&#160;&#160;&#160;&#160;/*&#25551;&#36848;SFC&#25511;&#21046;&#22120;&#30340;&#25968;&#25454;&#32467;&#26500; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *flash_info;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct device *dev;
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#143ae7">struct mtd_info</font>&#160;mtd; / *&#25551;&#36848;MTD&#21407;&#22987;&#35774;&#22791;&#30340;&#25968;&#25454;&#32467;&#26500; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct mutex lock;
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1523956647534" ID="ID_828016645" MODIFIED="1524025403707">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#e96413">/** </font>
    </p>
    <p>
      <font color="#e96413">&#160;* &#36825;&#20010;&#32467;&#26500;&#21253;&#21547;SFC&#25511;&#21046;&#22120;&#30340;&#30828;&#20214;&#30456;&#20851;&#30340;&#36164;&#28304;&#65292;&#26377;&#65306; </font>
    </p>
    <p>
      <font color="#e96413">&#160;* &#23492;&#23384;&#22120;&#22320;&#22336;&#31354;&#38388;&#12289;&#26102;&#38047;&#28304;&#21450;&#39057;&#29575;&#12289;&#20013;&#26029;&#21495;&#21450;&#20013;&#26029;&#26381;&#21153;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#e96413">&#160;* &#27599;&#20010;&#20256;&#36755;&#21160;&#20316;&#38656;&#35201;&#22635;&#20805;&#30340;&#32467;&#26500;sfc_transfer&#31561; </font>
    </p>
    <p>
      <font color="#e96413">&#160;*/</font>
    </p>
    <p>
      struct sfc {
    </p>
    <p>
      &#160;&#160;&#160;&#160;void __iomem&#160;&#160;&#160;&#160;*iomem;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct resource *ioarea;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;irq;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct clk&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*clk;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct clk&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*clk_gate;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned long src_clk;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct completion&#160;&#160;&#160;&#160;done;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;threshold;
    </p>
    <p>
      &#160;&#160;&#160;&#160;irqreturn_t (*irq_callback)(struct sfc *);
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned long&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;phys;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct sfc_transfer *transfer;
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1524020904791" ID="ID_704948158" MODIFIED="1524020909263">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct cmd_info {
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t cmd;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t dataen;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t pollen;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t sta_exp;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t sta_msk;
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1524020816152" ID="ID_1835949968" MODIFIED="1524020888841">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct sfc_transfer {
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t direction;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#1d42f4">struct cmd_info</font>&#160;cmd_info;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t addr_len;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t addr;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t addr_plus;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t *data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t data_dummy_bits;/*addr + data_dummy_bits + data*/
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t len;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t cur_len;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t sfc_mode;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t ops_mode;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t phase_format;/*we just use default value;phase1:cmd+dummy+addr... phase0:cmd+addr+dummy...*/
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct list_head list;
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1523958432982" ID="ID_1840728405" MODIFIED="1524128587846" STYLE="fork">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct mtd_info {&#160;
    </p>
    <p>
      &#160;&#160;&#160;&#160;u_char type;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* MTD&#31867;&#22411;&#65292;&#21253;&#25324;MTD_NORFLASH,MTD_NANDFLASH&#31561; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t flags;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* MTD&#23646;&#24615;&#26631;&#24535;&#65292;MTD_WRITEABLE,MTD_NO_ERASE&#31561; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint64_t size;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* MTD&#35774;&#22791;&#30340;&#22823;&#23567; */&#160;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t erasesize;&#160;&#160;&#160;&#160;/* MTD&#35774;&#22791;&#30340;&#25830;&#38500;&#21333;&#20803;&#22823;&#23567;&#65292;&#23545;&#20110;nandflash&#26469;&#35828;&#23601;&#26159;block&#30340;&#22823;&#23567; */&#160;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t writesize;&#160;&#160;&#160;&#160;/* &#20889;&#22823;&#23567;, &#23545;&#20110;norflash&#26159;&#23383;&#33410;&#65292;&#23545;nandflash&#20026;&#19968;&#39029; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t writebufsize; /* MTD&#35774;&#22791;&#20889;buffer&#22823;&#23567;&#65292;&#23545;nandflash&#20026;&#19968;&#39029; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t oobsize;&#160;&#160;&#160;&#160;&#160;&#160;/* OOB&#23383;&#33410;&#25968; */&#160;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t oobavail;&#160;&#160;&#160;&#160;&#160;/* &#21487;&#29992;&#30340;OOB&#23383;&#33410;&#25968; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* If erasesize is a power of 2 then the shift is stored in
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* erasesize_shift otherwise erasesize_shift is zero. Ditto writesize.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int erasesize_shift;&#160;&#160;&#160;/*&#160;&#20551;&#22914;erasesize&#26159;2&#30340;&#24130;&#27425;&#65292;erasesize_shift&#31561;&#20110;2&#30340;&#24130;&#65292;&#21542;&#21017;&#20026;0&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int writesize_shift;
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* Masks based on erasesize_shift and writesize_shift */&#160;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int erasesize_mask;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int writesize_mask;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* read ops return -EUCLEAN if max number of bitflips corrected on any
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* one region comprising an ecc step equals or exceeds this value.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* Settable by driver, else defaults to ecc_strength.&#160;&#160;User can override
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* in sysfs.&#160;&#160;N.B. The meaning of the -EUCLEAN return code has changed;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* see Documentation/ABI/testing/sysfs-class-mtd for more detail.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int bitflip_threshold;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;const char *name;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* &#21517;&#23383;&#65292;&#19981;&#37325;&#35201;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;int index;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* &#32034;&#24341;&#21495;&#65292;&#19981;&#37325;&#35201; */
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* ECC layout structure pointer - read only! */
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_ecclayout *ecclayout;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* max number of correctible bit errors per ecc step */
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int ecc_strength;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* Data for variable erase regions. If numeraseregions is zero,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* it means that the whole device has erasesize as given above.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;int numeraseregions;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct mtd_erase_region_info *eraseregions;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* Do not call via these pointers, use corresponding mtd_*()
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* wrappers instead.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_erase) (struct mtd_info *mtd, struct erase_info *instr);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_point) (struct mtd_info *mtd, loff_t from, size_t len,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t *retlen, void **virt, resource_size_t *phys);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_unpoint) (struct mtd_info *mtd, loff_t from, size_t len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned long (*_get_unmapped_area) (struct mtd_info *mtd,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;unsigned long len,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;unsigned long offset,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;unsigned long flags);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_read) (struct mtd_info *mtd, loff_t from, size_t len,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t *retlen, u_char *buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_write) (struct mtd_info *mtd, loff_t to, size_t len,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t *retlen, const u_char *buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_panic_write) (struct mtd_info *mtd, loff_t to, size_t len,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t *retlen, const u_char *buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_read_oob) (struct mtd_info *mtd, loff_t from,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;struct mtd_oob_ops *ops);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_write_oob) (struct mtd_info *mtd, loff_t to,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;struct mtd_oob_ops *ops);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_get_fact_prot_info) (struct mtd_info *mtd, struct otp_info *buf,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_read_fact_prot_reg) (struct mtd_info *mtd, loff_t from,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t len, size_t *retlen, u_char *buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_get_user_prot_info) (struct mtd_info *mtd, struct otp_info *buf,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_read_user_prot_reg) (struct mtd_info *mtd, loff_t from,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t len, size_t *retlen, u_char *buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_write_user_prot_reg) (struct mtd_info *mtd, loff_t to,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t len, size_t *retlen, u_char *buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_lock_user_prot_reg) (struct mtd_info *mtd, loff_t from,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_writev) (struct mtd_info *mtd, const struct kvec *vecs,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;unsigned long count, loff_t to, size_t *retlen);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*_sync) (struct mtd_info *mtd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_lock) (struct mtd_info *mtd, loff_t ofs, uint64_t len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_unlock) (struct mtd_info *mtd, loff_t ofs, uint64_t len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_is_locked) (struct mtd_info *mtd, loff_t ofs, uint64_t len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_block_isbad) (struct mtd_info *mtd, loff_t ofs);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_block_markbad) (struct mtd_info *mtd, loff_t ofs);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_suspend) (struct mtd_info *mtd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*_resume) (struct mtd_info *mtd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* If the driver is something smart, like UBI, it may need to maintain
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* its own reference counting. The below functions are only for driver.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*_get_device) (struct mtd_info *mtd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*_put_device) (struct mtd_info *mtd);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* Backing device capabilities for this device
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* - provides mmap capabilities
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct backing_dev_info *backing_dev_info;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct notifier_block reboot_notifier;&#160;&#160;/* default mode before reboot */
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* ECC status information */
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#0d4cfe">struct mtd_ecc_stats</font>&#160;ecc_stats;
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* Subpage shift (NAND) */
    </p>
    <p>
      &#160;&#160;&#160;&#160;int subpage_sft;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *priv; <font color="#ea1111">/* &#35774;&#22791;&#31169;&#26377;&#25968;&#25454;&#25351;&#38024;&#65292;&#23545;&#20110;nandflash&#26469;&#35828;&#25351;nand_chip&#32467;&#26500;&#20307; */</font>&#160;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct module *owner; /* &#19968;&#33324;&#35774;&#32622;&#20026;THIS_MODULE */&#160;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct device dev;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int usecount;
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1523951049550" ID="ID_616981799" MODIFIED="1524040474693">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#f78a19">/** </font>
    </p>
    <p>
      <font color="#f78a19">&#160;* &#36825;&#20010;&#32467;&#26500;&#23545;&#24212;&#19968;&#20010;nandflash&#65292;&#21253;&#21547;&#65306; </font>
    </p>
    <p>
      <font color="#f78a19">&#160;* nandflash&#21378;&#21830;id&#65292;&#35774;&#22791;id </font>
    </p>
    <p>
      <font color="#f78a19">&#160;* nandflash&#22522;&#30784;&#21442;&#25968;&#65292;&#27604;&#22914;&#65306;&#39029;&#22823;&#23567;&#12289;&#22359;&#22823;&#23567;&#31561; </font>
    </p>
    <p>
      <font color="#f78a19">&#160;* nandflash&#20998;&#21306;&#24773;&#20917; </font>
    </p>
    <p>
      <font color="#f78a19">&#160;* nandflash&#25805;&#20316;&#20989;&#25968;&#65292;&#27604;&#22914;&#65306;&#35835;&#12289;&#20889;&#21450;&#25830;&#38500;&#31561; </font>
    </p>
    <p>
      <font color="#f78a19">&#160;* </font>
    </p>
    <p>
      <font color="#f78a19">&#160;* &#27880;&#65306;&#36825;&#20010;&#32467;&#26500;&#22312;probe&#20989;&#25968;&#30003;&#35831;&#65292;&#24182;&#20445;&#23384;&#21040;sfc_flash </font>
    </p>
    <p>
      <font color="#f78a19">&#160;*&#160;&#32467;&#26500;&#20013;&#30340;flash_info&#20013; </font>
    </p>
    <p>
      <font color="#f78a19">&#160;*/</font>
    </p>
    <p>
      struct jz_sfcnand_flashinfo {
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t id_manufactory;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t id_device;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfcnand_base_param param;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfcnand_partition_param partition;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfcnand_ops ops;
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1523955382839" ID="ID_96604511" MODIFIED="1524025376587">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#f57e1b">/** </font>
    </p>
    <p>
      <font color="#f57e1b">&#160;* &#36825;&#20010;&#32467;&#26500;&#32473;&#20986;nandflash&#22522;&#26412;&#21442;&#25968;&#65292; </font>
    </p>
    <p>
      <font color="#f57e1b">&#160;* &#20197;&#21450;&#25805;&#20316;nandflash&#26102;&#24207;&#21442;&#25968; </font>
    </p>
    <p>
      <font color="#f57e1b">&#160;*/</font>
    </p>
    <p>
      struct jz_sfcnand_base_param {
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t pagesize;&#160;&#160;//&#39029;&#22823;&#23567;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t blocksize; //&#22359;&#22823;&#23567;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t oobsize;&#160;&#160;&#160;//oob&#21306;&#22823;&#23567;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t flashsize; //&#25972;&#29255;flash&#22823;&#23567;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint16_t tHOLD;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint16_t tSETUP;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint16_t tSHSL_R;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint16_t tSHSL_W;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint16_t tRD;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint16_t tPP;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint16_t tBE;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t ecc_max;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t need_quad;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1523955384045" ID="ID_28059711" MODIFIED="1524040631426">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct jz_sfcnand_partition_param {
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#224be5">struct mtd_partition</font>&#160;*partition; /* MTD&#39537;&#21160;&#25551;&#36848;&#20998;&#21306;&#32467;&#26500; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t num_partition; /* &#20998;&#21306;&#20010;&#25968; */
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1524139704338" ID="ID_1645424301" MODIFIED="1524139805809">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct mtd_partition {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *name;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* identifier string */
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint64_t size;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* partition size */
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint64_t offset;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* offset within the master MTD space */
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t mask_flags;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* master MTD flags to mask out for this partition */
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_ecclayout *ecclayout;&#160;&#160;&#160;&#160;/* out of band layout for this partition (NAND only) */
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1523955384741" ID="ID_326101797" MODIFIED="1524020739396">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct jz_sfcnand_ops {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfcnand_read nand_read_ops;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfcnand_write nand_write_ops;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfcnand_erase nand_erase_ops;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
<node CREATED="1523956032867" ID="ID_166430188" MODIFIED="1523957385218">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#ea1515">struct flash_operation_message</font>&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#1441e3">struct sfc_flash</font>&#160;*flash;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t pageaddr;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t columnaddr;
    </p>
    <p>
      &#160;&#160;&#160;&#160;u_char *buffer;
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t len;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1523955833617" ID="ID_868237363" MODIFIED="1523956577534">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct jz_sfcnand_read {
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*pageread_to_cache)(struct sfc_transfer *, <font color="#e41212">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int32_t (*get_feature)(<font color="#e31414">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*single_read)(struct sfc_transfer *, <font color="#e31414">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*quad_read)(struct sfc_transfer *, <font color="#da0808">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
<arrowlink DESTINATION="ID_166430188" ENDARROW="Default" ENDINCLINATION="342;0;" ID="Arrow_ID_1102742546" STARTARROW="None" STARTINCLINATION="342;0;"/>
</node>
<node CREATED="1523955835102" ID="ID_937842989" MODIFIED="1523956577534">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct jz_sfcnand_write {
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*write_enable)(struct sfc_transfer *, <font color="#e31414">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*single_load)(struct sfc_transfer *, <font color="#e30c0c">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*quad_load)(struct sfc_transfer *, <font color="#e40f0f">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*program_exec)(struct sfc_transfer *, <font color="#e21515">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int32_t (*get_feature)(<font color="#e90e0e">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
<arrowlink DESTINATION="ID_166430188" ENDARROW="Default" ENDINCLINATION="350;0;" ID="Arrow_ID_1949625749" STARTARROW="None" STARTINCLINATION="350;0;"/>
</node>
<node CREATED="1523955835472" ID="ID_385966317" MODIFIED="1523956577535">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct jz_sfcnand_erase {
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*write_enable)(struct sfc_transfer *, <font color="#fb1414">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*block_erase)(struct sfc_transfer *, <font color="#e71414">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int32_t (*get_feature)(<font color="#dc0a0a">struct flash_operation_message</font>&#160;*);
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
<arrowlink DESTINATION="ID_166430188" ENDARROW="Default" ENDINCLINATION="401;0;" ID="Arrow_ID_1732616977" STARTARROW="None" STARTINCLINATION="401;0;"/>
</node>
</node>
</node>
<node CREATED="1524040131390" ID="ID_1452901763" MODIFIED="1524040928864">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct nand_chip {
    </p>
    <p>
      &#160;&#160;&#160;&#160;void __iomem *IO_ADDR_R;
    </p>
    <p>
      &#160;&#160;&#160;&#160;void __iomem *IO_ADDR_W;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t (*read_byte)(struct mtd_info *mtd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;u16 (*read_word)(struct mtd_info *mtd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*write_buf)(struct mtd_info *mtd, const uint8_t *buf, int len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*read_buf)(struct mtd_info *mtd, uint8_t *buf, int len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*select_chip)(struct mtd_info *mtd, int chip);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*block_bad)(struct mtd_info *mtd, loff_t ofs, int getchip);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*block_markbad)(struct mtd_info *mtd, loff_t ofs);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*cmd_ctrl)(struct mtd_info *mtd, int dat, unsigned int ctrl);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*init_size)(struct mtd_info *mtd, struct nand_chip *this,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;u8 *id_data);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*dev_ready)(struct mtd_info *mtd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*cmdfunc)(struct mtd_info *mtd, unsigned command, int column,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;int page_addr);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int(*waitfunc)(struct mtd_info *mtd, struct nand_chip *this);
    </p>
    <p>
      &#160;&#160;&#160;&#160;void (*erase_cmd)(struct mtd_info *mtd, int page);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*scan_bbt)(struct mtd_info *mtd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*errstat)(struct mtd_info *mtd, struct nand_chip *this, int state,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;int status, int page);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*write_page)(struct mtd_info *mtd, struct nand_chip *chip,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;uint32_t offset, int data_len, const uint8_t *buf,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;int oob_required, int page, int cached, int raw);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*onfi_set_features)(struct mtd_info *mtd, struct nand_chip *chip,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;int feature_addr, uint8_t *subfeature_para);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*onfi_get_features)(struct mtd_info *mtd, struct nand_chip *chip,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;int feature_addr, uint8_t *subfeature_para);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;int chip_delay;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int options;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int bbt_options;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;int page_shift;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int phys_erase_shift;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int bbt_erase_shift;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int chip_shift;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int numchips;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint64_t chipsize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int pagemask;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int pagebuf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int pagebuf_bitflips;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int subpagesize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t cellinfo;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int badblockpos;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int badblockbits;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;int onfi_version;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_onfi_params&#160;&#160;&#160;&#160;onfi_params;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;flstate_t state;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t *oob_poi;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_hw_control *controller;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_ecclayout *ecclayout;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_ecc_ctrl ecc;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_buffers *buffers;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_hw_control hwcontrol;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t *bbt;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_bbt_descr *bbt_td;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_bbt_descr *bbt_md;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_bbt_descr *<font color="#e70404">badblock_pattern</font>;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *priv;
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1524040846766" ID="ID_647842787" MODIFIED="1524106194389">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /* The maximum number of NAND chips in an array */
    </p>
    <p>
      #define <font color="#0b32ef">NAND_MAX_CHIPS</font>&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;8
    </p>
    <p>
      
    </p>
    <p>
      /**
    </p>
    <p>
      &#160;* struct nand_bbt_descr - bad block table descriptor
    </p>
    <p>
      &#160;* @options:&#160;&#160;&#160;&#160;options for this descriptor
    </p>
    <p>
      &#160;* @pages:&#160;&#160;&#160;&#160;the page(s) where we find the bbt, used with option BBT_ABSPAGE
    </p>
    <p>
      &#160;*&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;when bbt is searched, then we store the found bbts pages here.
    </p>
    <p>
      &#160;*&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;Its an array and supports up to 8 chips now
    </p>
    <p>
      &#160;* @offs:&#160;&#160;&#160;&#160;offset of the pattern in the oob area of the page
    </p>
    <p>
      &#160;* @veroffs:&#160;&#160;&#160;&#160;offset of the bbt version counter in the oob are of the page
    </p>
    <p>
      &#160;* @version:&#160;&#160;&#160;&#160;version read from the bbt page during scan
    </p>
    <p>
      &#160;* @len:&#160;&#160;&#160;&#160;length of the pattern, if 0 no pattern check is performed
    </p>
    <p>
      &#160;* @maxblocks:&#160;&#160;&#160;&#160;maximum number of blocks to search for a bbt. This number of
    </p>
    <p>
      &#160;*&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;blocks is reserved at the end of the device where the tables are
    </p>
    <p>
      &#160;*&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;written.
    </p>
    <p>
      &#160;* @reserved_block_code: if non-0, this pattern denotes a reserved (rather than
    </p>
    <p>
      &#160;*&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;bad) block in the stored bbt
    </p>
    <p>
      &#160;* @pattern:&#160;&#160;&#160;&#160;pattern to identify bad block table or factory marked good /
    </p>
    <p>
      &#160;*&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;bad blocks, can be NULL, if len = 0
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* Descriptor for the bad block table marker and the descriptor for the
    </p>
    <p>
      &#160;* pattern which identifies good and bad blocks. The assumption is made
    </p>
    <p>
      &#160;* that the pattern and the version count are always located in the oob area
    </p>
    <p>
      &#160;* of the first block.
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      struct nand_bbt_descr {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int options;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int pages[NAND_MAX_CHIPS];
    </p>
    <p>
      &#160;&#160;&#160;&#160;int offs;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int veroffs;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t version[NAND_MAX_CHIPS];
    </p>
    <p>
      &#160;&#160;&#160;&#160;int len;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int maxblocks;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int reserved_block_code;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t *pattern;
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1524040908328" ID="ID_549390539" MODIFIED="1524042778022">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* struct nand_buffers - buffer structure for read/write
    </p>
    <p>
      &#160;* @ecccalc:&#160;&#160;&#160;&#160;buffer for calculated ECC
    </p>
    <p>
      &#160;* @ecccode:&#160;&#160;&#160;&#160;buffer for ECC read from flash
    </p>
    <p>
      &#160;* @databuf:&#160;&#160;&#160;&#160;buffer for data - dynamically sized
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* Do not change the order of buffers. databuf and oobrbuf must be in
    </p>
    <p>
      &#160;* consecutive order.
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      #define NAND_MAX_OOBSIZE&#160;&#160;&#160;&#160;&#160;640
    </p>
    <p>
      #define NAND_MAX_PAGESIZE&#160;&#160;&#160;&#160;8192
    </p>
    <p>
      struct nand_buffers {
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t&#160;ecccalc[NAND_MAX_OOBSIZE];
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t&#160;ecccode[NAND_MAX_OOBSIZE];
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t databuf[NAND_MAX_PAGESIZE + NAND_MAX_OOBSIZE];
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1523950996774" ID="ID_1157170827" MODIFIED="1524197066377">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static int __init jz_sfcnand_probe(struct platform_device *pdev)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;const char *jz_probe_types[] = {&quot;cmdlinepart&quot;,NULL};
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfc_info *board_info = pdev-&gt;dev.platform_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#244aee">struct sfc_flash</font>&#160;*flash;
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#0f3df0">struct nand_chip</font>&#160;*chip;
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#0d27ea">struct jz_sfcnand_flashinfo</font>&#160;*nand_info;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int32_t ret;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ef7d16">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#ef7d16">&#160;&#160;&#160;&#160;&#160;* &#30003;&#35831;&#20027;&#35201;&#32467;&#26500;&#30340;&#20869;&#23384;&#31354;&#38388; </font>
    </p>
    <p>
      <font color="#ef7d16">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash = kzalloc(sizeof(struct sfc_flash), GFP_KERNEL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!flash)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENOMEM;
    </p>
    <p>
      &#160;&#160;&#160;&#160;chip = kzalloc(sizeof(struct nand_chip), GFP_KERNEL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!chip) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(flash);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENOMEM;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;nand_info = kzalloc(sizeof(struct jz_sfcnand_flashinfo), GFP_KERNEL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(!nand_info) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(flash);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(chip);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENOMEM;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_JZ_SFC_FLASH_POWER_CTRL
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (board_info-&gt;flash_power_ctrl != NULL
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&amp;&amp; gpio_is_valid(board_info-&gt;flash_power_ctrl-&gt;power_pin)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = gpio_request(board_info-&gt;flash_power_ctrl-&gt;power_pin, &quot;flash-power&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (ret &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;Failed to request flash power pin: %d\n&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;board_info-&gt;flash_power_ctrl-&gt;power_pin);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;BUG();
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto free_base;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      #endif /* CONFIG_JZ_SFC_FLASH_POWER_CTRL */
    </p>
    <p>
      
    </p>
    <p>
      &#160;<font color="#eb7d10">&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#eb7d10">&#160;&#160;&#160;&#160;&#160;* &#35774;&#32622;&#35774;&#22791;&#23545;&#24212;&#30340;&#39537;&#21160;&#25968;&#25454;&#65292;&#22312;&#36866;&#24403;&#22320;&#26041;&#36890;&#36807;platform_get_drvdata() </font>
    </p>
    <p>
      <font color="#eb7d10">&#160;&#160;&#160;&#160;&#160;* &#33719;&#21462;&#21040;struct sfc_flash &#32467;&#26500;&#30340;&#39318;&#22320;&#22336; </font>
    </p>
    <p>
      <font color="#eb7d10">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;platform_set_drvdata(pdev, flash);
    </p>
    <p>
      
    </p>
    <p>
      <font color="#e1760a">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e1760a">&#160;&#160;&#160;&#160;&#160;* &#21021;&#22987;&#21270;struct sfc_flash </font>
    </p>
    <p>
      <font color="#e1760a">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;mutex_init(&amp;flash-&gt;lock);
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;dev = &amp;pdev-&gt;dev;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;flash_info = nand_info; /* &#35774;&#32622;&#25351;&#21521;&#32467;&#26500;jz_sfcnand_flashinfo */
    </p>
    <p>
      
    </p>
    <p>
      <font color="#e4750e">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e4750e">&#160;&#160;&#160;&#160;&#160;* sfc_res_init()&#20989;&#25968;&#30340;&#20316;&#29992;&#26377;&#65306; </font>
    </p>
    <p>
      <font color="#e4750e">&#160;&#160;&#160;&#160;&#160;* &#30003;&#35831;struct sfc&#32467;&#26500;&#20869;&#23384;&#31354;&#38388;&#24182;&#33719;&#21462;&#35774;&#22791;&#31471;&#27880;&#20876;&#30340;&#30828;&#20214;&#36164;&#28304; </font>
    </p>
    <p>
      <font color="#e4750e">&#160;&#160;&#160;&#160;&#160;* &#23436;&#25104;SFC&#25511;&#21046;&#22120;&#23492;&#23384;&#22120;&#22320;&#22336;&#26144;&#23556;&#65292;&#26102;&#38047;&#28304;&#33719;&#21462;&#12289;&#39057;&#29575;&#35774;&#32622;&#21450;&#20351;&#33021; </font>
    </p>
    <p>
      <font color="#e4750e">&#160;&#160;&#160;&#160;&#160;* SFC&#25511;&#21046;&#22120;&#20013;&#26029;&#30003;&#35831;&#65292;&#20851;&#32852;&#20013;&#26029;&#26381;&#21153;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#e4750e">&#160;&#160;&#160;&#160;&#160;* SFC&#25511;&#21046;&#22120;&#23492;&#23384;&#22120;&#21021;&#22987;&#21270; </font>
    </p>
    <p>
      <font color="#e4750e">&#160;&#160;&#160;&#160;&#160;* struct sfc&#32467;&#26500;&#20013;&#21508;&#20010;&#25104;&#21592;&#21021;&#22987;&#21270; </font>
    </p>
    <p>
      <font color="#e4750e">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;sfc = sfc_res_init(pdev);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(IS_ERR(flash-&gt;sfc)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;sfc control init error!\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = PTR_ERR(flash-&gt;sfc);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto free_base;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      #define THOLD&#160;&#160;&#160;&#160;&#160;&#160;5
    </p>
    <p>
      #define TSETUP&#160;&#160;&#160;&#160;&#160;5
    </p>
    <p>
      #define TSHSL_R&#160;&#160;&#160;&#160;20
    </p>
    <p>
      #define TSHSL_W&#160;&#160;&#160;&#160;50
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;set_flash_timing(flash-&gt;sfc, THOLD, TSETUP, TSHSL_R, TSHSL_W);
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ea7516">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#ea7516">&#160;&#160;&#160;&#160;&#160;* jz_sfc_nand_dev_init() &#35774;&#32622;nandflash&#30340;feature&#23492;&#23384;&#22120; </font>
    </p>
    <p>
      <font color="#ea7516">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if((ret = jz_sfc_nand_dev_init(flash))) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;nand device init failed!\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto free_base;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f27e0d">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f27e0d">&#160;&#160;&#160;&#160;&#160;* jz_sfc_nand_try_id() &#35835;&#21462;nandflash&#30340;id&#65292;&#24182;&#21435;&#21305;&#37197;&#24050;&#32463;&#27880;&#20876;nandflash&#65292; </font>
    </p>
    <p>
      <font color="#f27e0d">&#160;&#160;&#160;&#160;&#160;* &#22914;&#26524;&#27809;&#21305;&#37197;&#21040;&#65292;&#36825;&#20010;&#20989;&#25968;&#36820;&#22238;&#22833;&#36133;&#12290; </font>
    </p>
    <p>
      <font color="#f27e0d">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if((ret = jz_sfc_nand_try_id(flash))) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;try device id failed\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto free_base;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#e86b18">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e86b18">&#160;&#160;&#160;&#160;&#160;* &#33719;&#21462;&#21040;&#20855;&#20307;nandflash&#30340;&#22522;&#26412;&#21442;&#25968;&#21518;&#65292;&#37325;&#26032;&#35774;&#32622;timing </font>
    </p>
    <p>
      <font color="#e86b18">&#160;&#160;&#160;&#160;&#160;* &#21021;&#22987;&#21270;struct mtd_info&#21644;</font><font color="#f67515">struct nand_chip&#65292;&#21518;&#32773;&#23558;&#20445;&#23384;&#21040;&#21069;&#32773;&#30340;priv&#25104;&#21592;</font>
    </p>
    <p>
      <font color="#e86b18">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;set_flash_timing(flash-&gt;sfc, nand_info-&gt;param.tHOLD,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_info-&gt;param.tSETUP, nand_info-&gt;param.tSHSL_R, nand_info-&gt;param.tSHSL_W);
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.name = &quot;sfc_nand&quot;;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.owner = THIS_MODULE;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.type = MTD_NANDFLASH;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.flags |= MTD_CAP_NANDFLASH;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.erasesize = nand_info-&gt;param.blocksize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.writesize = nand_info-&gt;param.pagesize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.size = nand_info-&gt;param.flashsize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.oobsize = nand_info-&gt;param.oobsize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.writebufsize = flash-&gt;mtd.writesize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.bitflip_threshold = flash-&gt;mtd.ecc_strength = nand_info-&gt;param.ecc_max - 1;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;chip-&gt;select_chip = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;chip-&gt;badblockbits = 8;
    </p>
    <p>
      &#160;&#160;&#160;&#160;chip-&gt;scan_bbt = nand_default_bbt; /* &#25195;&#25551;nandflash&#22351;&#22359;&#24182;&#24314;&#31435;&#22351;&#22359;&#34920; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;chip-&gt;block_bad = jz_sfcnand_block_bad_check; /* &#26816;&#27979;&#26159;&#21542;&#26159;&#22351;&#22359; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;chip-&gt;block_markbad = jz_sfcnand_chip_block_markbad; /* &#26631;&#35760;&#22351;&#22359; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;//chip-&gt;ecc.layout= &amp;gd5f_ecc_layout_128; // for erase ops
    </p>
    <p>
      <font color="#f54e08">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f54e08">&#160;&#160;&#160;&#160;&#160;* ffs(x)&#36820;&#22238;x&#30340;&#20108;&#36827;&#21046;&#25968;&#20174;&#21491;&#36793;&#31532;&#19968;&#27425;&#20986;&#29616;1&#30340;&#20301;&#32622;&#65292;&#27604;&#22914;ffs(0x1)=1, ffs(0x810)=5 </font>
    </p>
    <p>
      <font color="#f54e08">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;chip-&gt;bbt_erase_shift = chip-&gt;phys_erase_shift = ffs(flash-&gt;mtd.erasesize) - 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;chip-&gt;buffers = kmalloc(sizeof(*chip-&gt;buffers), GFP_KERNEL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(!chip-&gt;buffers) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;alloc nand buffer failed\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = -ENOMEM;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto free_base;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* Set the bad block position */
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (flash-&gt;mtd.writesize &gt; 512 || (chip-&gt;options &amp; NAND_BUSWIDTH_16))
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;chip-&gt;badblockpos = NAND_LARGE_BADBLOCK_POS;
    </p>
    <p>
      &#160;&#160;&#160;&#160;else
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;chip-&gt;badblockpos = NAND_SMALL_BADBLOCK_POS;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd.priv = chip;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd._erase = jz_sfcnand_erase;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd._read = jz_sfcnand_read;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd._write = jz_sfcnand_write;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd._read_oob = jz_sfcnand_read_oob;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd._write_oob = jz_sfcnand_write_oob;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd._block_isbad = jz_sfcnand_block_isbab;
    </p>
    <p>
      &#160;&#160;&#160;&#160;flash-&gt;mtd._block_markbad = jz_sfcnand_block_markbad;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f4820b">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f4820b">&#160;&#160;&#160;&#160;&#160;* chip-&gt;scan_bbt()&#21363;&#35843;&#29992;nand_default_bbt()&#24314;&#31435;&#22351;&#22359;&#34920; </font>
    </p>
    <p>
      <font color="#f4820b">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if((ret = chip-&gt;scan_bbt(&amp;flash-&gt;mtd))) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;creat and scan bbt failed\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto free_all;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f37209">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f37209">&#160;&#160;&#160;&#160;&#160;* &#33719;&#21462;&#20998;&#21306;&#34920;&#65292;&#26377;&#20004;&#31181;&#36884;&#24452;&#65306; </font>
    </p>
    <p>
      <font color="#f37209">&#160;&#160;&#160;&#160;&#160;* &#36884;&#24452;&#19968;&#65306;&#20174;flash&#35835;&#20986;&#30001;&#28903;&#24405;&#24037;&#20855;&#28903;&#24405;&#21040;&#29305;&#23450;&#20301;&#32622;&#30340;&#20998;&#21306;&#20449;&#24687; </font>
    </p>
    <p>
      <font color="#f37209">&#160;&#160;&#160;&#160;&#160;* &#36884;&#24452;&#20108;&#65306;&#20351;&#29992;sfc_bus.c&#20013;&#35774;&#32622;&#30340;&#20998;&#21306;&#34920;&#160; </font>
    </p>
    <p>
      <font color="#f37209">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if((ret = jz_sfcnand_partition(flash, board_info))) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if(ret == -EINVAL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;read flash partition failed!\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto free_all;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      /*&#160;&#160;&#160;&#160;dump_flash_info(flash);*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;ret = mtd_device_parse_register(&amp;flash-&gt;mtd, jz_probe_types, NULL, nand_info-&gt;partition.partition, nand_info-&gt;partition.num_partition);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ret) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(nand_info-&gt;partition.partition);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if(!board_info-&gt;use_board_info) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(burn_param-&gt;partition);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(burn_param);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = -ENODEV;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto free_all;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      
    </p>
    <p>
      free_all:
    </p>
    <p>
      &#160;&#160;&#160;&#160;kfree(chip-&gt;buffers);
    </p>
    <p>
      
    </p>
    <p>
      free_base:
    </p>
    <p>
      &#160;&#160;&#160;&#160;kfree(flash);
    </p>
    <p>
      &#160;&#160;&#160;&#160;kfree(chip);
    </p>
    <p>
      &#160;&#160;&#160;&#160;kfree(nand_info);
    </p>
    <p>
      &#160;&#160;&#160;&#160;return ret;
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1523962203016" ID="ID_1711783332" MODIFIED="1524035484338">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static int32_t __init jz_sfc_nand_try_id(struct sfc_flash *flash)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfcnand_flashinfo *nand_info = flash-&gt;flash_info;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfcnand_device *nand_device;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct sfc_transfer transfer;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t addr_len[] = {0, 1};
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t id_buf[2] = {0};
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t i = 0;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ee8b07">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#ee8b07">&#160;&#160;&#160;&#160;&#160;* &#27599;&#27425;&#20256;&#36755;&#21160;&#20316;&#38656;&#35201;&#21021;&#22987;&#21270;&#19968;&#20010;struct sfc_transfer&#65292;&#21253;&#21547;&#65306; </font>
    </p>
    <p>
      <font color="#ee8b07">&#160;&#160;&#160;&#160;&#160;* SFC&#27169;&#24335;&#65306;&#26631;&#20934;SPI&#25110;QUAD </font>
    </p>
    <p>
      <font color="#ee8b07">&#160;&#160;&#160;&#160;&#160;* &#20256;&#36755;&#30340;&#25351;&#20196;&#21450;&#25351;&#20196;&#38468;&#24102;&#20449;&#24687;&#65292;&#22914;&#65306;&#26159;&#21542;&#26377;&#25968;&#25454;&#65292;&#23553;&#35013;&#22312;transfer.cmd_info&#20013; </font>
    </p>
    <p>
      <font color="#ee8b07">&#160;&#160;&#160;&#160;&#160;* &#25805;&#20316;&#21040;nandflash&#21738;&#20010;&#22320;&#22336;&#21450;&#22320;&#22336;&#38271;&#24230;&#65292;&#22320;&#22336;&#36319;&#25968;&#25454;&#38388;&#30340;dummy_bits </font>
    </p>
    <p>
      <font color="#ee8b07">&#160;&#160;&#160;&#160;&#160;* &#23384;&#20648;&#25968;&#25454;&#30340;&#22320;&#22336;&#21450;&#25968;&#25454;&#30340;&#38271;&#24230; </font>
    </p>
    <p>
      <font color="#ee8b07">&#160;&#160;&#160;&#160;&#160;* &#20256;&#36755;&#26041;&#21521;&#65306;&#35835;&#25110;&#20889; </font>
    </p>
    <p>
      <font color="#ee8b07">&#160;&#160;&#160;&#160;&#160;* &#26159;&#21542;&#21551;&#29992;DMA </font>
    </p>
    <p>
      <font color="#ee8b07">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;for(i = 0; i &lt; sizeof(addr_len); i++) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;memset(&amp;transfer, 0, sizeof(transfer));
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sfc_list_init(&amp;transfer);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;transfer.sfc_mode = TM_STD_SPI;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;transfer.cmd_info.cmd = SPINAND_CMD_RDID;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;transfer.addr = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;transfer.addr_len = addr_len[i];
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;transfer.cmd_info.dataen = ENABLE;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;transfer.data = id_buf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;transfer.len = sizeof(id_buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;transfer.direction = GLB_TRAN_DIR_READ;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;transfer.data_dummy_bits = 0;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;transfer.ops_mode = CPU_OPS;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#e97608">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e97608">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* sfc_sync(), &#26681;&#25454;transfer&#35774;&#32622;SFC&#25511;&#21046;&#22120;&#24182;&#24320;&#22987;&#20256;&#36755; </font>
    </p>
    <p>
      <font color="#e97608">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#36825;&#37324;&#26159;&#35835;&#21462;nandflash&#30340;id </font>
    </p>
    <p>
      <font color="#e97608">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if(sfc_sync(flash-&gt;sfc, &amp;transfer)){
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev,&quot;sfc_sync error ! %s %s %d\n&quot;,__FILE__,__func__,__LINE__);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -EIO;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#e98e0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e98e0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#36941;&#21382;nandflash&#25903;&#25345;&#21015;&#34920;&#65292;&#25214;&#21040;&#21305;&#37197;&#21378;&#21830;id&#30340;nandflash </font>
    </p>
    <p>
      <font color="#e98e0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#27880;&#65306;&#22312;drivers/mtd/devices/nand_device/&#19979;&#65292;&#25903;&#25345;&#30340; </font>
    </p>
    <p>
      <font color="#e98e0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* nandflash&#21015;&#34920;&#23601;&#26159;&#30001;&#36825;&#20010;&#30446;&#24405;&#19979;&#30340;&#21508;&#20010;.c&#25991;&#20214;&#28155;&#21152;&#30340; </font>
    </p>
    <p>
      <font color="#e98e0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;list_for_each_entry(nand_device, &amp;nand_list, list) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if(nand_device-&gt;id_manufactory == id_buf[0]) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_info-&gt;id_manufactory = id_buf[0]; //&#20445;&#23384;&#35835;&#21462;&#21040;&#30340;&#21378;&#21830;id
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_info-&gt;id_device = id_buf[1];&#160;&#160;&#160;&#160;&#160;&#160;//&#20445;&#23384;&#35835;&#21462;&#21040;&#30340;&#35774;&#22791;id
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if(nand_info-&gt;id_manufactory &amp;&amp; nand_info-&gt;id_device)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(!nand_info-&gt;id_manufactory &amp;&amp; !nand_info-&gt;id_device) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot; ERROR!: don`t support this nand manufactory, please add nand driver\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENODEV;
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      <font color="#e6810d">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e6810d">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#21069;&#38754;&#21305;&#37197;&#21040;&#21378;&#21830;id&#65292;&#19968;&#20010;&#21378;&#21830;&#30340;&#25152;&#26377;nandflash&#30340;&#21378;&#21830;id&#26159;&#19968;&#26679;&#30340;&#65292; </font>
    </p>
    <p>
      <font color="#e6810d">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#39537;&#21160;&#20013;&#21487;&#33021;&#25903;&#25345;&#36825;&#20010;&#21378;&#21830;&#22810;&#20010;nandflash&#65292;&#36941;&#21382;&#21378;&#21830;nandflash&#25903;&#25345;&#21015;&#34920;&#65292; </font>
    </p>
    <p>
      <font color="#e6810d">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#21305;&#37197;&#35774;&#22791;id&#65292;&#27809;&#21305;&#37197;&#21040;&#21017;&#39537;&#21160;&#36824;&#19981;&#25903;&#25345;&#36825;&#20010;nandflash </font>
    </p>
    <p>
      <font color="#e6810d">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;<font color="#142eec">struct device_id_struct</font>&#160; *device_id = nand_device-&gt;id_device_list;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;int32_t id_count = nand_device-&gt;id_device_count; /* &#25903;&#25345;&#36825;&#20010;&#22330;&#25152;nandflash&#30340;&#20010;&#25968; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;while(id_count--) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if(device_id-&gt;id_device == nand_info-&gt;id_device) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/*notice :base_param and partition param should read from nand*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_info-&gt;param = *device_id-&gt;param; /* &#20445;&#23384;nandflash&#30340;&#22522;&#26412;&#21442;&#25968; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;device_id++;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if(id_count &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;ERROR: do support this device, id_manufactory = 0x%02x, id_device = 0x%02x\n&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_info-&gt;id_manufactory, nand_info-&gt;id_device);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENODEV;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f5570d">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f5570d">&#160;&#160;&#160;&#160;&#160;* &#30001;&#20110;&#19981;&#21516;&#21378;&#21830;&#30340;nandflash&#26576;&#20123;&#25805;&#20316;&#65288;&#27604;&#22914;&#65306;&#35835;&#20889;&#65289;&#30456;&#20114;&#30452;&#25509;&#26377;&#24046;&#24322;&#65292;&#36825;&#26679;&#23601;&#38656;&#35201;&#33258;&#24049;&#30340;&#25805;&#20316;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#f5570d">&#160;&#160;&#160;&#160;&#160;* jz_sfcnand_fill_ops()&#20989;&#25968;&#21028;&#35835;&#36825;&#20010;nandflash&#26159;&#21542;&#23454;&#29616;&#20102;&#29305;&#23450;&#30340;&#25805;&#20316;&#20989;&#25968;&#65292;&#22914;&#26524;&#26377;&#65292;&#36825;&#20351;&#29992;&#29305;&#23450; </font>
    </p>
    <p>
      <font color="#f5570d">&#160;&#160;&#160;&#160;&#160;* &#30340;&#20989;&#25968;&#21435;&#22635;&#20805;struct sfc_flash&#20013;flash_info&#25351;&#21521;&#30340;struct jz_sfcnand_flashinfo&#32467;&#26500;&#20013;&#30340;ops&#65292; </font>
    </p>
    <p>
      <font color="#f5570d">&#160;&#160;&#160;&#160;&#160;* &#21542;&#21017;&#20351;&#29992;&#40664;&#35748;&#30340;&#25805;&#20316;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#f5570d">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;return jz_sfcnand_fill_ops(flash, &amp;nand_device-&gt;ops);
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1524039659916" ID="ID_295462030" MODIFIED="1524192263607">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int nand_default_bbt(struct mtd_info *mtd)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_chip *this = mtd-&gt;priv;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* Is a flash based bad block table requested? */
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (this-&gt;bbt_options &amp; NAND_BBT_USE_FLASH) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* Use the default pattern descriptors */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (!this-&gt;bbt_td) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (this-&gt;bbt_options &amp; NAND_BBT_NO_OOB) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;this-&gt;bbt_td = &amp;bbt_main_no_oob_descr;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;this-&gt;bbt_md = &amp;bbt_mirror_no_oob_descr;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;this-&gt;bbt_td = &amp;bbt_main_descr;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;this-&gt;bbt_md = &amp;bbt_mirror_descr;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;this-&gt;bbt_td = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;this-&gt;bbt_md = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!this-&gt;badblock_pattern)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_create_badblock_pattern(this); /* &#28155;&#21152;&#22351;&#22359;&#34920;&#25551;&#36848;&#32467;&#26500;&#24182;&#21021;&#22987;&#21270; */
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return nand_scan_bbt(mtd, this-&gt;badblock_pattern); /* &#24320;&#22987;&#25195;&#25551;&#22351;&#22359; */
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1524042552720" ID="ID_974442967" MODIFIED="1524106966255">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* nand_create_badblock_pattern - [INTERN] Creates a BBT descriptor structure
    </p>
    <p>
      &#160;* @this: NAND chip to create descriptor for
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* This function allocates and initializes a nand_bbt_descr for BBM detection
    </p>
    <p>
      &#160;* based on the properties of @this. The new descriptor is stored in
    </p>
    <p>
      &#160;* this-&gt;badblock_pattern. Thus, this-&gt;badblock_pattern should be NULL when
    </p>
    <p>
      &#160;* passed to this function.
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      static int nand_create_badblock_pattern(struct nand_chip *this)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_bbt_descr *bd;
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (this-&gt;badblock_pattern) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pr_warn(&quot;Bad block pattern already allocated; not replacing\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -EINVAL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;bd = kzalloc(sizeof(*bd), GFP_KERNEL); /* &#32473;struct nand_bbt_descr&#20998;&#37197;&#20869;&#23384; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!bd)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENOMEM;
    </p>
    <p>
      &#160;&#160;&#160;&#160;bd-&gt;options = this-&gt;bbt_options &amp; BADBLOCK_SCAN_MASK; /* this-&gt;bbt_options=0&#65292;&#25925;bd-&gt;options=0&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;bd-&gt;offs = this-&gt;badblockpos; /* &#22823;&#39029;bd-&gt;offs=0&#65292;&#23567;&#39029;bd-&gt;offs=5 */
    </p>
    <p>
      &#160;&#160;&#160;&#160;bd-&gt;len = (this-&gt;options &amp; NAND_BUSWIDTH_16) ? 2 : 1; /* this-&gt;options=0&#65292;&#25925;bd-&gt;len=1 */
    </p>
    <p>
      &#160;&#160;&#160;&#160;bd-&gt;pattern = scan_ff_pattern;
    </p>
    <p>
      &#160;&#160;&#160;&#160;bd-&gt;options |= NAND_BBT_DYNAMICSTRUCT; /* bd-&gt;options=0x80000000 */
    </p>
    <p>
      &#160;&#160;&#160;&#160;this-&gt;badblock_pattern = bd; /* &#20445;&#23384;&#21040;nand_chip-&gt;badblock_pattern */
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1524042560152" ID="ID_1287810336" MODIFIED="1524488448638">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* nand_scan_bbt - [NAND Interface] scan, find, read and maybe create bad block table(s)
    </p>
    <p>
      &#160;* @mtd: MTD device structure
    </p>
    <p>
      &#160;* @bd: descriptor for the good/bad block search pattern
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* The function checks, if a bad block table(s) is/are already available. If
    </p>
    <p>
      &#160;* not it scans the device for manufacturer marked good / bad blocks and writes
    </p>
    <p>
      &#160;* the bad block table(s) to the selected place.
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* The bad block table memory is allocated here. It must be freed by calling
    </p>
    <p>
      &#160;* the nand_free_bbt function.
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      int nand_scan_bbt(struct mtd_info *mtd, struct nand_bbt_descr *bd)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_chip *this = mtd-&gt;priv;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int len, res = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t *buf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_bbt_descr *td = this-&gt;bbt_td; /* this-&gt;bbt_td=NULL */
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_bbt_descr *md = this-&gt;bbt_md; /* this-&gt;bbt_md=NULL */
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f0860a">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f0860a">&#160;&#160;&#160;&#160;&#160;* mtd-&gt;size &gt;&gt; this-&gt;mtd-&gt;size=nandflash&#22359;&#25968;&#65292;&#20877;&gt;&gt;2&#30456;&#24403;&#20110;&#38500;&#20197;4&#65292; </font>
    </p>
    <p>
      <font color="#f0860a">&#160;&#160;&#160;&#160;&#160;* &#25509;&#30528;&#20998;&#37197;&#36825;&#20040;&#22810;&#23383;&#33410;&#30340;&#20869;&#23384;&#29992;&#20110;&#20570;&#22351;&#22359;&#34920;&#65292;&#21363;&#27599;&#22359;&#26377;2bit&#34920;&#31034; </font>
    </p>
    <p>
      <font color="#f0860a">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;len = mtd-&gt;size &gt;&gt; (this-&gt;mtd-&gt;size + 2);
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* Allocate memory (2bit per block) and clear the memory bad block
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* table.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;this-&gt;bbt = kzalloc(len, GFP_KERNEL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!this-&gt;bbt)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENOMEM;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* If no primary table decriptor is given, scan the device to build a
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* memory based bad block table.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!td) {
    </p>
    <p>
      <font color="#f96c19">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f96c19">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* nand_memory_bbt()&#20989;&#25968;&#21442;&#25968;&#65306; </font>
    </p>
    <p>
      <font color="#f96c19">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* @mtd: &#22312;probe&#20989;&#25968;&#20013;&#21019;&#24314;&#65292;&#36825;&#20010;&#32467;&#26500;&#21253;&#21547;&#22312;struct sfc_flash&#32467;&#26500;&#20013; </font>
    </p>
    <p>
      <font color="#f96c19">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* @bd: &#26159;nand_chip-&gt;badblock_pattern&#65292;&#22312;nand_create_badblock_pattern()&#20013;&#21019;&#24314; </font>
    </p>
    <p>
      <font color="#f96c19">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if ((res = <font color="#143def">nand_memory_bbt</font>(mtd, bd))) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pr_err(&quot;nand_bbt: can't scan flash and build the RAM-based BBT\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(this-&gt;bbt);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;this-&gt;bbt = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return res; <font color="#de0c0c">/* &#25191;&#34892;&#21040;&#36825;&#37324;&#65292;&#20989;&#25968;&#36820;&#22238; */</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;verify_bbt_descr(mtd, td);
    </p>
    <p>
      &#160;&#160;&#160;&#160;verify_bbt_descr(mtd, md);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* Allocate a temporary buffer for one eraseblock incl. oob */
    </p>
    <p>
      &#160;&#160;&#160;&#160;len = (1 &lt;&lt; this-&gt;bbt_erase_shift);
    </p>
    <p>
      &#160;&#160;&#160;&#160;len += (len &gt;&gt; this-&gt;page_shift) * mtd-&gt;oobsize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;buf = vmalloc(len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!buf) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(this-&gt;bbt);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;this-&gt;bbt = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENOMEM;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* Is the bbt at a given page? */
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (td-&gt;options &amp; NAND_BBT_ABSPAGE) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;read_abs_bbts(mtd, buf, td, md);
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* Search the bad block table using a pattern in oob */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;search_read_bbts(mtd, buf, td, md);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;res = check_create(mtd, buf, bd);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* Prevent the bbt regions from erasing / writing */
    </p>
    <p>
      &#160;&#160;&#160;&#160;mark_bbt_region(mtd, td);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (md)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;mark_bbt_region(mtd, md);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;vfree(buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;return res;
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1524107964488" ID="ID_657073464" MODIFIED="1524108849513">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* nand_memory_bbt - [GENERIC] create a memory based bad block table
    </p>
    <p>
      &#160;* @mtd: MTD device structure
    </p>
    <p>
      &#160;* @bd: descriptor for the good/bad block search pattern
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* The function creates a memory based bbt by scanning the device for
    </p>
    <p>
      &#160;* manufacturer / software marked good / bad blocks.
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      static inline int nand_memory_bbt(struct mtd_info *mtd, struct nand_bbt_descr *bd)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_chip *this = mtd-&gt;priv;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;bd-&gt;options &amp;= ~NAND_BBT_SCANEMPTY; /* &#28165;&#26970;bd-&gt;options&#20013;&#30340;NAND_BBT_SCANEMPTY&#20301; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;return <font color="#182fea">create_bbt</font>(mtd, this-&gt;buffers-&gt;databuf, bd, -1); /* &#24314;&#31435;&#22351;&#22359;&#34920; */
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1524108898001" ID="ID_1793277959" MODIFIED="1524128707371">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* create_bbt - [GENERIC] Create a bad block table by scanning the device
    </p>
    <p>
      &#160;* @mtd: MTD device structure
    </p>
    <p>
      &#160;* @buf: temporary buffer
    </p>
    <p>
      &#160;* @bd: descriptor for the good/bad block search pattern
    </p>
    <p>
      &#160;* @chip: create the table for a specific chip, -1 read all chips; applies only
    </p>
    <p>
      &#160;*&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if NAND_BBT_PERCHIP option is set
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* Create a bad block table by scanning the device for the given good/bad block
    </p>
    <p>
      &#160;* identify pattern.
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      static int create_bbt(struct mtd_info *mtd, uint8_t *buf,
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_bbt_descr *bd, int chip)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct nand_chip *this = mtd-&gt;priv;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int i, numblocks, numpages, scanlen;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int startblock;
    </p>
    <p>
      &#160;&#160;&#160;&#160;loff_t from;
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t readlen;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;pr_info(&quot;Scanning device for bad blocks\n&quot;);
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f56a0e">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f56a0e">&#160;&#160;&#160;&#160;&#160;* &#36825;&#37324;&#30830;&#23450;&#21028;&#26029;nandflash&#22359;&#26159;&#21542;&#26159;&#22351;&#22359;&#30340;&#26041;&#24335;&#65306; </font>
    </p>
    <p>
      <font color="#f56a0e">&#160;&#160;&#160;&#160;&#160;* &#31532;&#19968;&#31181;&#65306;&#38656;&#35201;&#25195;&#25551;&#36825;&#20010;&#22359;&#30340;&#25152;&#26377;&#39029; </font>
    </p>
    <p>
      <font color="#f56a0e">&#160;&#160;&#160;&#160;&#160;* &#31532;&#20108;&#31181;&#65306;&#38656;&#35201;&#25195;&#25551;&#36825;&#20010;&#22359;&#30340;&#20004;&#20010;&#39029; </font>
    </p>
    <p>
      <font color="#f56a0e">&#160;&#160;&#160;&#160;&#160;* &#31532;&#19977;&#31181;&#65306;&#21482;&#38656;&#25195;&#25551;&#36825;&#20010;&#22359;&#30340;&#19968;&#20010;&#39029; </font>
    </p>
    <p>
      <font color="#f56a0e">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (bd-&gt;options &amp; NAND_BBT_SCANALLPAGES)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;numpages = 1 &lt;&lt; (this-&gt;bbt_erase_shift - this-&gt;page_shift);
    </p>
    <p>
      &#160;&#160;&#160;&#160;else if (bd-&gt;options &amp; NAND_BBT_SCAN2NDPAGE)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;numpages = 2;
    </p>
    <p>
      &#160;&#160;&#160;&#160;else
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;numpages = 1;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!(bd-&gt;options &amp; NAND_BBT_SCANEMPTY)) { /* &#36825;&#20010;&#26465;&#20214;&#25104;&#31435; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* We need only read few bytes from the OOB area */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;scanlen = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;readlen = bd-&gt;len; /* bd-&gt;len=1 */
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* Full page content should be read */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;scanlen = mtd-&gt;writesize + mtd-&gt;oobsize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;readlen = numpages * mtd-&gt;writesize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (chip == -1) { /* &#36825;&#20010;&#26465;&#20214;&#25104;&#31435; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Note that numblocks is 2 * (real numblocks) here, see i+=2
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* below as it makes shifting and masking less painful
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;numblocks = mtd-&gt;size &gt;&gt; (this-&gt;bbt_erase_shift - 1);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;startblock = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;from = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (chip &gt;= this-&gt;numchips) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pr_warn(&quot;create_bbt(): chipnr (%d) &gt; available chips (%d)\n&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;chip + 1, this-&gt;numchips);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -EINVAL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;numblocks = this-&gt;chipsize &gt;&gt; (this-&gt;bbt_erase_shift - 1);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;startblock = chip * numblocks;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;numblocks += startblock;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;from = (loff_t)startblock &lt;&lt; (this-&gt;bbt_erase_shift - 1);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f77115">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f77115">&#160;&#160;&#160;&#160;&#160;* &#36825;&#37324;&#30830;&#23450;&#26159;&#20174;nandflash&#22359;&#30340;&#31532;&#19968;&#39029;&#25110;&#26368;&#21518;&#30340;&#39029;&#26469;&#21028;&#26029;&#26159;&#21542;&#26159;&#22351;&#22359; </font>
    </p>
    <p>
      <font color="#f77115">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (this-&gt;bbt_options &amp; NAND_BBT_SCANLASTPAGE) /* &#26465;&#20214;&#19981;&#25104;&#31435; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;from += mtd-&gt;erasesize - (mtd-&gt;writesize * numpages);
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ef6908">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#ef6908">&#160;&#160;&#160;&#160;&#160;* &#24490;&#29615;&#25195;&#25551;nandflash&#25152;&#26377;&#30340;&#22359; </font>
    </p>
    <p>
      <font color="#ef6908">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;for (i = startblock; i &lt; numblocks;) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;int ret;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;BUG_ON(bd-&gt;options &amp; NAND_BBT_NO_OOB);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (bd-&gt;options &amp; NAND_BBT_SCANALLPAGES) /* &#25195;&#25551;&#25152;&#26377;&#39029;&#65311;&#26465;&#20214;&#19981;&#25104;&#31435; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = scan_block_full(mtd, bd, from, buf, readlen,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;scanlen, numpages);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;else
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = <font color="#1434f0">scan_block_fast</font>(mtd, bd, from, buf, numpages);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (ret &lt; 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return ret;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#e96e0f">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e96e0f">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* ret &gt; 0&#65292;&#34920;&#26126;&#26159;&#22351;&#22359;&#65292;&#25226;nand_chip-&gt;bbt&#22351;&#22359;&#34920;&#20013;&#27492;&#22359; </font>
    </p>
    <p>
      <font color="#e96e0f">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#23545;&#24212;&#30340;2bit&#32622;1&#65292;&#26631;&#35760;&#20026;&#22351;&#22359; </font>
    </p>
    <p>
      <font color="#e96e0f">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (ret) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;this-&gt;bbt[i &gt;&gt; 3] |= 0x03 &lt;&lt; (i &amp; 0x6);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pr_warn(&quot;Bad eraseblock %d at 0x%012llx\n&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;i &gt;&gt; 1, (unsigned long long)from);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;mtd-&gt;ecc_stats.badblocks++; /* &#32479;&#35745;&#22351;&#22359;&#25968;&#37327; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;<font color="#db1010">i += 2;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;from += (1 &lt;&lt; this-&gt;bbt_erase_shift); /*&#160;&#19979;&#19968;&#22359;&#30340;&#29992;&#20110;&#21028;&#26029;&#26159;&#21542;&#26159;&#22351;&#22359;&#30340;&#39029;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1524111091874" ID="ID_1538145816" MODIFIED="1524129850670">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /* Scan a given block partially */
    </p>
    <p>
      static int scan_block_fast(struct mtd_info *mtd, struct nand_bbt_descr *bd,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;loff_t offs, uint8_t *buf, int numpages)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct mtd_oob_ops ops;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int j, ret;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f97d0f">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f97d0f">&#160;&#160;&#160;&#160;&#160;* &#21021;&#22987;&#21270;&#19968;&#20010;obb&#25805;&#20316;&#23545;&#35937;&#65292;mtd_read_oob()&#23558;&#26681;&#25454;&#36825;&#20010;&#26469;&#25805;&#20316;oob </font>
    </p>
    <p>
      <font color="#f97d0f">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;ops.ooblen = mtd-&gt;oobsize;
    </p>
    <p>
      &#160;&#160;&#160;&#160;ops.oobbuf = buf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;ops.ooboffs = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;ops.datbuf = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;ops.mode = MTD_OPS_PLACE_OOB;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;for (j = 0; j &lt; numpages; j++) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Read the full oob until read_oob is fixed to handle single
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* byte reads for 16 bit buswidth.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = <font color="#0923f8">mtd_read_oob</font>(mtd, offs, &amp;ops); /* &#35835;oob */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* Ignore ECC errors when checking for BBM */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (ret &amp;&amp; !mtd_is_bitflip_or_eccerr(ret))
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return ret;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ea7516">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#ea7516">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* mtd_read_oob()&#35835;&#21040;&#30340;oob&#25968;&#25454;&#23384;&#22312;buf&#20013;&#65292; </font>
    </p>
    <p>
      <font color="#ea7516">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#22312;check_short_pattern()&#36890;&#36807;&#27604;&#36739;buf&#30340;&#31532;bd-&gt;offs&#23383;&#33410; </font>
    </p>
    <p>
      <font color="#ea7516">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#36215;bd-&gt;len&#20010;&#23383;&#33410;&#26159;&#21542;&#31561;&#20110;bd-&gt;pattern&#65292;&#19981;&#31561;&#21017;&#26159;&#22351;&#22359; </font>
    </p>
    <p>
      <font color="#ea7516">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (<font color="#0f36ef">check_short_pattern</font>(buf, bd))
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return 1;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;offs += mtd-&gt;writesize; /* &#36339;&#36807;&#19968;&#20010;&#39029;&#22823;&#23567;&#65292;&#21363;&#19979;&#20010;&#39029;&#30340;oob */
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1523951050318" ID="ID_312126788" MODIFIED="1524111399630">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* struct mtd_oob_ops - oob operation operands
    </p>
    <p>
      &#160;* @mode:&#160;&#160;&#160;&#160;operation mode
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* @len:&#160;&#160;&#160;&#160;number of data bytes to write/read
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* @retlen:&#160;&#160;&#160;&#160;number of data bytes written/read
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* @ooblen:&#160;&#160;&#160;&#160;number of oob bytes to write/read
    </p>
    <p>
      &#160;* @oobretlen:&#160;&#160;&#160;&#160;number of oob bytes written/read
    </p>
    <p>
      &#160;* @ooboffs:&#160;&#160;&#160;&#160;offset of oob data in the oob area (only relevant when
    </p>
    <p>
      &#160;*&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;mode = MTD_OPS_PLACE_OOB or MTD_OPS_RAW)
    </p>
    <p>
      &#160;* @datbuf:&#160;&#160;&#160;&#160;data buffer - if NULL only oob data are read/written
    </p>
    <p>
      &#160;* @oobbuf:&#160;&#160;&#160;&#160;oob data buffer
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* Note, it is allowed to read more than one OOB area at one go, but not write.
    </p>
    <p>
      &#160;* The interface assumes that the OOB write requests program only one page's
    </p>
    <p>
      &#160;* OOB area.
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      struct mtd_oob_ops {
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int&#160;&#160;&#160;&#160;mode;
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;len;
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;retlen;
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ooblen;
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;oobretlen;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t&#160;&#160;&#160;&#160;&#160;&#160;ooboffs;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t&#160;&#160;&#160;&#160;&#160;&#160;&#160;*datbuf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint8_t&#160;&#160;&#160;&#160;&#160;&#160;&#160;*oobbuf;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1524111511267" ID="ID_103524349" MODIFIED="1524488466636">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int mtd_read_oob(struct mtd_info *mtd, loff_t from, struct mtd_oob_ops *ops)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int ret_code;
    </p>
    <p>
      &#160;&#160;&#160;&#160;ops-&gt;retlen = ops-&gt;oobretlen = 0;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#f8731b">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#f8731b">&#160;&#160;&#160;&#160;&#160;* mtd-&gt;_read_oob&#22312;probe&#20989;&#25968;&#20013;&#35774;&#32622;&#20026;jz_sfcnand_read_oob() </font>
    </p>
    <p>
      <font color="#f8731b">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!mtd-&gt;<font color="#0620f5">_read_oob</font>)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -EOPNOTSUPP;
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* In cases where ops-&gt;datbuf != NULL, mtd-&gt;_read_oob() has semantics
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* similar to mtd-&gt;_read(), returning a non-negative integer
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* representing max bitflips. In other cases, mtd-&gt;_read_oob() may
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* return -EUCLEAN. In all cases, perform similar logic to mtd_read().
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;ret_code = mtd-&gt;<font color="#0b33f1">_read_oob</font>(mtd, from, ops); /* &#30456;&#24403;&#20110;&#35843;&#29992; <font color="#f8731b">jz_sfcnand_read_oob() </font>*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (unlikely(ret_code &lt; 0))
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return ret_code;
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (mtd-&gt;ecc_strength == 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return 0;&#160;&#160;&#160;&#160;/* device lacks ecc */
    </p>
    <p>
      &#160;&#160;&#160;&#160;return ret_code &gt;= mtd-&gt;bitflip_threshold ? -EUCLEAN : 0;
    </p>
    <p>
      }
    </p>
    <p>
      EXPORT_SYMBOL_GPL(mtd_read_oob);
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1524111564138" ID="ID_565740109" MODIFIED="1524111569667">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* check_short_pattern - [GENERIC] check if a pattern is in the buffer
    </p>
    <p>
      &#160;* @buf: the buffer to search
    </p>
    <p>
      &#160;* @td:&#160;&#160;&#160;&#160;search pattern descriptor
    </p>
    <p>
      &#160;*
    </p>
    <p>
      &#160;* Check for a pattern at the given place. Used to search bad block tables and
    </p>
    <p>
      &#160;* good / bad block identifiers. Same as check_pattern, but no optional empty
    </p>
    <p>
      &#160;* check.
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      static int check_short_pattern(uint8_t *buf, struct nand_bbt_descr *td)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* Compare the pattern */
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (memcmp(buf + td-&gt;offs, td-&gt;pattern, td-&gt;len))
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
</node>
<node CREATED="1524130614214" ID="ID_456940469" MODIFIED="1524130876654">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static int32_t __init jz_sfcnand_partition(struct sfc_flash *flash, struct jz_sfc_info *board_info) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int32_t ret = 0;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ec7f16">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#ec7f16">&#160;&#160;&#160;&#160;&#160;* &#22312;&#26495;&#32423;sfc_bus.c&#20013;&#65292;use_board_info=0&#65292;&#21363;&#40664;&#35748;&#20174;flash&#33719;&#21462;&#20998;&#21306; </font>
    </p>
    <p>
      <font color="#ec7f16">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(!board_info-&gt;use_board_info) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if((ret = flash_part_from_chip(flash))) /* &#20174;flash&#33719;&#21462;&#20998;&#21306; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;read partition from flash failed!\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if((ret = flash_part_from_board(flash, board_info)))
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;copy partition from board failed!\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;return ret;
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1524131551543" ID="ID_1873027681" MODIFIED="1524131687161">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct jz_sfcnand_burner_param {
    </p>
    <p>
      &#160;&#160;&#160;&#160;uint32_t magic_num;&#160;&#160;&#160;&#160;/* &#29992;&#20110;&#30830;&#35748;&#25968;&#25454;&#30340;&#39764;&#25968; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;int32_t partition_num; /* &#20998;&#21306;&#20010;&#25968; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfcnand_partition *partition; /* &#20998;&#21306;&#36215;&#22987;&#22320;&#22336;&#160; */
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1524130987439" ID="ID_1852824382" MODIFIED="1524138927931">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static struct jz_sfcnand_burner_param *burn_param;
    </p>
    <p>
      static int32_t __init flash_part_from_chip(struct sfc_flash *flash) {
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;int32_t ret = 0, retlen = 0, count = 5;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;burn_param = kzalloc(sizeof(struct jz_sfcnand_burner_param), GFP_KERNEL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(!burn_param) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;alloc burn_param space error!\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENOMEM;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;count = 5; /* &#22914;&#26524;&#35835;&#21462;&#22833;&#36133;&#65292;&#23581;&#35797;5&#27425; */
    </p>
    <p>
      
    </p>
    <p>
      param_retry_read:
    </p>
    <p>
      <font color="#fc7d17">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#fc7d17">&#160;&#160;&#160;&#160;&#160;* &#20174;0x3c00&#20301;&#32622;&#35835;&#21462;sizeof(struct jz_sfcnand_burner_param)&#38271;&#24230;&#30340;&#25968;&#25454;&#65292; </font>
    </p>
    <p>
      <font color="#fc7d17">&#160;&#160;&#160;&#160;&#160;* &#28982;&#21518;&#36890;&#36807;burn_param-&gt;magic_num&#21028;&#26029;&#25968;&#25454;&#26159;&#21542;&#27491;&#30830;&#30340;&#65292;&#36825;&#20010;&#32467;&#26500;&#25968;&#25454;&#30456;&#24403; </font>
    </p>
    <p>
      <font color="#fc7d17">&#160;&#160;&#160;&#160;&#160;* &#20110;&#20998;&#21306;&#20449;&#24687;&#30340;&#22836;&#37096; </font>
    </p>
    <p>
      <font color="#fc7d17">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;ret = jz_sfcnand_read(&amp;flash-&gt;mtd, SPIFLASH_PARAMER_OFFSET,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sizeof(struct jz_sfcnand_burner_param), &amp;retlen, (u_char *)burn_param);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if((ret &lt; 0) &amp;&amp; count--)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto param_retry_read;
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(count &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;read nand base param failed!\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = -EIO;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto failed;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(burn_param-&gt;magic_num != SPINAND_MAGIC_NUM) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_info(flash-&gt;dev, &quot;NOTICE: this flash haven`t param\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = -EINVAL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto failed;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#fc7d17">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#fc7d17">&#160;&#160;&#160;&#160;&#160;* &#22797;&#21046;&#20986;&#19968;&#20221;&#20998;&#21306;&#20449;&#24687;&#65292;&#20445;&#23384;&#21040;&#39537;&#21160;&#20013;&#160; &#160;</font>
    </p>
    <p>
      <font color="#fc7d17">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(<font color="#1737e5">nand_partition_param_copy</font>(flash, burn_param)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = -ENOMEM;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto failed;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      failed:
    </p>
    <p>
      &#160;&#160;&#160;&#160;kfree(burn_param);
    </p>
    <p>
      &#160;&#160;&#160;&#160;return ret;
    </p>
    <p>
      
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1524132000619" ID="ID_1358604316" MODIFIED="1524132006164">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static int32_t __init nand_partition_param_copy(struct sfc_flash *flash, struct jz_sfcnand_burner_param *burn_param) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct jz_sfcnand_flashinfo *nand_info = flash-&gt;flash_info;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int i = 0, count = 5, ret;
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t retlen = 0;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*partition param copy*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;nand_info-&gt;partition.num_partition = burn_param-&gt;partition_num;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;burn_param-&gt;partition = kzalloc(nand_info-&gt;partition.num_partition * sizeof(struct jz_sfcnand_partition), GFP_KERNEL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!burn_param-&gt;partition) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;alloc partition space failed!\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENOMEM;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;nand_info-&gt;partition.partition = kzalloc(nand_info-&gt;partition.num_partition * sizeof(struct mtd_partition), GFP_KERNEL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!nand_info-&gt;partition.partition) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;alloc partition space failed!\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(burn_param-&gt;partition);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -ENOMEM;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      partition_retry_read:
    </p>
    <p>
      &#160;&#160;&#160;&#160;ret = jz_sfcnand_read(&amp;flash-&gt;mtd, SPIFLASH_PARAMER_OFFSET + sizeof(*burn_param) - sizeof(burn_param-&gt;partition),
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_info-&gt;partition.num_partition * sizeof(struct jz_sfcnand_partition),
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&amp;retlen, (u_char *)burn_param-&gt;partition);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if((ret &lt; 0) &amp;&amp; count--)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto partition_retry_read;
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(count &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dev_err(flash-&gt;dev, &quot;read nand partition failed!\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(burn_param-&gt;partition);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;kfree(nand_info-&gt;partition.partition);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -EIO;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;for(i = 0; i &lt; burn_param-&gt;partition_num; i++) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_info-&gt;partition.partition[i].name = burn_param-&gt;partition[i].name;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_info-&gt;partition.partition[i].size = burn_param-&gt;partition[i].size;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_info-&gt;partition.partition[i].offset = burn_param-&gt;partition[i].offset;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;nand_info-&gt;partition.partition[i].mask_flags = burn_param-&gt;partition[i].mask_flags;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
</node>
<node CREATED="1523950997150" ID="ID_1742822315" MODIFIED="1523950997150" TEXT=""/>
<node CREATED="1523950997806" ID="ID_403506633" MODIFIED="1523950997806" TEXT=""/>
</node>
<node CREATED="1523947324693" ID="ID_905706982" MODIFIED="1523947324693" TEXT=""/>
<node CREATED="1523947325437" ID="ID_751271712" MODIFIED="1523947325437" TEXT=""/>
</node>
<node CREATED="1523947295397" ID="ID_465254449" MODIFIED="1523947311447" TEXT="norflash"/>
</node>
<node CREATED="1523938175262" ID="ID_1715528701" MODIFIED="1523938175262" POSITION="right" TEXT=""/>
</node>
</map>
