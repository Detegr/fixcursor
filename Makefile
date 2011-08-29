CC=gcc

all: fixcursor.c
	gcc fixcursor.c -lX11 -o fixcursor
debug:
	$(CC) fixcursor.c -lX11 -o fixcursor -DDEBUG -ggdb
clean:
	rm fixcursor
