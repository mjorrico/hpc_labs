CC=gcc
CFLAGS=-fopenmp -g -Wall

all: omptest

omptest: omptest.c
	$(CC) $(CFLAGS) -o omptest omptest.c

clean:
	rm -f omptest