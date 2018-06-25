# Directories
S_DIR=./src
B_DIR=./builds

# Files
S_FILES=$(S_DIR)/*.c

# Output
EXEC=$(B_DIR)/mac/glugglug
WEB=$(B_DIR)/web/glugglug

# Build settings
CC=gcc
EMCC=emcc

# SDL options
CC_SDL=`sdl2-config --cflags --libs`
EMCC_SDL=-s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]'  -O3 -o $(WEB).html --preload-file ./assets/ --use-preload-plugins -s "BINARYEN_TRAP_MODE='clamp'"

all:build

build:
	$(CC) $(S_FILES) -o $(EXEC) $(CC_SDL) -lSDL2_image

build_run:build
	$(EXEC)

web:
	$(EMCC) $(S_FILES) $(EMCC_SDL)

clean:
	rm $(B_DIR)/mac/glugglug
	rm $(B_DIR)/web/glugglug