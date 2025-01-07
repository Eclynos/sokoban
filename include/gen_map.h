#ifndef GEN_MAP_H_
#define GEN_MAP_H_

#include "./fct_init.h"

typedef struct {
    int rows;
    int cols;
    char ** tab;
    char ** initial_tab;
    int tile_size;
    int num_of_map;
    int up_space;
} Map;


Map * createMap(const char * filename, Game * game, Player* player);
void freeMap(Map * map);

Map * nextMap(Game* game, Map* old_map, Player* player, const char ** tab_map);

Map * restartMap(Game* game, Map* map, Player* player, const char ** tab_map);

#endif // !GEN_MAP_H_
