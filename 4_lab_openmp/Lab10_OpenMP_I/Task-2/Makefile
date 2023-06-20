CC=gcc
CFLAGS=-fopenmp -g -Wall

all: threads_doing_work

threads_doing_work: threads_doing_work.c
	$(CC) $(CFLAGS) -o threads_doing_work threads_doing_work.c

clean:
	rm -f threads_doing_work