execute = guess_number transform year typewriting
sources = guess_number.c transform.c year.c	typewriting.c
objects = guess_number.o transform.o year.o typewriting.o

.PHONY:all
all:$(subst .c,,$(sources))
#$(patsubst %.c,%,$(sources))
#$(sources:.c=)

typewriting:typewriting.c
	gcc -o typewriting typewriting.c -w
guess_number:guess_number.c
	@echo "making guess_number.c"
	gcc -o guess_number guess_number.c -lm -w
transform:transform.c

year:year.c

.PHONY:clean
clean:
	rm $(execute)
