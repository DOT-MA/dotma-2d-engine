#ifndef SCENE_H
#define SCENE_H

#include <stddef.h>

#include "../Managers/assetmanager.h"
#include "../Managers/entitymanager.h"
#include "../Entities/entity.h"

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
    EntityManager* entityManager;           // Entities in scene.
    size_t assetRange[2];                   // Position of assets in assetmanager.
    SDL_Texture* background;                // Default background of scene.
} Scene;

/**
 * Initialize the scene components.
 */
bool initializeScene(Scene* scene, SDL_Renderer* renderer, AssetManager* assetManager, const char* manifest);

/**
 * Free a scene.
 */
void freeScene(Scene* scene);

#endif
