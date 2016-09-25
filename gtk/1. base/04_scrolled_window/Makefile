CC = gcc  
MAINC = scrolled_window.c
EXEC = scrolled_window

CFLAGS = `pkg-config --cflags --libs gtk+-2.0`

main:  
	$(CC)  $(MAINC)  -o $(EXEC) $(CFLAGS)
clean:
	rm $(EXEC) -rf