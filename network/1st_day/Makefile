all:qq yy

qq:qq.c
	gcc -o qq qq.c -lpthread
yy:qq.c
	gcc -o yy yy.c -lpthread

.PHONY:clean
clean:
	rm qq yy
