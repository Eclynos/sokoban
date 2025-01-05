#ifndef FCT_INIT
#define FCT_INIT
#include <SDL2/SDL.h>
#include <string.h>


typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Rect screensize;
    int frame;
} Game;

typedef struct {
    int pos_i;
    int pos_j;
    int nb_move;
    int direction; // can be 0 (NW), 1 (NE), 2(SE) or 3 (SW)
    SDL_Texture *** texture;
} Player;


Game * initGame();
Player * initPlayer(Game * game);

#endif
