CC=gcc
CFLAGS=-fopenmp -g -Wall
LDFLAGS=-lm

all: ompthreadtest

ompthreadtest: ompthreadtest.c
	$(CC) $(CFLAGS) -o ompthreadtest ompthreadtest.c $(LDFLAGS)

clean:
	rm -f ompthreadtest