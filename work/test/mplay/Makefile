TOPDIR := $(shell pwd)
GCC := mips-linux-gnu-gcc

CFLAGS := -Os -Wall -I$(TOPDIR)/include -L$(TOPDIR)/lib -ltinyalsa
LDFLAGS:= -Wl,-EL
SOURCES := $(wildcard *.c)

TARGET =mplay
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(GCC) $(CFLAGS)  $(LDFLAGS) -o $@ $^

INSTALL_DIR = ~/work/sz-halley2/out/product/yak/system/usr/bin
install:
	cp $(TARGET) $(INSTALL_DIR) -a

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
