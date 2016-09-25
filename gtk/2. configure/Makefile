CC := gcc
SRC := $(shell ls *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
#OBJ := $(SRC:%.c=%.o)
TAG := $(patsubst %.c,%,$(SRC))

.PHONY:all
all:$(TAG)

CFLAGS = `pkg-config --cflags --libs gtk+-2.0 gmodule-export-2.0`

$(TAG):$(OBJ)
	$(CC) -o $@ $< $(CFLAGS)
%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS)


.PHONY:clean
clean:
	rm -f $(TAG) $(OBJ)