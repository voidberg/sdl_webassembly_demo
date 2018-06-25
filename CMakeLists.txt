cmake_minimum_required(VERSION 3.10)
project(glugglug)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)
include_directories(src/libs)
include_directories(tmp/cJSON)
include_directories(tmp/cJSON/tests)
include_directories(tmp/cJSON/tests/unity/examples)
include_directories(tmp/cJSON/tests/unity/examples/example_1/src)
include_directories(tmp/cJSON/tests/unity/examples/example_2/src)
include_directories(tmp/cJSON/tests/unity/examples/example_3/helper)
include_directories(tmp/cJSON/tests/unity/examples/example_3/src)
include_directories(tmp/cJSON/tests/unity/extras/fixture/src)
include_directories(tmp/cJSON/tests/unity/extras/fixture/test)
include_directories(tmp/cJSON/tests/unity/src)
include_directories(tmp/cJSON/tests/unity/test/expectdata)
include_directories(tmp/cJSON/tests/unity/test/testdata)
include_directories(tmp/sdl-game-development-lessons/Chapter2)
include_directories(tmp/sdl-game-development-lessons/Chapter3)
include_directories(tmp/sdl-game-development-lessons/Chapter4)
include_directories(tmp/sdl-game-development-lessons/Chapter5)
include_directories(tmp/tmx/src)

add_executable(glugglug
        builds/web/glugglug.data
        builds/web/glugglug.html
        builds/web/glugglug.js
        builds/web/glugglug.wasm
        src/glugglug.c
        src/engine.c
        src/engine.h
        src/level.c
        src/level.h
        Makefile src/engine.h src/engine.c src/level.c src/level.h src/asset.h src/asset.c src/player.h src/player.c src/treasure.h src/treasure.c src/util.h src/util.c src/bullet.h src/bullet.c src/fish.h src/fish.c src/timer.h src/timer.c)
