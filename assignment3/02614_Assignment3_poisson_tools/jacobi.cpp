#include <math.h>
#include <omp.h>
#include <stdio.h>
#include "jacobi.h"

void
jacobi(double ***U, double ***F, double ***U_new, int N, int iter_max) {
    double delta = 2.0 / (N + 1);
    double scalar = 1.0/6.0;
    double total_flops = 0;
    double start, end;

    start = omp_get_wtime();

    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            for (int k = 0; k < N+2; k++) {
                F[i][j][k] = F[i][j][k] * delta * delta;
            }
        }
    }
    for (int iter = 0; iter < iter_max; iter++) {
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U_new[i][j][k] = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
                }
            }
        }

        double ***U_temp = U;
        U = U_new;
        U_new = U_temp;
    }
    end = omp_get_wtime();
    
    total_flops = log2f(iter_max) + log2f(N) + log2f(N) + log2f(N) + log2f(7) - log2f(1000000000);
    total_flops = pow(2, total_flops);
    printf("Time: %f \n", end - start);
    printf("GFLOPS/s: %f \n", total_flops / (end - start));
}