CC := gcc
#CC := mips-linux-gnu-gcc
SRC=test.c
TAG=test

all: $(TAG)
$(TAG):test.c
	$(CC) -o $(TAG) $(SRC)

.PHONY:clean
clean:
	rm -rf $(TAG)
