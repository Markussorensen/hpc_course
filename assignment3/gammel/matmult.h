extern "C" {
    void matmult_lib(int m, int n, int k, double **A, double **B, double **C);
}

extern "C" {
    void matmult_lib_offload(int m, int n, int k, double **A, double **B, double **C);
}

// extern "C" {
//     void matmult_mkn(int M, int N, int K, double **A, double **B, double **C) {
//         for (int m = 0; m < M; m++) {
//             for (int n = 0; n < N; n++) {
//                 C[m][n] = 0.0;
//                 }
//             }
//         for (int i = 0; i < M; i++) {
//             for (int k = 0; k < K; k++) {
//                 for (int j = 0; j < N; j++) {
//                     C[i][j] += A[i][k] * B[k][j];
//                 }
//             }
//         }
//     }
// }

// extern "C" {
//     void matmult_blk(int M,int N,int K,double **A,double **B,double **C, int bs) {
//         for (int m = 0; m < M; m++) {
//             for (int n = 0; n < N; n++) {
//                 C[m][n] = 0.0;
//                 }
//             }
//         for (int i = 0; i < M; i += bs) {
//             int row_min = fminf(i + bs, M);
//             for (int k = 0; k < K; k += bs) {
//                 int dot_min = fminf(k + bs, K);
//                 for (int j = 0; j < N; j += bs) {
//                     int col_min = fminf(j + bs, N);
//                     for (int ii = i; ii < row_min; ii++) {
//                         double *Aii = A[ii];
//                         for (int kk = k; kk < dot_min; kk++) {
//                             for (int jj = j; jj < col_min; jj++) {
//                                 C[ii][jj] += Aii[kk] * B[kk][jj];
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// extern "C" {
//     void matmult_mkn_omp(int M, int N, int K, double **A, double **B, double **C) {
//         #pragma omp parallel for
//         for (int m = 0; m < M; m++) {
//             for (int n = 0; n < N; n++) {
//                 C[m][n] = 0.0;
//                 }
//             }
//         #pragma omp parallel for collapse(2)
//         for (int i = 0; i < M; i++) {
//             for (int k = 0; k < K; k++) {
//                 for (int j = 0; j < N; j++) {
//                     C[i][j] += A[i][k] * B[k][j];
//                 }
//             }
//         }
//     }
// }

// extern "C" {
//     void matmult_blk_omp(int M,int N,int K,double **A,double **B,double **C, int bs) {
//         #pragma omp parallel for schedule(static, bs)
//         for (int m = 0; m < M; m++) {
//             for (int n = 0; n < N; n++) {
//                 C[m][n] = 0.0;
//                 }
//             }
//         #pragma omp parallel for schedule(static, bs)
//         for (int i = 0; i < M; i += bs) {
//             int row_min = fminf(i + bs, M);
//             for (int k = 0; k < K; k += bs) {
//                 int dot_min = fminf(k + bs, K);
//                 for (int j = 0; j < N; j += bs) {
//                     int col_min = fminf(j + bs, N);
//                     for (int ii = i; ii < row_min; ii++) {
//                         double *Aii = A[ii];
//                         for (int kk = k; kk < dot_min; kk++) {
//                             for (int jj = j; jj < col_min; jj++) {
//                                 C[ii][jj] += Aii[kk] * B[kk][jj];
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// extern "C" {
//     void matmult_mkn_offload(int M, int N, int K, double **A, double **B, double **C) {
//         #pragma omp target teams distribute parallel for
//         for (int m = 0; m < M; m++) {
//             for (int n = 0; n < N; n++) {
//                 C[m][n] = 0.0;
//                 }
//             }

//         #pragma omp target teams distribute parallel for collapse(2)
//         for (int i = 0; i < M; i++) {
//             for (int k = 0; k < K; k++) {
//                 for (int j = 0; j < N; j++) {
//                     C[i][j] += A[i][k] * B[k][j];
//                 }
//             }
//         }
//     }
// }

// extern "C" {
//     void matmult_mnk_offload(int M, int N, int K, double **A, double **B, double **C) {
//         #pragma omp target teams distribute parallel for
//         for (int m = 0; m < M; m++) {
//             for (int n = 0; n < N; n++) {
//                 C[m][n] = 0.0;
//                 }
//             }

//         #pragma omp target teams distribute parallel for collapse(2)
//         for (int i = 0; i < M; i++) {
//             for (int j = 0; j < N; j++) {
//                 for (int k = 0; k < K; k++) {
//                     C[i][j] += A[i][k] * B[k][j];
//                 }
//             }
//         }
//     }
// }

// extern "C" {
//     void matmult_blk_offload(int M,int N,int K,double **A,double **B,double **C, int bs) {
//         #pragma omp target teams distribute parallel for
//         for (int m = 0; m < M; m++) {
//             for (int n = 0; n < N; n++) {
//                 C[m][n] = 0.0;
//                 }
//             }

//         #pragma omp target teams distribute parallel for collapse(3)
//         for (int i = 0; i < M; i += bs) {
//             int row_min = fminf(i + bs, M);
//             for (int k = 0; k < K; k += bs) {
//                 int dot_min = fminf(k + bs, K);
//                 for (int j = 0; j < N; j += bs) {
//                     int col_min = fminf(j + bs, N);
//                     for (int ii = i; ii < row_min; ii++) {
//                         double *Aii = A[ii];
//                         for (int kk = k; kk < dot_min; kk++) {
//                             for (int jj = j; jj < col_min; jj++) {
//                                 C[ii][jj] += Aii[kk] * B[kk][jj];
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// // extern "C" {
// //     void matmult_asy_offload(int M, int N, int K, double **A, double **B, double **C, int num_slabs) {
// //         #pragma omp target teams distribute parallel for
// //         for (int m = 0; m < M; m++) {
// //             for (int n = 0; n < N; n++) {
// //                 C[m][n] = 0.0;
// //                 }
// //             }
        
// //         // Assume M, N, and K are integer multiples of the number of slabs
// //         int slab_size = M / num_slabs;

// //         #pragma omp target teams distribute parallel for collapse(3)
// //         for (int slab = 0; slab < num_slabs; slab++) {
// //             // Asynchronously transfer data for the current slab
// //             int slab_start = slab * slab_size;
// //             int slab_end = slab_start + slab_size;
// //             #pragma omp target update to(A[slab_start:slab_size], B) async(slab)

// //             #pragma omp task depend(in: A[slab_start:slab_size], B) depend(out: C[slab_start:slab_size])
// //             for (int i = slab_start; i < slab_end; i++) {
// //                 for (int k = 0; k < K; k++) {
// //                     for (int j = 0; j < N; j++) {
// //                         C[i][j] += A[i][k] * B[k][j];
// //                     }
// //                 }
// //             }
// //         }
// //         #pragma omp taskwait
// //     }
// // }
