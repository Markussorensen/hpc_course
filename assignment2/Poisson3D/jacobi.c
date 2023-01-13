/* jacobi.c - Poisson problem in 3d
 * 
 */
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

void
jacobi(double ***U, double ***F, double ***U_new, int N, int iter_max, double tolerance) {
    double delta = 2.0 / (N + 1);
    double se, mse, err;
    double scalar = 1.0/6.0;
    int last_iter;
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
        last_iter = iter;
        se = 0.0; //Calculating sum of errors
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U_new[i][j][k] = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
                    err = U_new[i][j][k] - U[i][j][k];
                    se += err * err;
                }
            }
        }
        mse = sqrt(se / (N*N*N)); // MSE
        if (mse < tolerance) {
            break;
        }
        //print mse
        // printf("iter: %d, mse: %f \n", iter, mse);
        

        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U[i][j][k] = U_new[i][j][k];
                }
            }
        }
    }
    end = omp_get_wtime();
    printf("last iter %d \n", last_iter);
    total_flops = log2(last_iter) + log2(N) + log2(N) + log2(N) + log2(10) - log2(1000000000);
    total_flops = pow(2, total_flops);
    double total_s = (double)(end - start);
    double flops_pr_second = total_flops / total_s;
    printf("iter: %d, mse: %f, time: %f, total gigaflops: %f, gigaflops pr second: %f \n", last_iter, mse, total_s, total_flops, flops_pr_second);
}

void
jacobi_omp_simpel(double ***U, double ***F, double ***U_new, int N, int iter_max, double tolerance) {
    double delta = 2.0 / (N + 1);
    double se, mse, err;
    double scalar = 1.0/6.0;
    int last_iter;
    double total_flops = 0;
    double start, end;
    int i, j, k;
    start = omp_get_wtime();
    // #pragma omp parallel for private(i,j,k)
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            for (int k = 0; k < N+2; k++) {
                F[i][j][k] = F[i][j][k] * delta * delta;
            }
        }
    }
    for (int iter = 0; iter < iter_max; iter++) {
        last_iter = iter;
        se = 0.0; //Calculating sum of errors
        #pragma omp parallel for private(i,j,k,err) reduction(+:se)
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U_new[i][j][k] = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
                    err = U_new[i][j][k] - U[i][j][k];
                    se += err * err;
                }
            }
        }
        mse = sqrt(se / (N*N*N)); // MSE
        if (mse < tolerance) {
            break;
        }
        //print mse
        
        #pragma omp parallel for private(i,j,k)
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U[i][j][k] = U_new[i][j][k];
                }
            }
        }
    }
    end = omp_get_wtime();
    printf("last iter %d \n", last_iter);
    total_flops = log2(last_iter) + log2(N) + log2(N) + log2(N) + log2(10) - log2(1000000000);
    total_flops = pow(2, total_flops);
    double total_s = (double)(end - start);
    double flops_pr_second = total_flops / total_s;
    printf("iter: %d, mse: %f, time: %f, total gigaflops: %f, gigaflops pr second: %f \n", last_iter, mse, total_s, total_flops, flops_pr_second);
}

void
jacobi_omp1(double ***U, double ***F, double ***U_new, int N, int iter_max, double tolerance) {
    double delta = 2.0 / (N + 1);
    double se, mse, err;
    double scalar = 1.0/6.0;
    int last_iter;
    double total_flops = 0;
    double start, end;
    int i, j, k;
    start = omp_get_wtime();
    // #pragma omp parallel for private(i,j,k)
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            for (int k = 0; k < N+2; k++) {
                F[i][j][k] = F[i][j][k] * delta * delta;
            }
        }
    }
    for (int iter = 0; iter < iter_max; iter++) {
        last_iter = iter;
        se = 0.0; //Calculating sum of errors
        #pragma omp parallel for private(i,j,k,err) reduction(+:se) schedule(dynamic)
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U_new[i][j][k] = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
                    err = U_new[i][j][k] - U[i][j][k];
                    se += err * err;
                }
            }
        }
        mse = sqrt(se / (N*N*N)); // MSE
        if (mse < tolerance) {
            break;
        }
        //print mse
        
        #pragma omp parallel for private(i,j,k) schedule(dynamic)
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U[i][j][k] = U_new[i][j][k];
                }
            }
        }
    }
    end = omp_get_wtime();
    printf("last iter %d \n", last_iter);
    total_flops = log2(last_iter) + log2(N) + log2(N) + log2(N) + log2(10) - log2(1000000000);
    total_flops = pow(2, total_flops);
    double total_s = (double)(end - start);
    double flops_pr_second = total_flops / total_s;
    printf("iter: %d, mse: %f, time: %f, total gigaflops: %f, gigaflops pr second: %f \n", last_iter, mse, total_s, total_flops, flops_pr_second);
}

