//
// Created by Alexandru Badiu on 16/06/2018.
//
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>
#include "engine.h"
#include "level.h"
#include "asset.h"
#include "player.h"
#include "treasure.h"
#include "bullet.h"
#include "fish.h"
#include "timer.h"

struct gameEngine engine;

void engine_loop() {
  engine_events(&engine);

  engine.timeStep = timer_get_ticks(engine.timer) / 1000.f;

  engine_update(&engine);

  timer_start(engine.timer);

  engine_render(&engine);
}

void engine_run(const char* title, int width, int height, float fps) {
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Game initializing.");

  engine.FPS = fps;
  engine.SCREEN_WIDTH = width;
  engine.SCREEN_HEIGHT = height;
  engine.DELAY_TIME = 1000.0f / engine.FPS;

  if (!engine_init(title, &engine)) {
    engine_quit(&engine);

    return;
  }

  engine.timer = timer_init();
  if (engine.timer == NULL) {
    engine_quit(&engine);

    return;
  }

  engine.level = level_init(&engine);
  if (engine.level == NULL) {
    engine_quit(&engine);

    return;
  }

  engine.player = player_init(&engine);
  if (engine.player == NULL) {
    engine_quit(&engine);

    return;
  }

  for (int i = Cup; i <= Jewelry; i++) {
    engine.treasures[i] = treasure_init(&engine, i);

    if (engine.treasures[i] == NULL) {
      engine_quit(&engine);

      return;
    }
  }

  engine.fish = fish_add(engine.fish, &engine, 150, 100, Right);
  engine.fish = fish_add(engine.fish, &engine, 50, 200, Right);
  engine.fish = fish_add(engine.fish, &engine, 70, 420, Right);

  engine.fish = fish_add(engine.fish, &engine, 550, 80, Left);
  engine.fish = fish_add(engine.fish, &engine, 500, 100, Left);
  engine.fish = fish_add(engine.fish, &engine, 560, 400, Left);

  engine.isRunning = 1;

  #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(engine_loop, 0, 1);
  #else
    while (engine.isRunning) {
      engine_loop();
    }
  #endif

  engine_quit(&engine);
}

int engine_init(const char* title, struct gameEngine *engine) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL failed to initialize. SDL_Error: %s", SDL_GetError());

    return 0;
  }

  engine->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, engine->SCREEN_WIDTH, engine->SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (engine->window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window failed to initialize. SDL_Error: %s", SDL_GetError());

    return 0;
  }

  engine->renderer = SDL_CreateRenderer(engine->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (engine->renderer == NULL){
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer failed to initialize. SDL_Error: %s", SDL_GetError());

    return 0;
  }

  return 1;
}

void engine_events(struct gameEngine *engine) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
      engine->isRunning = 0;

      #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
      #endif
    }

    player_events(engine->player, &event);

    for (int i = Cup; i <= Jewelry; i++) {
      treasure_events(engine->treasures[i], &event);
    }
  }
}

void bullet_update_callback(struct bulletNode* bullet) {
  bullet_update(bullet);
}

void fish_update_callback(struct fishNode* fish) {
  fish_update(fish);
}

void engine_update(struct gameEngine *engine) {
  player_update(engine->player);

  for (int i = Cup; i <= Jewelry; i++) {
    treasure_update(engine->treasures[i]);
  }

  bullet_traverse(engine->bullets, bullet_update_callback);

  fish_traverse(engine->fish, fish_update_callback);
}

void bullet_render_callback(struct bulletNode* bullet) {
  bullet_render(bullet);
}

void fish_render_callback(struct fishNode* fish) {
  fish_render(fish);
}

void engine_render(struct gameEngine *engine) {
  SDL_RenderClear(engine->renderer);

  level_render(engine->level);
  player_render(engine->player);

  for (int i = Cup; i <= Jewelry; i++) {
    treasure_render(engine->treasures[i]);
  }

  bullet_traverse(engine->bullets, bullet_render_callback);

  fish_traverse(engine->fish, fish_render_callback);

  SDL_RenderPresent(engine->renderer);
}

void engine_quit(struct gameEngine *engine) {
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Game quitting.");

  level_destroy(engine->level);
  player_destroy(engine->player);

  for (int i = 0; i < 3; i++) {
    treasure_destroy(engine->treasures[i]);
  }

  bullet_clear(engine->bullets);

  fish_clear(engine->fish);

  if (engine->renderer) {
    SDL_DestroyRenderer(engine->renderer);
    engine->renderer = NULL;
  }

  if (engine->window) {
    SDL_DestroyWindow(engine->window);
    engine->window = NULL;
  }

  if (engine->timer) {
    free(engine->timer);
  }

  SDL_Quit();
}
