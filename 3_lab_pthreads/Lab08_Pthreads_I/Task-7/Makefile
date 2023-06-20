CC=gcc
CFLAGS=-O1 -g
LDFLAGS=-lm -lpthread

all: recursive

recursive: recursive.c
	$(CC) $(CFLAGS) -o recursive recursive.c $(LDFLAGS)

test: test.c
	$(CC) $(CFLAGS) -o test test.c $(LDFLAGS)

clean:
	rm recursive test