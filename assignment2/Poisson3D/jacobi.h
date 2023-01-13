/* jacobi.h - Poisson problem 
 *
 * $Id: jacobi.h,v 1.1 2006/09/28 10:12:58 bd Exp bd $
 */

#ifndef _JACOBI_H
#define _JACOBI_H

void jacobi(double ***, double ***, double ***, int, int, double);
void jacobi_omp_simpel(double ***U, double ***F, double ***U_new, int N, int iter_max, double tolerance);
void jacobi_omp1(double ***U, double ***F, double ***U_new, int N, int iter_max, double tolerance);
void jacobi_omp2(double ***U, double ***F, double ***U_new, int N, int iter_max, double tolerance);

#endif
