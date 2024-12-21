#include "../include/move.h"

void move_up(Map * map){
    int i = map->pos_perso_i;
    int j = map->pos_perso_j;
    if (i - 1 >= 0){
        map->tab[i][j] = map->initial_tab[i][j];
        map->tab[i-1][j] = '1';
        --map->pos_perso_i;
    }
}

void move_down(Map * map){
    int i = map->pos_perso_i;
    int j = map->pos_perso_j;
    if (i + 1 < map->rows){
        map->tab[i][j] = map->initial_tab[i][j];
        map->tab[i+1][j] = '1';
        ++map->pos_perso_i; 
    }
}

void move_right(Map * map){
    int i = map->pos_perso_i;
    int j = map->pos_perso_j;
    if (j + 1 < map->cols){
        map->tab[i][j] = map->initial_tab[i][j];
        map->tab[i][j+1] = '1';
        ++map->pos_perso_j;
    }
}

void move_left(Map * map){
    int i = map->pos_perso_i;
    int j = map->pos_perso_j;
    if (j - 1 >= 0){
        map->tab[i][j] = map->initial_tab[i][j];
        map->tab[i][j-1] = '1';
        --map->pos_perso_j;
    }
}
