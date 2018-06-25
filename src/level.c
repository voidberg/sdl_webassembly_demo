//
// Created by Alexandru Badiu on 17/06/2018.
//
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_log.h>
#include "level.h"
#include "engine.h"
#include "asset.h"

struct levelEntity* level_init(struct gameEngine *engine) {
  struct levelEntity* level = malloc(sizeof(struct levelEntity));

  level->engine = engine;

  level->texture = asset_load(level->engine, "assets/level.png");

  if (!level->texture) {
    return NULL;
  }

  level->topBox.x = 0;
  level->topBox.y = 0;
  level->topBox.w = level->engine->SCREEN_WIDTH;
  level->topBox.h = 52;

  return level;
}

void level_render(struct levelEntity* level) {
  asset_render(level->engine, 0, 0, level->engine->SCREEN_WIDTH, level->engine->SCREEN_HEIGHT, level->texture);
}

void level_destroy(struct levelEntity* level) {
  SDL_DestroyTexture(level->texture);
  free(level);
}
