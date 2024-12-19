#include "../include/fct_init.h"
#include "../include/constants.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void msgError(const char* msg){
    printf("%s %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}


