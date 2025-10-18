# include "drawing_utils.h"

void write_pixel(int x, int y, int color) {
    // Extrai RGB
    Uint8 r = (color >> 16) & 0xFF;
    Uint8 g = (color >> 8) & 0xFF;
    Uint8 b = color & 0xFF;

    // Define a cor e desenha o ponto
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}