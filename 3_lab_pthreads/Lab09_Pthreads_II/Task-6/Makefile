CC=gcc
CFLAGS=-O3 -Wall
LDFLAGS=-lm -lpthread

all: enumsort enumsort_old

enumsort: enumsort.c
	$(CC) $(CFLAGS) -o enumsort enumsort.c -lpthread

enumsort_old: enumsort_old.c
	$(CC) $(CFLAGS) -o enumsort_old enumsort_old.c -lpthread

clean:
	rm -f enumsort enumsort_old