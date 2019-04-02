#include "../../include/assetmanager.h"
#include "../../include/entitymanager.h"
#include "../../include/eventmanager.h"

#include "../../include/scene.h"
#include "../../include/Scenes/mainmenu.h"

#include "../../include/Entities/cat.h"
#include "../../include/Entities/button.h"

Scene initMainMenu(SDL_Renderer* renderer) {
    Scene scene;
    if (!initScene(&scene)) {
        return (Scene) {};
    }
    // Load assets for the main menu.
    if (!loadAssets(renderer, &scene.assets, "./res/mainmenu.manifest")) {
        freeScene(&scene);
        return (Scene) {};
    }
    // Populate scene with entities.
    addEntity(&scene.entities, &scene.assets, &initButton);
    
    scene.eventHandler = &defaultHandler;
    scene.type = MainMenu;
    return scene;
}

