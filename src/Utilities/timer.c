#include <SDL2/SDL.h>

#include <stdio.h>

#include "../../include/config.h"
#include "../../include/Utilities/timer.h"

/**
 * Initialise a timer.
 */
Timer initTimer(void) {
    return (Timer) {
        .started = false,
        .paused = false,
        .startTime = 0,
        .pausedTime = 0.
    };
}

/**
 * Start the fps timer.
 */
void startTimer(Timer* t) {
    t->started = true;
    t->paused = false;
    t->startTime = SDL_GetTicks();
}

/**
 *  Stop the timer.
 */
void stopTimer(Timer* t) {
    t->started = false;
    t->paused = false;
}

/**
 * Pause the timer.
 */
void pauseTimer(Timer* t) {
    if (t->started && !t->paused) {
        t->paused = true;
        t->pausedTime = SDL_GetTicks() - t->startTime;
    }
}

/**
 * Unpasue the timer.
 */
void unpauseTimer(Timer* t) {
    if (t->paused) {
        t->paused = false;
        t->startTime = SDL_GetTicks() - t->pausedTime;
        t->pausedTime = 0;
    }
}

/**
 * Return the current ticks of the timer.
 */
uint32_t getTimerTicks(Timer* t) {
    if (t->started) {
        if (t->paused) {
            return t->pausedTime;
        } else {
            return t->startTime;
        }
    }
    return 0;
}

/**
 * Check if provided time in ms has elapsed already.
 */
bool timeElapsed(Timer* t, uint32_t ms) {
    uint32_t elapsed = SDL_GetTicks() - getTimerTicks(t);
    if (elapsed >= ms) {
        return true;
    }
    return false;
}
