#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

static double get_wall_seconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
    return seconds;
}

double **A, **B, **C;
int n, N_THREADS;

typedef struct thr_data
{
    int thr_id, row_start, row_end;
} thr_data;

void *calc_matmul(void *arg)
{
    thr_data *d = (thr_data *)arg;
    int thr_id = d->thr_id;
    int row_start = d->row_start;
    int row_end = d->row_end;
    printf("Thread ID: %d, start: %d, end: %d.\n", thr_id, row_start, row_end);

    // Multiply C=A*B
    for (int i = row_start; i < row_end; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];

    free(d);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Please give two arguments: the matrix size and number of threads\n");
        return -1;
    }

    n = atoi(argv[1]);
    N_THREADS = atoi(argv[2]);

    int base_batch_size = n / N_THREADS;
    int n_plus_one = n % N_THREADS;
    pthread_t thr[N_THREADS];

    // Allocate and fill matrices
    A = (double **)malloc(n * sizeof(double *));
    B = (double **)malloc(n * sizeof(double *));
    C = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        A[i] = (double *)malloc(n * sizeof(double));
        B[i] = (double *)malloc(n * sizeof(double));
        C[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            A[i][j] = rand() % 5 + 1;
            B[i][j] = rand() % 5 + 1;
            C[i][j] = 0.0;
        }

    printf("Doing matrix-matrix multiplication with %d threads...\n", N_THREADS);
    double startTime = get_wall_seconds();

    int start = 0, end;
    for (int i = 0; i < N_THREADS; i++)
    {
        thr_data *d = malloc(sizeof(thr_data));
        d->thr_id = i;
        d->row_start = start;
        end = (i < n_plus_one) ? start + base_batch_size + 1 : start + base_batch_size;
        d->row_end = end;

        pthread_create(&thr[i], NULL, calc_matmul, (void *)d);

        start = end;
    }

    for (int i = 0; i < N_THREADS; i++)
    {
        pthread_join(thr[i], NULL);
    }

    double timeTaken = get_wall_seconds() - startTime;
    printf("Elapsed time: %f wall seconds\n", timeTaken);

    // Correctness check (let this part remain serial)
    printf("Verifying result correctness for a few result matrix elements...\n");
    int nElementsToVerify = 5 * n;
    double max_abs_diff = 0;
    int i, j;
    for (int el = 0; el < nElementsToVerify; el++)
    {
        i = rand() % n;
        j = rand() % n;
        double Cij = 0;
        for (int k = 0; k < n; k++)
            Cij += A[i][k] * B[k][j];
        double abs_diff = fabs(C[i][j] - Cij);
        if (abs_diff > max_abs_diff)
            max_abs_diff = abs_diff;
    }
    printf("max_abs_diff = %g\n", max_abs_diff);
    if (max_abs_diff > 1e-10)
    {
        for (i = 0; i < 10; i++)
            printf("ERROR: TOO LARGE DIFF. SOMETHING IS WRONG.\n");
        return -1;
    }
    printf("OK -- result seems correct!\n");

    // Free memory
    for (int i = 0; i < n; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
