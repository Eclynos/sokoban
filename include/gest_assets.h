#ifndef GEST_ASSETS
#define GEST_ASSETS

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char type;
    SDL_Texture * texture;
    SDL_Rect imgRect;
} texture;

void createMap();
int * dataMap(const char * filename);
char ** readFileToTab(const char * filename, int row, int col);
void free2d(char ** tab, int row);
void print2d(char ** tab, int row, int col);
texture ** initGrille(char ** grille_txt, int len);

#endif // !GEST_ASSETS
