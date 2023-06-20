CC=gcc
CFLAGS=-g
LDFLAGS=-lm -lpthread

all: threadid

threadid: threadid.c
	$(CC) $(CFLAGS) -o threadid threadid.c $(LDFLAGS)

test: test.c
	$(CC) $(CFLAGS) -o test test.c $(LDFLAGS)

clean:
	rm threadid test