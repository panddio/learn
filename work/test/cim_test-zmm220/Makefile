#CC=gcc
#ifeq ($(MAKERULES),)
#include ../../Rules.make
#else
#include $(MAKERULES)
#endif
CC=mipsel-linux-gcc
#CC=arm-marvell-linux-gnueabi-gcc
#CFLAGS+=-Iinclude/ -DDEBUG_BUILD -DCONFIG_IPM \
	-I/home/work/300/rel/host/include\
	-g -Waggregate-return -Wmissing-noreturn -W -Wall -mcpu=iwmmxt -mtune=iwmmxt -mabi=aapcs-linux
#	-I/home/work/300/rel/host/include -L/home/work/300/rel/host/lib -L/home/work/300/rel/target/rootfs/lib -g -Waggregate-return -Wmissing-noreturn -W -Wall -mcpu=iwmmxt -mtune=iwmmxt -mabi=aapcs-linux
CFLAGS+=-O2 -W
#LFLAGS+= -I/opt/zem800/arm-marvell-linux-gnueabi/include -L/opt/zem800/arm-marvell-linux-gnueabi/lib -ljpeg
LFLAGS+= -ljpeg

.PHONY: all compile clean clean-local

all: compile

compile: cimtest 
	echo "built successfully"

OBJECTS=mt9v136.c cim.c gpio.c camera.c conver.c fvjpg.c futil.c yuv2jpg.c gc0308.c
cimtest:$(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

clean: clean-local

clean-local:
	-rm -f *.o  cimtest
