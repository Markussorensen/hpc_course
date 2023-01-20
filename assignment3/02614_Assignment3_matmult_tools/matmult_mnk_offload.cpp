#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "matmult_mnk_offload.h"

#ifndef _TEAMS
#define _TEAMS 256
#endif

#ifndef _THREADS
#define _THREADS 32
#endif

void matmult_mnk_offload(int M, int N, int K, double **A, double **B, double **C) {
    double warmup = 1.0;
    int i, k, j;
    double t1, t2, t3, t4;
    #pragma omp target data map(tofrom: warmup)
    {
        warmup = warmup + 1.0;
    }

    t1 = omp_get_wtime();
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
        t2 = omp_get_wtime();
        #pragma omp target teams distribute parallel for private(i, k, j) collapse(2) num_teams(_TEAMS) thread_limit(_THREADS)
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                for (k = 0; k < K; k++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
            }
        }
        t3 = omp_get_wtime();
    }
    t4 = omp_get_wtime();
    printf("Time with transfers: %f \n", t4 - t1);
    printf("Time without transfers: %f \n", t3 - t2);
}