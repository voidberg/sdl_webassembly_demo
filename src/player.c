//
// Created by Alexandru Badiu on 17/06/2018.
//

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>
#include "engine.h"
#include "asset.h"
#include "player.h"
#include "util.h"
#include "level.h"
#include "bullet.h"

const int PLAYER_VELOCITY = 100 * 4;
const int PLAYER_FRAMES = 6;

struct playerEntity* player_init(struct gameEngine *engine) {
  struct playerEntity* player = malloc(sizeof(struct playerEntity));

  player->engine = engine;

  player->shipTexture = asset_load(player->engine, "assets/ship.png");
  player->playerTexture = asset_load(player->engine, "assets/player.png");

  if (!player->shipTexture || !player->playerTexture) {
    return NULL;
  }

  player->box.x = engine->SCREEN_WIDTH / 2 - 31;
  player->box.y = 20;
  player->box.w = 39;
  player->box.h = 54;

  player->vx = 0;
  player->vy = 0;

  player->direction = Right;
  player->state = Free;

  SDL_QueryTexture(player->shipTexture, NULL, NULL, &player->shipBox.w, &player->shipBox.h);
//  SDL_QueryTexture(player->playerTexture, NULL, NULL, &player->box.w, &player->box.h);

  return player;
}

void player_events(struct playerEntity *player, SDL_Event *event) {
  if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
    switch(event->key.keysym.sym) {
      case SDLK_LEFT:
        player->vx -= PLAYER_VELOCITY;
        player->direction = Left;
        break;

      case SDLK_RIGHT:
        player->vx += PLAYER_VELOCITY;
        player->direction = Right;
        break;

      case SDLK_UP:
        player->vy -= PLAYER_VELOCITY;
        break;

      case SDLK_DOWN:
        player->vy += PLAYER_VELOCITY;
        break;

      case SDLK_SPACE:
        player_shoot(player);
        break;
    }
  }

  if (event->type == SDL_KEYUP && event->key.repeat == 0) {
    switch(event->key.keysym.sym) {
      case SDLK_LEFT:
        player->vx += PLAYER_VELOCITY;
        break;

      case SDLK_RIGHT:
        player->vx -= PLAYER_VELOCITY;
        break;

      case SDLK_UP:
        player->vy += PLAYER_VELOCITY;
        break;

      case SDLK_DOWN:
        player->vy -= PLAYER_VELOCITY;
        break;
    }
  }
}

void player_update(struct playerEntity *player) {
//  if (player->vx != 0 || player->vy != 0) {
//    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "VX: %f, VY: %f.", player->vx / player->engine->FPS, player->vy / player->engine->FPS);
//  }
  struct levelEntity* level = player->engine->level;

  player->box.x += player->vx * player->engine->timeStep;
  player->box.y += player->vy * player->engine->timeStep;

  if (player->box.x < 0) {
    player->box.x = 0;
  }

  if (player->box.x > player->engine->SCREEN_WIDTH - player->box.w) {
    player->box.x = player->engine->SCREEN_WIDTH - player->box.w;
  }

  if (player->box.y < 20) {
    player->box.y = 20;
  }

  if (player->box.y > player->engine->SCREEN_HEIGHT - 70) {
    player->box.y = player->engine->SCREEN_HEIGHT - 70;
  }
}

void player_render(struct playerEntity *player) {
  int sprite = (SDL_GetTicks() / 200) % PLAYER_FRAMES;

  int distance = player->box.y;

  SDL_SetRenderDrawColor(player->engine->renderer, 12, 26, 32, 255);

  SDL_Rect lineRect = { player->box.x + (player->box.w / 2), 14, 2, 2 };
  for (int y = 0; y < distance / 4; y++) {
    SDL_RenderFillRect(player->engine->renderer, &lineRect);
    lineRect.y += 4;
  }

  SDL_Rect dRect = { player->box.x, player->box.y, player->box.w, player->box.h };
  SDL_Rect sRect = { sprite * player->box.w, 0, player->box.w, player->box.h };

  asset_render_ex(player->engine, sRect, dRect, player->playerTexture, player->direction == Left);

  asset_render(player->engine, player->box.x - 242, -40, player->shipBox.w, player->shipBox.h, player->shipTexture);
}

void player_destroy(struct playerEntity* player) {
  SDL_DestroyTexture(player->shipTexture);
  SDL_DestroyTexture(player->playerTexture);

  free(player);
}

void player_shoot(struct playerEntity* player) {
  player->engine->bullets = bullet_add(player->engine->bullets, player);
}