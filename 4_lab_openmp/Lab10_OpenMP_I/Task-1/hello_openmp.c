#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    /*  use num_threads(n)
        use omp_set_num_threads(n)
        export OMP_NUM_THREADS */

    // omp_set_num_threads(5);
#pragma omp parallel num_threads(10)
    {
        printf("Bonjour! %d\n", omp_get_thread_num());
    }
    return 0;
}
