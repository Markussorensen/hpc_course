#include "data.h"
#include <math.h>
#include <stdlib.h>

#ifdef ARRAY_OF_STRUCTS
double 
distcheck(particle_t *p, int n) {

    double dist = -99.0;

    if (n <= 0 || p == NULL) {
        return dist;
    }

    dist = 0.0;

    for (int i = 0; i < n; i++) {
        dist += p[i].dist;
    }

    return dist;
}
#else
double 
distcheck(particle_t p, int n) {

    double dist = -99.0;

    if (n <= 0 || p.dist == NULL) {
        return dist;
    }

    dist = 0.0;

    for (int i = 0; i < n; i++) {
        dist += p.dist[i];
    }

    return dist;
}
#endif
