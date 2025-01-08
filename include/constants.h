#ifndef CONSTANTS_H_
#define CONSTANTS_H_ 

/**
 * \file constants.h
 * \brief Contient toutes les constantes utiles pour le fonctionnement du programme
 */

// Taille de la police
#define TEXT_SIZE 24

#define FPS 60
#define FRAME_DELAY (1000 / FPS)
#define NB_ANIMATIONS 6
#define MS_BETWEEN_ANIMATIONS 350

#define WATERFALL_SIZE 5

#define WATER_IMAGE "./assets/background.png"
#define GROUND_IMAGE "./assets/borders/ground.png"
#define CLIFF_IMAGE "./assets/cliff/cliff.png"
#define BORDERS_PATH "./assets/borders/"
#define WATERFALL_PATH "./assets/cliff/waterfall"
#define MOVING_WATER_PATH "./assets/cliff/water"

#define CAPY_PATH "./assets/capy/"

#define BOX_IMAGE "./assets/orange.png"
#define GOAL_IMAGE "./assets/nenuphar.png"
#define ROCK_IMAGE "./assets/rock.png"
#define VOID_IMAGE "./assets/void.png"
#define FROG_IMAGE "./assets/rock_with_frog.png"
#define GOAL_BOXED_IMAGE "./assets/nenuphar_with_orange.png"
#define ROCK_SUBMERGED_IMAGE "./assets/rock_submerged.png"
#define FROG_ROCK_SUBMERGED_IMAGE "./assets/rock_with_frog_submerged.png"

#define NUMBER_OF_MAP 4
#define FILE_MAP_START "./map/start_map.txt"
#define FILE_MAP_1 "./map/map1.txt"
#define FILE_MAP_2 "./map/map2.txt"
#define FILE_MAP_3 "./map/map3.txt"
#define MAP_TAB FILE_MAP_START, FILE_MAP_1, FILE_MAP_2, FILE_MAP_3

#define FILE_FONT "./fonts/dejavu-fonts-ttf-2.37/ttf/DejaVuSansMono.ttf"

#endif // !CONSTANTS_H_