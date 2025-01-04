#include "../include/gen_map.h"

Map * nextMap(Game* game, Map* old_map, const char ** tab_map){
    /* Remplace le pointeur de old_map pars un autre pointeur correspondant à la prochaine map dans la liste des maps */ 
    Map* new_map = createMap(tab_map[old_map->num_of_map], game);
    new_map->num_of_map = old_map->num_of_map + 1;
    freeMap(old_map);
    return new_map;
}
