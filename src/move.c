#include "../include/move.h"

void move(Map* map, char sens){
    int i = map->pos_perso_i;
    int j = map->pos_perso_j;

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
                    --map->pos_perso_i;
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
                    ++map->pos_perso_i; 
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
                    ++map->pos_perso_j;
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
                    --map->pos_perso_j;
                }
            }
            break;

        default:
            // Faire msg d'erreur, pas le bon char donnée dans la fct 
            break;
        
    }
}



void move_up(Map * map){
    int i = map->pos_perso_i;
    int j = map->pos_perso_j;
    
    if (i-1 >= 0 && map->tab[i-1][j] != 'T'){
        
        if (map->tab[i-1][j] == 'R' && i-2 >= 0 && map->tab[i-2][j] != 'T' && map->tab[i-2][j] != 'R'){
            map->tab[i-1][j] = map->initial_tab[i-1][j];
            map->tab[i-2][j] = 'R';
        }

        if (map->tab[i-1][j] != 'R'){
            map->tab[i][j] = map->initial_tab[i][j];
            map->tab[i-1][j] = '1';
            --map->pos_perso_i;
        }
    }

}

void move_down(Map * map){
    int i = map->pos_perso_i;
    int j = map->pos_perso_j;
    if (i+1 < map->rows && map->tab[i+1][j] != 'T'){
        if (map->tab[i+1][j] == 'R' && i + 2 < map->rows && map->tab[i+2][j] != 'T' && map->tab[i+2][j] != 'R'){
            map->tab[i+1][j] = map->initial_tab[i+1][j];
            map->tab[i+2][j] = 'R';
        }
        if (map->tab[i+1][j] != 'R'){
            map->tab[i][j] = map->initial_tab[i][j];
            map->tab[i+1][j] = '1';
            ++map->pos_perso_i; 
        }
    }
}

void move_right(Map * map){
    int i = map->pos_perso_i;
    int j = map->pos_perso_j;
    
    if (j + 1 < map->cols && map->tab[i][j+1] != 'T'){
        if (map->tab[i][j+1] == 'R' && j+2 < map->cols && map->tab[i][j+2] != 'T' && map->tab[i][j+2] != 'R'){
            map->tab[i][j+1] = map->initial_tab[i][j+1];
            map->tab[i][j+2] = 'R';
        }
        if (map->tab[i][j+1] != 'R'){
            map->tab[i][j] = map->initial_tab[i][j];
            map->tab[i][j+1] = '1';
            ++map->pos_perso_j;
        }
    }
}

void move_left(Map * map){
    int i = map->pos_perso_i;
    int j = map->pos_perso_j;

    if (j-1 >= 0 && map->tab[i][j-1] != 'T'){
        if(map->tab[i][j-1] == 'R' && j-2 >= 0 && map->tab[i][j-2] != 'T' && map->tab[i][j-2] != 'R'){
            map->tab[i][j-1] = map->initial_tab[i][j-1];
            map->tab[i][j-2] = 'R';
        }
        if (map->tab[i][j-1] != 'R'){
            map->tab[i][j] = map->initial_tab[i][j];
            map->tab[i][j-1] = '1';
            --map->pos_perso_j;
        }
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
