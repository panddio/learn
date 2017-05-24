ifneq ($(KERNELRELEASE),)
	obj-m := sync_drv.o

else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
#	KERNELDIR ?= /work/linux/linux-2.6.32.2
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	rm -rf *.o *.mod.c *.order *.symvers .*.cmd .tmp*
clean:
	rm -f *.o *~ *.ko  *.mod.c *.mod.o *.symvers *.order
endif

ins:
	sudo insmod ./sync_drv.ko
del:
	sudo rmmod sync_drv
	
CC := gcc
mt:
	$(CC) -o test test_sync.c

.PHONY:clc
clc:
	rm test


