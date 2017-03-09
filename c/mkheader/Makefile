CC := gcc

TAG := app
CFLAG := -lm

all: $(TAG) mkheader loader

$(TAG):$(SRC)
	$(CC) -o $(TAG) app.c

mkheader:$(TAG)
	$(CC) -o $@ mkheader.c
	strip $@
	@./mkheader ./app > log

loader:
	$(CC) -o $@ loader.c

.PHONY:clean
clean:
	rm -f $(TAG) *.o mkheader loader log n_app
