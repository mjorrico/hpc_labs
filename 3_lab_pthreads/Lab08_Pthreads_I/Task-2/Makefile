CC=gcc
CFLAGS=-Ofast -g
LDFLAGS=-lm -lpthread

all: thread_data

thread_data: thread_data.c
	$(CC) $(CFLAGS) -o threaddata thread_data.c $(LDFLAGS)

test: test.c
	$(CC) $(CFLAGS) -o test test.c $(LDFLAGS)

clean:
	rm threaddata test