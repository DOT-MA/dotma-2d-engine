#ifndef CAMERA_H
#define CAMERA_H

typedef struct Camera {
    int x;
    int y;
    int w;
    int h;
    int scale;
    int rotation;
} Camera;

/**
 * Takes a percentage for the x and y positions, width and height
 * and translates the desired parameters into the game's scale.
 */
SDL_Rect translateRect(SDL_Renderer* renderer, float x, float y,
        float w, float h);

#endif
