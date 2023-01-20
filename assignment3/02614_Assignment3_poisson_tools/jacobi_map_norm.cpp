#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "jacobi_map_norm.h"

void jacobi_map_norm(double ***U, double ***F, double ***U_new, int N, int iter_max, double tolerance) {
    // Part 8
    double delta = 2.0 / (N + 1);
    double scalar = 1.0/6.0;
    double total_flops = 0;
    double start, end;
    double se, mse, err;

    double warmup = 1.0;
    #pragma omp target data map(tofrom: warmup)
    {
        warmup = warmup + 1.0;
    }

    #pragma omp target data map(tofrom: F[0:N+2][0:N+2][0:N+2])
    {
        #pragma omp target teams distribute parallel for
        for (int i = 0; i < N+2; i++) {
            for (int j = 0; j < N+2; j++) {
                for (int k = 0; k < N+2; k++) {
                    F[i][j][k] = F[i][j][k] * delta * delta;
                }
            }
        }
    }

    start = omp_get_wtime();
    #pragma omp target data map(tofrom: U[0:N+2][0:N+2][0:N+2], U_new[0:N+2][0:N+2][0:N+2]) map(to: F[0:N+2][0:N+2][0:N+2])
    for (int iter = 0; iter < iter_max; iter++) {
        // Offload Jacobi iteration to the GPU
        se = 0.0;
        #pragma omp target teams distribute parallel for collapse(3) num_teams(N*N*N/128) thread_limit(128) reduction(+:se)
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U_new[i][j][k] = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
                    err = U_new[i][j][k] - U[i][j][k];
                    se += err * err;
                }
            }
        }
        mse = sqrt(se / (N*N*N)); 
        if (mse < tolerance) {
            break;
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


