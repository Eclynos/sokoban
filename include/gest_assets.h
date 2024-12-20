#ifndef GEST_ASSETS
#define GEST_ASSETS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "fct_init.h"

typedef struct {
    int rows;
    int cols;
    int ** tab;
    int ** initial_tab;
} Map;

Map * createMap(const char * filename);
void freeMap(Map * map);
void initMapData(const char * filename, Map * map);
void readFileToTab(const char * filename, Map * map);
void free2d(char ** tab, int row);
void print2d(char ** tab, int row, int col);
SDL_Surface* loadSurface(const char * filename, App app);
SDL_Texture* createTexture(SDL_Surface* surface, App app);

#endif // !GEST_ASSETS
