#include "includes.h"

int main() {
    // Initialisation du jeu et du joueur
    Game * game = initGame();
    Player * player = initPlayer(game);

    // Initialisation de la map
    Map * map = createMap(FILE_MAP_START, game, player);

    // Création du tableau contenant le chemin relatif des fichier map
    const char* tab_map[] = {MAP_TAB};

    // Création de toute les textures
    SDL_Texture* bg = createEntity(BACKGROUND_IMAGE, game);
    SDL_Texture* box = createEntity(BOX_IMAGE, game);
    SDL_Texture* goal = createEntity(GOAL_IMAGE, game);
    SDL_Texture* wall = createEntity(WALL_IMAGE, game);
    SDL_Texture* tex_void = createEntity(VOID_IMAGE, game);
    SDL_Texture* frog_rock = createEntity(FROG_IMAGE, game);
    SDL_Texture* goal_boxed = createEntity(GOAL_BOXED_IMAGE, game);

    // Création de la police d'écriture et des textures de texte
    SDL_Color text_color = {205, 147, 115, 255};
    TTF_Font * font = createFont(FILE_FONT, game);
    Text * start = createText(game, font, text_color, "Press Start to play", game->screensize.w/3, 0, 200, 200);
    Text * level = createText(game, font, text_color, "1", 0, 0, 20, 20);
    Text * moves = createText(game, font, text_color, "0", 0, 30, 20, 20);

    // Création du booléen de la boucle de jeu
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
        
            else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) { // Les touches sont interprété ssi elles ne restent pas enfoncées
                if (map->num_of_map == 0 && event.key.keysym.sym == SDLK_RETURN){
                    map = nextMap(game, map, player, tab_map);
                    // Affichage bandeaux Start
                    break;
                }

                // Gestion des touches
                switch (event.key.keysym.sym) {
                    case SDLK_r:    // Restart la map
                        map = restartMap(game, map, player, tab_map);
                        break;
                    case SDLK_z:
                        move(map, player, 'U'); // Déplacer vers le haut
                        player->direction = 1;
                        break;
                    case SDLK_s:
                        move(map, player, 'D'); // Déplacer vers le bas
                        player->direction = 3;
                        break;
                    case SDLK_q:
                        move(map, player, 'L'); // Déplacer vers la gauche
                        player->direction = 0;
                        break;
                    case SDLK_d:
                        move(map, player, 'R'); // Déplacer vers la droite
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

        frameAnimation(game, &last_animation_time);
        showBackground(game, bg);
        showAllEntities(game, map, player, box, goal, wall, tex_void, goal_boxed, frog_rock);
        showInteractives(game, font, text_color, start, level, moves, map->num_of_map, player->nb_move);
        SDL_RenderPresent(game->renderer);

        if (map->num_of_map != 0 && verif_win(map) == 0){
            SDL_Delay(300);
            print2d(map->initial_tab, map->rows, map->cols);
            if (map->num_of_map+1 == NUMBER_OF_MAP){
                    program_launched = SDL_FALSE;
                    printf("finish\n");
            }else {
                    map = nextMap(game, map, player, tab_map);
                    printf("change\n");
            }
        }

        capFPS(start_time);
    }

    freeMap(map);
    freeText(start);
    freeText(level);
    freeText(moves);
    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(box);
    SDL_DestroyTexture(goal);
    SDL_DestroyTexture(wall);
    SDL_DestroyTexture(tex_void);
    SDL_DestroyTexture(goal_boxed);
    SDL_DestroyTexture(frog_rock);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
