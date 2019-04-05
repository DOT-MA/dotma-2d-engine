#include "../../include/Managers/assetmanager.h"
#include "../../include/Managers/entitymanager.h"
#include "../../include/Managers/eventmanager.h"
#include "../../include/Rendering/camera.h"

#include "../../include/Scenes/scene.h"
#include "../../include/Scenes/mainmenu.h"

#include "../../include/Entities/cat.h"
#include "../../include/Entities/button.h"

/**
 * Constructor for the debug testing scene.
 */
Scene initializeDebugScene(SDL_Renderer* renderer, AssetManager* assetManager, const char* manifest) {
    Scene scene;
    if (!initializeScene(&scene, renderer, assetManager, manifest)) {
        return (Scene) {0};
    }
    // Populate scene with entities.
    for (int i = 0; i < 50; i++) {
        addEntity(scene.entityManager, assetManager, &initCat, translateRect(renderer, 0.5f, 0.2f, 0.2f, 0.2f));
    }
    // addEntity(&scene.entities, &scene.assets, &initButton);
    scene.type = MainMenu;
    return scene;
}
