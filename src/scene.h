#ifndef SCENE_H
#define SCENE_H

#include "etoiles.h"

#define T_VOL 5.f
#define T_ARRET 8.f
#define T_FORM_CUBE 10.f
#define T_ROT_CUBE 15.f
#define T_IMPL_CUBE 17.f
#define T_FORM_TORE 20.f
#define T_ROT_TORE 25.f
#define T_IMPL_TORE 27.f
#define T_FORM_SPHERE 30.f
#define T_ROT_SPHERE 35.f
#define T_EXPLOSION 38.f
#define T_CREDITS 33.f
#define T_FIN 50.f

void sceneUpdate(Etoile *e, float t, float dt);
float sceneFade(float t);
float getSceneAngle();

#endif