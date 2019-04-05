#include "../../include/Managers/assetmanager.h"
#include "../../include/Managers/entitymanager.h"
#include "../../include/Scenes/scene.h"

/**
 * Initialize the scene components.
 */
bool initializeScene(Scene* scene, SDL_Renderer* renderer, AssetManager* assetManager, const char* manifest) {
    // Load scene specific assets.
    scene->assetRange[0] = assetManager->currentSize;
    if (!loadAssets(renderer, assetManager, manifest)) {
        return false;
    }
    scene->assetRange[1] = assetManager->currentSize;
    // Create entity manager.
    if (!initEntityManager(scene->entityManager)) {
        return false;
    }
    scene->background = NULL;
    return true;
}

/**
 * Free a scene.
 */
void freeScene(Scene* scene) {
    
    freeEntities(scene->entityManager);
}
