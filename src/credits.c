#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4duw_SDL2.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "credits.h"

static GLuint _pId = 0;
static GLuint _quad = 0;
static GLuint _textTexId = 0;

static void initText(GLuint *ptId, const char *text);

void creditsInit(void) {
    _pId = gl4duCreateProgram("<vs>shaders/credits.vs", "<fs>shaders/credits.fs", NULL);
    _quad = gl4dgGenQuadf();

    initText(&_textTexId,
        "DEMO - ETOILES\n\n\n"
        "API8 - Track DemoMaker 64Mo\n"
        "Universite Paris 8\n\n\n"
        "Developpement :\n"
        "Fahik\n\n\n"
        "Bibliotheques :\n"
        "OpenGL\n"
        "GL4Dummies\n"
        "SDL2 / SDL2_ttf / SDL2_mixer\n\n\n"
        "Musique :\n"
        "L'Etoile danse - by Meydan\n"
        "Licence Creative Commons CC BY 4.0\n"
        "https://www.chosic.com/download-audio/30332/\n\n\n"
        "Police :\n"
        "DejaVu Sans Bold\n\n\n"
        "Inspirations techniques :\n\n"
        "Rendu de texte SDL2_ttf\n"
        "et lecture audio SDL2_mixer -\n"
        "F. Belhadj (cours GL4D)\n\n"
        "VBO / VAO -\n"
        "Deyan Sirakov\n"
        "opengl-notes.readthedocs.io\n\n"
        "Distribution Fibonacci sur sphere -\n"
        "Vagner Seibert\n\n"
        "Parametrisation du tore -\n"
        "math.stackexchange\n"
        "R. Womersley\n\n"
        "Coordonnees spheriques -\n"
        "Wikipedia\n\n"
        "Matrices de rotation -\n"
        "Wikipedia\n\n"
        "Easing easeOutQuad -\n"
        "easings.net\n\n\n\n"
        "Merci");
}

void creditsDraw(void) {
    const GLfloat inclinaison = -60.0f;
    static GLfloat t0 = -1;
    GLfloat t, d;
    if(t0 < 0.0f)
        t0 = SDL_GetTicks();
    t = (SDL_GetTicks() - t0) / 1000.0f,d = -2.4f /* retard pour commencer en bas */ + 0.25f /* vitesse */ * t;
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(_pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textTexId);
    glUniform1i(glGetUniformLocation(_pId, "inv"), 1);
    glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
    gl4duBindMatrix("modelViewMatrix");
    gl4duLoadIdentityf();
    gl4duScalef(1, 5, 1);
    gl4duTranslatef(0, d * cos(inclinaison * M_PI / 180.0f), -2 + d * sin(inclinaison * M_PI / 180.0f));
    gl4duRotatef(inclinaison, 1, 0, 0);
    gl4duSendMatrices();
    gl4dgDraw(_quad);
    glUseProgram(0);
}

void creditsQuit(void) {
    if(_textTexId) {
        glDeleteTextures(1, &_textTexId);
        _textTexId = 0;
    }
}

static void initText(GLuint *ptId, const char *text) {
    static int firstTime = 1;
    SDL_Color c = {180, 100, 220, 255};
    SDL_Surface *d, *s;
    TTF_Font *font = NULL;

    if(firstTime) {
        if(TTF_Init() == -1) {
            fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
            exit(2);
        }
        firstTime = 0;
    }

    if(*ptId == 0) {
        glGenTextures(1, ptId);
        glBindTexture(GL_TEXTURE_2D, *ptId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    if( !(font = TTF_OpenFont("assets/DejaVuSans-Bold.ttf", 128)) ) {
        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        return;
    }

    d = TTF_RenderUTF8_Blended_Wrapped(font, text, c, 2048);
    if(d == NULL) {
        TTF_CloseFont(font);
        fprintf(stderr, "Erreur lors du TTF_RenderText\n");
        return;
    }

    s = SDL_CreateRGBSurface(0, d->w, d->h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    assert(s);
    SDL_BlitSurface(d, NULL, s, NULL);
    SDL_FreeSurface(d);
    glBindTexture(GL_TEXTURE_2D, *ptId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s->w, s->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, s->pixels);
    fprintf(stderr, "Dimensions de la texture : %d %d\n", s->w, s->h);
    SDL_FreeSurface(s);
    TTF_CloseFont(font);
    glBindTexture(GL_TEXTURE_2D, 0);
}