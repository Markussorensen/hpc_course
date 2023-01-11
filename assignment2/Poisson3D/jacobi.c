/* jacobi.c - Poisson problem in 3d
 * 
 */
#include <math.h>
#include <stdio.h>

void
jacobi(double ***U, double ***F, double ***U_new, int N, int iter_max, double tolerance) {
    double delta = 2.0 / (N + 1);
    double se, mse;
    double scalar = 1.0/6.0;
    for (int iter = 0; iter < iter_max; iter++) {
        se = 0.0; //Calculating sum of errors
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U_new[i][j][k] = scalar * (U[i-1][j][k] + U[i+1][j][k] + U[i][j-1][k] + U[i][j+1][k] + U[i][j][k-1] + U[i][j][k+1] + delta*delta*F[i][j][k]);
                    se += (U_new[i][j][k] - U[i][j][k]) * (U_new[i][j][k] - U[i][j][k]);
                }
            }
        }
        mse = sqrt(se / (N*N*N)); // MSE
        if (mse < tolerance) {
            break;
        }
        //print mse
        
        //printf("iter: %d, mse: %f \n", iter, mse);

        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                for (int k = 1; k < N+1; k++) {
                    U[i][j][k] = U_new[i][j][k];
                }
            }
        }
    }
}
