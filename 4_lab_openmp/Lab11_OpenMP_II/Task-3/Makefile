CC=gcc
CFLAGS=-fopenmp -g -Wall

all: other-loop simple-loop

other-loop: other-loop.c
	$(CC) $(CFLAGS) -o other-loop other-loop.c

simple-loop: simple-loop.c
	$(CC) $(CFLAGS) -o simple-loop simple-loop.c	

clean:
	rm -f other-loop simple-loop