#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct thread_data
{
    int thr_id;
    int some_number;
} thread_data;

void *threaded_function(void *arg)
{
    thread_data *data = (thread_data *)arg;
    printf("Thread index: %d. Number: %d.\n", data->thr_id, data->some_number);
    free(arg);

    return NULL;
}

int main(int argc, char *argv[])
{
    int N_THR = atoi(argv[1]);
    pthread_t thr[N_THR];
    for (int i = 0; i < N_THR; i++)
    {
        thread_data *d = malloc(sizeof(thread_data)); // doesn't have malloc
        d->thr_id = i;
        d->some_number = i * i - i;
        pthread_create(&thr[i], NULL, threaded_function, (void *)d);
    }

    for (int i = 0; i < N_THR; i++)
    {
        pthread_join(thr[i], NULL);
    }

    return 0;
}