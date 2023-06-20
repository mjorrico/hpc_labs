CC=gcc
CFLAGS=-fopenmp -g -Wall

all: datasharing

datasharing: datasharing.c
	$(CC) $(CFLAGS) -o datasharing datasharing.c

clean:
	rm -f datasharing