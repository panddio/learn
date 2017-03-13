TOPDIR := $(shell pwd)
GCC := mips-linux-gnu-gcc

CFLAGS := -Os -Wall -mabi=32 -mhard-float -march=mips32r2 -I$(TOPDIR)/include
LDFLAGS := -Wl,-EL
LDLIBS := -L$(TOPDIR)/lib -ljpeg-hw

SOURCES := $(wildcard *.c)

TARGET = cimcapt
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(GCC) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -o $@ $^

INSTALL_DIR = ~/work/sz-halley2/out/product/yak/system/usr/bin
install: all
	cp $(TARGET) $(INSTALL_DIR) -a

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
