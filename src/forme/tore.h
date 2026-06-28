#ifndef TORE_H
#define TORE_H

#include <math.h>
#include "../etoiles.h"
#define TORE_R1 9.f
#define TORE_R2 3.5f
#define VITESSE_ROT_TORE 45.f
#define INCL_TORE (55.f * (float)M_PI / 180.f)

void calcTore(Etoile *e);
void formeTore(Etoile *e, float d);

#endif