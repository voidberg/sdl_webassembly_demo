//
// Created by Alexandru Badiu on 16/06/2018.
//

#ifndef GLUGGLUG_ENGINE_H
#define GLUGGLUG_ENGINE_H

#include <SDL2/SDL_render.h>

struct gameEngine {
  int SCREEN_WIDTH;
  int SCREEN_HEIGHT;
  float FPS;
  int DELAY_TIME;

  SDL_Window* window;
  SDL_Renderer* renderer;

  int isRunning;

  struct timer* timer;
  float timeStep;

  struct levelEntity* level;
  struct playerEntity* player;
  struct treasureEntity* treasures[3];
  struct bulletNode* bullets;
  struct fishNode* fish;
};

void engine_run(const char* title, int width, int height, float fps);
int engine_init(const char* title, struct gameEngine* engine);

void engine_events(struct gameEngine* engine);
void engine_update(struct gameEngine* engine);
void engine_render(struct gameEngine* engine);

void engine_quit(struct gameEngine* engine);

#endif //GLUGGLUG_ENGINE_H
