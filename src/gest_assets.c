#include "../include/gest_assets.h"
#define LEN_MAX 500

void print2d(char ** tab, int row, int col){
    /*Affiche tout les elements d'un tableau 2d*/
    int i, j;
    for (i=0; i<row; ++i){
        for (j=0; j<col; ++j){
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}

void free2d(char ** tab, int row){
    /*Libere la memoire utilisee par un tableau 2d*/
    int i;

    for (i=0; i<row; ++i){
        free(tab[i]);
    }
    free(tab);
}

char ** readFileToTab(const char * filename, int row, int col){
    int i, j;
    FILE *file;

    file = fopen (filename, "r");
    if (file == NULL){
        exit(EXIT_FAILURE);
    }

    char ** tab_data = malloc(row * sizeof(*tab_data));
    char tmp;
    //Recupere les valeurs des cases de la map
    for (i=0; i<row; ++i){
        tab_data[i] = malloc(col * sizeof(*tab_data[i]));
        for (j=0; j<col+1; ++j){
            tmp = fgetc(file);
            if (tmp != '\n') tab_data[i][j] = tmp;
        }
    }

    fclose(file);
    return tab_data; 
}

int * dataMap(const char * filename){
    char chaine[LEN_MAX];
    int * map_data = malloc(2 * sizeof(map_data));
    map_data[0] = 1;

    FILE *file;

    file = fopen (filename, "r");
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

void createMap(){
    int * map_data = dataMap("./map/map1.txt");
    printf("%d %d\n", map_data[0], map_data[1]);
    char ** tab = readFileToTab("./map/map1.txt", map_data[0], map_data[1]);
    print2d(tab, map_data[0], map_data[1]);

    free2d(tab, map_data[0]);
    free(map_data);
}


texture ** initGrille(char ** grille_txt, int len){
    texture ** tab_game = malloc(len * sizeof(*tab_game));

    return tab_game;
}

