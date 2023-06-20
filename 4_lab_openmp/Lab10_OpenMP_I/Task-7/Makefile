CC=gcc
CFLAGS=-g -Wall -fopenmp
LDFLAGS=-lm

all: prime

prime: prime.c
	$(CC) $(CFLAGS) -o prime prime.c $(LDFLAGS)

clean:
	rm -f prime