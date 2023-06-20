#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *the_thread_func_A(void *arg)
{
    printf("the_thread_func_A() starts working.\n");
    long int i;
    double sum;
    for (i = 0; i < 1000000000; i++)
    {
        sum += 1e-7;
    }
    printf("Result at the_thread_func_A(): sum = %f\n", sum);
    return NULL;
}

void *the_thread_func_B(void *arg)
{
    printf("the_thread_func_B() starts working.\n");
    long int i;
    double sum;
    for (i = 0; i < 1000000000; i++)
    {
        sum += 1e-7;
    }
    printf("Result at the_thread_func_B(): sum = %f\n", sum);
    return NULL;
}

int main()
{
    printf("This is the main() function starting.\n");

    /* Start thread. */
    pthread_t thread_A, thread_B;
    pthread_create(&thread_A, NULL, the_thread_func_A, NULL);
    pthread_create(&thread_B, NULL, the_thread_func_B, NULL);

    printf("main() starts working.\n");
    long int i;
    double sum;
    for (i = 0; i < 1000000000; i++)
    {
        sum += 1e-7;
    }
    printf("Result at main(): sum = %f\n", sum);

    /* Wait for thread to finish. */
    printf("the main() function now calling pthread_join().\n");
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);

    return 0;
}
