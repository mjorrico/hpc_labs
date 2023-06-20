CC=gcc
CFLAGS=-O1 -g -Wall
LDFLAGS=-lm -lpthread

all: threadtest

threadtest: threadtest.c
	$(CC) $(CFLAGS) -o threadtest threadtest.c $(LDFLAGS)

test: test.c
	$(CC) $(CFLAGS) -o test test.c $(LDFLAGS)

clean:
	rm threadtest test