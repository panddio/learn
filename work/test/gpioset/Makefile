CC := mipsel-linux-gcc
TAG := gpioset gpior
INSTALL_DIR := ../../mozart/rootfs/updater/usr/bin/

all:$(TAG)

.PHONY:gpioset
gpioset:gpioset.c
	$(CC) -o gpioset gpioset.c

.PHONY:gpior
gpior:
	$(CC) -o gpior gpior.c

.PHONY:install
install:gpioset gpior
	cp $(TAG) $(INSTALL_DIR)

.PHONY:clean
clean:
	rm $(TAG) *.o -rf
