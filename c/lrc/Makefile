CC := gcc
SRC := $(shell ls *.c)
#OBJ := $(patsubst %.c,%.o,$(SRC))
OBJ := $(SRC: %.c=%.o)
TAG := lrc

$(TAG):$(OBJ)
	$(CC) -o $@ $^ 
%.o:%.c
	$(CC) -o $@ -c $<


.PHONY:clean
clean:
	rm -f $(TAG) *.o
