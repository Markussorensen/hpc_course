#include <stdio.h>
#include "xtime.h"

int main(int argc, char *argv[]) {
    int i, N;
    double pi;

    if (argc != 2) {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }
    N = atoi(argv[1]);
    pi = 0.0;
    double ts, te;
    ts = xtime();
    #pragma omp parallel num_threads(20) for reduction(+:pi)
    for (i = 0; i < N; i++) {
        double x = ((i-0.5)/N);
        pi += 4.0 / (1 + x*x);
    } // end of parallel for
    pi /= N;
    te = xtime() - ts;
    printf("Parallized version: \n");
    printf("pi = %f", pi);
    printf("\n");
    printf("time = %f", te);
    printf("\n");
    return 0;
}