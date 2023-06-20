CC=gcc
CFLAGS=-fopenmp -g -Wall
LDFLAGS=-lm

all: prime

prime: prime.c
	$(CC) $(CFLAGS) -o prime prime.c $(LDFLAGS)

clean:
	rm -f prime