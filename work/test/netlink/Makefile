ifneq ($(KERNELRELEASE),)
	obj-m := netlink_kernel.o

else
	CC=mips-linux-gnu-gcc
	KERNELDIR ?= ~/work/sz-halley2/kernel
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	rm -rf *.o *.mod.c *.order *.symvers .*.cmd .tmp*
clean:
	rm -f *.o *~ *.ko  *.mod.c *.mod.o *.symvers *.order
endif

