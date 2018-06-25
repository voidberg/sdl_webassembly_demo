//
// Created by Alexandru Badiu on 17/06/2018.
//

#ifndef GLUGGLUG_LEVEL_H
#define GLUGGLUG_LEVEL_H

struct levelEntity {
  SDL_Texture *texture;

  SDL_Rect topBox;
  SDL_Rect bottomBox;

  struct gameEngine *engine;
};

struct levelEntity* level_init(struct gameEngine *engine);
void level_render(struct levelEntity* level);
void level_destroy(struct levelEntity* level);

#endif //GLUGGLUG_LEVEL_H
