#include <SDL2/SDL.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../../include/debug.h"

#include "../../include/Entities/entity.h"
#include "../../include/Components/component.h"
#include "../../include/Managers/assetmanager.h"
#include "../../include/Rendering/renderertemplates.h"

// --------------- Global components
/**
 * Default deleted component call for all entities.
 */
void deleted(void* e) {
    Entity* entity = (Entity*) e;
    entity->remove = true;
}

/**
 * Default render call for all entities.
 */
void render(void* e, SDL_Renderer* r) {
    Entity* entity = (Entity*) e;
    renderTexture(r, entity->textures[0], &entity->position);
}

// --------------- Utility functions

/**
 * Returns true if the entity has queried component.
 */
bool hasComponent(Entity* e, ComponentType c) {
    return !(e->components[c].call == NULL);
}

// --------------- Prepare the entity struct

/**
 * Initialize an entity with a default size, location and with provided texture and sound.
 */
bool initEntity(Entity* e, AssetManager* assetManager, const char* textureRef, const char* soundRef) {
    // Initialize all calls as null
    for (int i = 0; i < COMPONENT_TOTAL; i++) {
        e->components[i].call = NULL;
    }
    memset(e->stats, -1, sizeof(int));
    if (textureRef != NULL) {
        Asset* asset = getAssetByReference(assetManager, textureRef);
        if (asset == NULL) {
            DEBUG_PRINT(stderr, "Unable to find asset for entity: %s\n", textureRef);
            return false;
        }
        e->textures[0] = asset->pointer.texture;
    }
    if (soundRef != NULL) {
        Asset* asset = getAssetByReference(assetManager, soundRef);
        if (asset == NULL) {
            DEBUG_PRINT(stderr, "Unable to find asset for entity: %s\n", soundRef);
            return false;
        }
        e->sounds[0] = asset->pointer.sound;
    }
    e->remove = false;
    e->components[Deleted].call = &deleted;
    e->components[Render].call = &render;
    return true;
}
