/**********************************************************************
 * This program calculates pi using C
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]) {

    int i;
    const int intervals = 2000000000;
    double sum, tempsum, dx, x;

    if (argc != 2) {
        return -1;
    }
    int n_thr = atoi(argv[1]);

    dx = 1.0 / intervals;
    sum = 0.0;
    double start = omp_get_wtime();
    #pragma omp parallel num_threads(n_thr) private(tempsum) reduction(+: sum)
    {
        tempsum = 0.0;
        #pragma omp for
        for (i = 1; i <= intervals; i++) {
            x = dx * (i - 0.5);
            sum += dx * 4.0 / (1.0 + x * x);
        }
        sum += tempsum;
    }

    printf("PI is approx. %.16f. Time: %lf\n", sum, omp_get_wtime() - start);

    return 0;
}
