#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 3 // Number of rows in matrix1
#define K 5 // Number of columns in matrix1 and rows in matrix2
#define N 2 // Number of columns in matrix2
#define NUM_ITERATIONS 1000000 // Number of times to perform matrix addition

int main(int argc, char *argv[]) {
    double A[M][K], B[K][N], C[M][N];
    int i, j, k, u;
    double elapsed_total = 0.0;
    clock_t start, end;

    // Initialize matrices A and B
    for (i = 0; i < M; i++) {
        for (j = 0; j < K; j++) {
            A[i][j] = 10 * (i+1) + j+1;
        }
    }
    for (i = 0; i < K; i++) {
        for (j = 0; j < N; j++) {
            B[i][j] = 20 * (i+1) + j+1;
        }
    }
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0.0;
        }
    }

    for (i = 0; i < M; i++) {
        for (j = 0; j < K; j++) {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < K; i++) {
        for (j = 0; j < N; j++) {
            printf("%f ", B[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < K; k++) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%f ", C[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    
    start = clock();

    // Perform matrix addition NUM_ITERATIONS times
    for (u = 0; u < NUM_ITERATIONS; u++) {
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                for (k = 0; k < K; k++) {
                    C[i][j] = C[i][j] + A[i][k] * B[k][j];
                }
            }
        }
    }

    end = clock();

    elapsed_total = (double)(end - start);
    printf("Elapsed time: %f seconds \n", elapsed_total);
    printf("Elapsed time per iteration: %f seconds \n", elapsed_total / NUM_ITERATIONS);
}