//
// Created by Alexandru Badiu on 25/06/2018.
//

#ifndef GLUGGLUG_TIMER_H
#define GLUGGLUG_TIMER_H

struct timer {
  unsigned int ticksStart;
  unsigned int ticksPaused;

  int paused;
  int started;
};

struct timer* timer_init();
void timer_start(struct timer* t);
void timer_stop(struct timer* t);
void timer_pause(struct timer* t);
void timer_unpause(struct timer* t);
unsigned int timer_get_ticks(struct timer* t);
int timer_is_started(struct timer* t);
int timer_is_paused(struct timer* t);

#endif //GLUGGLUG_TIMER_H
