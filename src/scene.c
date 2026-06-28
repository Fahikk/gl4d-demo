#include "scene.h"
#include "etoiles.h"
#include "forme/cube.h"
#include "forme/tore.h"
#include "forme/sphere.h"
#include "utils.h"

static int explCube = 0;
static int explTore = 0;
static int explFinale = 0;
static float angle = 0.f;

float getSceneAngle() {
    return angle;
}

void rotationScene(Etoile *e, float dt, float vitesse) {
    for(int i = 0; i < NB_ETOILES; i++)
        setVitesseEtoile(&e[i], 0.f, 0.f, 0.f);
    angle += dt * vitesse;
}

void explosion(Etoile *e, float speedMin, float speedMax) {
    for(int n = 0; n < NB_ETOILES; n++) {
        float i = randf(0.f, (float)M_PI);
        float a = randf(0.f, 2.f * (float)M_PI);
        float speed = randf(speedMin, speedMax);

        float vx = speed * sinf(i) * cosf(a);
        float vy = speed * cosf(i);
        float vz = speed * sinf(i) * sinf(a);
        setVitesseEtoile(&e[n], vx, vy, vz);
    }

    angle = 0.f;
}

float sceneFade(float t) {
    if(t < 3.f)
        return t / 3.f;
    else if(t < T_EXPLOSION)
        return 1.f;
    else if(t < T_CREDITS)
        return 1.f - (t - T_EXPLOSION) / (T_CREDITS - T_EXPLOSION);
    return 0.f;
}

void sceneUpdate(Etoile *e, float t, float dt) {
    if(t < T_VOL) {}
    else if(t < T_ARRET) {
        float p = (t - T_VOL) / (T_ARRET - T_VOL);
        float coef = (1.f - p) * (1.f - p);

        for(int i = 0; i < NB_ETOILES; i++)
            setVitesseEtoile(&e[i], 0.f, 0.f, e[i].vzBase * coef);

    } else if(t < T_FORM_CUBE) {
        float d = T_FORM_CUBE - t;
        if(d < dt) d = dt;
        formeCube(e, d);

    } else if(t < T_ROT_CUBE) {
        rotationScene(e, dt, VITESSE_ROT_CUBE);

    } else if(t < T_IMPL_CUBE) {
        if(!explCube) {
            explosion(e, 20.f, 50.f);
            explCube = 1;
        }

    } else if(t < T_FORM_TORE) {
        float d = T_FORM_TORE - t;
        if(d < dt) d = dt;
        formeTore(e, d);

    } else if(t < T_ROT_TORE) {
        rotationScene(e, dt, VITESSE_ROT_TORE);

    } else if(t < T_IMPL_TORE) {
        if(!explTore) {
            explosion(e, 20.f, 50.f);
            explTore = 1;
        }

    } else if(t < T_FORM_SPHERE) {
        float d = T_FORM_SPHERE - t;
        if(d < dt) d = dt;
        formeSphere(e, d);

    } else if(t < T_ROT_SPHERE) {
        rotationScene(e, dt, VITESSE_ROT_SPHERE);

    } else if(t < T_EXPLOSION) {
        if(!explFinale) {
            explosion(e, 30.f, 100.f);
            explFinale = 1;
        }

    } else if(t >= T_FIN) {
        exit(0);
    }

    int reset = (t < T_VOL);
    updateEtoiles(e, dt, reset);
}