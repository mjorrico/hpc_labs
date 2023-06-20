#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// #define NUM_THREADS 5
#define len 100000

typedef struct thr_data
{
    int thr_id;
    int start;
    int end;
} thr_data;

static double get_wall_seconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
    return seconds;
}

double indata[len], outdata[len];

void *findrank(void *arg)
{
    int rank;
    thr_data *d = (thr_data *)arg;
    int thr_id = d->thr_id;
    int start = d->start;
    int end = d->end;
    printf("Thread: %d, begin: %d, end: %d.\n", thr_id, start, end);

    for (int i = start; i < end; i++)
    {
        rank = 0;
        for (int j = 0; j < len; j++)
            if (indata[j] < indata[i])
                rank++;
        outdata[rank] = indata[i];
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int NUM_THREADS = atoi(argv[1]);
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    void *status;
    int base_batch_size = len / NUM_THREADS;
    int n_plus_one = len % NUM_THREADS;
    printf("Base: %d, plusone: %d.\n", base_batch_size, n_plus_one);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Generate random numbers
    for (int i = 0; i < len; i++)
    {
        indata[i] = drand48();
        outdata[i] = -1.0;
    }

    // Enumeration sort
    double startTime = get_wall_seconds();
    int start = 0, end;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thr_data *d = malloc(sizeof(thr_data));
        d->thr_id = i;
        d->start = start;
        end = (i < n_plus_one) ? start + base_batch_size + 1 : start + base_batch_size;
        d->end = end;
        pthread_create(&threads[i], &attr, findrank, (void *)d);
        start = end;
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], &status);
    }
    double timeTaken = get_wall_seconds() - startTime;
    printf("Time: %f  NUM_THREADS: %d\n", timeTaken, NUM_THREADS);

    // Check results, -1 implies data same as the previous element
    for (int i = 0; i < len - 1; i++)
        if (outdata[i] > outdata[i + 1] && outdata[i + 1] > -1)
            printf("ERROR: %f,%f\n", outdata[i], outdata[i + 1]);

    return 0;
}