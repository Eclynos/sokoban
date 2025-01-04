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
#define WALL_IMAGE "./assets/wall.png"
#define VOID_IMAGE "./assets/void.png"
#define GOAL_BOXED_IMAGE "./assets/nenuphar_with_orange.png"

#define NUMBER_OF_MAP 3
#define FILE_MAP_START "./map/start_map.txt"
#define FILE_MAP_1 "./map/map1.txt"
#define FILE_MAP_2 "./map/map2.txt"
#define MAP_TAB FILE_MAP_START, FILE_MAP_1, FILE_MAP_2

 


#define FILE_FONT "./fonts/dejavu-fonts-ttf-2.37/ttf/DejaVuSansMono.ttf"

#endif // !CONSTANTS_H_
