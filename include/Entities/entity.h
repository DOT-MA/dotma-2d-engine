#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>

#include "../Managers/assetmanager.h"
#include "../Components/component.h"
#include "../Utilities/timer.h"

/**
 * Possible stats an entity can have.
 */
 typedef enum Stats {
    HP,
    MaxHP,
    Attack,
    Defence,
    Speed,
    NUMBER_OF_STATS
 } Stats;

/**
 * A simple entity, with a position, texture and movement function.
 */
typedef struct Entity {
    int stats[NUMBER_OF_STATS];
    SDL_Texture* textures[4];
    Mix_Chunk* sounds[4];
    SDL_Rect position;
    Component components[COMPONENT_TOTAL];
    Timer timers[4];
    bool remove;
} Entity;

/**
 * Initalize an entity with a default size, location and with provided texture.
 */
bool initEntity(Entity* e, AssetManager* assetManager, const char* textureRef, const char* soundRef);

/**
 * Returns true if the entity has queried component.
 */
bool hasComponent(Entity* e, ComponentType c);

#endif
