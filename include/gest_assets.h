#ifndef GESTION_ASSETS
#define GESTION_ASSETS

#include <SDL2/SDL.h>
#include "./constants.h"

typedef struct{
    char type;
    SDL_Texture * texture;
    SDL_Rect imgRect;
} texture;

#endif // !GESTION_ASSETS
