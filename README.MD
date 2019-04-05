# Dotma's 2D Game Engine

## Compilation

The build requires GNU binutils, so if you are on a system without them (Windows) you need to install them (MinGW).

### Windows
- Requires mingw32, gcc, make, sdl2(mingw32), sdl_image(mingw32), sdl_ttf(mingw32) and sdl_mixer(mingw32)
- MinGW can be found here -> http://www.mingw.org/
- SDL2 development libraries for MinGW and runtime dlls can be found here -> https://www.libsdl.org/download-2.0.php
- SDL_image development and runtime -> https://www.libsdl.org/projects/SDL_image/
- SDL_ttf development and runtime -> https://www.libsdl.org/projects/SDL_ttf/
- SDL_mixer development and runtime -> https://www.libsdl.org/projects/SDL_mixer/

### Linux
- Install sdl2-dev, sdl2-image, sdl2-ttf and sdl2-mixer from your favorite package manager
- apt `sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev`
- pacman `sudo pacman -Syu sdl2 sdl2_image sdl2_ttf sdl2_mixer`

### macOS
- Install sdl2, sdl2_image, sdl2_ttf and sdl2_mixer using the Homebrew package manager
- brew `brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer

### To compile on all supported operating systems;
- `make` or `make -j` (to use multiple threads for jobs which us usually faster!)
- `make debug` to build with debug messages enabled
- `make clean` to clean the built objects and output exectutable

## Running
Currently only runs when executed from the executables root directory. This will be changed later but it currently relies on it's working environment being its directory so executing it like `./stuff/output.exe` would prevent it from finding its assets.
For now just ensure you are in the same directory before executing it. (Clicking on the .exe or .out works too!).

## About
Simple engine for rendering 2d texutures with simple sound playback and user interaction.
This project was started to help a friend make his dream game (a visual novel) however eventually the base of this engine may be added to, in order to support more advanced functions and mechanics.

## Licence
This repo is licenced under GPL-3
