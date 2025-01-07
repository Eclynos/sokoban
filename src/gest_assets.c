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
    text->sentence = sentence;
    SDL_QueryTexture(text->texture, NULL, NULL, &text->rect.w, &text->rect.h);
    SDL_FreeSurface(textSurface);

    return text;
}


void updateText(Game * game, Text * text, TTF_Font * font, SDL_Color text_color, char * sentence) {
    SDL_Surface * textSurface = TTF_RenderText_Solid(font, sentence, text_color);
    text->texture = SDL_CreateTextureFromSurface(game ->renderer, textSurface);
    SDL_QueryTexture(text->texture, NULL, NULL, &text->rect.w, &text->rect.h);
    SDL_FreeSurface(textSurface);
}


void freeText(Text * text) {
    SDL_DestroyTexture(text->texture);
    free(text);
}


void showBackground(Game * game, Map * map, Background * background) {
    int i;
    SDL_Rect tileRect;
    int tile_size = map->tile_size;
    int rows = map->rows;
    int cols = map->cols;
    SDL_RenderCopy(game->renderer, background->water, NULL, NULL);

    for (i = 0; i < cols; ++i) {
        tileRect = (SDL_Rect){(game->screensize.w/2) + (i * tile_size) / 2,
                                map->up_space + (i * tile_size) / 4,
                                tile_size, tile_size};
        SDL_RenderCopy(game->renderer, background->borders[0], NULL, &tileRect);

        tileRect = (SDL_Rect){(game->screensize.w/2) + (-rows * tile_size + i * tile_size) / 2,
                                map->up_space + (rows * tile_size + i * tile_size) / 4,
                                tile_size, tile_size};
        SDL_RenderCopy(game->renderer, background->borders[4], NULL, &tileRect);
    }

    for (i = 0; i < rows; ++i) {
        tileRect = (SDL_Rect){(game->screensize.w/2) + (cols * tile_size - i * tile_size) / 2,
                                map->up_space + (cols * tile_size + i * tile_size) / 4,
                                tile_size, tile_size};
        SDL_RenderCopy(game->renderer, background->borders[2], NULL, &tileRect);
    }

    tileRect = (SDL_Rect){(game->screensize.w/2) + (-rows * tile_size + cols * tile_size) / 2,
                            map->up_space + (rows * tile_size + cols * tile_size) / 4,
                            tile_size, tile_size};
    SDL_RenderCopy(game->renderer, background->borders[3], NULL, &tileRect);

    tileRect = (SDL_Rect){(game->screensize.w/2) + (cols * tile_size) / 2,
                            map->up_space + (cols * tile_size) / 4,
                            tile_size, tile_size};
    SDL_RenderCopy(game->renderer, background->borders[1], NULL, &tileRect);
}


void showAllEntities(Game * game, Map * map, Player * player, SDL_Texture* box, SDL_Texture* goal, SDL_Texture* rock, SDL_Texture* tex_void, SDL_Texture* goal_boxed, SDL_Texture* frog_rock, SDL_Texture* rock_submerged, SDL_Texture* frog_rock_submerged){
    int i, j;
    SDL_Rect tileRect;
    int tile_size = map->tile_size;

    for (i = 0; i < map->rows; ++i) {
        for (j = 0; j < map->cols; ++j) {
            tileRect = (SDL_Rect){(game->screensize.w/2) + (j * tile_size - i * tile_size) / 2,
                                    map->up_space + (j * tile_size + i * tile_size) / 4,
                                    tile_size, tile_size};
            switch (map->tab[i][j]) {
            case ' ': // trouver une formule math pour faire en sorte que de temps en temps il y ait une bulle
                if ((game->frame * i + j) % 16 == 0 && j != 0) {
                    SDL_RenderCopy(game->renderer, tex_void, NULL, &tileRect);
                }
                break;
            case 'W':
                if (game->frame == 0) {
                    SDL_RenderCopy(game->renderer, rock_submerged, NULL, &tileRect);
                } else {
                    SDL_RenderCopy(game->renderer, rock, NULL, &tileRect);
                }
                break;
            case 'C':
                if (game->frame == 0) --tileRect.y;
                if (map->initial_tab[i][j] == 'I') {
                    SDL_RenderCopy(game->renderer, goal_boxed, NULL, &tileRect);
                } else {
                    SDL_RenderCopy(game->renderer, box, NULL, &tileRect);
                }
                break;
            case 'I':
                if (game->frame == 0) --tileRect.y;
                SDL_RenderCopy(game->renderer, goal, NULL, &tileRect);
                break;
            case 'P':
                SDL_RenderCopy(game->renderer, player->texture[player->direction][game->frame], NULL, &tileRect);
                break;
            case 'F':
                if (game->frame == 0) {
                    SDL_RenderCopy(game->renderer, frog_rock_submerged, NULL, &tileRect);
                } else {
                    SDL_RenderCopy(game->renderer, frog_rock, NULL, &tileRect);
                }
                break;
            default:
                break;
            }
        }
    }
}


void showInteractives(Game * game, TTF_Font * font, SDL_Color text_color, Text * start, Text * level, Text * moves, Text * text_level, Text * text_moves, int map_nb, int nb_moves) {
    if (map_nb == 0) {
        SDL_RenderCopy(game->renderer, start->texture, NULL, &start->rect);
    } else {
        if (atoi(level->sentence) != map_nb) {
            char newsentence[10];
            sprintf(newsentence, "%d", map_nb);
            updateText(game, level, font, text_color, newsentence);
        }
        SDL_RenderCopy(game->renderer, text_level->texture, NULL, &text_level->rect);
        SDL_RenderCopy(game->renderer, level->texture, NULL, &level->rect);
    }
    if (atoi(moves->sentence) != nb_moves) {
        char newsentence[10];
        sprintf(newsentence, "%d", nb_moves);
        updateText(game, moves, font, text_color, newsentence);
    }
    SDL_RenderCopy(game->renderer, text_moves->texture, NULL, &text_moves->rect);
    SDL_RenderCopy(game->renderer, moves->texture, NULL, &moves->rect);
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
                if (tmp != ' ' && tmp != 'I' && tmp != 'T') map->initial_tab[i][j] = ' ';
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
    player->nb_move = 0;

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


void capFPS(Uint32 start_time) {
    Uint32 frameTime = SDL_GetTicks() - start_time;
    if (FRAME_DELAY > frameTime) {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}


void frameAnimation(Game* game, Uint32* last_animation_time){
    Uint32 current_time = SDL_GetTicks();
    if (current_time - *last_animation_time >= 400) { // en ms
        ++game->frame;
        if (game->frame > NB_ANIMATIONS - 1) game->frame = 0;
        *last_animation_time = current_time;
    }
}


Background * initBackgroundTextures(Game * game) {
    unsigned int i;
    char filename[40];
    Background * background = (Background*)malloc(sizeof(*background));
    if (!background) {
        perror("Erreur allocation des textures d'arrière plan");
        exit(EXIT_FAILURE);
    }
    background->borders = malloc(5 * sizeof(SDL_Texture *));
    for (i = 0; i < 5; ++i) {
        sprintf(filename, "%s%d%s", BORDERS_PATH, i+1, ".png");
        background->borders[i] = createEntity(filename, game);
    }
    background->water = createEntity(WATER_IMAGE, game);
    background->ground = createEntity(GROUND_IMAGE, game);

    return background;
}


void freeBackground(Background * background) {
    int i;
    for (i = 0; i < 5; ++i) {
        SDL_DestroyTexture(background->borders[i]);
    }
    SDL_DestroyTexture(background->water);
    SDL_DestroyTexture(background->ground);
    free(background);
}