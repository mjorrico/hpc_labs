CC=gcc
CFLAGS=-O3 -g -Wall
LDFLAGS=-lm -lpthread

all: matmul matmul_old

matmul: matmul.c
	$(CC) $(CFLAGS) -O3 -o matmul matmul.c

matmul_old: matmul_old.c
	$(CC) $(CFLAGS) -O3 -o matmul_old matmul_old.c

clean:
	rm -f matmul matmul_old