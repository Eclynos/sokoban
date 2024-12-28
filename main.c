#include "includes.h"

int main() {

    Game game = initGame();
    Player player = initPlayer();
    Map * map = createMap(FILE_MAP_1, game);

    SDL_Texture* bg = createEntity(BACKGROUND_IMAGE, game);
    SDL_Texture* perso = createEntity(CHARACTER_IMAGE, game);
    SDL_Texture* box = createEntity(BOX_IMAGE, game);
    SDL_Texture* goal = createEntity(GOAL_IMAGE, game);
    SDL_Texture* wall = createEntity(WALL_IMAGE, game);
    SDL_Texture* tex_void = createEntity(VOID_IMAGE, game);

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
                        move(map, 'U'); // Déplacer vers le haut
                        player.direction = 1;
                        break;
                    case SDLK_s:
                        move(map, 'D'); // Déplacer vers le bas
                        player.direction = 3;
                        break;
                    case SDLK_q:
                        move(map, 'L'); // Déplacer vers la gauche
                        player.direction = 0;
                        break;
                    case SDLK_d:
                        move(map, 'R'); // Déplacer vers la droite
                        player.direction = 2;
                        break;
                }
            }
        if (verif_win(map) == 0){
            print2d(map->initial_tab, map->rows, map->cols);
            printf("WIN!!\n");
            program_launched = SDL_FALSE;
        }

        showAllEntities(game, map, player, bg, perso, box, goal, wall, tex_void);

        }

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
