#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>

void matmult_nat(int M, int N, int K, double **A, double **B, double **C) {
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            C[m][n] = 0.0;
            }
        }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmult_lib(int m, int n, int k, double **A, double **B, double **C) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, *A, k, *B, n, 0.0, *C, n);
}

//Now we make all permutations of the matmul_nat function
void matmult_mnk(int M, int N, int K, double **A, double **B, double **C) {
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            C[m][n] = 0.0;
            }
        }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

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

void matmult_nmk(int M, int N, int K, double **A, double **B, double **C) {
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            C[m][n] = 0.0;
            }
        }
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < M; i++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmult_nkm(int M, int N, int K, double **A, double **B, double **C) {
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            C[m][n] = 0.0;
            }
        }
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < K; k++) {
            for (int i = 0; i < M; i++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmult_kmn(int M, int N, int K, double **A, double **B, double **C) {
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            C[m][n] = 0.0;
            }
        }
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmult_knm(int M, int N, int K, double **A, double **B, double **C) {
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            C[m][n] = 0.0;
            }
        }
    for (int k = 0; k < K; k++) {
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < M; i++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


