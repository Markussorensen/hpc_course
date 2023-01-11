/* main.c - Poisson problem in 3D
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "alloc3d.h"
#include "print.h"

#ifdef _JACOBI
#include "jacobi.h"
#endif

#ifdef _GAUSS_SEIDEL
#include "gauss_seidel.h"
#endif

#define N_DEFAULT 100

int
main(int argc, char *argv[]) {

    int 	N = N_DEFAULT;
    int 	iter_max = 1000;
    double	tolerance;
    double	start_T;
    int		output_type = 0;
    char	*output_prefix = "poisson_res";
    char        *output_ext    = "";
    char	output_filename[FILENAME_MAX];
    double 	***u = NULL;


    /* get the paramters from the command line */
    N         = atoi(argv[1]);	// grid size
    iter_max  = atoi(argv[2]);  // max. no. of iterations
    tolerance = atof(argv[3]);  // tolerance
    start_T   = atof(argv[4]);  // start T for all inner grid points
    if (argc == 6) {
	output_type = atoi(argv[5]);  // ouput type
    }

    // allocate memory
    if ( (u = malloc_3d(N, N, N)) == NULL ) {
        perror("array u: allocation failed");
        exit(-1);
    }

    /*
     *
     * fill in your code here 
     *
     *
     */

    // initialize u
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            for (int k = 1; k < N; k++) {
                u[i][j][k] = start_T;
            }
        }
    }

    for (int i = 0; i < N+2; i++) {         
        for (int j = 0; j < N+2; j++) {
            u[i][N+1][j] = 20; // u(x, 1, z) = 20
            u[i][0][j] = 0; // u(x, -1, z) = 0
            u[N+1][i][j] = 20; // u(1, y, z) = 20
            u[0][i][j] = 20; // u(−1, y, z) = 20
            u[i][j][N+1] = 20; // u(x, y, 1) = 20
            u[i][j][0] = 20;// u(x, y, −1)
        }
    }


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
	    break;
	default:
	    fprintf(stderr, "Non-supported output type!\n");
	    break;
    }

    // de-allocate memory
    free_3d(u);

    return(0);
}
