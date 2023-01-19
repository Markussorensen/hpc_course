#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "matmult_mnk_offload.h"

void matmult_mnk_offload(int M, int N, int K, double **A, double **B, double **C) {
    double warmup = 1.0;
    int i, k, j;
    #pragma omp target data map(tofrom: warmup)
    {
        warmup = warmup + 1.0;
    }

    #pragma omp target data map(tofrom: C[0:M][0:N])
    {
        #pragma omp target teams distribute parallel for
        for (int m = 0; m < M; m++) {
            for (int n = 0; n < N; n++) {
                C[m][n] = 0.0;
                }
            }
    }

    #pragma omp target data map(to: A[0:M][0:K], B[0:K][0:N]) map(from: C[0:M][0:N])
    {
        #pragma omp target teams distribute parallel for private(i, k, j) collapse(2)
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                for (k = 0; k < K; k++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
            }
        }
    }
}