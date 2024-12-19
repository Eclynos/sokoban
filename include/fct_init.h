#ifndef FCT_INIT
#define FCT_INIT
#include <SDL2/SDL.h>

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

App initApp();

void msgError(const char* msg);

#endif
