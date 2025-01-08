#ifndef FCT_INIT
#define FCT_INIT

#include <SDL2/SDL.h>
#include <string.h>

/**
 * \file fct_init.h 
 * \brief Contient les structures Game et Player et leurs fonctions d'initialisation.
 */

/**
 * \struct Game
 * \brief Représente les éléments de base pour un rendu avec SDL2.
 */
typedef struct {
    SDL_Renderer *renderer; /**< Moteur de rendu de la fenetre SDL2. */
    SDL_Window *window;     /**< Fenêtre de jeu. */
    SDL_Rect screensize;    /**< Taille de l'écran de l'ordinateur de l'utilisateur. */
    int frame;              /**< Numéro de la frame à un instant t de l'éxécution du jeu. */
} Game;

/**
 * \brief Représente le joueur.
 */
typedef struct {
    int pos_i;              /**< Position i du joueur dans la grille de jeu. */
    int pos_j;              /**< Position j du joueur dans la grille de jeu. */
    int nb_move;            /**< Nombre de mouvement fait par le joueur. */
    int direction;          /**< Direction du personnage(vers où il regarde), il y a 4 points cardinaux possible: 0 (NW), 1 (NE), 2(SE) ou 3 (SW)*/
    SDL_Texture *** texture; /**< Tableaux de toutes les textures différentes du personnage. */
} Player;


Game * initGame();
Player * initPlayer(Game * game);

#endif
