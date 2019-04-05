#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../include/debug.h"

#include "../../include/Managers/assetmanager.h"

/**
 * Determine the type of the asset and set the filename and type.
 */
bool typeAsset(Asset* asset, const char* path) {
    // Parse filename to get extention.
    char copy[strlen(path)];
    strcpy(copy, path);
    char* filename = strtok(copy, "/");
    while (1) {
        char* test = strtok(NULL, "/");
        if (test == NULL) {
            break;
        }
        filename = test;
    }
    asset->reference = (char*) malloc(sizeof(char) * strlen(filename) + 1);
    strcpy(asset->reference, filename);
    char* ext = strtok(filename, ".");
    while (1) {
        char* test = strtok(NULL, ".");
        if (test == NULL) {
            break;
        }
        ext = test;
    }
    // Determine which load function to use
    if (!strcmp(ext, "png") || !strcmp(ext, "jpg")) {
        asset->type = Texture;
    } else if (!strcmp(ext, "ttf") || !strcmp(ext, "otf")) {
        asset->type = Font;
    } else if (!strcmp(ext, "ogg") || !strcmp(ext, "mp3")) {
        asset->type = Sound;
    } else {
        // File type not supported.
        return false;
    }
    return true;
}

/**
 *  Load an asset into the manager.
 */
bool loadAsset(SDL_Renderer* renderer, const char* path, Asset* asset) {
    // Set the texture's reference string and check the asset type.
    if (!typeAsset(asset, path)) {
        DEBUG_PRINT(stderr, "Unable to type asset %s.\n", path);
        return false;
    }
    switch (asset->type) {
        case Texture:
            asset->pointer.texture = IMG_LoadTexture(renderer, path);
            if (asset->pointer.texture == NULL) {
                return false;
            }
            break;
        case Font:
            asset->pointer.font = TTF_OpenFont(path, 20);
            if (asset->pointer.font == NULL) {
                return false;
            }
            break;
        case Sound:
            asset->pointer.sound = Mix_LoadWAV(path);
            if (asset->pointer.font == NULL) {
                return false;
            }
            break;
        default:
            return false;
    }
    return true;
}

/**
 * Free an entry in the texture AssetManager.
 */
bool freeAsset(Asset* asset) {
    // Free asset data.
    switch (asset->type) {
        case Texture:
            SDL_DestroyTexture(asset->pointer.texture);
            break;
        case Font:
            TTF_CloseFont(asset->pointer.font);
            break;
        case Sound:
            Mix_FreeChunk(asset->pointer.sound);
            break;
        default:
            DEBUG_PRINT(stderr, "Asset type unknown, unable to free.\n");
            return false;
            break;
    }
    // Free asset reference name.
    if (asset->reference) {
        free(asset->reference);
        asset->reference = NULL;
    } else {
        DEBUG_PRINT(stderr, "Reference name not allocated.\n");
        return false;
    }
    return true;
}

/**
 * Initialize the asset manager.
 */
bool initializeAssetManager(AssetManager* assetManager) {
    assetManager->currentSize = 0;
    assetManager->totalSize = 0;
    assetManager->assets = NULL;
    return true;
}

/**
 * Load assets into the assetmanager via a manifest file.
 */
bool loadAssets(SDL_Renderer* renderer, AssetManager* assetManager, const char* manifest) {
    // How many textures are we loading?
    int total = 0;
    char buffer[100];
    // Open file and count how many lines
    FILE* fp = fopen(manifest, "r");
    if (!fp) {
        DEBUG_PRINT(stderr, "Unable to find specified asset manifest file.\n");
        return false;
    }
    while(fgets(buffer, sizeof(buffer), fp)) {
        total++;
    }
    // Reset the pointer back to the beginning of the file
    fseek(fp, 0, SEEK_SET);
    memset(buffer, '\0', sizeof(buffer));
    // Allocate space for each of the textures.
    assetManager->totalSize += total;
    // Check if we need to malloc or realloc
    if (assetManager->totalSize - total == 0) {
        assetManager->assets = (Asset*) malloc(sizeof(Asset) * assetManager->totalSize);
    } else {
        assetManager->assets = (Asset*) realloc(assetManager->assets, sizeof(Asset) * assetManager->totalSize);
    }
    // Loop each line and load the texture.
    while(fgets(buffer, sizeof(buffer), fp)) {
        // If last character of buffer is a newline, strip it
        int blen = strlen(buffer);
        if (buffer[blen - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        if (!loadAsset(renderer, buffer, &assetManager->assets[assetManager->currentSize])) {
            // Unable to load?
            DEBUG_PRINT(stderr, "Could not load file: %s\n", assetManager->assets[assetManager->currentSize].reference);
            memset(buffer, '\0', sizeof(buffer));
            continue;
        }
        // Let the AssetManager know we have added an asset.
        // Set the texture's unique id
        assetManager->assets[assetManager->currentSize].uniqueID = assetManager->currentSize;
        assetManager->currentSize++;
        memset(buffer, '\0', sizeof(buffer));
    }
    fclose(fp);
    DEBUG_PRINT(stdout, "Loaded %zu out of %zu assets.\n", assetManager->currentSize, assetManager->totalSize);
    return true;
}

/**
 * Free all assets in provided AssetManager.
 * If we are unable to free an asset what do we do?
 */
bool freeAssets(AssetManager* assetManager) {
    // The real remaining number of assets in the manager.
    size_t current = assetManager->currentSize;
    // For all Assets in the manager.
    for (size_t i = 0; i < assetManager->currentSize; i++) {
        // Attempt to free the asset.
        if (!freeAsset(&assetManager->assets[i])) {
            DEBUG_PRINT(stderr, "Failed to free asset in position %zu [%s].\n", i, assetManager->assets[i].reference);
        }
        // Decrement the number of assets in the manager.
        current--;
    }
    DEBUG_PRINT(stdout, "Freed %lu assets out of %zu.\n", assetManager->currentSize - current, assetManager->currentSize);
    assetManager->currentSize = current;
    return true;
}

/**
 * Free all assets in a given range from the AssetManager.
 */
bool freeAssetRange(AssetManager* assetManager, size_t range[2]) {
    // Check if our range is possibly correct.
    if (!(range[0] < range[1] && range[1] < assetManager->currentSize)) {
        return false;
    }
    // Provide a wrapper around the real asset register so that it is compatable with freeAssets.
    AssetManager temp = {
        .assets = &assetManager->assets[range[0]],
        .currentSize = range[1] - range[0],
        .totalSize = range[1] - range[0]
    };
    if (!freeAssets(&temp)) {
        return false;
    }
    // Shift assets to the left if required.
    if (range[1] != assetManager->currentSize) {
        // We have to adjust for assets remaining on right side of freed assets.
        for (size_t i = range[1]; i < assetManager->currentSize; i++) {
            assetManager->assets[i - range[0]] = assetManager->assets[i];
        }
    }
    // Resize the array.
    assetManager->currentSize = assetManager->currentSize - (range[1] - range[0]);
    assetManager->totalSize = assetManager->currentSize;
    assetManager->assets = (Asset*) realloc(assetManager->assets, sizeof(Asset) * assetManager->totalSize);
    return true;
}

/**
 * If an asset is found with provided reference, return pointer to asset, else return NULL.
 */
Asset* getAssetByReference(AssetManager* assetManager, const char* reference) {
    for (int i = 0; i < assetManager->currentSize; i++) {
        if (strcmp(assetManager->assets[i].reference, reference) == 0) {
            return &assetManager->assets[i];
        }
    }
    return NULL;
}
