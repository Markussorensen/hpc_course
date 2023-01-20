#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "matmult_blk_offload.h"

void matmult_blk_offload(int M, int N, int K, double **A, double **B, double **C) {
    double warmup = 1.0;
    const int bs = 64;
    // double sum[bs] = {0.0};
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
        #pragma omp target teams distribute parallel for collapse(2)
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
    }
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