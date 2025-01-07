#ifndef GEST_ASSETS
#define GEST_ASSETS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "fct_init.h"
#include "gen_map.h"

typedef struct {
    SDL_Texture * texture;
    SDL_Rect rect;
    char * sentence;
} Text;

typedef struct {
    SDL_Texture * water;
    SDL_Texture * ground;
    SDL_Texture ** borders;
} Background;

SDL_Texture* createEntity(const char * filename, Game * game);
TTF_Font* createFont(const char * filename, Game * game);
Text * createText(Game * game, TTF_Font * font, SDL_Color text_color, char * sentence, int x, int y, int w, int h);
void updateText(Game * game, Text * text, TTF_Font * font, SDL_Color text_color, char * sentence);
void freeText(Text * text);

void showBackground(Game * game, Map * map, Background * background);

void showAllEntities(Game * game, Map * map, Player * player, SDL_Texture* box, SDL_Texture* goal, SDL_Texture* rock, SDL_Texture* tex_void, SDL_Texture* goal_boxed, SDL_Texture* frog_rock, SDL_Texture* rock_submerged, SDL_Texture* frog_rock_submerged);

void showInteractives(Game * game, TTF_Font * font, SDL_Color text_color, Text * start, Text * level, Text * moves, Text * text_level, Text * text_moves, int map_nb, int nb_moves);

void capFPS(Uint32 sart_time);
void frameAnimation(Game* game, Uint32* last_animation_time);
Background * initBackgroundTextures(Game * game);
void freeBackground(Background * background);

#endif // !GEST_ASSETS