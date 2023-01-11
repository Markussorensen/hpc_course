/* gauss_seidel.h - Poisson problem
 *
 */
#ifndef _GAUSS_SEIDEL_H
#define _GAUSS_SEIDEL_H

// define your function prototype here
// gauss_seidel(...);
void gauss_seidel(double ***U, double ***F, int N, int iter_max, double tolerance);

#endif
