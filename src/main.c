#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dg.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "scene.h"
#include "credits.h"
#include "audio.h"

static void init(void);
static void draw(void);
static void resize(int w, int h);
static void uploadVBO(void);
static void quit(void);

static GLfloat _dim[] = {1280, 720};
static Etoile _etoiles[NB_ETOILES];
static GLuint _vao = 0, _vbo = 0;
static GLuint _pId = 0;
static float _temps = 0.f;

int main(int argc, char **argv) {
    srand(time(NULL));

    if(!gl4duwCreateWindow(argc, argv, "Etoiles",
                            GL4DW_POS_UNDEFINED, GL4DW_POS_UNDEFINED,
                            _dim[0], _dim[1],
                            GL4DW_SHOWN | GL4DW_RESIZABLE))
        return 1;
    
    init();
    atexit(quit);
    gl4duwResizeFunc(resize);
    gl4duwDisplayFunc(draw);

    gl4duwMainLoop();

    return 0;
}

void init(void) {
    SDL_GL_SetSwapInterval(1);
    glClearColor(0.0f, 0.0f, 0.02f, 1.0f);

    gl4duGenMatrix(GL_FLOAT, "model");
    gl4duGenMatrix(GL_FLOAT, "view");
    gl4duGenMatrix(GL_FLOAT, "proj");
    gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
    gl4duGenMatrix(GL_FLOAT, "projectionMatrix");

    _pId = gl4duCreateProgram("<vs>shaders/etoiles.vs", "<fs>shaders/etoiles.fs", NULL);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, NB_ETOILES * 7 * sizeof(float), NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));

    initEtoiles(_etoiles);
    initAudio("assets/musique.ogg");
    creditsInit();
    resize(_dim[0], _dim[1]);
}

void draw(void) {
    static double pt = 0.0;
    double t = gl4dGetElapsedTime();
    float dt = (float)((t - pt) / 1000.0);
    pt = t;

    _temps += dt;
    float fade = sceneFade(_temps);
    sceneUpdate(_etoiles, _temps, dt);
    uploadVBO();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(_pId);
    glBindVertexArray(_vao);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    gl4duBindMatrix("view");
    gl4duLoadIdentityf();
    gl4duLookAtf(0.0f, 0.0f, 60.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    gl4duBindMatrix("model");
    gl4duLoadIdentityf();

    float angle = getSceneAngle();
    if(angle != 0.f) {
        gl4duRotatef(angle, 0.f, 1.f, 0.f);
    }

    gl4duSendMatrices();
    glUniform1f(glGetUniformLocation(_pId, "fade"), fade);
    glDrawArrays(GL_POINTS, 0, NB_ETOILES);
    glBindVertexArray(0);

    if(_temps >= T_CREDITS)
        creditsDraw();
}

void resize(int w, int h) {
    _dim[0] = w;
    _dim[1] = h;
    glViewport(0, 0, _dim[0], _dim[1]);

    gl4duBindMatrix("proj");
    gl4duLoadIdentityf();
    gl4duFrustumf(-1, 1, -_dim[1]/_dim[0], _dim[1]/_dim[0], 1, 500);
    gl4duBindMatrix("projectionMatrix");
    gl4duLoadIdentityf();
    gl4duFrustumf(-1, 1, -_dim[1]/(GLfloat)_dim[0], _dim[1]/(GLfloat)_dim[0], 1, 1000);
}

void uploadVBO(void) {
    float buf[NB_ETOILES * 7];
    for(int i = 0; i < NB_ETOILES; i++) {
        int base = i * 7;
        buf[base + 0] = _etoiles[i].x;
        buf[base + 1] = _etoiles[i].y;
        buf[base + 2] = _etoiles[i].z;
        buf[base + 3] = _etoiles[i].r;
        buf[base + 4] = _etoiles[i].g;
        buf[base + 5] = _etoiles[i].b;
        buf[base + 6] = _etoiles[i].taille;
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buf), buf);
}

void quit(void) {
    creditsQuit();
    gl4duClean(GL4DU_ALL);
}