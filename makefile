CC=gcc -std=c99
EXEC=main

# Variables needed by default.mk

ALL = $(EXEC)

# targets

main : main.o Affichage.o Operation.o
	$(CC) -o main main.o Affichage.o Operation.o

main.o: Main.c
	$(CC) -o main.o -c Main.c

Affichage.o: Affichage.c
	$(CC) -o Affichage.o -c Affichage.c

Operation.o: Operation.c
	$(CC) -o Operation.o -c Operation.c

clean:
	rm -rf *.o




