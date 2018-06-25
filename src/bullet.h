//
// Created by Alexandru Badiu on 20/06/2018.
//

#ifndef GLUGGLUG_BULLET_H
#define GLUGGLUG_BULLET_H

#include <SDL2/SDL_rect.h>
#include "player.h"

struct bulletNode {
  SDL_Rect box;

  enum Direction direction;

  struct gameEngine *engine;

  struct bulletNode* next;
};

typedef void (*bulletCallback)(struct bulletNode* data);

struct bulletNode* bullet_add(struct bulletNode* head, struct playerEntity* player);
struct bulletNode* bullet_delete(struct bulletNode* head, struct bulletNode* bullet);
void bullet_traverse(struct bulletNode* head, bulletCallback callback);
void bullet_clear(struct bulletNode* head);
void bullet_render(struct bulletNode *bullet);
void bullet_update(struct bulletNode *bullet);

#endif //GLUGGLUG_BULLET_H
