#include <stdio.h>
#include <omp.h>

int main()
{
    int n_thr = 3;
    omp_set_nested(0);
    printf("Nested? %d.\n", omp_get_nested());
#pragma omp parallel num_threads(n_thr)
    {
        int outer_thr_id = omp_get_thread_num();
        printf("Outer thread: %d.\n", outer_thr_id);
        if (outer_thr_id == 0)
        {
            omp_set_nested(0);
        }
#pragma omp parallel num_threads(n_thr)
        {
            int inner_thr_id = omp_get_thread_num();
            printf("Outer thread: %d, inner thread: %d.\n", outer_thr_id, inner_thr_id);
        }
    }
}