//
// Created by Alexandru Badiu on 25/06/2018.
//

#include <stdlib.h>
#include <SDL2/SDL_timer.h>
#include "timer.h"

struct timer* timer_init() {
  struct timer* t = malloc(sizeof(struct timer));
  if (t == NULL) {
    return NULL;
  }

  t->ticksStart = 0;
  t->ticksPaused = 0;

  t->paused = 0;
  t->started = 0;

  return t;
}

void timer_start(struct timer* t) {
  t->started = 1;
  t->paused = 0;

  t->ticksStart = SDL_GetTicks();
  t->ticksPaused = 0;
}

void timer_stop(struct timer* t) {
  t->started = 0;
  t->paused = 0;

  t->ticksStart = 0;
  t->ticksPaused = 0;
}

void timer_pause(struct timer* t) {
  if(t->started && !t->paused) {
    t->paused = 1;

    t->ticksPaused = SDL_GetTicks() - t->ticksStart;
    t->ticksStart = 0;
  }
}

void timer_unpause(struct timer* t) {
  if(t->started && !t->paused) {
    t->paused = 0;

    t->ticksStart = SDL_GetTicks() - t->ticksPaused;

    t->ticksPaused = 0;
  }
}

unsigned int timer_get_ticks(struct timer* t) {
  unsigned int time = 0;

  if (t->started) {
    if (t->paused) {
      time = t->ticksPaused;
    } else {
      time = SDL_GetTicks() - t->ticksStart;
    }
  }

  return time;
}

int timer_is_started(struct timer* t) {
  return t->started;
}

int timer_is_paused(struct timer* t) {
  return (t->started && t->paused);
}
