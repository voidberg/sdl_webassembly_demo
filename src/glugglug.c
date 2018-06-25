#ifdef __EMSCRIPTEN__
  #include <emscripten/emscripten.h>
#endif

#include "engine.h"

int main(int argc, char* args[]) {
  engine_run("GlugGlug", 640, 480);
}