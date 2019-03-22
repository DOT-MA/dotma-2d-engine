#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../include/framerate.h"
#include "../include/assetmanager.h"
#include "../include/eventmanager.h"
#include "../include/renderer.h"
#include "../include/renderertemplates.h"

#include "../include/Entities/cat.h"
#include "../include/Entities/button.h"

#include "../include/game.h"

/**
 *  Initialize SDL components.
 */
 bool initModules(void) {
    // Start SDL and components.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Unable to initialize SDL_image\n");
        return false;
    }
    if (TTF_Init() != 0) {
        fprintf(stderr, "Unable to initialize SDL_ttf\n");
        return false;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        fprintf(stderr, "Unable to initialize SDL_mixer\n");
        return false;    
    }
    return true;
 }

/**
 * Quit SDL components.
 */
 void quitModules(void) {
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
 }

/**
 * Entry point for the engine.
 */
int main(int argc, char* argv[]) {
    // Start all major game components.
    if (!initModules()) {
        return 1;
    }
    // Load game components and state.
    GameData gameData;
    if (!initGame(&gameData)) {
        fprintf(stderr, "Unable to initialize game modules.\n");
        return 2;
    }
    // Load game assets.
    if (!loadAssets(gameData.renderer, &gameData.assets, "./res/debug.manifest")) {
        fprintf(stderr, "Unable to load assets.\n");
        SDL_Quit();
        return 3;
    }
    
    addEntity(&gameData.entities, &gameData.assets, &initCat);
    addEntity(&gameData.entities, &gameData.assets, &initButton);

    // Main game loop.
    while (gameData.status) {
        while (SDL_PollEvent(&gameData.event)) {
            eventHandler(&gameData);
            if (gameData.event.type == SDL_QUIT) {
                gameData.status = false;
                break;
            }
        }
        // On tick
        for (int i = 0; i < gameData.entities.current; i++) {
            if (hasComponent(&gameData.entities.entities[i], OnTick)) {
                gameData.entities.entities[i].components[OnTick].call(&gameData.entities.entities[i]);
            }
        }
        // Remove all entities marked for deletion.
        cleanEntities(&gameData.entities);
        // Render.
        SDL_RenderClear(gameData.renderer);
        renderBackground(gameData.renderer, getAssetByReference("cat1.jpg", (&gameData.assets))->pointer.texture);
        renderEntities(&gameData);
        renderDebugMessage(gameData.renderer, getAssetByReference("ssp-regular.otf", (&gameData.assets))->pointer.font,
                getAssetByReference("ssp-regular.otf", (&gameData.assets))->reference);
        // renderFPS(gameData.renderer, gameData.assets->registry[7].pointer.font, gameData.fps->currentFPS);
        SDL_RenderPresent(gameData.renderer);

        capFPS(&gameData.fps);
    }

    freeGame(&gameData);
    quitModules();
    printf("Quitting now!\n");
    return 0;
}
