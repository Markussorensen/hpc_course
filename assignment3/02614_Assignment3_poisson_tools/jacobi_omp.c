void
jacobi_omp(double ***U, double ***F, double ***U_new, int N, int iter_max) {
    double delta = 2.0 / (N + 1);
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
        #pragma omp parallel for private(i,j,k)
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U_new[i][j][k] = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + F[i][j][k]);
                }
            }
        }
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
    total_flops = log2(last_iter) + log2(N) + log2(N) + log2(N) + log2(7) - log2(1000000000);
    total_flops = pow(2, total_flops);
    printf("Total FLOPS: %f \n", total_flops);
    printf("Time: %f \n", end - start);
    printf("GFLOPS/s: %f \n", total_flops / (end - start));
}