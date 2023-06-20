#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

typedef struct bound
{
    int thr_id;
    int M; // lower
    int N; // upper
} bound;

void *count_primes(void *arg)
{
    int tid = (*(bound *)arg).thr_id;
    printf("Thread %d starts working.\n", tid);
    int M = (*(bound *)arg).M;
    int N = (*(bound *)arg).N;
    int *result = malloc(sizeof(int));
    *result = 0;
    int is_prime;
    for (int i = M; i < N; i++)
    {
        is_prime = 1;
        // printf("Index %d.\n", i);
        if (i == 2)
        {
            *result += 1;
            continue;
        }
        else if (i % 2 == 0 || i < 2)
        {
            continue;
        }

        for (int j = 3; j <= sqrt(i); j++)
        {
            if (i % j == 0)
            {
                is_prime = 0;
                break;
            }
        }

        if (is_prime == 1)
        {
            *result += 1;
        }
    }

    printf("Thread %d done calculating. Result: %d.\n", tid, *result);
    free(arg);
    return (void *)result;
}

int threaded_count_primes(int M, int N, int N_THR)
{
    pthread_t thr[N_THR];

    int n_large = (N - M) % N_THR;
    int base_chunksize = (N - M) / N_THR;

    int lower_bound = M, upper_bound;
    for (int i = 0; i < N_THR; i++)
    {
        upper_bound = lower_bound + base_chunksize + ((i < n_large) ? 1 : 0);
        bound *input_thr = malloc(sizeof(bound));
        input_thr->thr_id = i;
        input_thr->M = lower_bound;
        input_thr->N = upper_bound;
        pthread_create(&thr[i], NULL, count_primes, (void *)input_thr);
        printf("Thread %d. Lower: %d, Upper: %d.\n", i, input_thr->M, input_thr->N);
        lower_bound = upper_bound;
    }

    int result_array[N_THR];
    for (int i = 0; i < N_THR; i++)
    {
        int *tmp;
        pthread_join(thr[i], (void **)&tmp);
        result_array[i] = *tmp;
        free(tmp);
    }

    int result = 0;
    for (int i = 0; i < N_THR; i++)
    {
        result += result_array[i];
    }

    return result;
}

int main(int argc, char *argv[])
{
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int N_THR = atoi(argv[3]);
    int result = threaded_count_primes(M, N, N_THR);
    printf("Result: %d.\n", result);
}