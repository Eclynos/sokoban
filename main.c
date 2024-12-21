#include "includes.h"

int main() {

    Game game = initGame();
    Map * map = createMap(FILE_MAP_1);

    SDL_Texture* bg = createEntity(BACKGROUND_IMAGE, game);
    SDL_Texture* perso = createEntity(CHARACTER_IMAGE, game);
    SDL_Texture* box = createEntity(BOX_IMAGE, game);
    SDL_Texture* goal = createEntity(GOAL_IMAGE, game);
    SDL_Texture* wall = createEntity(WALL_IMAGE, game);
    SDL_Texture* tex_void = createEntity(VOID_IMAGE, game);


    // Position initiale de l'image
    SDL_Rect imgRect = {100, 100, 50, 50}; // {x, y, largeur, hauteur}

    SDL_bool program_launched = SDL_TRUE;
    
    while (program_launched) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                program_launched = SDL_FALSE;
            } 
            else if (event.type == SDL_KEYDOWN) {
                // Gestion des touches
                switch (event.key.keysym.sym) {
                    case SDLK_z:
                        imgRect.y -= 10; // Déplacer vers le haut
                        break;
                    case SDLK_s:
                        imgRect.y += 10; // Déplacer vers le bas
                        break;
                    case SDLK_q:
                        imgRect.x -= 10; // Déplacer vers la gauche
                        break;
                    case SDLK_d:
                        imgRect.x += 10; // Déplacer vers la droite
                        break;
                }
            }
        }

        afficheAllEntities(game, map, bg, perso, box, goal, wall, tex_void);


    }

    freeMap(map);
    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(perso);
    SDL_DestroyTexture(box);
    SDL_DestroyTexture(goal);
    SDL_DestroyTexture(wall);
    SDL_DestroyTexture(tex_void);
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
