#include "../include/game_loop.h"


SDL_bool gameLoop(Map * map){
    SDL_bool program_launched = SDL_TRUE;

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            program_launched = SDL_FALSE;
        } 
        else if (event.type == SDL_KEYDOWN) {
            // Gestion des touches
            switch (event.key.keysym.sym) {
                case SDLK_z:
                    move(map, 'U'); // Déplacer vers le haut
                    break;
                case SDLK_s:
                    move(map, 'D'); // Déplacer vers le bas
                    break;
                case SDLK_q:
                    move(map, 'L'); // Déplacer vers la gauche
                    break;
                case SDLK_d:
                    move(map, 'R'); // Déplacer vers la droite                        break;
            }
        }



    }
    return program_launched;
}
