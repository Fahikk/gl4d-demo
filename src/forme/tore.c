#include <math.h>
#include "tore.h"
#include "../utils.h"

void calcTore(Etoile *e) {
    float phi = randf(0.f, 2.f * (float)M_PI);
    float theta = randf(0.f, 2.f * (float)M_PI);

    e->tx = (TORE_R2 * cosf(theta) + TORE_R1) * cosf(phi);
    e->ty = TORE_R2 * sinf(theta);
    e->tz = (TORE_R2 * cosf(theta) + TORE_R1) * sinf(phi);

    float cosI = cosf(INCL_TORE);
    float sinI = sinf(INCL_TORE);
    float dy = e->ty;
    float dz = e->tz;
    e->ty = dy * cosI - dz * sinI;
    e->tz = dy * sinI + dz * cosI;
}

void formeTore(Etoile *e, float d) {
    for (int i = 0; i < NB_ETOILES; i++) {
        float vx = (e[i].tx - e[i].x) / d;
        float vy = (e[i].ty - e[i].y) / d;
        float vz = (e[i].tz - e[i].z) / d;
        setVitesseEtoile(&e[i], vx, vy, vz);
    }
}