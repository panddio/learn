CC := gcc
SRC := $(shell ls *.c)
#OBJ := $(patsubst %.c,%.o,$(SRC))
OBJ := $(SRC:%.c=%.o)
TAG := elf
CFLAGS = `pkg-config --cflags --libs gtk+-2.0`	

$(TAG):$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lpthread
%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) -lpthread


.PHONY:clean
clean:
	rm -f $(TAG) *.o *~
