GCC := mips-linux-gnu-gcc

CFLAGS := -EL -mabi=32 -mhard-float -march=mips32r2 -Os
LDFLAGS:= -Wl,-EL
LDLIBS :=

SOURCES := $(wildcard *.c)

TARGET = pwm-led
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(GCC) $(CFLAGS) $(LDFLAGS) -o $@ $^

INSTALL_DIR = ~/work/sz-halley2/out/product/yak/system/usr/bin
install:
	cp $(TARGET) $(INSTALL_DIR) -a

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
