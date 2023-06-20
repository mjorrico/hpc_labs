all: task test

task: task_example_code.c
	gcc -O3 -Wall -fopenmp task_example_code.c -o task
test: test.c
	gcc -fopenmp -o test test.c
clean:
	rm -f task test
