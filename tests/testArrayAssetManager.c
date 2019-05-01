#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../include/Managers/assetmanager.h"

/**
 *  Initialize SDL components.
 */
 static bool init_modules(void) {
    // Start SDL and components.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        return false;
    }
    if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) == 0) {
        return false;
    }
    if (TTF_Init() != 0) {
        return false;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        return false;    
    }
    return true;
 }

/**
 * Quit SDL components.
 */
 static void quit_modules(void) {
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
 }

/**
 * Entry point for the engine.
 */
int main(int argc, char** argv) {
    // Start all major game components.
    if (!init_modules()) {
        return 1;
    }
    // Required initialisation.
    SDL_Window* window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, 720, 420, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    AssetManager assetManager;
    initializeAssetManager(&assetManager);

    for (int i = 0; i < 50; i++) {
        loadAssets(renderer, &assetManager, "../bin/res/debug.manifest");
    }

    freeAssets(&assetManager);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    quit_modules();
    return 0;
}
