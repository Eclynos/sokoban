#include "move.h"

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


int verif_win(Map * map){
    int i,j;
    int win = 0;

    for (i=0; i<map->rows; ++i){
        for (j=0; j<map->cols; ++j){
            if (map->tab[i][j] != 'C' && map->initial_tab[i][j] == 'I'){
                win = -1;
            }
        }
    }
    return win;
}


