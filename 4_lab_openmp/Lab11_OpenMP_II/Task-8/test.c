#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

int main() {
    #pragma omp parallel num_threads(8)
    {
        #pragma omp single
        {
            printf("Single thread: %d.\n", omp_get_thread_num());
            #pragma omp task
            {
                printf("Task thread: %d.\n", omp_get_thread_num());
            }
        }
    }
}
