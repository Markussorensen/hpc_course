#include <cublas_v2.h>
#include "matmult_lib_offload.h"

void matmult_lib_offload(int m, int n, int k, double **A, double **B, double **C) {
    cublasHandle_t handle;
    cublasCreate(&handle);
    double * AA = A[0];
    double * BB = B[0];
    double * CC = C[0];
    #pragma omp target data map(tofrom: AA[0:m*k], BB[0:k*n], CC[0:m*n]) use_device_ptr(AA, BB, CC)
    {
    const double alpha = 1.0;
    const double beta = 0.0;
    cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, &alpha, AA, k, BB, n, &beta, CC, n);
    }
    cublasDestroy(handle);
}