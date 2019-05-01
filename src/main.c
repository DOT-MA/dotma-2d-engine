#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../include/debug.h"

#include "../include/game.h"

#include "../include/Utilities/framerate.h"
#include "../include/Managers/assetmanager.h"
#include "../include/Managers/eventmanager.h"
#include "../include/Rendering/renderer.h"
#include "../include/Rendering/renderertemplates.h"
#include "../include/Rendering/camera.h"
#include "../include/Entities/cat.h"
#include "../include/Entities/button.h"

/**
 *  Initialize SDL components.
 */
 bool initModules(void) {
    // Start SDL and components.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        DEBUG_PRINT(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) == 0) {
        DEBUG_PRINT(stderr, "Unable to initialize SDL_image\n");
        return false;
    }
    if (TTF_Init() != 0) {
        DEBUG_PRINT(stderr, "Unable to initialize SDL_ttf\n");
        return false;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        DEBUG_PRINT(stderr, "Unable to initialize SDL_mixer\n");
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
int main(int argc, char** argv) {
    // Start all major game components.
    if (!initModules()) {
        return 1;
    }
    // Load game components and state.
    GameData gameData;
    if (!initGame(&gameData)) {
        DEBUG_PRINT(stderr, "Unable to initialize game modules.\n");
        return 2;
    }

    DEBUG_PRINT(stdout, "Game starting....\n");
    // Main game loop.
    while (gameData.status) {

        // ---------------- Handle user events.
        while (SDL_PollEvent(&gameData.event)) {
            defaultHandler(&gameData);
        }

        //----------------- Update state.
        for (int i = 0; i < gameData.scene.entityManager->current; i++) {
            if (hasComponent(&gameData.scene.entityManager->entities[i], OnTick)) {
                gameData.scene.entityManager->entities[i].components[OnTick].call(&gameData.scene.entityManager->entities[i]);
            }
        }

        // Remove all entities marked for deletion.
        cleanEntities(gameData.scene.entityManager);

        // --------------- Render state.
        renderScene(&gameData);

        // --------------- Wait if we have finished too soon.
        capFPS(&gameData.fps);
    }

    // Game over, free everything.
    freeGame(&gameData);
    quitModules();
    return 0;
}
