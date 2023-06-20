#include <omp.h>
#include <stdio.h>

long int N = 700000000;

void funcA()
{
    long int i;
    double x = 1.0;
    for (i = 0; i < N; i++)
        x *= 1.000000001;
    printf("funcA() result: x = %f\n", x);
}

void funcB()
{
    long int i;
    double x = 1.0;
    for (i = 0; i < N; i++)
        x *= 1.000000002;
    printf("funcB() result: x = %f\n", x);
}

void funcC()
{
    long int i;
    double x = 1.0;
    for (i = 0; i < N; i++)
        x *= 1.000000003;
    printf("funcC() result: x = %f\n", x);
}

int main(int argc, char* argv[])
{
    double start = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp sections // THIS TELLS THAT: don't let threads do the following block to run independently but rather run each section within this block to be run by threads
        {
            #pragma omp section
            {
                funcA();
            }
            #pragma omp section
            {
                funcB();
            }
            // #pragma omp section
            // {
            //     funcC();
            // }
        }
    }

    printf("Time taken: %lf s.\n", omp_get_wtime() - start);
    return 0;
}
