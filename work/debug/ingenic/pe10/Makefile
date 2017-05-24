ifneq ($(KERNELRELEASE),)
	obj-m := pe10_drv.o

else
#	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
#	KERNELDIR ?= ~/work/m200/4.3/kernel/
	KERNELDIR ?= ~/work/m200/5.1/kernel-3.10.14/
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	rm -rf *.o *.mod.c *.order *.symvers .*.cmd .tmp*
clean:
	rm -f *.o *~ *.ko  *.mod.c *.mod.o *.symvers *.order
endif

test:
	mips-linux-gnu-gcc -static -o test_pe10 test_pe10.c
