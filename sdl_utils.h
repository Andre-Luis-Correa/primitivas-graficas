#ifndef PRIMITIVASGRAFICAS_SDL_UTILS_H
#define PRIMITIVASGRAFICAS_SDL_UTILS_H

#include <stdio.h>
#include <SDL2/SDL.h>

extern SDL_Renderer* renderer;
extern SDL_Window* window;

int init_sdl();
void close_sdl();
void clear_screen();
void update_and_wait();
int rgb_to_color(int r, int g, int b);

#endif