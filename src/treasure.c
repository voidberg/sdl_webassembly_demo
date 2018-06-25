//
// Created by Alexandru Badiu on 18/06/2018.
//

#include <SDL2/SDL_log.h>
#include "treasure.h"
#include "asset.h"
#include "player.h"
#include "level.h"

struct treasureEntity* treasure_init(struct gameEngine *engine, enum TreasureType type) {
  int part;
  struct treasureEntity* treasure = malloc(sizeof(struct treasureEntity));

  treasure->engine = engine;
  treasure->type = type;
  treasure->state = Sitting;

  if (type == Cup) {
    treasure->treasureTexture= asset_load(treasure->engine, "assets/cup.png");
    part = 0;
  }

  if (type == Jewelry) {
    treasure->treasureTexture= asset_load(treasure->engine, "assets/jewelry.png");
    part = 1;
  }

  if (type == Chest) {
    treasure->treasureTexture= asset_load(treasure->engine, "assets/chest.png");
    part = 2;
  }

  if (!treasure->treasureTexture) {
    return NULL;
  }

  SDL_QueryTexture(treasure->treasureTexture, NULL, NULL, &treasure->box.w, &treasure->box.h);

  treasure->box.x = part * engine->SCREEN_WIDTH / 3 + rand() % (engine->SCREEN_WIDTH / 3);
  treasure->box.y = treasure->engine->SCREEN_HEIGHT - (16 + treasure->box.h);
  treasure->show = 1;

  return treasure;
}

void treasure_events(struct treasureEntity *treasure, SDL_Event *event) {

}

void treasure_update(struct treasureEntity *treasure) {
  struct playerEntity* player = treasure->engine->player;
  struct levelEntity* level = treasure->engine->level;

  if (treasure->state == Deposited) {
    return;
  }

  if (player->state == Free) {
    if (collisionCheck(treasure->box, player->box)) {
      player->state = Carrying;
      treasure->state = Carried;
    }
  }

  if (treasure->state == Carried) {
    treasure->box.x = player->box.x + player->box.w - 14;
    treasure->box.y = player->box.y + player->box.h - 14;

    if (collisionCheck(player->box, level->topBox)) {
      treasure->state = Deposited;
      treasure->show = 0;

      player->state = Free;
    }

    if (collisionCheck(treasure->box, level->bottomBox)) {
      treasure->box.y = treasure->engine->SCREEN_HEIGHT - (treasure->box.h + level->bottomBox.h);
    }
  }
}

void treasure_render(struct treasureEntity *treasure) {
  if (treasure->show) {
    asset_render(treasure->engine, treasure->box.x, treasure->box.y, treasure->box.w, treasure->box.h, treasure->treasureTexture);
  }
}

void treasure_destroy(struct treasureEntity* treasure) {
  SDL_DestroyTexture(treasure->treasureTexture);

  free(treasure);
}