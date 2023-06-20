#include <omp.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int a, b, i;
    a = 100;
    b = 20;
    printf("main a: %d, a address= %p\n", a, &a);

    // #pragma omp parallel num_threads(4) firstprivate(a)
    // {
    //     printf("thr %d, a address= %p\n", omp_get_thread_num(), &a);
    //     a += omp_get_thread_num();
    //     printf("thr %d, a= %d b= %d\n", omp_get_thread_num(), a, b);
    // }

    #pragma omp parallel for lastprivate(i) // lastprivate(a) ONLY FOR #pragma omp parallel for (LOOPS)
    for (i = 0; i < 20; i++)
    {
        printf("thr %d,a = %d,  a address= %p\n", omp_get_thread_num(), a, &a);
        a += omp_get_thread_num();
        printf("thr %d, a= %d b= %d\n", omp_get_thread_num(), a, b);
    }

    printf("a= %d b= %d i= %d\n", a, b, i);
    printf("main a: %d, a address= %p\n", a, &a);
    return 0;
}
