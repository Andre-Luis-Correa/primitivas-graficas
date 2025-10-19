#ifndef PRIMITIVASGRAFICAS_SCANLINE_FILL_ALGORITHM_H
#define PRIMITIVASGRAFICAS_SCANLINE_FILL_ALGORITHM_H

#include <stdlib.h>
#include <math.h>
#include "sdl_utils.h"
#include "drawing_utils.h"

typedef struct EdgeNode {
    int ymax;          // Coordenada y máxima da aresta
    float x_atual;     // Coordenada x da interseção com a scanline y
    float inv_m;       // Incremento em x (1/m, ou dx/dy)
    struct EdgeNode* next; // Próximo nó na lista ligada
} EdgeNode;

void fill_polygon_with_scanline(int* vx, int* vy, int num_vertices, int color);

#endif
