/* main.c - Poisson problem in 3D
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "alloc3d.h"
#include "print.h"
#include "utils.h"

#ifdef _JACOBI
#include "jacobi.h"
#endif

#ifdef _GAUSS_SEIDEL
#include "gauss_seidel.h"
#endif

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
    int		output_type = 0;
    char	*output_prefix = "poisson_res";
    char	*output_f = "poisson_res_f";
    char        *output_ext    = "";
    char	output_filename[FILENAME_MAX];
    char    output_filename_f[FILENAME_MAX];
    double 	***u = NULL, ***u_new = NULL, ***f = NULL;


    /* get the paramters from the command line */
    N         = atoi(argv[1]);	// grid size
    iter_max  = atoi(argv[2]);  // max. no. of iterations
    tolerance = atof(argv[3]);  // tolerance
    start_T   = atof(argv[4]);  // start T for all inner grid points
    if (argc == 6) {
	output_type = atoi(argv[5]);  // ouput type
    }

    // allocate memory
    if ( (u = malloc_3d(N+2, N+2, N+2)) == NULL ) {
        perror("array u: allocation failed");
        exit(-1);
    }
    if ( (f = malloc_3d(N+2, N+2, N+2)) == NULL ) {
        perror("array f: allocation failed");
        exit(-1);
    }

    init_f(f, N);
    init_u(u, N, start_T);

    // solve the Poisson problem
    #ifdef _JACOBI
    if ( (u_new = malloc_3d(N+2, N+2, N+2)) == NULL ) {
        perror("array u: allocation failed");
        exit(-1);
    }
    jacobi(u, u_new, f, N, iter_max, tolerance);
    free_3d(u_new);
    output_prefix = "poisson_res_j";
    #endif

    #ifdef _GAUSS_SEIDEL
    gauss_seidel(u, f, N, iter_max, tolerance);
    output_prefix = "poisson_res_gs";
    #endif

    // dump  results if wanted 
    switch(output_type) {
	case 0:
	    // no output at all
	    break;
	case 3:
	    output_ext = ".bin";
	    sprintf(output_filename, "%s_%d%s", output_prefix, N, output_ext);
	    fprintf(stderr, "Write binary dump to %s: ", output_filename);
	    print_binary(output_filename, N, u);
	    break;
	case 4:
	    output_ext = ".vtk";
	    sprintf(output_filename, "%s_%d%s", output_prefix, N, output_ext);
	    fprintf(stderr, "Write VTK file to %s: ", output_filename);
	    print_vtk(output_filename, N, u);

	    sprintf(output_filename_f, "%s_%d%s", output_f, N, output_ext);
	    fprintf(stderr, "Write VTK file to %s: ", output_filename_f);
	    print_vtk(output_filename_f, N, f);
	    break;
	default:
	    fprintf(stderr, "Non-supported output type!\n");
	    break;
    }

    // de-allocate memory
    free_3d(u);
    free_3d(f);

    return(0);
}
