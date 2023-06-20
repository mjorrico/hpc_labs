#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#endif

int calc_prime(int M)
{
    int thr_id = 0, total_thr = 1;
#ifdef _OPENMP
    thr_id = omp_get_thread_num();
    total_thr = omp_get_num_threads();
#endif
    int result = 0; // Number 2 is prime
    int is_prime = 1;

    for (int i = thr_id * 2 + 3; i <= M; i += total_thr * 2)
    {
        is_prime = 1;
        for (int j = 2; j <= sqrt(i); j++)
        {
            if (i % j == 0)
            {
                is_prime = 0;
                break;
            }
        }

        if (is_prime == 1)
        {
            // printf("Thread: %d found %d prime!\n", thr_id, i);
            result++;
        }
    }

    printf("Thread %d done!\n", thr_id);
    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./prime [UPPER_BOUND_TO_CHECK] [NUM_OF_THREADS].\n");
        return 0;
    }
    int M = atoi(argv[1]);
    int N_THR = atoi(argv[2]);
    int result[N_THR];
    int final_result = 0;

#ifdef _OPENMP
    double start = omp_get_wtime();
#pragma omp parallel num_threads(N_THR)
    {
        result[omp_get_thread_num()] = calc_prime(M);
    }
    printf("Done in %lf s.\n", omp_get_wtime() - start);

    for (int i = 0; i < N_THR; i++)
    {
        final_result += result[i];
    }
#else
    final_result = calc_prime(M);
#endif

    printf("M: %d, result: %d.\n", M, final_result + 1); // +1 for number 2

    return 0;
}