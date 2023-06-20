CC=gcc
CFLAGS=-fopenmp -g -Wall

all: hello_openmp

hello_openmp: hello_openmp.c
	$(CC) $(CFLAGS) -o hello_openmp hello_openmp.c

clean:
	rm -f hello_openmp