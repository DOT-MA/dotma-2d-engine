#include "../../include/assetmanager.h"
#include "../../include/entitymanager.h"
#include "../../include/eventmanager.h"

#include "../../include/scene.h"
#include "../../include/camera.h"
#include "../../include/Scenes/mainmenu.h"

#include "../../include/Entities/cat.h"
#include "../../include/Entities/button.h"

Scene initMainMenu(SDL_Renderer* renderer) {
    Scene scene;
    if (!initScene(&scene)) {
        return (Scene) {0};
    }
    // Load assets for the main menu.
    if (!loadAssets(renderer, &scene.assets, "./res/mainmenu.manifest")) {
        freeScene(&scene);
        return (Scene) {0};
    }
    // Set the background texture.
    scene.background = getAssetByReference("cat3.jpg", &scene.assets)->pointer.texture;
    // Populate scene with entities.
    addEntity(&scene.entities, &scene.assets, &initButton,
            translateRect(renderer, 0.5f, 0.8f, 0.2f, 0.2f));
    addEntity(&scene.entities, &scene.assets, &initButton,
            translateRect(renderer, 0.5f, 0.2f, 0.2f, 0.2f));
    
    scene.eventHandler = &defaultHandler;
    scene.type = MainMenu;
    return scene;
}

