#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <stdint.h>
#include <stdbool.h>

#include "entity.h"
#include "assetmanager.h"

/**
 * Holds total number of entities.
 */
typedef struct EntityManager {
    size_t current;
    size_t maximum;
    Entity* entities;
} EntityManager;

/**
 * Create new entity manager.
 */
bool initEntityManager(EntityManager* entityManager);

/**
 * Add a new entity to the manager if there is space, if not allocate more space for new entity.
 */
void addEntity(EntityManager* entityManager, AssetManager* assets, Entity (*initEntity)(AssetManager* assets), SDL_Rect position);

/**
 * Remove all entities that are marked to delete then shift all right of the removed entity left to conserve space.
 */
void cleanEntities(EntityManager* entityManager);

/**
 * Free entity manager.
 */
 void freeEntities(EntityManager* entityManager);

#endif