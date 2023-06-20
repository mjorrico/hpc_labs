#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double sum = 0.0;

typedef struct thr_data
{
    int thr_id;
    long begin;
    long end;
    long intervals;
} thr_data;

void *integrate(void *arg);

int main(int argc, char *argv[])
{
    const long intervals = 2000000000;
    int N_THR = atoi(argv[1]);

    long base_n_interval = intervals / N_THR;
    int n_plus_one = intervals % N_THR;
    long start = 0, end = 0;
    double sum = 0.0;

    double temp_results[N_THR];
    pthread_t thr[N_THR];

    for (int i = 0; i < N_THR; i++)
    {
        thr_data *d = malloc(sizeof(thr_data));
        end = start + base_n_interval;
        if (i < n_plus_one)
        {
            end++;
        }
        d->thr_id = i;
        d->begin = start;
        d->end = end;
        d->intervals = intervals;
        pthread_create(&thr[i], NULL, integrate, (void *)d);
        start = end;
    }

    for (int i = 0; i < N_THR; i++)
    {
        double *thread_result;
        pthread_join(thr[i], (void **)&thread_result);
        temp_results[i] = *thread_result;
        free(thread_result);
    }

    for (int i = 0; i < N_THR; i++)
    {
        sum += temp_results[i];
    }

    printf("PI is approx. %.16f\n", sum);

    return 0;
}

void *integrate(void *arg)
{
    thr_data *data = (thr_data *)arg;
    int thr_id = data->thr_id;
    long begin = data->begin;
    long end = data->end;
    long intervals = data->intervals;

    double *thread_sum = malloc(sizeof(double));
    *thread_sum = 0.0;
    double dx = 1.0 / intervals;
    double x;

    printf("Thread id: %d, begin: %ld, end: %ld.\n", thr_id, begin, end);

    for (long i = begin; i <= end; i++)
    {
        x = dx * (i - 0.5);
        *thread_sum += dx * 4.0 / (1.0 + x * x);
    }

    free(data);
    return (void *)thread_sum;
}