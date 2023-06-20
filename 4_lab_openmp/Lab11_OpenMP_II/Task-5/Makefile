CC=gcc
CFLAGS=-fopenmp -g -Wall

all: reduce

loop: reduce.c
	$(CC) $(CFLAGS) -o reduce reduce.c

clean:
	rm -f reduce
