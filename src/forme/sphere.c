#include <math.h>
#include "sphere.h"
#include "../utils.h"

void calcSphere(Etoile *e, int i) {
    float k = (float)i + 0.5f;
    float phi = acosf(1.f - 2.f * k / NB_ETOILES);
    float theta = (float)M_PI * (1.f + sqrtf(5.f)) * k;

    e->sx = SPHERE_R * cosf(theta) * sinf(phi);
    e->sy = SPHERE_R * cosf(phi);
    e->sz = SPHERE_R * sinf(theta) * sinf(phi);
}

void formeSphere(Etoile *e, float d) {
    for(int i = 0; i < NB_ETOILES; i++) {
        float vx = (e[i].sx - e[i].x) / d;
        float vy = (e[i].sy - e[i].y) / d;
        float vz = (e[i].sz - e[i].z) / d;
        setVitesseEtoile(&e[i], vx, vy, vz);
    }
}