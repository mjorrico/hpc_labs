CC=gcc
CFLAGS=-g
LDFLAGS=-lm -lpthread

all: threaded

threaded: threaded_computation.c
	$(CC) $(CFLAGS) -o threaded threaded_computation.c $(LDFLAGS)

clean:
	rm threaded