all: spinwait synch

spinwait: spinwait.c
	gcc -Wall -O3 -o spinwait spinwait.c -lm -lpthread

synch: synch.c
	gcc -Wall -O3 -o synch synch.c -lm -lpthread

clean:
	rm -f spinwait synch
