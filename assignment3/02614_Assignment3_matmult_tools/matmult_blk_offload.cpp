#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "matmult_blk_offload.h"

#ifndef _TEAMS
#define _TEAMS 256
#endif

#ifndef _THREADS
#define _THREADS 32
#endif

void matmult_blk_offload(int M, int N, int K, double **A, double **B, double **C) {
    double warmup = 1.0;
    const int bs = 64;
    double t1, t2, t3, t4;
    // double sum[bs] = {0.0};
    int teams, threads;

    char* teams_env = getenv("TEAMS");
    if (teams_env != NULL) {
        teams = atoi(teams_env);
    } else {
        teams = _TEAMS;
    }

    char* threads_env = getenv("THREADS");
    if (threads_env != NULL) {
        threads = atoi(threads_env);
    } else {
        threads = _THREADS;
    }

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
        #pragma omp target teams distribute parallel for collapse(2) num_teams(teams) thread_limit(threads)
        for (int i = 0; i < M; i += bs) {
            for (int j = 0; j < N; j++) {
                double sum[bs] = {0.0};
                int row_min = fminf(i + bs, M);
                for (int k = 0; k < K; k++) {
                    for (int m = i; m < row_min; m++) {
                        sum[m - i] += A[m][k] * B[k][j];
                    }
                }
                for (int m = i; m < row_min; m++) {
                    C[m][j] += sum[m - i];
                }
            }
        }
        t3 = omp_get_wtime();
    }
    t4 = omp_get_wtime();
    printf("Time with transfers: %f \n", t4 - t1);
    printf("Time without transfers: %f \n", t3 - t2);
}


// void matmult_blk_offload(int M,int N,int K,double **A,double **B,double **C) {
//     double warmup = 1.0;
//     const int bs = 50;

//     #pragma omp target data map(tofrom: warmup)
//     {
//         warmup = warmup + 1.0;
//     }
//     #pragma omp target enter data map(alloc: A[0:M][0:K], B[0:K][0:N], C[0:K][0:N])
//     #pragma omp target update to(A[0:M][0:K], B[0:K][0:N])
//     #pragma omp target teams distribute parallel for
//     for (int m = 0; m < M; m++) {
//         for (int n = 0; n < N; n++) {
//             C[m][n] = 0.0;
//             }
//         }
//     #pragma omp parallel for
//     for (int i = 0; i < M; i += bs) {
//         int row_min = fminf(i + bs, M);
//         for (int k = 0; k < K; k += bs) {
//             int dot_min = fminf(k + bs, K);
//             for (int j = 0; j < N; j += bs) {
//                 int col_min = fminf(j + bs, N);
//                 #pragma omp target teams distribute parallel for collapse(1) nowait depend(out: C[i:bs][j:bs]) depend(in: A, B)
//                 for (int ii = i; ii < row_min; ii++) {
//                     for (int kk = k; kk < dot_min; kk++) {
//                         double sum[bs] = 0.0;
//                         for (int jj = j; jj < col_min; jj++) {
//                            for (int ii = i; ii < row_min; ii++) {
//                             sum[ii] += A[ii][kk] * B[kk][jj];
//                            }
//                         }
//                 for (int ii = i; ii < BS; ii++) {
//                         C[ii][j] = sum[ii];
//                 }
//                     }
//                 }
//                 #pragma omp target update from(C[i:bs][j:bs]) nowait
//             }
//         }
//     }
//     #pragma omp taskwait
//     #pragma omp target exit data map(release: A[0:M][0:K], B[0:K][0:N], C[0:M][0:N])
// }