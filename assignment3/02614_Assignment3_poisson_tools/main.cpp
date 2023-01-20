/* main.c - Poisson problem in 3D
 *
 * hpcintrogpush
module load nvhpc/22.11-nompi
module load cuda/11.8
module load gcc/11.3.0-binutils-2.38

 */
#include <stdio.h>
#include <stdlib.h>
#include "alloc3d.h"
#include "print.h"
#include "utils.h"
#include <omp.h>
#include "jacobi.h"
#include "jacobi_omp.h"
#include "jacobi_map.h"
#include "jacobi_target.h"
#include "jacobi_map_norm.h"
#include "jacobi_dual.h"

#define N_DEFAULT 100
#define TOLERANCE_DEFAULT 1e-6
#define ITER_MAX_DEFAULT 1000
#define START_T_DEFAULT 0.0

int
main(int argc, char *argv[]) {

    int 	N = N_DEFAULT;
    int 	iter_max = ITER_MAX_DEFAULT;
    double	tolerance = TOLERANCE_DEFAULT;
    double	start_T = START_T_DEFAULT;
    int		method = 0;
    double 	***u = NULL;
    double 	***u_new = NULL; 
    double  ***f = NULL;


    /* get the paramters from the command line */
    N         = atoi(argv[1]);	// grid size
    iter_max  = atoi(argv[2]);  // max. no. of iterations
    tolerance = atof(argv[3]);  // tolerance
    start_T   = atof(argv[4]);  // start T for all inner grid points
    if (argc == 6) {
	method = atoi(argv[5]);  // ouput type
    }
    
    printf("N = %d, iter_max = %d, tolerance = %f, start_T = %f, method = %d \n", N, iter_max, tolerance, start_T, method);

    // allocate memory
    if ( (u = malloc_3d(N+2, N+2, N+2)) == NULL ) {
        perror("array u: allocation failed");
        exit(-1);
    }
    if ( (u_new = malloc_3d(N+2, N+2, N+2)) == NULL ) {
        perror("array u_new: allocation failed");
        exit(-1);
    }
    if ( (f = malloc_3d(N+2, N+2, N+2)) == NULL ) {
        perror("array f: allocation failed");
        exit(-1);
    }

    // initialize u and f
    init_u(u, N, start_T);
    init_u(u_new, N, start_T);
    init_f(f, N);

    omp_set_default_device(0);
    double* device_U_new_data_arrays;
    double*** device_U_new = d_malloc_3d(N+2, N+2, N+2, &device_U_new_data_arrays);
    size_t length = (N+2) * (N+2) * (N+2) * sizeof(double);

    double* device_U_data_arrays;
    double*** device_U = d_malloc_3d(N+2, N+2, N+2, &device_U_data_arrays);

    double* device_F_data_arrays;
    double*** device_F = d_malloc_3d(N+2, N+2, N+2, &device_F_data_arrays);
    // Copy F to device

    omp_set_default_device(1);
    double* device_U_new_data_arrays1;
    double*** device_U_new1 = d_malloc_3d(N+2, N+2, N+2, &device_U_new_data_arrays1);

    double* device_U_data_arrays1;
    double*** device_U1 = d_malloc_3d(N+2, N+2, N+2, &device_U_data_arrays1);

    double* device_F_data_arrays1;
    double*** device_F1 = d_malloc_3d(N+2, N+2, N+2, &device_F_data_arrays1);
 
    switch(method) {
	case 0:
	    // no output at all
	    break;
	case 1:
	    jacobi(u, f, u_new, N, iter_max);
	    break;
    case 2:
        jacobi_omp(u, f, u_new, N, iter_max);
        break;
    case 3:
        jacobi_map(u, f, u_new, N, iter_max);
        break;
	case 4:
        // Copy U to device
        omp_target_memcpy(device_U_data_arrays, u[0][0], length, 0, 0, omp_get_default_device(), omp_get_initial_device());
        omp_target_memcpy(device_F_data_arrays, f[0][0], length, 0, 0, omp_get_default_device(), omp_get_initial_device());


        jacobi_target(device_U, device_F, device_U_new, N, iter_max);
        
        // Copy from device to host
        omp_target_memcpy(u[0][0], device_U_data_arrays, length, 0, 0, omp_get_initial_device(), omp_get_default_device());

        break;
    case 5:
        jacobi_map_norm(u, f, u_new, N, iter_max, tolerance);
        break;
    case 6:
        omp_target_memcpy(device_U_data_arrays, u[0][0], length, 0, 0, omp_get_default_device(), omp_get_initial_device());
        omp_target_memcpy(device_F_data_arrays, f[0][0], length, 0, 0, omp_get_default_device(), omp_get_initial_device());
        omp_target_memcpy(device_U_new_data_arrays, u_new[0][0], length, 0, 0, omp_get_default_device(), omp_get_initial_device());
        omp_target_memcpy(device_U_data_arrays1, u[0][0], length, 0, 0, omp_get_default_device(), omp_get_initial_device());
        omp_target_memcpy(device_F_data_arrays1, f[0][0], length, 0, 0, omp_get_default_device(), omp_get_initial_device());
        omp_target_memcpy(device_U_new_data_arrays1, u_new[0][0], length, 0, 0, omp_get_default_device(), omp_get_initial_device());

        jacobi_dual(device_U, device_U1, device_F, device_F1, device_U_new, device_U_new1, N, iter_max);

        omp_target_memcpy(u[0][0], device_U_data_arrays, length, 0, 0, omp_get_initial_device(), omp_get_default_device());


	default:
	    fprintf(stderr, "Non-supported output type!\n");
	    break;
    }

    omp_set_default_device(0);
    d_free_3d(device_U_new, device_U_new_data_arrays);
    d_free_3d(device_U, device_U_data_arrays);
    d_free_3d(device_F, device_F_data_arrays);
    omp_set_default_device(1);
    d_free_3d(device_U_new1, device_U_new_data_arrays1);
    d_free_3d(device_U1, device_U_data_arrays1);
    d_free_3d(device_F1, device_F_data_arrays1);

    // de-allocate memory
    free_3d(u);
    free_3d(f);
    free_3d(u_new);

    return(0);
}
