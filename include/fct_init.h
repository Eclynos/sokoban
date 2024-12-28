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
    SDL_Texture* texture0;
    SDL_Texture* texture1;
    SDL_Texture* texture2;
    SDL_Texture* texture3;
} Player;


Game initGame();
Player initPlayer(Game game);

#endif
