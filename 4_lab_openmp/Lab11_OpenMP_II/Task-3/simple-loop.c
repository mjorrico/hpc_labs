#include <omp.h>
#include <stdio.h>
#include <time.h>

long int N = 5000000;

double f(int q)
{
    long int i;
    double x = 1.0;
    for (i = 0; i < N; i++)
        x *= 1.000000001;
    return x * q;
}

int main(int argc, char* argv[])
{
    const int M = 200;
    double arr[M];


    // clock_t start = clock();
    double start = omp_get_wtime(); // if using OMP
    #pragma omp parallel for num_threads(2) schedule(static)
    for (int i = 0; i < M; i++)
        arr[i] = f(i);

    // double elapsed = ((double) (clock() - start))/CLOCKS_PER_SEC;
    // printf("Time taken: %lf s.\n", elapsed);
    printf("Time taken: %lf s.\n", omp_get_wtime() - start); // if using OMP

    /* Sum up results. */
    double sum = 0;
    int k;
    for (k = 0; k < M; k++)
        sum += arr[k];

    printf("sum = %f\n", sum);

    return 0;
}
