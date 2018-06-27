//
// Created by Alexandru Badiu on 22/06/2018.
//

#ifndef GLUGGLUG_FISH_H
#define GLUGGLUG_FISH_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_system.h>
#include "util.h"

struct fishNode {
  SDL_Rect box;
  SDL_Texture *texture;
  SDL_Texture *deathTexture;

  enum Direction direction;
  enum EnemyState state;

  struct gameEngine *engine;

  struct fishNode* next;
};

typedef void (*fishCallback)(struct fishNode* data);

struct fishNode* fish_add(struct fishNode* head, struct gameEngine* engine, int x, int y, enum Direction direction);
struct fishNode* fish_delete(struct fishNode* head, struct fishNode* fish);
void fish_traverse(struct fishNode* head, fishCallback callback);
void fish_clear(struct fishNode* head);

void fish_render(struct fishNode *fish);
void fish_update(struct fishNode *fish);

void fish_destroy(struct fishNode *fish);

#endif //GLUGGLUG_FISH_H
