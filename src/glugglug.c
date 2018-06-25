#ifdef __EMSCRIPTEN__
  #include <emscripten/emscripten.h>
#endif

#include "engine.h"

/**
 * https://www.reddit.com/r/learnprogramming/comments/1qiwes/c_following_sdl_game_development_book_state/
 * 
 */

int main(int argc, char* args[]) {
  engine_run("GlugGlug", 640, 480, 60.0);
}

//const int FPS = 60;
//const int DELAY_TIME = 1000.0f / FPS;
//
//Game* g_game = 0;
//Uint32 frameStart, frameTime;
//
//void gameLoop() {
//  frameStart = SDL_GetTicks();
//
//  g_game->handleEvents();
//  g_game->update();
//  g_game->render();
//
//  frameTime = SDL_GetTicks() - frameStart;
//
//  if (frameTime< DELAY_TIME) {
//    SDL_Delay((int)(DELAY_TIME - frameTime));
//  }
//}
//
//int main(int argc, char* args[]) {
//  g_game = new Game();
//
//  if (!g_game->init("Level 1", 100, 100, 640, 480, 0)) {
//    return 0;
//  }
//
//  #ifdef __EMSCRIPTEN__
//    emscripten_set_main_loop(gameLoop, 0, 1);
//  #else
//    while(g_game->isRunning()) {
//      gameLoop();
//    }
//  #endif
//
//  g_game->clean();
//}