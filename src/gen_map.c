#include "../include/gen_map.h"

Map * nextMap(Game* game, Map* old_map, Player* player, const char ** tab_map){
    /* Remplace le pointeur de old_map pars un autre pointeur correspondant à la prochaine map dans la liste des maps */
    int num_of_map = old_map->num_of_map + 1;
    Map* new_map = createMap(tab_map[num_of_map], game, player);
    new_map->num_of_map = num_of_map;
    freeMap(old_map);
    return new_map;
}

Map * restartMap(Game* game, Map* map, Player* player, const char ** tab_map){
    int num_of_map = map->num_of_map;
    Map* new_map = createMap(tab_map[num_of_map], game, player);
    new_map->num_of_map = num_of_map;
    freeMap(map);
    return new_map;
}
