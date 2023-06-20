CC=gcc
CFLAGS=-O2 -g -Wall
LDFLAGS=-lm -lpthread

all: pi_old pi

pi_old: pi_old.c
	$(CC) $(CFLAGS) -o pi_old pi_old.c

pi: pi.c
	$(CC) $(CFLAGS) -o pi pi.c

clean:
	rm -f pi pi_old
