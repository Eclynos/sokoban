#include "move.h"

/**
 * \file move.c
 * \brief Gestion des déplacements du personnage.
**/


/**
 * \fn void move(Map* map, Player* player, char sens)
 * 
 * \brief Gère les déplacements du personnage selon l'appui des touches.
 * 
 * \param map Structure Map stockant entre autre la grille de jeu que l'on va modifier.
 * \param player Strut Player stockant la position du joueur qui va changer.
 * \param sens Char contenant le sens du déplacement.
 */
void move(Map* map, Player* player, char sens){
    int i = player->pos_i;
    int j = player->pos_j;

    switch (sens) {
        
        case 'U': // Move Up
            if (i-1 >= 0 && map->tab[i-1][j] != 'W' && map->tab[i-1][j] != 'F'){
                if (map->tab[i-1][j] == 'C' && i-2 >= 0 && map->tab[i-2][j] != 'W' && map->tab[i-2][j] != 'C'&& map->tab[i-2][j] != 'F'){
                    map->tab[i-1][j] = map->initial_tab[i-1][j];
                    map->tab[i-2][j] = 'C';
                }
                if (map->tab[i-1][j] != 'C'){
                    map->tab[i][j] = map->initial_tab[i][j];
                    map->tab[i-1][j] = 'P';
                    --player->pos_i;
                    ++player->nb_move;
                }
            }
            break;

        case 'D': // Move Down
            if (i+1 < map->rows && map->tab[i+1][j] != 'W' && map->tab[i+1][j] != 'F'){
                if (map->tab[i+1][j] == 'C' && i + 2 < map->rows && map->tab[i+2][j] != 'W' && map->tab[i+2][j] != 'C'&& map->tab[i+2][j] != 'F'){
                    map->tab[i+1][j] = map->initial_tab[i+1][j];
                    map->tab[i+2][j] = 'C';
                }
                if (map->tab[i+1][j] != 'C'){
                    map->tab[i][j] = map->initial_tab[i][j];
                    map->tab[i+1][j] = 'P';
                    ++player->pos_i; 
                    ++player->nb_move;
                }
            }
            break;

        case 'R': // Move Right
            if (j + 1 < map->cols && map->tab[i][j+1] != 'W' && map->tab[i][j+1] != 'F'){
                if (map->tab[i][j+1] == 'C' && j+2 < map->cols && map->tab[i][j+2] != 'W' && map->tab[i][j+2] != 'C'&& map->tab[i][j+2] != 'F'){
                    map->tab[i][j+1] = map->initial_tab[i][j+1];
                    map->tab[i][j+2] = 'C';
                }
                if (map->tab[i][j+1] != 'C'){
                    map->tab[i][j] = map->initial_tab[i][j];
                    map->tab[i][j+1] = 'P';
                    ++player->pos_j;
                    ++player->nb_move;
                }
            }
            break;

        case 'L': // Move Left
            if (j-1 >= 0 && map->tab[i][j-1] != 'W' && map->tab[i][j-1] != 'F'){
                if(map->tab[i][j-1] == 'C' && j-2 >= 0 && map->tab[i][j-2] != 'W' && map->tab[i][j-2] != 'W' && map->tab[i][j-2] != 'F'){
                    map->tab[i][j-1] = map->initial_tab[i][j-1];
                    map->tab[i][j-2] = 'C';
                }
                if (map->tab[i][j-1] != 'C'){
                    map->tab[i][j] = map->initial_tab[i][j];
                    map->tab[i][j-1] = 'P';
                    --player->pos_j;
                    ++player->nb_move;
                }
            }
            break;

        default:
            // Faire msg d'erreur, pas le bon char donnée dans la fct 
            break;
        
    }
}


/**
 * \fn int verif_win(Map * map)
 * 
 * \brief Vérifie si le joueur a finis le level.
 * 
 * \param map Struct Map stockant la grille de jeu.
 * 
 * \return 0 si le joueur ne gagne pas et 1 si le joueur a remplis tout les objectifs.
 */
int verif_win(Map * map){
    int i,j;
    int win = 1;

    for (i=0; i<map->rows; ++i){
        for (j=0; j<map->cols; ++j){
            if (map->tab[i][j] != 'C' && map->initial_tab[i][j] == 'I'){
                win = 0;
            }
        }
    }
    return win;
}


