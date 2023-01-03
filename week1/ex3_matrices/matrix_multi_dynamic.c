#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int M, K, N;
    double **A, **B, **C;
    int i, j, k, u;
    double elapsed_total = 0.0;
    clock_t start, end;

    // Read in the sizes of the matrices from the user
    printf("Enter the number of rows in matrix A: ");
    scanf("%d", &M);
    printf("Enter the number of columns in matrix A: ");
    scanf("%d", &K);
    printf("Enter the number of columns in matrix B: ");
    scanf("%d", &N);

    // Allocate memory for the matrices
    A = malloc(M * sizeof(double*));
    for (i = 0; i < M; i++) {
        A[i] = malloc(K * sizeof(double));
    }
    B = malloc(K * sizeof(double*));
    for (i = 0; i < K; i++) {
        B[i] = malloc(N * sizeof(double));
    }
    C = malloc(M * sizeof(double*));
    for (i = 0; i < M; i++) {
        C[i] = malloc(N * sizeof(double));
    }

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
    for (u = 0; u < 1000000; u++) {
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
    printf("Elapsed time per iteration: %f seconds \n", elapsed_total / 1000000);
}