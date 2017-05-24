ifneq ($(KERNELRELEASE),)
	obj-m := keys_drv.o

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
	sudo insmod ./keys_drv.ko
CC := arm-linux-gcc
mt:
	$(CC) -o test test_buttons.c

.PHONY:clc
clc:
	rm test


