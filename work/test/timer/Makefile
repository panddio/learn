#GCC := gcc

GCC := mips-linux-gnu-gcc
CFLAGS := -EL -mabi=32 -mhard-float -march=mips32r2 -Os
LDFLAGS:= -Wl,-EL
LDLIBS := -lrt -lpthread

SOURCES := $(wildcard *.c)

TARGET = timer
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(GCC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

INSTALL_DIR = ~/work/sz-halley2/out/product/yak/system/usr/bin
install:
	cp $(TARGET) $(INSTALL_DIR) -a

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
