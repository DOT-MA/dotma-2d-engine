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
bool initAssetManager(AssetRegistry* reg) {
    reg->currentSize = 0;
    reg->totalSize = 0;
    reg->registry = NULL;
    return true;
}

/**
 * Load assets into the assetmanager.
 */
bool loadAssets(SDL_Renderer* renderer, AssetRegistry* reg, const char* filepath) {
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
    reg->totalSize += total;
    // Check if we need to malloc or realloc
    if (reg->totalSize - total == 0) {
        reg->registry = (RegisteredAsset*) malloc(sizeof(RegisteredAsset) * reg->totalSize);
    } else {
        reg->registry = (RegisteredAsset*) realloc(reg->registry, sizeof(RegisteredAsset) * reg->totalSize);
    }
    // Loop each line and load the texture.
    while(fgets(buffer, sizeof(buffer), fp)) {
        // If last character of buffer is a newline, strip it
        int blen = strlen(buffer);
        if (buffer[blen - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        if (!loadAsset(renderer, buffer, &reg->registry[reg->currentSize])) {
            // Unable to load?
            fprintf(stderr, "Could not load file: %s\n", reg->registry[reg->currentSize].reference);
            memset(buffer, '\0', sizeof(buffer));
            continue;
        }
        // Let the registry know we have added an asset.
        // Set the texture's unique id
        reg->registry[reg->currentSize].uniqueID = reg->currentSize;
        reg->currentSize++;
        memset(buffer, '\0', sizeof(buffer));
    }
    fclose(fp);
    printf("Loaded %d out of %d assets.\n", reg->currentSize, reg->totalSize);
    return true;
}

/**
 *  Load an asset into the manager.
 */
bool loadAsset(SDL_Renderer* renderer, const char* path, RegisteredAsset* asset) {
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
bool typeAsset(RegisteredAsset* asset, const char* path) {
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
 * Free an entry in the texture registry.
 */
bool freeAsset(RegisteredAsset* asset) {
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
 * Free all assets in registry.
 */
bool freeAssets(AssetRegistry* reg) {
    int freed = 0;
    for (int i = 0; i < reg->currentSize; i++) {
        if (!freeAsset(&reg->registry[i])) {
            fprintf(stderr, "Failed to free asset in position %d [%s].\n", i, reg->registry[i].reference);
        }
        freed++;
    }
    printf("Freed %d assets out of %d.\n", freed, reg->totalSize);
    return true;
}

/**
 * If an asset is found with provided reference, return pointer to asset, else return NULL.
 */
RegisteredAsset* getAssetByReference(const char* reference, AssetRegistry* reg) {
    for (int i = 0; i < reg->currentSize; i++) {
        if (strcmp(reg->registry[i].reference, reference) == 0) {
            return &reg->registry[i];
        }
    }
    return NULL;
}
