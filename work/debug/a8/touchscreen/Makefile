# If KERNELRELEASE is 2.6.35.7, we've been invoked from the 
# kernel build system and can use its language. 
ifeq ($(KERNELRELEASE),2.6.35.7)

#if you want use param to make,as follow:
#use��make t=XXX
TARGET=$(t)
ifneq ($(TARGET),)
obj-m := $(TARGET).o
else
#if have only one *.c file and get one *.ko file
#obj-m := virtualchar.o 

#if have many *.c file and get many *.ko
obj-m := goodix_dev.o goodix_touch_v2.1.o

#if have many *.c file and get one *.ko
#note: The object file name of the next two line must be consistent
#obj-m := ZZZ.o 
#ZZZ-objs := XXX.o YYY.o ... 
endif

else

#if not define KERNELDIR in enviroment,you need define KERNELDIR by yourself 
ifeq ($(KERNELDIR),)
KERNELDIR = /home/edu/a8/2.6.35.7_tools/unsp210_linux_2.6.35/
endif	

$(PWD) := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules	
	rm -rf *.o *.mod.c *.order *.symvers .*.cmd .tmp*
	
clean:
	rm -rf *.ko 

# app test need 
test:
	arm-linux-gcc -o $@ test.c
testclean:
	rm -fr test	
	
endif 
