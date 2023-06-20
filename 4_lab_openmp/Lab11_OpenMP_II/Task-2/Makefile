CC=gcc
CFLAGS=-fopenmp -g -Wall

all: ompsections

ompsections: ompsections.c
	$(CC) $(CFLAGS) -o ompsections ompsections.c

clean:
	rm -f ompsections