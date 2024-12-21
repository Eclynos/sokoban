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

Game initGame() {
    Game game;
    game.window = NULL;
    game.renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)  msgError("Error video:");

    if (SDL_GetDisplayBounds(0, &game.screensize) != 0) msgError("Error screen size fetcher");

    game.window = SDL_CreateWindow(
                            "Sokoban",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            game.screensize.w/2,
                            game.screensize.h/2,
                            (SDL_WINDOW_SHOWN)
                            );
    
    if (!game.window)    msgError("Error window:");
    
    game.renderer = SDL_CreateRenderer(
                                game.window,
                                -1,
                                SDL_RENDERER_SOFTWARE
                                );
    
    if (!game.renderer)  msgError("Error renderer:");

    return game;
}
