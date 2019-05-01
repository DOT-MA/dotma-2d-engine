#include <stdlib.h>
#include <string.h>

#include "liststack.h"


AssetStack initialize_asset_stack(void) {
    return (AssetStack) {
        .allocations = -1,
        .heads = NULL,
        .tail = NULL
    };
}

bool push_asset(SDL_Renderer* renderer, AssetStack* stack, const char* asset_path) {
    if (stack->heads[stack->allocations] == NULL) {
        // If we dont have a node at our current head make one.
        stack->heads[stack->allocations] = (AssetNode*) malloc(sizeof(AssetNode));
        stack->tail = stack->heads[stack->allocations];
    } else {
        // We need to allocate memory for the current head->next.
        stack->tail->next = (AssetNode*) malloc(sizeof(AssetNode));
        stack->tail = stack->tail->next;
    }
    // Set the tail's next node to NULL.
    stack->tail->next = NULL;
    AssetNode* node = stack->tail;
    node->asset = (Asset*) malloc(sizeof(Asset));
    // Set the texture's reference string and check the asset type.
    if (!typeAsset(node->asset, asset_path)) {
        fprintf(stderr, "Unable to type asset %s.\n", asset_path);
        return false;
    }
    switch (node->asset->type) {
        case Texture:
            node->asset->pointer.texture = IMG_LoadTexture(renderer, asset_path);
            if (node->asset->pointer.texture == NULL) {
                return false;
            }
            break;
        case Font:
            node->asset->pointer.font = TTF_OpenFont(asset_path, 20);
            if (node->asset->pointer.font == NULL) {
                return false;
            }
            break;
        case Sound:
            node->asset->pointer.sound = Mix_LoadWAV(asset_path);
            if (node->asset->pointer.font == NULL) {
                return false;
            }
            break;
        default:
            return false;
    }
    return true;
}

bool push_chunk(SDL_Renderer* renderer, AssetStack* stack, const char* manifest) {
    // Check if the file can be opened.
    char asset_path[100];   // Maximum size of provided filename.
    FILE* fp = fopen(manifest, "r");
    if (fp == NULL) {
        return false;
    }
    // Is this the first allocation for the stack?
    if (stack->allocations == -1) {
        stack->heads = (AssetNode**) malloc(sizeof(AssetNode*));
        stack->allocations++;
    // Increase the size of the head array.
    } else {
        stack->allocations++;
        stack->heads = (AssetNode**) realloc(stack->heads, sizeof(AssetNode*) * (stack->allocations + 1));
    }
    stack->heads[stack->allocations] = NULL;
    // Read each line of the file and add a new node for each loaded asset.
    while(fgets(asset_path, sizeof(asset_path), fp)) {
        int blen = strlen(asset_path);
        if (asset_path[blen - 1] == '\n') {
            asset_path[strlen(asset_path) - 1] = '\0';
        }
        if (!push_asset(renderer, stack, asset_path)) {
            // Unable to load?
            fprintf(stderr, "Could not load file: %s\n", asset_path);
        }
        memset(asset_path, '\0', sizeof(asset_path));
    }
    // Close file.
    fclose(fp);
    return true;
}

bool pop_chunk(AssetStack* stack) {
    // Free all assets from the top most chunk.
    AssetNode* current = stack->heads[stack->allocations];
    while(current != NULL) {
        freeAsset(current->asset);
        AssetNode* temp = current->next;
        free(current);
        current = temp;
    }
    // Re-allocate the list of heads.
    if (stack->allocations != 0) {
        stack->allocations--;
        stack->heads = (AssetNode**) realloc(stack->heads, (stack->allocations + 1) * sizeof(Asset*));
        // Set the tail pointer.
        AssetNode* tail = stack->heads[stack->allocations];
        while(tail->next != NULL) {
            tail = tail->next;
        };
    } else {
        // Free all data.
        stack->allocations = -1;
        free(stack->heads);
    }
    return true;
}

bool free_stack(AssetStack* stack) {
    while(stack->allocations > -1) {
        pop_chunk(stack);
    }
}

void debug_stack(AssetStack* stack) {
    AssetNode* start = stack->heads[0];
    while (start != NULL) {
        start = start->next;
    }
}