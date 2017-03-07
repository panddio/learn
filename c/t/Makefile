CC := gcc

TAG := app
CFLAG := -lm

all: $(TAG) god loader

$(TAG):$(SRC)
	$(CC) -o $(TAG) app.c

god:$(TAG)
	$(CC) -o $@ god.c
	strip $@
	@./god ./app > log

loader:
	$(CC) -o $@ loader.c

.PHONY:clean
clean:
	rm -f $(TAG) *.o god loader log n_app
