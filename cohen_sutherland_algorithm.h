#ifndef PRIMITIVASGRAFICAS_COHEN_SUTHERLAND_ALGORITHM_H
#define PRIMITIVASGRAFICAS_COHEN_SUTHERLAND_ALGORITHM_H

#include "midpoint_line_algorithm.h"

#define XMIN 100.0f
#define YMIN 100.0f
#define XMAX 500.0f
#define YMAX 400.0f

typedef enum {
    LEFT = 0,
    RIGHT = 1,
    BOTTOM = 2,
    TOP = 3
} edge;

typedef enum {
    FALSE,
    TRUE
} boolean;

typedef boolean outcode;

void line_cutout_with_cohen_sutherland(float x0, float y0, float x1, float y1, int color);

boolean empty(outcode code[]);
boolean emptyIntersection(outcode code0[], outcode code1[]);
void calculateOutCode(float x, float y, outcode code[]);

#endif