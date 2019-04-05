#include <SDL2/SDL_mixer.h>

#include <stdio.h>

#include "../../include/debug.h"

#include "../../include/Entities/entity.h"
#include "../../include/Components/component.h"
#include "../../include/Entities/button.h"

/**
 * Behaviour of button when left clicked.
 */
void buttonLeftClicked(void* e) {
    Entity* entity = (Entity*) e;
    // Swap colour of button
    SDL_Texture* temp = entity->textures[0];
    entity->textures[0] = entity->textures[1];
    entity->textures[1] = temp;
    Mix_PlayChannel(-1, entity->sounds[0], 0);
}

/**
 * Initializes the button.
 */
Entity initButton(AssetManager* assetManager) {
    Entity entity;
    if (!initEntity(&entity, assetManager, "click.png", "click1.ogg")) {
        DEBUG_PRINT(stderr, "Could not initialize button entity.\n");
        return (Entity) { 0 };
    }
    entity.textures[1] = getAssetByReference(assetManager, "unclick.png")->pointer.texture;
    // Load custom components.
    entity.components[LeftClicked].call = &buttonLeftClicked;
    return entity;
}

