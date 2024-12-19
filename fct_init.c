#include "includes.h"

App initApp() {
    App app;
    app.renderer = NULL;
    app.window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)  msgError("Error video:");

    app.window = SDL_CreateWindow(
                            "Sokoban",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            SCREEN_WIDTH,
                            SCREEN_HEIGHT,
                            (SDL_WINDOW_SHOWN)
                            );

    if (!app.window)    msgError("Error window:");
    
    app.renderer = SDL_CreateRenderer(
                                app.window,
                                -1,
                                SDL_RENDERER_SOFTWARE
                                );

    if (!app.renderer)  msgError("Error renderer:");

    return app;
}