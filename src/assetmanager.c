#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/assetmanager.h"

/**
 * Initialize the asset manager.
 */
bool initAssetManager(AssetManager* assetManager) {
    assetManager->currentSize = 0;
    assetManager->totalSize = 0;
    assetManager->assetManageristry = NULL;
    return true;
}

/**
 * Load assets into the assetmanager.
 */
bool loadAssets(SDL_Renderer* renderer, AssetManager* assetManager, const char* filepath) {
    // How many textures are we loading?
    int total = 0;
    char buffer[100];
    // Open file and count how many lines
    FILE* fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Unable to find specified asset manifest file.\n");
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
        assetManager->assetManageristry = (Asset*) malloc(sizeof(Asset) * assetManager->totalSize);
    } else {
        assetManager->assetManageristry = (Asset*) realloc(assetManager->assetManageristry, sizeof(Asset) * assetManager->totalSize);
    }
    // Loop each line and load the texture.
    while(fgets(buffer, sizeof(buffer), fp)) {
        // If last character of buffer is a newline, strip it
        int blen = strlen(buffer);
        if (buffer[blen - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        if (!loadAsset(renderer, buffer, &assetManager->assetManageristry[assetManager->currentSize])) {
            // Unable to load?
            fprintf(stderr, "Could not load file: %s\n", assetManager->assetManageristry[assetManager->currentSize].reference);
            memset(buffer, '\0', sizeof(buffer));
            continue;
        }
        // Let the assetManageristry know we have added an asset.
        // Set the texture's unique id
        assetManager->assetManageristry[assetManager->currentSize].uniqueID = assetManager->currentSize;
        assetManager->currentSize++;
        memset(buffer, '\0', sizeof(buffer));
    }
    fclose(fp);
    printf("Loaded %d out of %d assets.\n", assetManager->currentSize, assetManager->totalSize);
    return true;
}

/**
 *  Load an asset into the manager.
 */
bool loadAsset(SDL_Renderer* renderer, const char* path, Asset* asset) {
    // Set the texture's reference string and check the asset type.
    if (!typeAsset(asset, path)) {
        fprintf(stderr, "Unable to type asset %s.\n", path);
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
 * Free an entry in the texture assetManageristry.
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
            fprintf(stderr, "Asset type unknown, unable to free.\n");
            return false;
            break;
    }
    // Free asset reference name.
    if (asset->reference) {
        free(asset->reference);
        asset->reference = NULL;
    } else {
        fprintf(stderr, "Reference name not allocated.\n");
        return false;
    }
    return true;
}

/**
 * Free all assets in assetManageristry.
 */
bool freeAssets(AssetManager* assetManager) {
    int freed = 0;
    for (int i = 0; i < assetManager->currentSize; i++) {
        if (!freeAsset(&assetManager->assetManageristry[i])) {
            fprintf(stderr, "Failed to free asset in position %d [%s].\n", i, assetManager->assetManageristry[i].reference);
        }
        freed++;
    }
    printf("Freed %d assets out of %d.\n", freed, assetManager->totalSize);
    return true;
}

/**
 * If an asset is found with provided reference, return pointer to asset, else return NULL.
 */
Asset* getAssetByReference(const char* reference, AssetManager* assetManager) {
    for (int i = 0; i < assetManager->currentSize; i++) {
        if (strcmp(assetManager->assetManageristry[i].reference, reference) == 0) {
            return &assetManager->assetManageristry[i];
        }
    }
    return NULL;
}
