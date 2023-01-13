#ifndef _UTILS_H
#define _UTILS_H

void init_u(double ***u, int N, double start_T);
void init_f(double ***f, int N);
void init_u_omp(double ***u, int N, double start_T);
void init_f_omp(double ***f, int N);

#endif