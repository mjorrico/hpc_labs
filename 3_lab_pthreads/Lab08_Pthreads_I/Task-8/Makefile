CC=gcc
CFLAGS=-O1 -g
LDFLAGS=-lm -lpthread

all: mutex

mutex: mutextest.c
	$(CC) $(CFLAGS) -o mutex mutextest.c $(LDFLAGS)

test: test.c
	$(CC) $(CFLAGS) -o test test.c $(LDFLAGS)

clean:
	rm mutex test