#include "../include/assetmanager.h"
#include "../include/entitymanager.h"
#include "../include/scene.h"

/**
 * Initialize the scene components.
 */
bool initScene(Scene* scene) {
    if (!initEntityManager(&scene->entities)) {
        freeAssets(&scene->assets);
        return false;
    }
    scene->background = NULL;
    return true;
}

/**
 * Free a scene.
 */
void freeScene(Scene* scene) {
    freeAssets(&scene->assets);
    freeEntities(&scene->entities);
}