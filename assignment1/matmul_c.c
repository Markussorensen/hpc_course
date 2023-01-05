#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>
#include <math.h>

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

// void matmult_blk(int M,int N,int K,double **A,double **B,double **C, int bs) {
//     for (int m = 0; m < M; m++) {
//         for (int n = 0; n < N; n++) {
//             C[m][n] = 0.0;
//             }
//         }
//     for (int i = 0; i < M; i += bs) {
//          int row_min = fmin(i + bs, M);
//         for (int j = 0; j < N; j += bs) {
//             int col_min = fmin(j + bs, N);
//             for (int k = 0; k < K; k += bs) {
//                 int dot_min = fmin(k + bs, K);
//                 for (int ii = i; ii < row_min; ii++) {
//                     double *Aii = A[ii];
//                     for (int jj = j; jj < col_min; jj++) {
//                         for (int kk = k; kk < dot_min; kk++) {
//                             C[ii][jj] += Aii[kk] * B[kk][jj];
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// void matmult_blk(int M,int N,int K,double **A,double **B,double **C, int bs) {
//     for (int m = 0; m < M; m++) {
//         for (int n = 0; n < N; n++) {
//             C[m][n] = 0.0;
//             }
//         }
//     double **B_T = malloc(N * sizeof(double *));
//     for (int i3 = 0; i3 < N; i3++) {
//         B_T[i3] = malloc(K * sizeof(double));
//     }
//     for (int i4 = 0; i4 < N; i4++) {
//         for (int j4 = 0; j4 < K; j4++) {
//             B_T[i4][j4] = B[j4][i4];
//         }
//     }
//     for (int i = 0; i < M; i += bs) {
//          int row_min = fmin(i + bs, M);
//         for (int j = 0; j < N; j += bs) {
//             int col_min = fmin(j + bs, N);
//             for (int k = 0; k < K; k += bs) {
//                 int dot_min = fmin(k + bs, K);
//                 for (int ii = i; ii < row_min; ii++) {
//                     double *Aii = A[ii];
//                     for (int jj = j; jj < col_min; jj++) {
//                         double *Bjj = B_T[jj];
//                         for (int kk = k; kk < dot_min; kk++) {
//                             C[ii][jj] += Aii[kk] * Bjj[kk];
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

void matmult_blk(int M,int N,int K,double **A,double **B,double **C, int bs) {
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            C[m][n] = 0.0;
            }
        }
    for (int i = 0; i < M; i += bs) {
         int row_min = fmin(i + bs, M);
        for (int k = 0; k < K; k += bs) {
            int dot_min = fmin(k + bs, K);
            for (int j = 0; j < N; j += bs) {
                int col_min = fmin(j + bs, N);
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
