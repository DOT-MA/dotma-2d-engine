#ifndef RENDERTEMPLATES_H
#define RENDERTEMPLATES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

/**
 * Simple function to draw a message to the screen using a font.
 */
bool renderFont(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect* pos, SDL_Color colour, char* text);


/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dpos);

/**
 * Render an image as the background.
 */
bool renderBackground(SDL_Renderer* renderer, SDL_Texture* texture);

/**
 * Draw a pre-designed debug message to the screen.
 */
bool renderDebugMessage(SDL_Renderer* renderer, TTF_Font* font, char* text);

/**
 * Show the fps in the top right corner of the screen.
 */
bool renderFPS(SDL_Renderer* renderer, TTF_Font* font, int fps);

#endif
