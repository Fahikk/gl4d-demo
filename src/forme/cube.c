#include <math.h>
#include "cube.h"
#include "../utils.h"

void calcCube(Etoile *e, int face) {
    float h = CUBE_TAILLE / 2.f;
    float u = randf(-h, h);
    float v = randf(-h, h);

    switch (face) {
        case 0: e->cx =  h; e->cy =  u; e->cz =  v; break;
        case 1: e->cx = -h; e->cy =  u; e->cz =  v; break;
        case 2: e->cx =  u; e->cy =  h; e->cz =  v; break;
        case 3: e->cx =  u; e->cy = -h; e->cz =  v; break;
        case 4: e->cx =  u; e->cy =  v; e->cz =  h; break;
        case 5: e->cx =  u; e->cy =  v; e->cz = -h; break;
    }
}

void formeCube(Etoile *e, float d) {
    for(int i = 0; i < NB_ETOILES; i++) {
        float vx = (e[i].cx - e[i].x) / d;
        float vy = (e[i].cy - e[i].y) / d;
        float vz = (e[i].cz - e[i].z) / d;
        setVitesseEtoile(&e[i], vx, vy, vz);
    }
}