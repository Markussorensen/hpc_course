#include <stdio.h>
#include "xtime.h"

int main(int argc, char *argv[]) {
    int i, N;
    double **A, *B, *C;

    if (argc != 2) {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }
    N = atoi(argv[1]);
    A = (double **)malloc(N * sizeof(double *));
    B = (double *)malloc(N * sizeof(double));
    for (i = 0; i < N; i++) {
        A[i] = (double *)malloc(N * sizeof(double));
    }
    double ts, te;
    ts = xtime();
    // Matrix vector multiplication
    for (i = 0; i < N; i++) {
        C[i] = 0.0;
        for (j = 0; j < N; j++) {
            C[i] += A[i][j] * B[j];
        }
    }
    te = xtime() - ts;
    printf("Unparallized version: \n");
    printf("time = %f", te);
    printf("\n");
    return 0;
}
    