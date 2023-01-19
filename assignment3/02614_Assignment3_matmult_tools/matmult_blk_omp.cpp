#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "matmult_blk_omp.h"

void matmult_blk_omp(int M,int N,int K,double **A,double **B,double **C, int bs) {
    
    #pragma omp parallel for
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            C[m][n] = 0.0;
        }
    }
    
    #pragma omp parallel for shared(M, N, K, A, B, C, bs)
    for (int i = 0; i < M; i += bs) {
        int row_min = fminf(i + bs, M);
        for (int k = 0; k < K; k += bs) {
            int dot_min = fminf(k + bs, K);
            for (int j = 0; j < N; j += bs) {
                int col_min = fminf(j + bs, N);
                for (int ii = i; ii < row_min; ii++) {
                    double *Aii = A[ii];
                    for (int kk = k; kk < dot_min; kk++) {
                        for (int jj = j; jj < col_min; jj++) {
                            C[ii][jj] += Aii[kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}
