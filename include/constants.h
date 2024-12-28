#ifndef CONSTANTS_H_
#define CONSTANTS_H_ 

// Taille du déplacement
#define MOVE 100
// taille prise par les tiles en px sur l'écran (devra être relatif à la taille de la fenêtre dans le futur)
#define TILE_SIZE 128

#define FPS 60
#define FRAME_DELAY (1000 / FPS)

#define BACKGROUND_IMAGE "./assets/background.png"
#define CHARACTER_IMAGE "./assets/capy.png"

#define BOX_IMAGE "./assets/box.png"
#define GOAL_IMAGE "./assets/goal.png"
#define WALL_IMAGE "./assets/wall.png"
#define VOID_IMAGE "./assets/void.png"

#define FILE_MAP_1 "./map/map1.txt"

#endif // !CONSTANTS_H_
