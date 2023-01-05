#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>

void matmul_nat(int m, int n, int k, double **A, double **B, double **C) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < k; l++) {
                C[i][j] += A[i][l] * B[l][j];
            }
        }
    }
}

void matmul_lib(int m, int n, int k, double **A, double **B, double **C) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, *A, k, *B, n, 0.0, *C, n);
}

//Now we make all permutations of the matmul_nat function
void matmul_mnk(int m, int n, int k, double **A, double **B, double **C) {
    for (int m = 0; m < m; m++) {
        for (int n = 0; n < n; n++) {
            for (int k = 0; k < k; k++) {
                C[m][n] += A[m][k] * B[k][n];
            }
        }
    }
}

void matmul_mkn(int m, int n, int k, double **A, double **B, double **C) {
    for (int m = 0; m < m; m++) {
        for (int k = 0; k < k; k++) {
            for (int n = 0; n < n; n++) {
                C[m][n] += A[m][k] * B[k][n];
            }
        }
    }
}

void matmul_nmk(int m, int n, int k, double **A, double **B, double **C) {
    for (int n = 0; n < n; n++) {
        for (int m = 0; m < m; m++) {
            for (int k = 0; k < k; k++) {
                C[m][n] += A[m][k] * B[k][n];
            }
        }
    }
}

void matmul_nkm(int m, int n, int k, double **A, double **B, double **C) {
    for (int n = 0; n < n; n++) {
        for (int k = 0; k < k; k++) {
            for (int m = 0; m < m; m++) {
                C[m][n] += A[m][k] * B[k][n];
            }
        }
    }
}

void matmul_kmn(int m, int n, int k, double **A, double **B, double **C) {
    for (int k = 0; k < k; k++) {
        for (int m = 0; m < m; m++) {
            for (int n = 0; n < n; n++) {
                C[m][n] += A[m][k] * B[k][n];
            }
        }
    }
}

void matmul_knm(int m, int n, int k, double **A, double **B, double **C) {
    for (int k = 0; k < k; k++) {
        for (int n = 0; n < n; n++) {
            for (int m = 0; m < m; m++) {
                C[m][n] += A[m][k] * B[k][n];
            }
        }
    }
}




