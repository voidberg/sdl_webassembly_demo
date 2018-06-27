//
// Created by Alexandru Badiu on 22/06/2018.
//

#include <stdlib.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_log.h>
#include "fish.h"
#include "asset.h"

const int FISH_VELOCITY = 100;
const int FISH_FRAMES = 4;
const int DEATH_FRAMES = 6;

struct fishNode* fish_add(struct fishNode* head, struct gameEngine* engine, int x, int y, enum Direction direction) {
  struct fishNode* node = malloc(sizeof(struct fishNode));

  if (node == NULL) {
    return NULL;
  }

  node->texture = asset_load(engine, "assets/fish.png");
  if (node->texture == NULL) {
    return NULL;
  }

  node->deathTexture = asset_load(engine, "assets/death.png");
  if (node->deathTexture == NULL) {
    return NULL;
  }

  node->engine = engine;
  node->direction = direction;
  node->state = Alive;

  node->box.w = 32;
  node->box.h = 32;
  node->box.x = x;
  node->box.y = y;

  node->next = head;

  return node;

}

struct fishNode* _fish_remove_front(struct fishNode* head) {
  if (head == NULL) {
    return NULL;
  }

  struct fishNode* front = head;
  head = head->next;
  front->next = NULL;

  if (front == head) {
    head = NULL;
  }

  fish_destroy(front);

  return head;
}

struct fishNode* _fish_remove_back(struct fishNode* head) {
  if (head == NULL) {
    return NULL;
  }

  struct fishNode* cursor = head;
  struct fishNode* back = NULL;

  while (cursor->next != NULL) {
    back = cursor;
    cursor = cursor->next;
  }

  if (back != NULL) {
    back->next = NULL;
  }

  if (cursor == head) {
    head = NULL;
  }

  fish_destroy(cursor);

  return head;
}

struct fishNode* fish_delete(struct fishNode* head, struct fishNode* fish) {
  if (head == fish) {
    head = _fish_remove_front(head);
    return head;
  }

  if(fish->next == NULL) {
    head = _fish_remove_back(head);
    return head;
  }

  struct fishNode* cursor = head;
  while (cursor != NULL) {
    if(cursor->next == fish) {
      break;
    }
    cursor = cursor->next;
  }

  if (cursor != NULL) {
    struct fishNode* tmp = cursor->next;
    cursor->next = tmp->next;
    tmp->next = NULL;

    fish_destroy(tmp);
  }

  return head;
}

void fish_traverse(struct fishNode* head, fishCallback callback) {
  struct fishNode* cursor = head;
  while (cursor != NULL) {
    callback(cursor);
    cursor = cursor->next;
  }
}

void fish_clear(struct fishNode* head) {
  struct fishNode* cursor, *tmp;

  if (head != NULL) {
    cursor = head->next;
    head->next = NULL;

    while (cursor != NULL) {
      tmp = cursor->next;
      fish_destroy(cursor);
      cursor = tmp;
    }
  }
}

void fish_render(struct fishNode *fish) {
  int sprite;

  if (fish->state == Alive) {
    sprite = (SDL_GetTicks() / 200) % FISH_FRAMES;

    SDL_Rect dRect = { fish->box.x, fish->box.y, fish->box.w, fish->box.h };
    SDL_Rect sRect = { sprite * fish->box.w, 0, fish->box.w, fish->box.h };

    asset_render_ex(fish->engine, sRect, dRect, fish->texture, fish->direction == Left);
  }

  if (fish->state == Dying) {
    sprite = (SDL_GetTicks() / 200) % DEATH_FRAMES;

    SDL_Rect dRect = { fish->box.x, fish->box.y, 52, 53 };
    SDL_Rect sRect = { sprite * 52, 0, 52, 53 };

    asset_render_ex(fish->engine, sRect, dRect, fish->deathTexture, fish->direction == Left);

    if (sprite == DEATH_FRAMES - 1) {
      fish->state = Dead;
    }
  }
}

void fish_update(struct fishNode *fish) {
  if (fish->state == Alive) {
    fish->box.x += (fish->direction == Left ? -FISH_VELOCITY : FISH_VELOCITY) * fish->engine->timeStep;

    if (fish->box.x < -fish->box.w) {
      fish->box.x = fish->engine->SCREEN_WIDTH;
    }

    if (fish->box.x > fish->engine->SCREEN_WIDTH + fish->box.w) {
      fish->box.x = 0;
    }
  }

//  if (fish->state == Dead) {
//    struct gameEngine* engine;
//
//    engine->fish = fish_delete(engine->fish, fish);
//  }
}

void fish_destroy(struct fishNode *fish) {
  SDL_DestroyTexture(fish->texture);
  free(fish);
}