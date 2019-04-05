#include <SDL2/SDL.h>

#include <stdio.h>

#include "../../include/debug.h"

#include "../../include/Utilities/timer.h"
#include "../../include/Utilities/framerate.h"
#include "../../include/config.h"

/**
 * Initialise the timer using some global constants defined in config.h.
 */
FrameRateManager initFPSManager(void) {
    FrameRateManager f = (FrameRateManager) {
        .capped = FPS_CAPPED,
        .cappedFPS = FRAME_CAP,
        .currentFPS = 0,
        .timer = initTimer(),
    };
    startTimer(&f.timer);
    return f;
}

/**
 * Maintain capped framerate.
 */
void capFPS(FrameRateManager* f) {
    if (f->capped) {
        int cap = (1000 / f->cappedFPS);
        // Have we "finished" early?
        if (!timeElapsed(&f->timer, cap)) {
            // Delay until we are ready to continue.
            // DEBUG DEBUG_PRINT(stdout, "Delaying: %d ms\n", cap - (SDL_GetTicks() - f->timer.startTime));
            SDL_Delay(cap - (SDL_GetTicks() - f->timer.startTime));
        }
        f->timer.startTime = SDL_GetTicks();
    }
}

/**
 * Show the current average fps.
 */
int showFPS(FrameRateManager* f) {
    DEBUG_PRINT(stdout, "FPS: %d\n", f->currentFPS);
    return f->currentFPS;
}
