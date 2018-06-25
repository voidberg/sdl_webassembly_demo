//
// Created by Alexandru Badiu on 17/06/2018.
//

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "engine.h"

SDL_Texture *asset_load(struct gameEngine *engine, char path[]) {
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load(path);

  if (loadedSurface == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load image %s. SDL_image Error: %s", path, IMG_GetError());
  } else {
    newTexture = SDL_CreateTextureFromSurface(engine->renderer, loadedSurface);

    if (newTexture == NULL) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create texture from %s. SDL Error: %s", path, SDL_GetError());
    }

    SDL_FreeSurface(loadedSurface);
  }

  return newTexture;
}

void asset_render_ex(struct gameEngine *engine, SDL_Rect sRect, SDL_Rect dRect, SDL_Texture *texture, int flip) {
  SDL_RenderCopyEx(engine->renderer, texture, &sRect, &dRect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void asset_render(struct gameEngine *engine, int x, int y, int w, int h, SDL_Texture *texture) {
  SDL_Rect dRect = { x, y, w, h };

  SDL_RenderCopy(engine->renderer, texture, NULL, &dRect);
}