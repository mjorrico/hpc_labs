#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *print_prime(void *arg)
{
    sleep(2);
    int *result = malloc(sizeof(int));
    int index = *(int *)arg;
    if (index == 6){
        sleep(10);
    }
    printf("Index %d\n", index);
    *result = primes[index];
    free(arg);
    return (void *)result;
}

int main()
{
    pthread_t th[10];
    int *final_result = malloc(10 * sizeof(int));

    for (int i = 0; i < 10; i++)
    {
        int *thr_idx = malloc(sizeof(int));
        *thr_idx = i;
        pthread_create(&th[i], NULL, print_prime, (void *)thr_idx);
    }

    for (int i = 0; i < 10; i++)
    {
        int *tmp;
        pthread_join(th[i], (void **)&tmp);
        final_result[i] = *tmp;
        printf("%d\n", final_result[i]);
        free(tmp);
    }

    for (int i = 0; i < 10; i++)
    {
        printf("Index %d: %d\n", i, final_result[i]);
    }

    return 0;
}