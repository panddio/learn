GCC := mips-linux-gnu-gcc

CFLAGS := -EL -mabi=32 -mhard-float -march=mips32r2 -Os
LDFLAGS:= -Wl,-EL
LDLIBS :=

SOURCES := $(wildcard *.c)

TARGET = fb_test
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(GCC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY:install clean distclean
INSTALL_DIR := ~/work/mozart-new/mozart/rootfs/updater/usr/bin/
install:fb_test
	cp $(TARGET) $(INSTALL_DIR)

clean:
	rm $(TARGET) *.o -rf

distclean:
	rm $(TARGET) $(INSTALL_DIR)/$(TARGET) *.o -rf
