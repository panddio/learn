.PHONY:all
all:peter lucy bob

peter:chat.c
	gcc chat.c -o peter -DP
	
lucy:chat.c
	gcc chat.c -o lucy -DL
	
bob:chat.c
	gcc chat.c -o bob -DB
	
.PHONY:clean
clean:
	rm peter lucy bob