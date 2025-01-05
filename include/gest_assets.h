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
    int num_of_map;
} Map;

typedef struct {
    SDL_Texture * texture;
    SDL_Rect rect;
    char * sentence;
} Text;


Map * createMap(const char * filename, Game * game, Player* player);
void freeMap(Map * map);
void print2d(char ** tab, int row, int col);

SDL_Texture* createEntity(const char * filename, Game * game);
TTF_Font* createFont(const char * filename, Game * game);
Text * createText(Game * game, TTF_Font * font, SDL_Color text_color, char * sentence, int x, int y, int w, int h);
void updateText(Game * game, Text * text, TTF_Font * font, SDL_Color text_color, char * sentence);


void showBackground(Game * game, SDL_Texture* bg);

void showAllEntities(Game * game, Map * map, Player * player, SDL_Texture* box, SDL_Texture* goal, SDL_Texture* wall, SDL_Texture* tex_void, SDL_Texture* goal_boxed, SDL_Texture* frog_rock);

void showInteractives(Game * game, TTF_Font * font, SDL_Color text_color, Text * start, Text * level, int map_nb);

#endif // !GEST_ASSETS
