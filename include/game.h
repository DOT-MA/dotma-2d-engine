#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "./Utilities/framerate.h"
#include "./Scenes/scene.h"

/**
 * GameData struct, holds all data such as current scene,
 * SDL Window/Renderer and more.
 */
typedef struct GameData {
    // Is the game still running?
    bool status;
    // SDL window, renderer and event.
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    // Frame rate manager.
    FrameRateManager fps;
    // Asset manager.
    AssetManager assetManager;
    // Resources required for the main/escape menu and debugging.
    Scene menu;
    // Current scene.
    Scene scene;
} GameData;

/**
 * Return initialized GameData struct.
 */
bool initGame(GameData* gameData);

/**
 * Free game objects.
 */
void freeGame(GameData* game);

#endif
