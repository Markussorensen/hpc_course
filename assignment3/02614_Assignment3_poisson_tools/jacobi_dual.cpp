#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "jacobi_dual.h"

void jacobi_dual(double ***device_U0, double ***device_U1, double ***device_F0, double ***device_F1, double ***device_U_new0, double ***device_U_new1, int N, int iter_max){
    double delta = 2.0 / (N + 1);
    double scalar = 1.0/6.0;
    double total_flops = 0;
    double start, end;

    double warmup = 1.0;
    #pragma omp target data map(tofrom: warmup)
    {
        warmup = warmup + 1.0;
    }

    #pragma omp target teams loop is_device_ptr(device_F0)
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            for (int k = 0; k < N+2; k++) {
                device_F0[i][j][k] = device_F0[i][j][k] * delta * delta;
            }
        }
    }
    #pragma omp target teams loop is_device_ptr(device_F1)
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            for (int k = 0; k < N+2; k++) {
                device_F1[i][j][k] = device_F1[i][j][k] * delta * delta;
            }
        }
    }

    cudaSetDevice(0);
    cudaDeviceEnablePeerAccess(1, 0); // (dev 1, future flag)
    cudaSetDevice(1);
    cudaDeviceEnablePeerAccess(0, 0); // (dev 0, future flag)

    start = omp_get_wtime();

    for (int iter = 0; iter < iter_max; iter++) {
        // Offload Jacobi iteration to the GPU
        #pragma omp target teams loop is_device_ptr(device_U0, device_U1, device_F0, device_F1, device_U_new0, device_U_new1) collapse(3) num_teams(N*N*N/128) thread_limit(128) device(0)
        for (int i = 1; i < N/2+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    device_U_new0[i][j][k] = scalar * (device_U0[i-1][j][k] + device_U0[i+1][j][k] + device_U0[i][j-1][k] + device_U0[i][j+1][k] + device_U0[i][j][k-1] + device_U0[i][j][k+1] + device_F0[i][j][k]);
                }
            }
        }
        #pragma omp target teams loop is_device_ptr(device_U0, device_U1, device_F0, device_F1, device_U_new0, device_U_new1) collapse(3) num_teams(N*N*N/128) thread_limit(128) device(1)
        for (int i = N/2+1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    device_U_new1[i][j][k] = scalar * (device_U1[i-1][j][k] + device_U1[i+1][j][k] + device_U1[i][j-1][k] + device_U1[i][j+1][k] + device_U1[i][j][k-1] + device_U1[i][j][k+1] + device_F1[i][j][k]);
                }
            }
        }
        #pragma omp taskwait
        // copy U_new to U on the host
        double ***U_temp = device_U0;
        device_U0 = device_U_new0;
        device_U_new0 = U_temp;
        U_temp = device_U1;
        device_U1 = device_U_new1;
        device_U_new1 = U_temp;
    }
    end = omp_get_wtime();

    total_flops = log2f(iter_max) + log2f(N) + log2f(N) + log2f(N) + log2f(7) - log2f(1000000000);
    total_flops = pow(2, total_flops);
    printf("Time: %f \n", end - start);
    printf("GFLOPS/s: %f \n", total_flops / (end - start));
}