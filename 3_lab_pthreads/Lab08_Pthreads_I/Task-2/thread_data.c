#include <stdio.h>
#include <pthread.h>

void *the_thread_func(void *arg)
{
    double *input_array = (double *)arg;
    double sum = 0;
    for (int i = 0; i < 3; i++){
        sum += input_array[i];
    }
    printf("The sum is %lf\n", sum);
    return NULL;
}

int main()
{
    printf("This is the main() function starting.\n");

    double data_for_thread[3];
    data_for_thread[0] = 5.7;
    data_for_thread[1] = 9.2;
    data_for_thread[2] = 1.6;

    double data_for_thread_B[3] = {7, 9, 11};

    /* Start thread. */
    pthread_t thread, thread_B;
    printf("the main() function now calling pthread_create().\n");
    pthread_create(&thread, NULL, the_thread_func, data_for_thread);
    pthread_create(&thread_B, NULL, the_thread_func, data_for_thread_B);

    printf("This is the main() function after pthread_create()\n");

    /* Do something here? */

    /* Wait for thread to finish. */
    printf("the main() function now calling pthread_join().\n");
    pthread_join(thread, NULL);
    pthread_join(thread_B, NULL);

    return 0;
}
