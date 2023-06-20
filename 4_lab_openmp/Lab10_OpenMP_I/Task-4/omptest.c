#include <stdio.h>
#include <omp.h>

typedef struct DataForThread
{
    double A;
    double B;
    int x;
    int y;
    double result;
} DataForThread_t;

void thread_func(DataForThread_t *p)
{
    printf("This is inside thread_func()!\n");
    double A = p->A;
    double B = p->B;
    int x = p->x;
    int y = p->y;
    printf("A: %lf, B: %lf, x: %d, y: %d.\n", A, B, x, y);
    double result = A + B + x + y;
    printf("Result: %lf.\n", result);
    p->result = result;
}

int main(int argc, char **argv)
{

    const int nThreads = 2;
    DataForThread_t arr[nThreads];
    /* Prepare data for thread 0. */
    arr[0].A = 3.7;
    arr[0].B = 1.2;
    arr[0].x = 88;
    arr[0].y = 77;
    /* Prepare data for thread 1. */
    arr[1].A = 2.2;
    arr[1].B = 8.8;
    arr[1].x = 444;
    arr[1].y = 555;

#pragma omp parallel num_threads(nThreads)
    {
        /* OK, now we are inside the parallel block, so this is executed
           by several threads. Get ID of current thread. */
        int id = omp_get_thread_num();
        /* Call thread_func and give it a pointer to arr[id] as input. */
        thread_func(&arr[id]);
    }

    printf("Result thread 1: %lf.\n", arr[0].result);
    printf("Result thread 2: %lf.\n", arr[1].result);

    return 0;
}
