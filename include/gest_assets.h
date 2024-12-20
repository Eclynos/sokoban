#ifndef GEST_ASSETS
#define GEST_ASSETS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "fct_init.h"

typedef struct{
    char type;
    SDL_Texture * texture;
    SDL_Rect imgRect;
} object;

void createMap(App app);
int * dataMap(const char * filename);
char ** readFileToTab(const char * filename, int row, int col);
void free2d(char ** tab, int row);
void print2d(char ** tab, int row, int col);
SDL_Surface* loadSurface(const char * filename, App app);
SDL_Texture* createTexture(SDL_Surface* surface, App app);
object ** initTexturesVars(char ** char_grid, App app, int row, int col);
void update_textures(App app);

#endif // !GEST_ASSETS
