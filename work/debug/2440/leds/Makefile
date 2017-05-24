ifneq ($(KERNELRELEASE),)
	obj-m := leds_drv.o

else
#	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	KERNELDIR ?= ~/micro2440/linux/linux-2.6.32.2
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	rm -rf *.o *.mod.c *.order *.symvers .*.cmd .tmp*
clean:
	rm -f *.o *~ *.ko  *.mod.c *.mod.o *.symvers *.order
endif

mod:
	sudo insmod ./leds_dev.ko

mt:
	gcc -o test test_leds.c

.PHONY:clc
clc:
	rm test


