CC=gcc -std=c99
EXEC=main

# Variables needed by default.mk

ALL = $(EXEC)

# targets

main : main.o
	$(CC) -o main main.o

main.o: Main.c
	$(CC) -o main.o -c Main.c

clean:
	rm -rf *.o




