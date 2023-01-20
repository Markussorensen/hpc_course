#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matmult_asy_offload.h"

#ifndef _TEAMS
#define _TEAMS 256
#endif

#ifndef _THREADS
#define _THREADS 32
#endif

void matmult_asy_offload(int M, int N, int K, double **A, double **B, double **C) {
    double warmup = 1.0;
    const int num_slabs = 16;
    double t1, t2, t3, t4;

    #pragma omp target data map(tofrom: warmup)
    {
        warmup = warmup + 1.0;
    }
    t1 = omp_get_wtime();
    #pragma omp target enter data map(alloc: A[0:M][0:K], B[0:K][0:N], C[0:K][0:N])
    #pragma omp target update to(B[0:K][0:N])
    #pragma omp target teams distribute parallel for
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            C[m][n] = 0.0;
            }
        }

    int slab_size = M / num_slabs;
    #pragma omp parallel for
    for (int slab = 0; slab < num_slabs; slab++) {

        int m_start = slab * slab_size;
        int m_end = m_start + slab_size;
        #pragma omp target update to(A[m_start:slab_size][0:K]) depend(out: A) nowait
        #pragma omp target teams distribute parallel for collapse(2) nowait depend(in: A) depend(out: C) num_teams(_TEAMS) thread_limit(_THREADS)
        for (int m = m_start; m < m_end; m++) {
            for (int n = 0; n < N; n++) {
                for (int k = 0; k < K; k++) {
                    C[m][n] += A[m][k] * B[k][n];
                }
            }
        }
        #pragma omp target update from(C[m_start:slab_size][0:N]) depend(in: C) nowait
    }
    #pragma omp taskwait
    #pragma omp target exit data map(delete: A, B, C)

    t2 = omp_get_wtime();
    printf("Time: %f  \n", t2 - t1);
}




















// void matmult_asy_offload(int M, int N, int K, double **A, double **B, double **C) {
//     double warmup = 1.0;
//     const int num_slabs = 10;
//     #pragma omp target data map(tofrom: warmup)
//     {
//         warmup = warmup + 1.0;
//     }
    
//     #pragma omp target data map(tofrom: C[0:M][0:N])
//     {
//         #pragma omp target teams distribute parallel for
//         for (int m = 0; m < M; m++) {
//             for (int n = 0; n < N; n++) {
//                 C[m][n] = 0.0;
//                 }
//             }
//     }
    
//     // Assume M, N, and K are integer multiples of the number of slabs
//     int slab_size = M / num_slabs;
//     #pragma omp target enter data map(alloc: A[0:M][0:K], C[0:M][0:N])
//     #pragma omp target data map(to: B[0:K][0:N]) map(from: C[0:M][0:N])
//     {
//         for (int slab = 0; slab < num_slabs; slab++) {
//             // Asynchronously transfer data for the current slab
//             int slab_start = slab * slab_size;
//             int slab_end = slab_start + slab_size;
//             #pragma omp target update map (to: A[slab_start:slab_size][0:K]) map (from: C[slab_start:slab_size][0:N]) nowait depend(out: A[slab_start:slab_size][0:K])
//             // Compute the current slab
//             #pragma omp target teams distribute parallel for collapse(1) nowait depend(in: A[slab_start:slab_size][0:K])
//             for (int i = slab_start; i < slab_end; i++) {
//                 for (int j = 0; j < N; j++) {
//                     for (int k = 0; k < K; k++) {
//                         C[i][j] += A[i][k] * B[k][j];
//                     }
//                 }
//             }
            
//         }
//         #pragma omp taskwait
//     }
//     #pragma omp target exit data map(release: A[0:M][0:K], C[0:M][0:N])
// }
















// void matmult_asy_offload(int M, int N, int K, double **A, double **B, double **C) {
//     double warmup = 1.0;
//     const int num_slabs = 10;
//     #pragma omp target data map(tofrom: warmup)
//     {
//         warmup = warmup + 1.0;
//     }
    
//     #pragma omp target data map(tofrom: C[0:M][0:N])
//     {
//         #pragma omp target teams distribute parallel for
//         for (int m = 0; m < M; m++) {
//             for (int n = 0; n < N; n++) {
//                 C[m][n] = 0.0;
//                 }
//             }
//     }
    
//     // Assume M, N, and K are integer multiples of the number of slabs
//     int slab_size = M / num_slabs;

//     for (int slab = 0; slab < num_slabs; slab++) {
//         // Asynchronously transfer data for the current slab
//         int slab_start = slab * slab_size;
//         int slab_end = slab_start + slab_size;
//         // Compute the current slab
//         #pragma omp target data map(to: A[slab_start:slab_size][0:K], B[0:K][0:N]) map(from: C[slab_start:slab_size][0:N]) depend(in: A[slab_start:slab_size][0:K], B[0:K][0:N])
//         {
//             #pragma omp target teams distribute parallel for collapse(1) nowait depend(out: C[slab_start:slab_size][0:N])
//             for (int i = slab_start; i < slab_end; i++) {
//                 for (int j = 0; j < N; j++) {
//                     for (int k = 0; k < K; k++) {
//                         C[i][j] += A[i][k] * B[k][j];
//                     }
//                 }
//             }
//         }
//     }
// }

// //         #pragma omp target data map(to: A[slab_start:slab_size][0:K], B[0:K][0:N]) map(from: C[slab_start:slab_size][0:N]) depend(in: A[slab_start:slab_size][0:K], B[0:K][0:N]) {
// //             #pragma omp target teams loop distribute parallel for collapse(1) nowait //depend(out: C[slab_start:slab_size][0:N]) nowait
// //             for (int i = slab_start; i < slab_end; i++) {
// //                 for (int j = 0; j < N; j++) {
// //                     for (int k = 0; k < K; k++) {
// //                         C[i][j] += A[i][k] * B[k][j];
// //                     }
// //                 }
// //             }
// //         }
// //     }
// // }

