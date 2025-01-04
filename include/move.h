#ifndef MOVE_H_
#define MOVE_H_

#include <stdio.h>
#include <stdlib.h>
#include "../include/gest_assets.h"


void move(Map* map, Player* player, char sens);
int verif_win(Map * map);

#endif // !MOVE_H_
