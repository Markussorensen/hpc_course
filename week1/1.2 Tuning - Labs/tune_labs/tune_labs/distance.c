#include "data.h"
#include <math.h>
#include <stdlib.h>

#ifdef ARRAY_OF_STRUCTS
double 
distance(particle_t *p, int n) {
    
    double dist = -99.0;
    
    if (n <= 0 || p == NULL) {
        return dist;
    }

    dist = 0.0;

    for (int i = 0; i < n; i++) {
        p[i].dist = sqrt(p[i].x * p[i].x + p[i].y * p[i].y + p[i].z * p[i].z);
        dist += p[i].dist;
    }

    return dist;
}
#else
double 
distance(particle_t p, int n) {

    double dist = -99.0;

    if (n <= 0 || p.x == NULL || p.y == NULL || p.z == NULL) {
        return dist;
    }

    dist = 0.0;

    for (int i = 0; i < n; i++) {
        p.dist[i] = sqrt(p.x[i] * p.x[i] + p.y[i] * p.y[i] + p.z[i] * p.z[i]);
        dist += p.dist[i];
    }

    return dist;
}
#endif
