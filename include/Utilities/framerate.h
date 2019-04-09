#ifndef FRAMERATE_H
#define FRAMERATE_H

#include <stdbool.h>

#include "timer.h"

/**
 * A frame rate counter.
 */
typedef struct FrameRateManager {
    bool capped;
    short cappedFPS;
    unsigned int frames;
    short currentFPS;
    Timer timer;
} FrameRateManager;

/**
 * Initialise the timer using some global constants defined in config.h.
 */
FrameRateManager initFPSManager(void);

/**
 * Maintain capped framerate.
 */
void capFPS(FrameRateManager* f);

/**
 * Show the current average fps.
 */
int getFPS(FrameRateManager* f);

#endif
