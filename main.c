#include "includes.h"

int main() {

    Game * game = initGame();
    Player * player = initPlayer(game);
    Map * map = createMap(FILE_MAP_1, game);

    SDL_Texture* bg = createEntity(BACKGROUND_IMAGE, game);
    SDL_Texture* box = createEntity(BOX_IMAGE, game);
    SDL_Texture* goal = createEntity(GOAL_IMAGE, game);
    SDL_Texture* wall = createEntity(WALL_IMAGE, game);
    SDL_Texture* tex_void = createEntity(VOID_IMAGE, game);

    SDL_Color text_color = {255, 255, 255, 255}; // pour l'instant du blanc
    TTF_Font* font = createFont(FILE_FONT, game);

    SDL_bool program_launched = SDL_TRUE;
    Uint32 last_animation_time = 0;
    
    while (program_launched) {

        Uint32 start_time = SDL_GetTicks();

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                program_launched = SDL_FALSE;
                break;
            } 
            else if (event.type == SDL_KEYDOWN) {
                // Gestion des touches
                switch (event.key.keysym.sym) {
                    case SDLK_z:
                        move(map, 'U'); // Déplacer vers le haut
                        player->direction = 1;
                        break;
                    case SDLK_s:
                        move(map, 'D'); // Déplacer vers le bas
                        player->direction = 3;
                        break;
                    case SDLK_q:
                        move(map, 'L'); // Déplacer vers la gauche
                        player->direction = 0;
                        break;
                    case SDLK_d:
                        move(map, 'R'); // Déplacer vers la droite
                        player->direction = 2;
                        break;
                    case SDLK_ESCAPE:
                        program_launched = SDL_FALSE;
                        break;
                    default:
                        break;
                }
            }
        }
        
        if (!program_launched) break;
        
        if (verif_win(map) == 0){
            print2d(map->initial_tab, map->rows, map->cols);
            printf("WIN!!\n");
            program_launched = SDL_FALSE;
        }

        Uint32 current_time = SDL_GetTicks();
        if (current_time - last_animation_time >= 500) { // 500 ms = 0.5 seconde
            ++player->frame;
            if (player->frame > 5) player->frame = 0; // 6 animations au total
            last_animation_time = current_time;
        }

        showBackground(game, bg);
        showAllEntities(game, map, player, box, goal, wall, tex_void);
        showInteractives(game, font, text_color);

        SDL_RenderPresent(game->renderer);

        Uint32 frame_time = SDL_GetTicks() - start_time;

        if (frame_time < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }

    freeMap(map);
    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(box);
    SDL_DestroyTexture(goal);
    SDL_DestroyTexture(wall);
    SDL_DestroyTexture(tex_void);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}