#ifndef GEN_MAP_H_
#define GEN_MAP_H_

#include "./fct_init.h"

/**
 * \file gen_map.h 
 * \brief Contient les fonctions relatives à la gestion de la grille de jeu.
 */

/**
 * \struct Map
 * \brief Représente la grille de jeu.
 */
typedef struct {
    int rows;       /**< Nombre de ligne de la map. */
    int cols;       /**< Nombre de colonne de la map. */
    char ** tab;    /**< Contient la grille de jeu avec tout les éléments. */
    char ** initial_tab;    /**< Contient la grille de jeu avec seulement les cases de vides et de but*/
    int tile_size;  /**< Taille en pixels d'une tuile (élément) de jeu. */
    int num_of_map; /**< Numéro de la map actuel dans la liste de map. */
    int up_space;   /**<  */
} Map;


Map * createMap(const char * filename, Game * game, Player* player);
void freeMap(Map * map);

Map * nextMap(Game* game, Map* old_map, Player* player, const char ** tab_map);

Map * restartMap(Game* game, Map* map, Player* player, const char ** tab_map);

#endif // !GEN_MAP_H_
