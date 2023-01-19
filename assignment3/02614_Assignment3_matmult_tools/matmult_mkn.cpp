#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "matmult_mkn.h"

void matmult_mkn(int M, int N, int K, double **A, double **B, double **C) {
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            C[m][n] = 0.0;
            }
        }
    for (int i = 0; i < M; i++) {
        for (int k = 0; k < K; k++) {
            for (int j = 0; j < N; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}