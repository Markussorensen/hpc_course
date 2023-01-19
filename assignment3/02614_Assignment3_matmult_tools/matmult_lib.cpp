extern "C" {
    #include <cblas.h>
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matmult_lib.h"

void matmult_lib(int m, int n, int k, double **A, double **B, double **C) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, *A, k, *B, n, 0.0, *C, n);
}
