#include "fct_init.h"
#include "constants.h"
#include "gest_assets.h"

/**
 * \file fct_init.c
 * \brief Fonctions d'initialisation de structure importante
**/


/**
   \fn void msgError(const char* msg)

   \brief Affiche un message d'erreur et quitte le programme proprement.

   \param msg Char de message d'erreur.
 */
void msgError(const char* msg){
    printf("%s %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

/**
 * \fn Game * initGame()
 * 
 * \brief Initialise le jeu c.a.d. initialise SDL2 et la fenêtre de jeu.
 * 
 * \return Occurrence de la structure Game complétement remplie.
 * \see game
 */
Game * initGame() {
    Game * game = (Game*)malloc(sizeof(*game));
    if (!game) {
        perror("Erreur allocation joueur");
        exit(EXIT_FAILURE);
    }
    game->window = NULL;
    game->renderer = NULL;
    game->frame = 0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)  msgError("Error video:");
    if (TTF_Init() == -1) msgError("Error ttf:");

    if (SDL_GetDisplayBounds(0, &game->screensize) != 0) msgError("Error screen size fetcher");
    game->screensize.w /= 1.4;
    game->screensize.h /= 1.4;

    game->window = SDL_CreateWindow(
                            "Sokoban",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            game->screensize.w,
                            game->screensize.h,
                            (SDL_WINDOW_SHOWN)
                            );
    if (!game->window)    msgError("Error window:");
    
    game->renderer = SDL_CreateRenderer(
                                game->window,
                                -1,
                                SDL_RENDERER_SOFTWARE
                                );
    if (!game->renderer)  msgError("Error renderer:");

    return game;
}

/**
 * \fn Player * initPlayer(Game * game)
 * 
 * \brief Initialise le personnage c.a.d. initialise ses textures et le nombre de mouvement du personnage.
 * 
 * \return Occurrence de la structure Player partiellement remplie.
 * \see player
 */
Player * initPlayer(Game * game) {
    unsigned int i, j;
    char filename[40];

    Player * player = (Player*)malloc(sizeof(*player));
    if (!player) {
        perror("Erreur allocation joueur");
        exit(EXIT_FAILURE);
    }
    player->direction = 0;
    player->texture = malloc(4 * sizeof(SDL_Texture**));
    for (i = 0; i < 4; ++i) {
        player->texture[i] = malloc(NB_ANIMATIONS * sizeof(SDL_Texture*));
        for (j = 0; j < NB_ANIMATIONS; ++j) {
            sprintf(filename, "%s%d%d%s", CAPY_PATH, i, j, ".png");
            player->texture[i][j] = createEntity(filename, game);
        }
    }
    player->nb_move = 0;
    return player;
}
