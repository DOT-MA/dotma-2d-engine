#ifndef SCENE_H
#define SCENE_H

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
    SceneType type;
    AssetRegistry assets;
    EntityManager entities;
    // Need to cast as GameData
    void (*eventHandler)(void* gameData);
    SDL_Texture* background;
} Scene;

/**
 * Initialize the scene components.
 */
bool initScene(Scene* scene);

/**
 * Free a scene.
 */
void freeScene(Scene* scene);

#endif
