CC=gcc
CFLAGS=-g
LDFLAGS=-lm -lpthread

all: prime

prime: prime.c
	$(CC) $(CFLAGS) -o prime prime.c $(LDFLAGS)

test: test.c
	$(CC) $(CFLAGS) -o test test.c $(LDFLAGS)

clean:
	rm prime test