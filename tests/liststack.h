#ifndef LISTSTACK_H
#define LISTSTACK_H

#include <stdint.h>

#include "../include/Managers/assetmanager.h"

/**********************************************************************
 * A stack implementation for loading assets that uses a linked list.
 *********************************************************************/

/**
 * The node containing an asset.
 */
typedef struct AssetNode {
    Asset* asset;
    void* next;
} AssetNode;

/**
 * The stack holding our assets.
 */
typedef struct AssetStack {
    int8_t allocations;
    AssetNode** heads;
    AssetNode* tail;
} AssetStack;

AssetStack initialize_asset_stack(void);

bool push_chunk(SDL_Renderer* renderer, AssetStack* stack, const char* manifest);

bool pop_chunk(AssetStack* stack);

bool free_stack(AssetStack* stack);

void debug_stack(AssetStack* stack);

#endif

