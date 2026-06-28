#include "etoiles.h"
#include "forme/cube.h"
#include "forme/tore.h"
#include "forme/sphere.h"
#include "utils.h"

void setVitesseEtoile(Etoile *e, float vx, float vy, float vz) {
    e->vx = vx;
    e->vy = vy;
    e->vz = vz;
}

void resetEtoile(Etoile *e) {
    float c = randf(0.f, 1.f);

    e->x = randf(-50.f, 50.f);
    e->y = randf(-50.f, 50.f);
    e->z = randf(-40.f, 0.f);
    e->taille = randf(1.f, 4.f);

    float v = randf(8.f, 25.f);
    setVitesseEtoile(e, 0.f, 0.f, v);
    e->vzBase = v;

    if(c < .5f) {
        e->r = 1.f;
        e->g = 1.f;
        e->b = 1.f;
    } else if(c < .75f) {
        e->r = 0.f;
        e->g = 1.f;
        e->b = 1.f;
    } else {
        e->r = 1.f;
        e->g = 0.f;
        e->b = 1.f;
    }
}

void initEtoiles(Etoile *e) {
    for(int i = 0; i < NB_ETOILES; i++) {
        resetEtoile(&e[i]);
        calcCube(&e[i], i % 6);
        calcTore(&e[i]);
        calcSphere(&e[i], i);
    }
}

void updateEtoiles(Etoile *e, float dt, int reset) {
    for(int i = 0; i < NB_ETOILES; i++) {
        e[i].x += e[i].vx * dt;
        e[i].y += e[i].vy * dt;
        e[i].z += e[i].vz * dt;

        if(reset && e[i].z > 61.f)
            resetEtoile(&e[i]);
    }
}