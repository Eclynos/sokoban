#ifndef GEST_ASSETS
#define GEST_ASSETS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "fct_init.h"


typedef struct {
    int rows;
    int cols;
    char ** tab;
    char ** initial_tab;
    int tile_size;
    int pos_perso_i;
    int pos_perso_j;
} Map;


Map * createMap(const char * filename, Game * game);
void freeMap(Map * map);
void print2d(char ** tab, int row, int col);
SDL_Texture* createEntity(const char * filename, Game * game);
TTF_Font* createFont(const char * filename, Game * game);
void showBackground(Game * game, SDL_Texture* bg);
void showAllEntities(Game * game, Map * map, Player * player, SDL_Texture* box, SDL_Texture* goal, SDL_Texture* wall, SDL_Texture* tex_void, SDL_Texture* goal_boxed);
void showInteractives(Game * game, TTF_Font * font, SDL_Color text_color);

#endif // !GEST_ASSETS
