#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "jacobi_target.h"


void jacobi_target(double ***device_U, double ***device_F, double ***device_U_new, int N, int iter_max){
    double delta = 2.0 / (N + 1);
    double scalar = 1.0/6.0;
    double total_flops = 0;
    double start, end;

    double warmup = 1.0;
    #pragma omp target data map(tofrom: warmup)
    {
        warmup = warmup + 1.0;
    }

    #pragma omp target teams loop is_device_ptr(device_F)
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            for (int k = 0; k < N+2; k++) {
                device_F[i][j][k] = device_F[i][j][k] * delta * delta;
            }
        }
    }

    start = omp_get_wtime();

    for (int iter = 0; iter < iter_max; iter++) {
        // Offload Jacobi iteration to the GPU
        #pragma omp target teams loop is_device_ptr(device_U, device_U_new, device_F) collapse(3) num_teams(N*N*N/128) thread_limit(128)
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    device_U_new[i][j][k] = scalar * (device_U[i-1][j][k] + device_U[i+1][j][k] + device_U[i][j-1][k] + device_U[i][j+1][k] + device_U[i][j][k-1] + device_U[i][j][k+1] + device_F[i][j][k]);
                }
            }
        }
        // copy U_new to U on the host
        double ***U_temp = device_U;
        device_U = device_U_new;
        device_U_new = U_temp;
    }
    end = omp_get_wtime();

    total_flops = log2f(iter_max) + log2f(N) + log2f(N) + log2f(N) + log2f(7) - log2f(1000000000);
    total_flops = pow(2, total_flops);
    printf("Time: %f \n", end - start);
    printf("GFLOPS/s: %f \n", total_flops / (end - start));
}