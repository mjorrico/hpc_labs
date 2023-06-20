CC=gcc
CFLAGS=-O1 -g -Wall
LDFLAGS=-lm -lpthread

all: wait_test cond_test

wait_test: wait_test.c
	$(CC) $(CFLAGS) -o wait_test wait_test.c $(LDFLAGS)

cond_test: cond_test.c
	$(CC) $(CFLAGS) -o cond_test cond_test.c $(LDFLAGS)

clean:
	rm wait_test cond_test