CC=gcc
CFLAGS=-Ofast -g
LDFLAGS=-lm -lpthread

all: threadtest

threadtest: threadtest1.c
	$(CC) $(CFLAGS) -o threadtest threadtest1.c $(LDFLAGS)

clean:
	rm threadtest