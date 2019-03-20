#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

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
 * A frame rate counter.
 */
typedef struct FrameRateManager {
    bool capped;
    short cappedFPS;
    short currentFPS;
    Timer timer;
} FrameRateManager;

/**
 * Initialise the timer using some global constants defined in config.h.
 */
FrameRateManager initFPSManager(void);

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
 * Maintain capped framerate.
 */
void updateTimer(FrameRateManager* f);

/**
 * Show the current average fps.
 */
void showFPS(FrameRateManager* f);

#endif