//
// Created by Alexandru Badiu on 18/06/2018.
//

#ifndef GLUGGLUG_TREASURE_H
#define GLUGGLUG_TREASURE_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include "util.h"

struct treasureEntity {
  SDL_Texture *treasureTexture;

  int show;

  SDL_Rect box;

  enum TreasureType type;
  enum TreasureState state;

  struct gameEngine *engine;
};

struct treasureEntity *treasure_init(struct gameEngine *engine, enum TreasureType type);
void treasure_events(struct treasureEntity *treasure, SDL_Event *event);
void treasure_update(struct treasureEntity *treasure);
void treasure_render(struct treasureEntity *treasure);
void treasure_destroy(struct treasureEntity* treasure);

#endif //GLUGGLUG_TREASURE_H
