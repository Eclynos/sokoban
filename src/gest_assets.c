#include "../include/gest_assets.h"


SDL_Surface* loadSurface(const char * filename, App app) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        printf("Error init image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(app.renderer);
        SDL_DestroyWindow(app.window);
        IMG_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return surface;
}


SDL_Texture* createTexture(SDL_Surface* surface, App app) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    if (!texture) {
        printf("Erreur lors de la création de la texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(app.renderer);
        SDL_DestroyWindow(app.window);
        IMG_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return texture;
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


void free2d(char ** tab, int row) {
    /*Libere la memoire utilisee par un tableau 2d*/
    int i;

    for (i = 0; i < row; ++i){
        free(tab[i]);
    }
    free(tab);
}


void readFileToTab(const char * filename, Map * map) {
    int i, j;
    FILE *file;

    file = fopen (filename, "r");
    if (file == NULL){
        exit(EXIT_FAILURE);
    }

    map->initial_tab = malloc(map->rows * sizeof(char*));
    map->tab = malloc(map->rows * sizeof(char*));
    char tmp;
    //Recupere les valeurs des cases de la map
    for (i = 0; i < map->rows; ++i){
        map->initial_tab[i] = malloc(map->cols * sizeof(char));
        map->tab[i] = malloc(map->cols * sizeof(char));
        for (j = 0; j < map->cols + 1; ++j){
            tmp = fgetc(file);
            if (tmp != '\n') {
                map->initial_tab[i][j] = tmp;
                map->tab[i][j] = tmp;
            }
        }
    }

    fclose(file);
}


void initMapData(const char * filename, Map * map) {
    char chaine[LEN_MAX];
    map->rows = 1;

    FILE *file;

    file = fopen(filename, "r");
    if (file == NULL){
        exit(EXIT_FAILURE);
    }

    for (map->rows = 0; fgetc(file) != '\n'; ++map->rows);
    
    while (fgets(chaine, LEN_MAX, file) != NULL){
        ++map->cols;
    }

    fclose(file);
}


Map * createMap(const char * filename) {
    Map * map = NULL;

    initMapData(filename, map);
    readFileToTab(filename, map);

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