#include "../../include/Entities/entity.h"
#include "../../include/Components/move.h"

/**
 * Move an entity a set distance in a provided direction.
 */
void move(void* e, Direction d, int pixels) {
    Entity* entity = (Entity*) e;
    switch (d) {
        case UP:
            entity->position.y -= pixels;
            break;
        case DOWN:
            entity->position.y += pixels;
            break;
        case LEFT:
            entity->position.x -= pixels;
            break;
        case RIGHT:
            entity->position.x += pixels;
            break;
        default:
            break;
    }
}

