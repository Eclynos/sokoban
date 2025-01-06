#ifndef CONSTANTS_H_
#define CONSTANTS_H_ 

// Taille du déplacement
#define MOVE 100
// taille prise par les tiles en px sur l'écran (devra être relatif à la taille de la fenêtre dans le futur)
#define TILE_SIZE 128
// Taille de la police
#define TEXT_SIZE 24

#define FPS 60
#define FRAME_DELAY (1000 / FPS)
#define NB_ANIMATIONS 6

#define BACKGROUND_IMAGE "./assets/background.png"

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
