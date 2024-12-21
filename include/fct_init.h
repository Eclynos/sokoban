#ifndef FCT_INIT
#define FCT_INIT
#include <SDL2/SDL.h>

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Rect screensize;
} Game;

Game initGame();

void msgError(const char* msg);

#endif
