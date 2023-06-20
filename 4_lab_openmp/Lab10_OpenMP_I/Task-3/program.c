#include <stdio.h>
#include <omp.h>

void thread_func()
{
    printf("This is inside thread_func()!\n");
    int x = omp_get_num_threads(); // how many threads are running?
    int y = omp_get_thread_num();  // thread id
    int z = omp_get_max_threads(); // max number of threads that can run
    printf("Thread %d / %d. Max threads: %d.\n", y + 1, x, z);
}

int main(int argc, char **argv)
{

#pragma omp parallel num_threads(10)
    {
        thread_func();
    }

    return 0;
}
