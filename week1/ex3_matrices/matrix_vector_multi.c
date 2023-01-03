#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 3 // Number of rows in matrices
#define N 2 // Number of columns in matrices
#define NUM_ITERATIONS 1000000 // Number of times to perform matrix addition

int main(int argc, char *argv[]) {
    double A[M][N], B[1][N], C[1][M];
    int i, j, k;
    double elapsed_total = 0.0;
    clock_t start, end;

    // Initialize matrices A and B
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[0][j] = (double)rand() / (double)RAND_MAX;
        }
        C[0][i] = 0.0;
    }

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < N; i++) {
        printf("%f ", B[0][i]);
    }
    printf("\n");
    for (i = 0; i < N; i++) {
        C[0][i] = 0.0;
    }
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            C[0][i] = C[0][i] + A[i][j] * B[0][j];
        }
    }

    for (i = 0; i < M; i++) {
        printf("%f ", C[0][i]);
    }

    printf("\n");
    
    start = clock();

    // Perform matrix addition NUM_ITERATIONS times
    for (k = 0; k < NUM_ITERATIONS; k++) {
        for (i = 0; i < N; i++) {
            C[0][i] = 0.0;
        }
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                C[0][i] = C[0][i] + A[i][j] * B[0][j];
            }
        }
    }

    end = clock();

    elapsed_total = (double)(end - start);
    printf("Elapsed time: %f seconds \n", elapsed_total);
    printf("Elapsed time per iteration: %f seconds \n", elapsed_total / NUM_ITERATIONS);
}