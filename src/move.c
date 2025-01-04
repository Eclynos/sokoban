#include "move.h"

void move(Map* map, Player* player, char sens){
    int i = player->pos_i;
    int j = player->pos_j;

    switch (sens) {
        
        case 'U': // Move Up
            if (i-1 >= 0 && map->tab[i-1][j] != 'T'){
                if (map->tab[i-1][j] == 'R' && i-2 >= 0 && map->tab[i-2][j] != 'T' && map->tab[i-2][j] != 'R'){
                    map->tab[i-1][j] = map->initial_tab[i-1][j];
                    map->tab[i-2][j] = 'R';
                }
                if (map->tab[i-1][j] != 'R'){
                    map->tab[i][j] = map->initial_tab[i][j];
                    map->tab[i-1][j] = '1';
                    --player->pos_i;
                }
            }
            break;

        case 'D': // Move Down
            if (i+1 < map->rows && map->tab[i+1][j] != 'T'){
                if (map->tab[i+1][j] == 'R' && i + 2 < map->rows && map->tab[i+2][j] != 'T' && map->tab[i+2][j] != 'R'){
                    map->tab[i+1][j] = map->initial_tab[i+1][j];
                    map->tab[i+2][j] = 'R';
                }
                if (map->tab[i+1][j] != 'R'){
                    map->tab[i][j] = map->initial_tab[i][j];
                    map->tab[i+1][j] = '1';
                    ++player->pos_i; 
                }
            }
            break;

        case 'R': // Move Right
            if (j + 1 < map->cols && map->tab[i][j+1] != 'T'){
                if (map->tab[i][j+1] == 'R' && j+2 < map->cols && map->tab[i][j+2] != 'T' && map->tab[i][j+2] != 'R'){
                    map->tab[i][j+1] = map->initial_tab[i][j+1];
                    map->tab[i][j+2] = 'R';
                }
                if (map->tab[i][j+1] != 'R'){
                    map->tab[i][j] = map->initial_tab[i][j];
                    map->tab[i][j+1] = '1';
                    ++player->pos_j;
                }
            }
            break;

        case 'L': // Move Left
            if (j-1 >= 0 && map->tab[i][j-1] != 'T'){
                if(map->tab[i][j-1] == 'R' && j-2 >= 0 && map->tab[i][j-2] != 'T' && map->tab[i][j-2] != 'R'){
                    map->tab[i][j-1] = map->initial_tab[i][j-1];
                    map->tab[i][j-2] = 'R';
                }
                if (map->tab[i][j-1] != 'R'){
                    map->tab[i][j] = map->initial_tab[i][j];
                    map->tab[i][j-1] = '1';
                    --player->pos_j;
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
            if (map->tab[i][j] != 'R' && map->initial_tab[i][j] == '0'){
                win = -1;
            }
        }
    }
    return win;
}
