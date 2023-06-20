#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct child_thread_data
{
    int parent_idx;
    int idx;
} child_thread_data;

void *second_threaded_func(void *arg)
{
    child_thread_data *data = (child_thread_data *)arg;
    printf("Thread %d.%d running.\n", data->parent_idx, data->idx);
    free(arg);
    return NULL;
}

void *first_threaded_func(void *arg)
{
    int *index = (int *)arg;
    printf("Thread %d running.\n", *index);

    int N = 2;
    pthread_t thr[N];

    for (int i = 0; i < N; i++)
    {
        child_thread_data *data = malloc(sizeof(child_thread_data));
        data->parent_idx = *index;
        data->idx = i;
        pthread_create(&thr[i], NULL, second_threaded_func, (void *)data);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(thr[i], NULL);
    }

    free(arg);
    return NULL;
}

int main()
{
    int N = 2;
    pthread_t thr[N];

    for (int i = 0; i < N; i++)
    {
        int *idx = malloc(sizeof(int));
        *idx = i;
        pthread_create(&thr[i], NULL, first_threaded_func, (void *)idx);
    }

    printf("Main thread running.\n");

    for (int i = 0; i < N; i++)
    {
        pthread_join(thr[i], NULL);
    }

    return 0;
}