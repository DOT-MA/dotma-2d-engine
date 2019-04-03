#include <SDL2/SDL.h>

#include "../include/camera.h"

/**
 * Takes a percentage for the x and y positions, width and height
 * and translates the desired parameters into the game's scale.
 */
SDL_Rect translateRect(SDL_Renderer* renderer, float x, float y,
        float w, float h) {
    int windowWidth = 0;
    int windowHeight = 0;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    SDL_Rect transformed = {
        .w = (int) (windowWidth * w),
        .h = (int) (windowHeight * h),
        .x = (int) (windowWidth * x) + ((windowWidth * w) / 2),
        .y = (int) (windowHeight * y) - ((windowHeight * h) / 2)
    };
    // printf("%d %d %d %d %d %d\n", windowWidth, windowHeight, transformed.w, transformed.h, transformed.x, transformed.y);
    return transformed;
}

