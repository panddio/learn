all:qq yy

qq:qq.c
	gcc -o qq qq.c -lpthread
yy:qq.c
	gcc -o yy qq.c -lpthread

.PHONY:clean
clean:
	rm qq yy
