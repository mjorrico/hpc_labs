all: join detach

join: join.c
	gcc -Wall -O3 -o join join.c -lm -lpthread

detach: detach.c
	gcc -Wall -O3 -o detach detach.c -lm -lpthread

clean:
	rm -f join detach
