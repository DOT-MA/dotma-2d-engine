#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../include/renderertemplates.h"

/**
 * Simple function to draw a message to the screen using a font.
 */
bool renderFont(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect* pos, SDL_Color colour, char* text) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, colour);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    // Draw to renderer
    bool result = SDL_RenderCopy(renderer, texture, NULL, pos);
    SDL_DestroyTexture(texture);
    return result;
}

/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dpos) {
    if (SDL_RenderCopy(renderer, texture, NULL, dpos) != 0) {
        return false;
    }
    return true;
}

/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool renderBackground(SDL_Renderer* renderer, SDL_Texture* texture) {
    if (SDL_RenderCopy(renderer, texture, NULL, NULL) != 0) {
        return false;
    }
    return true;
}

/**
 * Draw a pre-designed debug message to the screen.
 */
bool renderDebugMessage(SDL_Renderer* renderer, TTF_Font* font, char* text) {
    int text_size = strlen(text);
    int font_height = TTF_FontHeight(font);
    int font_width = font_height / 2;
    SDL_Rect pos = {
        .x = 0,
        .y = 0,
        .w = font_width * text_size,
        .h = font_height
    };
    SDL_Color c = {255, 0, 0};
    return renderFont(renderer, font, &pos, c, text);
}

/**
 * Show the fps in the top right corner of the screen.
 */
bool renderFPS(SDL_Renderer* renderer, TTF_Font* font, int fps) {
    char text[10];
    sprintf(text, "%d", fps);
    int height, width;
    SDL_GetRendererOutputSize(renderer, &width, &height);
    int font_size = TTF_FontHeight(font);
    SDL_Rect pos = {
        .x = width - ((font_size/2) * 4) - 5,
        .y = 0,
        .w = font_size * 2,
        .h = font_size
    };
    SDL_Color c = {0, 0, 0};
    return renderFont(renderer, font, &pos, c, text);
}
