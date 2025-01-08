#ifndef GEST_ASSETS
#define GEST_ASSETS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "fct_init.h"
#include "gen_map.h"

/**
 * \file gest_assets.h 
 * \brief Contient le nécessaire pour afficher toutes les textures en jeu.
 */

/**
 * \struct Text
 * \brief 
 */
typedef struct {
    SDL_Texture * texture;  /**<  */
    SDL_Rect rect;          /**<  */
    char * sentence;        /**< Chaine de charactère a afficher. */
} Text;

/**
 * \struct Background
 * \brief 
 */
typedef struct {
    SDL_Texture * water;    /**< Texture de fond donc de l'eau dans notre cas. */
    SDL_Texture * ground;   /**<  */
    SDL_Texture * cliff;
    SDL_Texture ** waterfall;
    SDL_Texture ** moving_water;
    SDL_Texture ** borders; /**<  */
    SDL_Texture ** submerged_borders; /**<  */
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