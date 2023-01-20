#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "jacobi_map.h"

void jacobi_map(double ***U, double ***F, double ***U_new, int N, int iter_max) {
    double delta = 2.0 / (N + 1);
    double scalar = 1.0/6.0;
    double total_flops = 0;
    double start, end;

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
    {
        for (int iter = 0; iter < iter_max; iter++) {
            // Offload Jacobi iteration to the GPU
            #pragma omp target teams distribute parallel for collapse(3) num_teams(N*N*N/128) thread_limit(128)
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
    }
    end = omp_get_wtime();

    total_flops = log2f(iter_max) + log2f(N) + log2f(N) + log2f(N) + log2f(7) - log2f(1000000000);
    total_flops = pow(2, total_flops);
    printf("Time: %f \n", end - start);
    printf("GFLOPS/s: %f \n", total_flops / (end - start));
}



// void jacobi_map(double ***U, double ***F, double ***U_new, int N, int iter_max) {
//     double delta = 2.0 / (N + 1);
//     double scalar = 1.0/6.0;
//     double total_flops = 0;
//     double start, end;
//     int i, j, k;

//     double warmup = 1.0;
//     #pragma omp target data map(tofrom: warmup)
//     {
//         warmup = warmup + 1.0;
//     }
    
//     start = omp_get_wtime();

//     #pragma omp target teams distribute parallel for collapse(2)
//     for (int i = 0; i < N+2; i++) {
//         for (int j = 0; j < N+2; j++) {
//             for (int k = 0; k < N+2; k++) {
//                 F[i][j][k] = F[i][j][k] * delta * delta;
//             }
//         }
//     }

//     for (int iter = 0; iter < iter_max; iter++) {
//         // Offload Jacobi iteration to the GPU
//         #pragma omp target teams loop map(from: U_new[0:N+2][0:N+2][0:N+2]) map(to: U[0:N+2][0:N+2][0:N+2], F[0:N+2][0:N+2][0:N+2]) \
//         collapse(3) num_teams(108) thread_limit(128)
//         {
//         for (int i = 1; i < N+1; i++) {
//             for (int j = 1; j < N+1; j++) {
//                 for (int k = 1; k < N+1; k++) {
//                     U_new[i][j][k] = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
//                 }
//             }
//         }
//         }

//         // double ***tmp = U;
//         // U = U_new;
//         // U_new = tmp;
//         // copy U_new to U on the host
//         #pragma omp target teams distribute parallel for collapse(3)
//             for (int i = 1; i < N+1; i++) {
//                 for (int j = 1; j < N+1; j++) {
//                     for (int k = 1; k < N+1; k++) {
//                         U[i][j][k] = U_new[i][j][k];
//                     }
//                 }
//             }
//     }
//     end = omp_get_wtime();

//     total_flops = log2f(iter_max) + log2f(N) + log2f(N) + log2f(N) + log2f(7) - log2f(1000000000);
//     total_flops = pow(2, total_flops);
//     printf("Total FLOPS: %f \n", total_flops);
//     printf("Time: %f \n", end - start);
//     printf("GFLOPS/s: %f \n", total_flops / (end - start));
// }










// void jacobi_map(double *U, double *F, double *U_new, int N, int iter_max) {
//     double delta = 2.0 / (N + 1);
//     double scalar = 1.0/6.0;
//     int last_iter;
//     double total_flops = 0;
//     double start, end;
//     int i, j, k;
//     start = omp_get_wtime();
//     // Offload F calculation to the GPU
//     #pragma omp target map(to: F[:N*N*N]) map(from: F[:N*N*N])
//     {
//         for (int i = 0; i < N*N*N; i++) {
//             F[i] = F[i] * delta * delta;
//         }
//     }
//     for (int iter = 0; iter < iter_max; iter++) {
//         last_iter = iter;
//         // Offload Jacobi iteration to the GPU
//         #pragma omp target map(to: U[:N*N*N]) map(from: U_new[:N*N*N])
//         {
//             for (int i = 1; i < N+1; i++) {
//                 for (int j = 1; j < N+1; j++) {
//                     for (int k = 1; k < N+1; k++) {
//                         int idx = i*(N+2)*(N+2) + j*(N+2) + k;
//                         U_new[idx] = scalar * (U[idx-1] + U[idx+1] + U[idx-(N+2)] + U[idx+(N+2)] + U[idx-(N+2)*(N+2)] + U[idx+(N+2)*(N+2)] + F[idx]);
//                     }
//                 }
//             }
//         }
//         // copy U_new to U on the host
//         #pragma omp target map(to: U_new[:N*N*N]) map(from: U[:N*N*N])
//         {
//             for (int i = 0; i < N*N*N; i++) {
//                 U[i] = U_new[i];
//             }
//         }
//     }
//     end = omp_get_wtime();
//     printf("last iter %d \n", last_iter);
//     total_flops = log2f(last_iter) + log2f(N) + log2f(N) + log2f(N) + log2f(7) - log2f(1000000000);
//     total_flops = pow(2, total_flops);
//     printf("Total FLOPS: %f \n", total_flops);
//     printf("Time: %f \n", end - start);
//     printf("GFLOPS/s: %f \n", total_flops / (end - start));
// }