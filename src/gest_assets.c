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


char ** readFileToTab(const char * filename, int row, int col) {
    int i, j;
    FILE *file;

    file = fopen (filename, "r");
    if (file == NULL){
        exit(EXIT_FAILURE);
    }

    char ** tab_data = malloc(row * sizeof(*tab_data));
    char tmp;
    //Recupere les valeurs des cases de la map
    for (i = 0; i < row; ++i){
        tab_data[i] = malloc(col * sizeof(*tab_data[i]));
        for (j = 0; j < col + 1; ++j){
            tmp = fgetc(file);
            if (tmp != '\n') tab_data[i][j] = tmp;
        }
    }

    fclose(file);
    return tab_data;
}


int * dataMap(const char * filename) {
    char chaine[LEN_MAX];
    int * map_data = malloc(2 * sizeof(map_data));
    map_data[0] = 1;

    FILE *file;

    file = fopen(filename, "r");
    if (file == NULL){
        exit(EXIT_FAILURE);
    }

    for (map_data[1] = 0; fgetc(file) != '\n'; ++map_data[1]);
    
    while (fgets(chaine, LEN_MAX, file) != NULL){
        ++map_data[0];
    }

    fclose(file);
    return map_data;
}


void createMap(App app) {
    int * map_data = dataMap(FILE_MAP_1);
    //printf("%d %d\n", map_data[0], map_data[1]);
    char ** tab = readFileToTab(FILE_MAP_1, map_data[0], map_data[1]);
    //print2d(tab, map_data[0], map_data[1]);
    object ** tab_game = initTexturesVars(tab, app, map_data[0], map_data[1]);

    free2d(tab, map_data[0]);
    free(map_data);
}


object ** initTexturesVars(char ** char_grid, App app, int row, int col) {
    int i, j;
    object ** tab_game = malloc(row * sizeof(object*));

    SDL_Surface* surface_box = loadSurface(BOX_IMAGE, app);
    SDL_Surface* surface_goal = loadSurface(GOAL_IMAGE, app);
    SDL_Surface* surface_wall = loadSurface(WALL_IMAGE, app);

    SDL_Texture* texture_box = createTexture(surface_box, app);
    SDL_Texture* texture_goal = createTexture(surface_goal, app);
    SDL_Texture* texture_wall = createTexture(surface_wall, app);

    for (i = 0; i < row; ++i) {
        tab_game[i] = malloc(col * sizeof(object));
        for (j = 0; j < col; ++j) {
            if (char_grid[i][j] == '#') {
                
            }
        }
    }

    return tab_game;
}


void update_textures(App app) {

}
