#ifndef CUBE_H
#define CUBE_H

#include "../etoiles.h"
#define CUBE_TAILLE 20.f
#define VITESSE_ROT_CUBE 45.f

void calcCube(Etoile *e, int face);
void formeCube(Etoile *e, float d);

#endif