#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stddef.h>
#include <stdbool.h>

/**
 * Enumeration of each asset type.
 * How we know what type each assetManager asset is.
 */
enum AssetType {
    Texture,
    Font,
    Sound
};

/**
 * Each possible asset type.
 */
typedef union AssetPointer {
    SDL_Texture* texture;
    TTF_Font* font;
    Mix_Chunk* sound;
} AssetPointer;

/**
 * Each texture to be registered.
 */
typedef struct Asset {
    size_t uniqueID;
    enum AssetType type;
    char* reference;
    AssetPointer pointer;
} Asset;

/**
 * The AssetManager of all loaded textures.
 */
typedef struct AssetManager {
    size_t currentSize;
    size_t totalSize;
    Asset* assets;
} AssetManager;

/**
 * Initialize the asset manager.
 */
bool initializeAssetManager(AssetManager* assetManager);

/**
 * Load assets from a newline-delimated plain text file.
 */
bool loadAssets(SDL_Renderer* renderer, AssetManager* assetManager, const char* manifest);

/**
 * Free all assets from a provided AssetManager.
 */
bool freeAssets(AssetManager* assetManager);

/**
 * Free all assets in a given range from the AssetManager.
 */
bool freeAssetRange(AssetManager* assetManager, size_t range[2]);

/**
 * If an asset is found with provided reference, return pointer to asset, else return NULL.
 */
Asset* getAssetByReference(AssetManager* assetManager, const char* reference);

#endif
