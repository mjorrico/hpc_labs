#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *the_thread_func(void *arg)
{
    int *result = malloc(sizeof(int));
    *result = 212;
    // pthread_exit(result);
    return (void *)result;
}

int main()
{
    printf("This is the main() function starting.\n");

    /* Start thread. */
    pthread_t thread;
    printf("the main() function now calling pthread_create().\n");
    if (pthread_create(&thread, NULL, the_thread_func, NULL) != 0)
    {
        printf("ERROR: pthread_create failed.\n");
        return -1;
    }

    printf("This is the main() function after pthread_create()\n");

    int *int_result;

    /* Wait for thread to finish. */
    printf("the main() function now calling pthread_join().\n");
    if (pthread_join(thread, (void **)&int_result) != 0)
    {
        printf("ERROR: pthread_join failed.\n");
        return -1;
    }

    printf("The number returned from thread is %d.\n", *int_result);
    free(int_result);

    return 0;
}
