#include "includes.h"

int main() {
    // Initialisation du jeu et du joueur
    Game * game = initGame();
    Player * player = initPlayer(game);

    // Initialisation de la map
    Map * map = createMap(FILE_MAP_START, game, player);
    map->num_of_map = 0;

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

    // Création de la police d'écriture
    SDL_Color text_color = {255, 255, 255, 255}; // pour l'instant du blanc
    TTF_Font* font = createFont(FILE_FONT, game);
    Text * start = createText(game, font, text_color, "Press Start to play", game->screensize.w/3, 0, 200, 200);
    Text * level = createText(game, font, text_color, "1", game->screensize.w - 20, 0, 20, 20);

    // faire fonc qui crée pour chaque texte que l'on veut mette un struct contenant:
    //  -la texture du texte
    //  -la position en textRect
    // prenant en argument couleur, font, etc

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
            else if (event.type == SDL_KEYDOWN) {

                if (map->num_of_map == 0 && event.key.keysym.sym == SDLK_RETURN){
                    map = nextMap(game, map, player, tab_map);
                    // AFfichage bandeaux Start
                    break;
                }

                // Gestion des touches
                switch (event.key.keysym.sym) {
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


        if (map->num_of_map != 0 && verif_win(map) == 0){
            print2d(map->initial_tab, map->rows, map->cols);
            printf("WIN!!\n");
            if (map->num_of_map == NUMBER_OF_MAP){
                    program_launched = SDL_FALSE;
                    printf("finish\n");
            }else {
                    map = nextMap(game, map, player, tab_map);
                    printf("change\n");
            }
        }

        Uint32 current_time = SDL_GetTicks();
        if (current_time - last_animation_time >= 400) { // en ms
            ++game->frame;
            if (game->frame > 5) game->frame = 0; // 6 animations
            last_animation_time = current_time;
        }

        showBackground(game, bg);
        showAllEntities(game, map, player, box, goal, wall, tex_void, goal_boxed, frog_rock);
        showInteractives(game, font, text_color, start, level, map->num_of_map);

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
    SDL_DestroyTexture(goal_boxed);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
