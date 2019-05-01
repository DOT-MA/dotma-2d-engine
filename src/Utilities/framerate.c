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
        .frames = 0,
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
    f->frames++;
    if (f->capped) {
        int cap = (1000 / f->cappedFPS);
        // Have we "finished" early?
        if (!timeElapsed(&f->timer, cap)) {
            // Delay until we are ready to continue.
            // DEBUG_PRINT(stdout, "Delaying: %d ms\n", cap - (SDL_GetTicks() - f->timer.startTime));
            SDL_Delay(cap - (SDL_GetTicks() - f->timer.startTime));
        }
        // Reset framerate timer.
        f->timer.startTime = SDL_GetTicks();
        // Calculate the current fps.
        f->currentFPS = (int) f->frames / (SDL_GetTicks() - getTimerTicks(&f->timer) / 1000.f);
        f->frames = 0;
    }
}

/**
 * Show the current average fps.
 */
int getFPS(FrameRateManager* f) {
    DEBUG_PRINT(stdout, "FPS: %d\n", f->currentFPS);
    return f->currentFPS;
}
