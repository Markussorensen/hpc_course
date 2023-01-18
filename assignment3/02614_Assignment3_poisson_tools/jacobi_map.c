void jacobi_map(double *U, double *F, double *U_new, int N, int iter_max) {
    double delta = 2.0 / (N + 1);
    double scalar = 1.0/6.0;
    int last_iter;
    double total_flops = 0;
    double start, end;
    int i, j, k;
    start = omp_get_wtime();
    // Offload F calculation to the GPU
    #pragma omp target map(to: F[:N*N*N]) map(from: F[:N*N*N])
    {
        for (int i = 0; i < N*N*N; i++) {
            F[i] = F[i] * delta * delta;
        }
    }
    for (int iter = 0; iter < iter_max; iter++) {
        last_iter = iter;
        // Offload Jacobi iteration to the GPU
        #pragma omp target map(to: U[:N*N*N]) map(from: U_new[:N*N*N])
        {
            for (int i = 1; i < N+1; i++) {
                for (int j = 1; j < N+1; j++) {
                    for (int k = 1; k < N+1; k++) {
                        int idx = i*(N+2)*(N+2) + j*(N+2) + k;
                        U_new[idx] = scalar * (U[idx-1] + U[idx+1] + U[idx-(N+2)] + U[idx+(N+2)] + U[idx-(N+2)*(N+2)] + U[idx+(N+2)*(N+2)] + F[idx]);
                    }
                }
            }
        }
        // copy U_new to U on the host
        #pragma omp target map(to: U_new[:N*N*N]) map(from: U[:N*N*N])
        {
            for (int i = 0; i < N*N*N; i++) {
                U[i] = U_new[i];
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