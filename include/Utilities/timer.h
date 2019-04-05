#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

#include <stdint.h>

#include <stdio.h>
#include <stdbool.h>

/**
 * A timer.
 */
typedef struct Timer {
    bool started;
    bool paused;
    uint32_t startTime;
    uint32_t pausedTime;
} Timer;

/**
 * Initialise a timer.
 */
Timer initTimer(void);

/**
 * Start the fps timer.
 */
void startTimer(Timer* t);
/**
 *  Stop the timer.
 */
void stopTimer(Timer* t);

/**
 * Pause the timer.
 */
void pauseTimer(Timer* t);

/**
 * Unpasue the timer.
 */
void unpauseTimer(Timer* t);

/**
 * Return the current ticks of the timer.
 */
uint32_t getTimerTicks(Timer* t);

/**
 * Check if provided time in ms has elapsed already.
 */
bool timeElapsed(Timer* t, uint32_t ms);

#endif
