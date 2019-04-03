#include "../../include/assetmanager.h"
#include "../../include/entitymanager.h"
#include "../../include/eventmanager.h"

#include "../../include/scene.h"
#include "../../include/Scenes/mainmenu.h"

#include "../../include/Entities/cat.h"
#include "../../include/Entities/button.h"

/**
 * Constructor for the debug testing scene.
 */
Scene initDebugScene(SDL_Renderer* renderer) {
    Scene scene;
    if (!initScene(&scene)) {
        return (Scene) {0};
    }
    // Load assets for the main menu.
    if (!loadAssets(renderer, &scene.assets, "./res/debug.manifest")) {
        freeScene(&scene);
        return (Scene) {0};
    }
    // Populate scene with entities.
    for (int i = 0; i < 50; i++) {
        // addEntity(&scene.entities, &scene.assets, &initCat);
    }
    // addEntity(&scene.entities, &scene.assets, &initButton);
    scene.eventHandler = &defaultHandler;
    scene.type = MainMenu;
    return scene;
}

