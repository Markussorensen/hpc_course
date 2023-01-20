#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "utils.h"

void 
init_f(double ***f, int N) {
    int f_x_max = (int)ceil((5/16.0)*(N+1));
    int f_y_max = (int)ceil((1/4.0)*(N+1));
    int f_z_min = (int)ceil((1/6.0)*(N+1));
    int f_z_max = (int)ceil((1/2.0)*(N+1));
    // printf("f_x_max: %d, f_y_max: %d, f_z_min: %d, f_z_max: %d \n", f_x_max, f_y_max, f_z_min, f_z_max);
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            for (int k = 0; k < N+2; k++) {
                f[i][j][k] = 0;
            }
        }
    }
    // initialize radiator in f
    for (int i = 0; i < f_x_max; i++) {
        for (int j = 0; j < f_y_max; j++) {
            for (int k = f_z_min; k < f_z_max; k++) {
                f[i][j][k] = 200;
            }
        }
    }
}

void
init_u(double ***u, int N, double start_T) {
    // initialize u interior
    for (int i = 1; i < N+1; i++) {
        for (int j = 1; j < N+1; j++) {
            for (int k = 1; k < N+1; k++) {
                u[i][j][k] = start_T;
            }
        }
    }
    // initialize u boundary
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
}

void
init_u_omp(double ***u, int N, double start_T) {
    // initialize u interior
    int i, j, k;
    #pragma omp parallel for private(i,j,k)  schedule(static,1)
    for (int i = 1; i < N+1; i++) {
        for (int j = 1; j < N+1; j++) {
            for (int k = 1; k < N+1; k++) {
                u[i][j][k] = start_T;
            }
        }
    }
    // initialize u boundary
    #pragma omp parallel for private(i,j) schedule(static,1)
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
}

void 
init_f_omp(double ***f, int N) {
    int f_x_max = (int)ceil((5/16.0)*(N+1));
    int f_y_max = (int)ceil((1/4.0)*(N+1));
    int f_z_min = (int)ceil((1/6.0)*(N+1));
    int f_z_max = (int)ceil((1/2.0)*(N+1));
    int i, j, k;
    // printf("f_x_max: %d, f_y_max: %d, f_z_min: %d, f_z_max: %d \n", f_x_max, f_y_max, f_z_min, f_z_max);
    #pragma omp parallel for private(i,j,k) schedule(static,1)
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            for (int k = 0; k < N+2; k++) {
                f[i][j][k] = 0;
            }
        }
    }
    // initialize radiator in f
    #pragma omp parallel for private(i,j,k) schedule(static,1)
    for (int i = 0; i < f_x_max; i++) {
        for (int j = 0; j < f_y_max; j++) {
            for (int k = f_z_min; k < f_z_max; k++) {
                f[i][j][k] = 200;
            }
        }
    }
}
