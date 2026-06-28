#include <stdio.h>
#include <SDL_mixer.h>
#include "audio.h"

static Mix_Music *_mmusic = NULL;

void initAudio(const char *filename) {
    int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_MOD, res;
    res = Mix_Init(mixFlags);
    if((res & mixFlags) != mixFlags) {
        fprintf(stderr, "Mix_Init: Erreur lors de l'initialisation de la bibliotheque SDL_Mixer\n");
        fprintf(stderr, "Mix_Init: %s\n", Mix_GetError());
    }
    if(Mix_OpenAudio(44100, AUDIO_S16LSB, 2, 1024) < 0)
        exit(4);
    if(!(_mmusic = Mix_LoadMUS(filename))) {
        fprintf(stderr, "Erreur lors du Mix_LoadMUS: %s\n", Mix_GetError());
        exit(5);
    }

    if(!Mix_PlayingMusic())
        Mix_PlayMusic(_mmusic, 1);
}

void audioQuit(void) {
    if(_mmusic) {
        if(Mix_PlayingMusic())
            Mix_HaltMusic();
        Mix_FreeMusic(_mmusic);
        _mmusic = NULL;
    }
    Mix_CloseAudio();
    Mix_Quit();
}