#include <SDL2/SDL.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../include/entity.h"
#include "../include/component.h"
#include "../include/assetmanager.h"
#include "../include/renderertemplates.h"

// --------------- Global components
/**
 * Defualt deleted component call for all entites.
 */
void deleted(void* e) {
    Entity* entity = (Entity*) e;
    entity->remove = true;
}

/**
 * Defualt render call for all entites.
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
 * Initalize an entity with a default size, location and with provided texture and sound.
 */
bool initEntity(Entity* e, AssetRegistry* reg, const char* textureRef, const char* soundRef) {
    // Initalize all calls as null
    for (int i = 0; i < COMPONENT_TOTAL; i++) {
        e->components[i].call = NULL;
    }
    memset(e->stats, -1, sizeof(int));
    if (textureRef != NULL) {
        RegisteredAsset* asset = getAssetByReference(textureRef, reg);
        if (asset == NULL) {
            fprintf(stderr, "Unable to find asset for entity: %s\n", textureRef);
            return false;
        }
        e->textures[0] = asset->pointer.texture;
    }
    if (soundRef != NULL) {
        RegisteredAsset* asset = getAssetByReference(soundRef, reg);
        if (asset == NULL) {
            fprintf(stderr, "Unable to find asset for entity: %s\n", soundRef);
            return false;
        }
        e->sounds[0] = asset->pointer.sound;
    }
    e->remove = false;
    e->components[Deleted].call = &deleted;
    e->components[Render].call = &render;
    return true;
}

