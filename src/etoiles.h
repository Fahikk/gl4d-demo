#ifndef ETOILES_H
#define ETOILES_H

#define NB_ETOILES 3000

typedef struct {
    float x, y, z;
    float r, g, b;
    float taille;
    float vx, vy, vz;
    float vzBase;
    float cx, cy, cz;
    float tx, ty, tz;
    float sx, sy, sz;
} Etoile;

void setVitesseEtoile(Etoile *e, float vx, float vy, float vz);
void resetEtoile(Etoile *e);
void updateEtoiles(Etoile *e, float dt, int reset);
void initEtoiles(Etoile *e);

#endif