void
jacobi_omp2(double ***U, double ***F, double ***U_new, int N, int iter_max, double tolerance) {
    // Added collapse(3) to the for loop
    double delta = 2.0 / (N + 1);
    double se, mse, err;
    double scalar = 1.0/6.0;
    int last_iter;
    double total_flops = 0;
    double start, end;
    int i, j, k;
    start = omp_get_wtime();
    // #pragma omp parallel for private(i,j,k)
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            for (int k = 0; k < N+2; k++) {
                F[i][j][k] = F[i][j][k] * delta * delta;
            }
        }
    }
    for (int iter = 0; iter < iter_max; iter++) {
        last_iter = iter;
        se = 0.0; //Calculating sum of errors
        #pragma omp parallel for private(i,j,k,err) reduction(+:se) collapse(3)
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U_new[i][j][k] = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
                    err = U_new[i][j][k] - U[i][j][k];
                    se += err * err;
                }
            }
        }
        mse = sqrt(se / (N*N*N)); // MSE
        if (mse < tolerance) {
            break;
        }
        //print mse
        
        #pragma omp parallel for private(i,j,k) collapse(3)
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U[i][j][k] = U_new[i][j][k];
                }
            }
        }
    }
    end = omp_get_wtime();
    printf("last iter %d \n", last_iter);
    total_flops = log2(last_iter) + log2(N) + log2(N) + log2(N) + log2(10) - log2(1000000000);
    total_flops = pow(2, total_flops);
    double total_s = (double)(end - start);
    double flops_pr_second = total_flops / total_s;
    printf("iter: %d, mse: %f, time: %f, total gigaflops: %f, gigaflops pr second: %f \n", last_iter, mse, total_s, total_flops, flops_pr_second);
}

// void
// jacobi_omp2(double ***U, double ***F, double ***U_new, int N, int iter_max, double tolerance) {
//     // 
//     double delta = 2.0 / (N + 1);
//     double se, mse, err;
//     double scalar = 1.0/6.0;
//     int last_iter;
//     double total_flops = 0;
//     double start, end;
//     start = omp_get_wtime();
//     // #pragma omp parallel for private(i,j,k)
//     #pragma omp parallel shared(U, F, U_new)
//     {
//         printf("Number of threads: %d \n", omp_get_num_threads());
//         #pragma omp for private(i,j,k)
//         for (int i = 0; i < N+2; i++) {
//             for (int j = 0; j < N+2; j++) {
//                 for (int k = 0; k < N+2; k++) {
//                     F[i][j][k] = F[i][j][k] * delta * delta;
//                 }
//             }
//         }
//         for (int iter = 0; iter < iter_max; iter++) {
//             last_iter = iter;
//             se = 0.0; //Calculating sum of errors
//             #pragma omp for private(i,j,k) reduction(+:se) schedule(static)
//             for (int i = 1; i < N+1; i++) {
//                 for (int j = 1; j < N+1; j++) {
//                     for (int k = 1; k < N+1; k++) {
//                         U_new[i][j][k] = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
//                         err = U_new[i][j][k] - U[i][j][k];
//                         se += err * err;
//                     }
//                 }
//             }
//             mse = sqrt(se / (N*N*N)); // MSE
//             if (mse < tolerance) {
//                 break;
//             }
//             //print mse
            
//             #pragma omp for private(i,j,k) schedule(dynamic)
//             for (int i = 1; i < N+1; i++) {
//                 for (int j = 1; j < N+1; j++) {
//                     for (int k = 1; k < N+1; k++) {
//                         U[i][j][k] = U_new[i][j][k];
//                     }
//                 }
//             }
//         }
//     }
//     end = omp_get_wtime();
//     printf("iter: %d, mse: %f, time: %f \n", last_iter, mse, end - start);
// }

    // end = omp_get_wtime();
    // total_flops = log(last_iter) + log(N) + log(N) + log(N) + log(10) - log(1000000);
    // total_flops = pow(10, total_flops);
    // int flops_pr_iter = N*N*N*10;
    // double flops_pr_second = (double)total_flops / ((double)(end - start)/CLOCKS_PER_SEC);
    // printf("iter: %d, mse: %f, time: %f, total megaflops: %d, megaflops pr iteration: %d, megaflops pr second: %f \n", last_iter, mse, (double)(end - start)/CLOCKS_PER_SEC), total_flops, flops_pr_iter, flops_pr_second;