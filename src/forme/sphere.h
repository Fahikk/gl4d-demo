#ifndef SPHERE_H
#define SPHERE_H

#include "../etoiles.h"
#define SPHERE_R 12.f
#define VITESSE_ROT_SPHERE 45.f

void calcSphere(Etoile *e, int i);
void formeSphere(Etoile *e, float d);

#endif