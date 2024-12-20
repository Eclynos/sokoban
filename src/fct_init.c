#include "../include/fct_init.h"
#include "../include/constants.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void msgError(const char* msg){
    printf("%s %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

App initApp() {
    App app;
    app.window = NULL;
    app.renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)  msgError("Error video:");

    if (SDL_GetDisplayBounds(0, &app.screensize) != 0) msgError("Error screen size fetcher");

    app.window = SDL_CreateWindow(
                            "Sokoban",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            app.screensize.w/2,
                            app.screensize.h/2,
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
