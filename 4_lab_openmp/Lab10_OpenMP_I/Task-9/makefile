CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -Werror -fopenmp
LDFLAGS = 
RM = /bin/rm -f
OBJS = main.o sort_funcs.o
EXECUTABLE = sort_test

all:$(EXECUTABLE) simple

$(EXECUTABLE): $(OBJS)
	$(LD) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)

sort_funcs.o: sort_funcs.h sort_funcs.c
	$(CC) $(CFLAGS) -c sort_funcs.c

main.o: main.c sort_funcs.h
	$(CC) $(CFLAGS) -c main.c 

simple: simple.c
	$(CC) $(CFLAGS) -fopenmp simple.c -o simple

clean:
	$(RM) $(EXECUTABLE) $(OBJS) simple
