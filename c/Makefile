CC := gcc
SRC := $(shell ls *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
#OBJ := $(SRC:%.c=%.o)

TAG := test
CFLAG := -lm

$(TAG):$(OBJ)
	$(CC) -o $@ $^ $(CFLAG)
%.o:%.c
	$(CC) -o $@ -c $< $(CFLAG)


.PHONY:clean
clean:
	rm -f $(TAG) $(OBJ)
