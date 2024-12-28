#ifndef FCT_INIT
#define FCT_INIT
#include <SDL2/SDL.h>

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Rect screensize;
} Game;

typedef struct {
    int direction; // can be 0 (NW), 1 (NE), 2(SE) or 3 (SW)
} Player;


Game initGame();
Player initPlayer();

#endif
