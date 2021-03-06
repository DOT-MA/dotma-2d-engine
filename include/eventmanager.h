#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "entity.h"

/**
 * Check the event against the registered events and execute
 * associated command.
 */
void checkEvent(SDL_Keycode);

/**
 * Process input depending on the context of the current scene.
 */
void defaultHandler(void* game);

#endif