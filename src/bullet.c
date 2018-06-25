//
// Created by Alexandru Badiu on 20/06/2018.
//
#include "bullet.h"

const int BULLET_VELOCITY = 150;

struct bulletNode* bullet_add(struct bulletNode* head, struct playerEntity* player) {
  struct bulletNode* node = malloc(sizeof(struct bulletNode));

  node->engine = player->engine;
  node->direction = player->direction;

  node->box.y = player->box.y + 26;
  node->box.w = 20;
  node->box.h = 2;

  if (node->direction == Left) {
    node->box.x = player->box.x - (node->box.w);
  } else {
    node->box.x = player->box.x + player->box.w;
  }

  node->next = head;

  return node;
}

void bullet_traverse(struct bulletNode* head, bulletCallback callback) {
  struct bulletNode* cursor = head;
  while (cursor != NULL) {
    callback(cursor);
    cursor = cursor->next;
  }
}

struct bulletNode* _bullet_remove_front(struct bulletNode* head)
{
  if (head == NULL) {
    return NULL;
  }

  struct bulletNode* front = head;
  head = head->next;
  front->next = NULL;

  if(front == head) {
    head = NULL;
  }

  free(front);

  return head;
}

struct bulletNode* _bullet_remove_back(struct bulletNode* head) {
  if (head == NULL) {
    return NULL;
  }

  struct bulletNode* cursor = head;
  struct bulletNode* back = NULL;

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

  free(cursor);

  return head;
}

struct bulletNode* bullet_delete(struct bulletNode* head, struct bulletNode* bullet) {
  if (head == bullet) {
    head = _bullet_remove_front(head);
    return head;
  }

  if(bullet->next == NULL) {
    head = _bullet_remove_back(head);
    return head;
  }

  struct bulletNode* cursor = head;
  while (cursor != NULL) {
    if(cursor->next == bullet) {
      break;
    }
    cursor = cursor->next;
  }

  if (cursor != NULL) {
    struct bulletNode* tmp = cursor->next;
    cursor->next = tmp->next;
    tmp->next = NULL;
    free(tmp);
  }

  return head;
}

void bullet_clear(struct bulletNode* head) {
  struct bulletNode* cursor, *tmp;

  if (head != NULL) {
    cursor = head->next;
    head->next = NULL;

    while (cursor != NULL) {
      tmp = cursor->next;
      free(cursor);
      cursor = tmp;
    }
  }
}

void bullet_render(struct bulletNode *bullet) {
  SDL_SetRenderDrawColor(bullet->engine->renderer, 122, 235, 243, 255);
  SDL_RenderFillRect(bullet->engine->renderer, &bullet->box);
}

void bullet_update(struct bulletNode *bullet) {
  bullet->box.x += (bullet->direction == Left ? -BULLET_VELOCITY : BULLET_VELOCITY) * bullet->engine->timeStep;

  if (bullet->box.x > bullet->engine->SCREEN_WIDTH) {
    bullet->engine->bullets = bullet_delete(bullet->engine->bullets, bullet);
    return;
  }

  if (bullet->box.x < -bullet->box.w) {
    bullet->engine->bullets = bullet_delete(bullet->engine->bullets, bullet);
    return;
  }
}