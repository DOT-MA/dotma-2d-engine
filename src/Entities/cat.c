#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "../../include/debug.h"

#include "../../include/Entities/entity.h"
#include "../../include/Components/component.h"
#include "../../include/Utilities/timer.h"
#include "../../include/Entities/cat.h"

#include "../../include/Components/move.h"

/**
 * Behaviour of cat when clicked.
 */
void catRightClicked(void* e) {
    Entity* entity = (Entity*) e;
    unsigned int fattenBy = 10;
    entity->position.w += fattenBy;
    entity->position.h += fattenBy;
    entity->position.x -= fattenBy / 2;
    entity->position.y -= fattenBy / 2;
}

/**
 * Behaviour of cat when dragged.
 */
void catDragged(void *e, int x, int y) {
    printf("Dragged cat!\n");
}

/**
 * On tick.
 * Limit time via a local timer initialized using a static variable.
 */
void catOnTick(void* e) {
    Entity* entity = (Entity*) e;
    if (!entity->timers[0].started) {
        startTimer(&entity->timers[0]);
    }
    if (timeElapsed(&entity->timers[0], 100)) {
        // Pick which direction we are moving.
        unsigned int direction = rand() % 4;
        entity->components[Moved].call(entity, direction, 10);
        entity->timers[0].startTime = SDL_GetTicks();
    }

}

/**
 * Initializes the cat entity and its components.
 */
Entity initCat(AssetManager* assetManager) {
    Entity cat;
    // Load cat assets make more flexable and specific later.
    if (!initEntity(&cat, assetManager, "cat4.jpg", "meow1.ogg")) {
        DEBUG_PRINT(stderr, "Could not initialize cat entity.\n");
        return (Entity) { 0 };
    }
    //cat.stats[0] = 10;

    // Cat specific specifications.
    // Starting position.
    cat.position.x = 400;
    cat.position.y = 400;
    // Width and height.
    cat.position.w = 20;
    cat.position.h = 20;
    // Load cat components.
    cat.timers[0] = initTimer();
    cat.components[Moved].call = &move;
    cat.components[RightClicked].call = &catRightClicked;
    cat.components[Dragged].call = &catDragged;
    cat.components[OnTick].call = &catOnTick;
    return cat;
}
