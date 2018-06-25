//
// Created by Alexandru Badiu on 17/06/2018.
//

#ifndef GLUGGLUG_PLAYER_H
#define GLUGGLUG_PLAYER_H

#include <SDL2/SDL_events.h>
#include "engine.h"
#include "util.h"

struct playerEntity {
  SDL_Texture *shipTexture;
  SDL_Texture *playerTexture;

  SDL_Rect box;
  SDL_Rect shipBox;

  int vx;
  int vy;

  enum Direction direction;
  enum PlayerState state;

  struct gameEngine *engine;
};

struct playerEntity *player_init(struct gameEngine *engine);
void player_events(struct playerEntity *player, SDL_Event *event);
void player_update(struct playerEntity *player);
void player_render(struct playerEntity *player);
void player_destroy(struct playerEntity* player);
void player_shoot(struct playerEntity* player);

#endif //GLUGGLUG_PLAYER_H
