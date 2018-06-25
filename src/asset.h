//
// Created by Alexandru Badiu on 17/06/2018.
//

#include <SDL2/SDL_render.h>
#include "engine.h"

#ifndef GLUGGLUG_ASSET_H
#define GLUGGLUG_ASSET_H

SDL_Texture *asset_load(struct gameEngine *engine, char path[]);
void asset_render_ex(struct gameEngine *engine, SDL_Rect sRect, SDL_Rect dRect, SDL_Texture *texture, int flip);
void asset_render(struct gameEngine *engine, int x, int y, int w, int h, SDL_Texture *texture);

#endif //GLUGGLUG_ASSET_H