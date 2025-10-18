#ifndef PRIMITIVASGRAFICAS_DRAWING_UTILS_H
#define PRIMITIVASGRAFICAS_DRAWING_UTILS_H

#include <SDL2/SDL.h>

extern SDL_Renderer* renderer;

void write_pixel(int x, int y, int color);

#endif