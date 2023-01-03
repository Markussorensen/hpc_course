#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 20000 // Number of rows in matrices
#define N 20000 // Number of columns in matrices
#define NUM_ITERATIONS 1000000 // Number of times to perform matrix addition

int main(int argc, char *argv[]) {
    double A[M][N], B[M][N], C[M][N];
    int i, j, k;
    double elapsed_total = 0.0;
    clock_t start, end;

    // Initialize matrices A and B
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }

    start = clock();

    // Perform matrix addition NUM_ITERATIONS times
    for (k = 0; k < NUM_ITERATIONS; k++) {
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
    }

    end = clock();

    elapsed_total = (double)(end - start);
    printf("Elapsed time: %f seconds \n", elapsed_total);
    printf("Elapsed time per iteration: %f seconds \n", elapsed_total / NUM_ITERATIONS);
}