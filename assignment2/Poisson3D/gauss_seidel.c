/* gauss_seidel.c - Poisson problem in 3d
 *
 */
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

void gauss_seidel(double ***U, double ***F, int N, int iter_max, double tolerance) {
    double se, mse, err;
    int iter;
    double delta = 2.0 / (N + 1);
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
    for (iter = 0; iter < iter_max; iter++) {
        last_iter = iter;
        se = 0.0; // Calculating sum of errors
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    double new_val = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
                    err = new_val - U[i][j][k];
                    se += err * err;
                    U[i][j][k] = new_val;
                }
            }
        }
        mse = sqrt(se / (N*N*N));
        if (mse < tolerance) {
            break;
        }
        //print mse
        // printf("iter: %d, mse: %f \n", iter, mse);
        
    }
    end = omp_get_wtime();
    total_flops = log2(last_iter) + log2(N) + log2(N) + log2(N) + log2(10) - log2(1000000000);
    total_flops = pow(2, total_flops);
    double total_s = (double)(end - start);
    double flops_pr_second = total_flops / total_s;
    printf("iter: %d, mse: %f, time: %f, total gigaflops: %f, gigaflops pr second: %f \n", last_iter, mse, total_s, total_flops, flops_pr_second);
}

//Make an omp version with the red-black method

void gauss_seidel_omp(double ***U, double ***F, int N, int iter_max, double tolerance) {
    double se, mse, err, new_val;
    int iter;
    double delta = 2.0 / (N + 1);
    double scalar = 1.0/6.0;
    int last_iter;
    double total_flops = 0;
    double start, end;
    start = omp_get_wtime();
    int i, j, k;
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            for (int k = 0; k < N+2; k++) {
                F[i][j][k] = F[i][j][k] * delta * delta;
            }
        }
    }
    for (iter = 0; iter < iter_max; iter++) {
        last_iter = iter;
        se = 0.0; // Calculating sum of errors
        #pragma omp parallel for ordered(2) reduction(+:se) private(i,j,k,err,new_val) schedule(static,1)
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                #pragma omp ordered depend(sink:i-1,j) depend(sink:i,j-1)
                for (int k = 1; k < N+1; k++) {
                    new_val = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
                    err = new_val - U[i][j][k];
                    se += err * err;
                    U[i][j][k] = new_val;
                }
                #pragma omp ordered depend(source)
            }
        }
        mse = sqrt(se / (N*N*N));
        if (mse < tolerance) {
            break;
        }
        //print mse
        
    }
    end = omp_get_wtime();
    printf("last iter %d \n", last_iter);
    total_flops = log2(last_iter) + log2(N) + log2(N) + log2(N) + log2(10) - log2(1000000000);
    total_flops = pow(2, total_flops);
    double total_s = (double)(end - start);
    double flops_pr_second = total_flops / total_s;
    printf("iter: %d, mse: %f, time: %f, total gigaflops: %f, gigaflops pr second: %f \n", last_iter, mse, total_s, total_flops, flops_pr_second);
}
