#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdint.h>
#include <stdbool.h>

/**
 * Enumeration of each asset type.
 * How we know what type each assetManageristry asset is.
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
 * Each texture to be assetManageristered.
 */
typedef struct Asset {
    int uniqueID;
    enum AssetType type;
    char* reference;
    AssetPointer pointer;
} Asset;

/**
 * The assetManageristry of all loaded textures.
 */
typedef struct AssetManager {
    size_t currentSize;
    size_t totalSize;
    Asset* assetManageristry;
} AssetManager;

/**
 * Initialize the asset manager.
 */
bool initAssetManager(AssetManager* assetManager);

/**
 * Load assets from a newline-delimated plain text file.
 */
bool loadAssets(SDL_Renderer* renderer, AssetManager* assetManager, const char* configPath);

/**
 *  Load an asset into the manager.
 */
bool loadAsset(SDL_Renderer* renderer, const char* path, Asset* assetManager);

/**
 * Determine the type of the asset and set the filename and type.
 */
bool typeAsset(Asset* asset, const char* path);

/**
 * Free all assets from a provided assetManageristry.
 */
bool freeAssets(AssetManager* assetManager);

/**
 * If an asset is found with provided reference, return pointer to asset, else return NULL.
 */
Asset* getAssetByReference(const char* reference, AssetManager* assetManager);

#endif