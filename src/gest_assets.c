#include "../include/gest_assets.h"
#define LEN_MAX 500


SDL_Texture* createEntity(const char * filename, Game game){

    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        printf("Error init surface: %s\n", IMG_GetError());
        SDL_DestroyRenderer(game.renderer);
        SDL_DestroyWindow(game.window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(game.renderer, surface);
    if (!texture) {
        printf("Erreur init texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(game.renderer);
        SDL_DestroyWindow(game.window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(surface);
    return texture;
}


void showAllEntities(Game game, Map * map, Player player, SDL_Texture* bg, SDL_Texture* box, SDL_Texture* goal, SDL_Texture* wall, SDL_Texture* tex_void){
    int i, j;
    SDL_Rect tileRect;
    int tile_size = map->tile_size;

    //SDL_RenderClear(game.renderer);
        
    SDL_RenderCopy(game.renderer, bg, NULL, NULL);

    for (i = 0; i < map->rows; ++i) {
        for (j = 0; j < map->cols; ++j) {
            tileRect = (SDL_Rect){(game.screensize.w/2) + (j * tile_size - i * tile_size) / 2,
                                    10 + (j * tile_size + i * tile_size) / 4,
                                    tile_size, tile_size};
            switch (map->tab[i][j]) {
            case '#':
                SDL_RenderCopy(game.renderer, tex_void, NULL, &tileRect);
                break;
            case 'T':
                SDL_RenderCopy(game.renderer, wall, NULL, &tileRect);
                break;
            case 'R':
                SDL_RenderCopy(game.renderer, box, NULL, &tileRect);
                break;
            case '0': // on pourra ajouter un cas pour le goal recouvert par une caisse
                SDL_RenderCopy(game.renderer, goal, NULL, &tileRect);
                break;
            case '1':
                if (player.direction == 0) {
                    SDL_RenderCopy(game.renderer, player.texture0, NULL, &tileRect);
                } else if (player.direction == 1) {
                    SDL_RenderCopy(game.renderer, player.texture1, NULL, &tileRect);
                } else if (player.direction == 2) {
                    SDL_RenderCopy(game.renderer, player.texture2, NULL, &tileRect);
                } else {
                    SDL_RenderCopy(game.renderer, player.texture3, NULL, &tileRect);
                }
            default:
                break;
            }
        }
    }

        SDL_RenderPresent(game.renderer);
}


void print2d(char ** tab, int row, int col) {
    /*Affiche tout les elements d'un tableau 2d*/
    int i, j;
    for (i = 0; i < row; ++i){
        for (j = 0; j < col; ++j){
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}


void getData(FILE * file, Map * map){
    /* Trouve et stocke dans la struct Map la taille de la grille de jeu */
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


Map *createMap(const char *filename, Game game) {
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
                if (tmp != '#' && tmp != '0' && tmp != 'T') map->initial_tab[i][j] = '#';
                else                                        map->initial_tab[i][j] = tmp;

                if (tmp == '1'){
                    map->pos_perso_i = i;
                    map->pos_perso_j = j;
                }
            }
        }
    }

    map->tile_size = game.screensize.w / map->cols;
    // faire un calcul savant pour faire en sorte que la fenêtre fit à peu près l'affichage de l'ensemble des tiles

    fclose(file);
    return map;
}


void freeMap(Map * map) {
    int i;

    for (i = 0; i < map->rows; ++i) {
        free(map->initial_tab[i]);
        free(map->tab[i]);
    }

    free(map);
}


