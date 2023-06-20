#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void f(int N, int i, double* resultPtr) {
    double result = 0;
    for (int k = 0; k < i; k++)
        for (int a = 0; a < N; a++)
            for (int b = 0; b < N; b++)
                result += 0.001 * (0.3 * a * b + b);
    *resultPtr = result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please give 1 arg: N\n");
        return -1;
    }
    int N = atoi(argv[1]);
    int M = 100, i;
    double result[M];
    double finalresult = 0;

    #ifdef _OPENMP
    double start = omp_get_wtime();
    #else
    clock_t start = clock();
    #endif

    #pragma omp parallel num_threads(8)
    {
        #pragma omp single
        {
            for (i = 0; i < M; i++) {
                #pragma omp task
                {
                    f(N, i, &result[i]);
                }
            }
        }
    }

    #ifdef _OPENMP
    double end = omp_get_wtime() - start;
    #else
    double end = ((double)(clock() - start)) / CLOCKS_PER_SEC;
    #endif

    for (i = 0; i < M; i++)
        finalresult += result[i];

    printf("Time = %f  finalSum = %f\n", end, finalresult);
    return 0;
}
