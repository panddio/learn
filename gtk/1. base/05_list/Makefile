CC = gcc  
MAINC = list.c
EXEC = list

CFLAGS = `pkg-config --cflags --libs gtk+-2.0`

main:  
	$(CC)  $(MAINC)  -o $(EXEC) $(CFLAGS)
clean:
	rm $(EXEC) -rf