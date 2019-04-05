#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <string.h>

#include "../../include/debug.h"

#include "../../include/Rendering/renderer.h"
#include "../../include/Rendering/renderertemplates.h"
#include "../../include/Entities/entity.h"

/**
 * Render all renderable entities.
 */
void renderEntities(EntityManager* entityManager, SDL_Renderer* renderer) {
    for (int i = 0; i < entityManager->current; i++) {
        if (hasComponent(&entityManager->entities[i], Render)) {
            entityManager->entities[i].components[Render].call(entityManager->entities[i], renderer);
            DEBUG_PRINT(stdout, "Rendered entity at: %d %d\n", entityManager->entities[i].position.x, entityManager->entities[i].position.y);
        }
    } 
}

/**
 * Render the current scene.
 */
void renderScene(GameData* gameData) {
    // Clear previous render.
    SDL_RenderClear(gameData->renderer);
    // Check if we want a background.
    if (gameData->scene.background != NULL) {
        renderBackground(gameData->renderer, gameData->scene.background);
    }
    // Render entities.
    renderEntities(gameData->scene.entityManager, gameData->renderer);
    // Swap out for new frame.
    SDL_RenderPresent(gameData->renderer);
}
