#ifndef SCENE_H
#define SCENE_H

#include <stdint.h>

#include "assetmanager.h"
#include "entitymanager.h"
#include "entity.h"

/**
 * What is the context of this "scene".
 */
typedef enum SceneType {
    ExcMenu,
    MainMenu,
    TileSelect,
    Battle
} SceneType;

/**
 * Scene specific assets, entities,
 * the type of scene.
 */
typedef struct Scene {
    SceneType type;                         // Type of scene.
    EntityManager entitiyManager;           // Entities in scene.
    size_t assetRange[2];                   // Position of assets in assetmanager.
    void (*eventHandler)(void* gameData);   // Event handler for scene.
    SDL_Texture* background;                // Default background of scene.
} Scene;

/**
 * Initialize the scene components.
 */
bool initializeScene(Scene* scene);

/**
 * Free a scene.
 */
void freeScene(Scene* scene);

#endif
