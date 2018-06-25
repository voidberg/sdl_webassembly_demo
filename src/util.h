//
// Created by Alexandru Badiu on 18/06/2018.
//

#ifndef GLUGGLUG_UTIL_H
#define GLUGGLUG_UTIL_H

#include <SDL2/SDL_rect.h>

enum Direction { Left = 0, Right, Up, Down };
enum TreasureType { Cup = 0, Chest, Jewelry };
enum PlayerState { Free = 0, Carrying, Dying };
enum TreasureState { Sitting = 0, Carried, Deposited };

int collisionCheck(SDL_Rect a, SDL_Rect b);

#endif //GLUGGLUG_UTIL_H
