#include "gest_assets.h"
#define LEN_MAX 500


SDL_Texture* createEntity(const char * filename, Game * game){

    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        printf("Error init surface: %s\n", IMG_GetError());
        SDL_DestroyRenderer(game->renderer);
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    if (!texture) {
        printf("Erreur init texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(game->renderer);
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(surface);
    return texture;
}


TTF_Font* createFont(const char * filename, Game * game) {

    TTF_Font* font = TTF_OpenFont(filename, TEXT_SIZE);
    if (!font) {
        printf("Erreur init police: %s\n", SDL_GetError());
        SDL_DestroyRenderer(game->renderer);
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return font;
}


Text * createText(Game * game, TTF_Font * font, SDL_Color text_color, char * sentence, int x, int y, int w, int h) {
    Text * text = (Text*)malloc(sizeof(*text));
    if (!text) {
        perror("Erreur allocation texte");
        exit(EXIT_FAILURE);
    }

    SDL_Surface * textSurface = TTF_RenderText_Solid(font, sentence, text_color);
    text->texture = SDL_CreateTextureFromSurface(game ->renderer, textSurface);
    text->rect = (SDL_Rect){x, y, w, h};
    SDL_QueryTexture(text->texture, NULL, NULL, &text->rect.w, &text->rect.h);
    SDL_FreeSurface(textSurface);

    return text;
}


void showBackground(Game * game, SDL_Texture* bg) {
    //SDL_RenderClear(game->renderer);
        
    SDL_RenderCopy(game->renderer, bg, NULL, NULL);
}


void showAllEntities(Game * game, Map * map, Player * player, SDL_Texture* box, SDL_Texture* goal, SDL_Texture* wall, SDL_Texture* tex_void, SDL_Texture* goal_boxed, SDL_Texture* frog_rock){
    int i, j;
    SDL_Rect tileRect;
    int tile_size = map->tile_size;

    for (i = 0; i < map->rows; ++i) {
        for (j = 0; j < map->cols; ++j) {
            tileRect = (SDL_Rect){(game->screensize.w/2) + (j * tile_size - i * tile_size) / 2,
                                    10 + (j * tile_size + i * tile_size) / 4,
                                    tile_size, tile_size};
            switch (map->tab[i][j]) {
            case '#':
                SDL_RenderCopy(game->renderer, tex_void, NULL, &tileRect);
                break;
            case 'T':
                SDL_RenderCopy(game->renderer, wall, NULL, &tileRect);
                break;
            case 'R':
                if (map->initial_tab[i][j] == '0') {
                    SDL_RenderCopy(game->renderer, goal_boxed, NULL, &tileRect);
                } else {
                    SDL_RenderCopy(game->renderer, box, NULL, &tileRect);
                }
                break;
            case '0':
                SDL_RenderCopy(game->renderer, goal, NULL, &tileRect);
                break;
            case '1':
                SDL_RenderCopy(game->renderer, player->texture[player->direction][game->frame], NULL, &tileRect);
                break;
            case 'F':
                SDL_RenderCopy(game->renderer, frog_rock, NULL, &tileRect);
                break;
            default:
                break;
            }
        }
    }
}

void showInteractives(Game * game, Text * start, int map_nb) {
    if (map_nb == 0) {
        SDL_RenderCopy(game->renderer, start->texture, NULL, &start->rect);
    }
    // sinon il affiche en haut à droite le numéro de map
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
                if (tmp != '#' && tmp != '0' && tmp != 'T') map->initial_tab[i][j] = '#';
                else                                        map->initial_tab[i][j] = tmp;

                if (tmp == '1'){
                    player->pos_i = i;
                    player->pos_j = j;
                }
            }
        }
    }

    map->tile_size = game->screensize.w / map->cols;
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
