#include "../include/gen_map.h"
#define LEN_MAX 500

/**
 * \file gen_map.c
 * \brief Manipulation des structures Map.
**/


/**
 * \fn void getData(FILE * file, Map * map)
 * 
 * \brief Trouve et stocke dans la struct Map la taille de la grille de jeu.
 * 
 * \param file Pointeur sur le fichier map.txt associé.
 * \param map Struct Map qui va stocker la taille de la grille de jeu.
 */
void getData(FILE * file, Map * map){
    char chaine[LEN_MAX];

    map->rows = 0; 
    map->cols = 0;

    while (fgetc(file) != '\n') {
        ++map->cols;
    }
    rewind(file);

    while (fgets(chaine, LEN_MAX, file) != NULL) {
        ++map->rows;
    }
    rewind(file); 
}

/**
 * \fn Map *createMap(const char *filename, Game * game, Player* player)
 * 
 * \brief Initialise une structure Map qui va stocker la grille de jeu dans 2 tableau et d'autres informations utiles au fonctionnement du jeu.
 * 
 * \param file Pointeur sur le fichier map.txt associé.
 * \param game Srtucture Game, permet d'associer la map au jeu (game).
 * \param player Structure Player, permet d'associer la map au joueur.
 * 
 * \return Map complétement initialiser.
 * \see Map
 */
Map *createMap(const char *filename, Game * game, Player* player) {
    int i, j;
    char tmp;

    FILE * file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    Map *map = (Map*)malloc(sizeof(*map));
    if (!map) {
        perror("Erreur allocation map");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    getData(file, map);

    map->initial_tab = malloc(map->rows * sizeof(* map->initial_tab));
    map->tab = malloc(map->rows * sizeof(* map->tab));

    for (i = 0; i < map->rows; ++i) {
        map->initial_tab[i] = malloc(map->cols * sizeof(char));
        map->tab[i] = malloc(map->cols * sizeof(char));

        for (j = 0; j < map->cols+1; ++j) { // On parcours cols +1 la ligne pour prendre en compte le saut de ligne
            tmp = fgetc(file);

            if (tmp != '\n') {
                map->tab[i][j] = tmp;

                // On stocke dans initial_tab seulement les cases voids et goal.
                if (tmp != ' ' && tmp != 'I') map->initial_tab[i][j] = ' ';
                else                                        map->initial_tab[i][j] = tmp;

                if (tmp == 'P'){
                    player->pos_i = i;
                    player->pos_j = j;
                }
            }
        }
    }
    map->num_of_map = 0;
    map->tile_size = 0.80 * game->screensize.w / map->cols;
    map->up_space = game->screensize.h / 6;
    map->waterfall_position = map->cols / 4;
    player->nb_move = 0;

    fclose(file);
    return map;
}

/**
 * \fn Map * nextMap(Game* game, Map* old_map, Player* player, const char ** tab_map)
 * 
 * \brief Créer la pochaine map dans la liste des maps pour remplacer l'ancienne.
 * 
 * \param game Struct Game nécessaire pour créer une nouvelle map.
 * \param old_map Struct Map qui doit être libérer.
 * \param player Struct Player nécessaire pour créer une nouvelle map.
 * \param tab_map Tableaux contenant la liste des chemins vers le fichier map.txt (contenant la grille de jeu).
 * 
 * \return La nouvelle map .
 * \see Map
 */
Map * nextMap(Game* game, Map* old_map, Player* player, const char ** tab_map){
    int num_of_map = old_map->num_of_map + 1;
    Map* new_map = createMap(tab_map[num_of_map], game, player);
    new_map->num_of_map = num_of_map;
    freeMap(old_map);
    return new_map;
}

/**
 * \fn Map * restartMap(Game* game, Map* map, Player* player, const char ** tab_map)
 * 
 * \brief Réinitialise la map passer en argument.
 * 
 * \param game Struct Game nécessaire pour recommencer la map.
 * \param map Struct Map qui doit être réinitialisé.
 * \param player Struct Player nécessaire pour recommencer la map.
 * \param tab_map Tableaux contenant la liste des chemins vers le fichier map.txt (contenant la grille de jeu).
 * 
 * \return La map réinitialiser.
 * \see Map
 */
Map * restartMap(Game* game, Map* map, Player* player, const char ** tab_map){
    int num_of_map = map->num_of_map;
    Map* new_map = createMap(tab_map[num_of_map], game, player);
    new_map->num_of_map = num_of_map;
    freeMap(map);
    return new_map;
}

/**
 * \fn void freeMap(Map * map)
 * 
 * \brief Libère la mémoire prie par la structure Map.
 * 
 * \param map Struct Map a libérer.
 * \see Map
 */
void freeMap(Map * map) {
    int i;

    for (i = 0; i < map->rows; ++i) {
        free(map->initial_tab[i]);
        free(map->tab[i]);
    }

    free(map);
}
