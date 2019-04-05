#include "../../include/Managers/assetmanager.h"
#include "../../include/Managers/entitymanager.h"
#include "../../include/Managers/eventmanager.h"

#include "../../include/Rendering/camera.h"

#include "../../include/Scenes/scene.h"
#include "../../include/Scenes/mainmenu.h"

#include "../../include/Entities/cat.h"
#include "../../include/Entities/button.h"

/**
 * Constructor for the Main Menu scene.
 */
Scene initializeMainMenu(SDL_Renderer* renderer, AssetManager* assetManager, const char* manifest) {
    Scene scene;
    if (!initializeScene(&scene, renderer, assetManager, manifest)) {
        return (Scene) {0};
    }
    // Set the background texture.
    // scene.background = getAssetByReference("cat3.jpg", &scene.assets)->pointer.texture;
    
    // Populate scene with entities.
    addEntity(scene.entityManager, assetManager, &initButton, (SDL_Rect) {20, 20, 20, 20});
    addEntity(scene.entityManager, assetManager, &initButton,
            translateRect(renderer, 0.5f, 0.2f, 0.2f, 0.2f));
    
    scene.type = MainMenu;
    return scene;
}
