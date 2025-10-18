#ifndef PRIMITIVASGRAFICAS_COHEN_SUTHERLAND_ALGORITHM_H
#define PRIMITIVASGRAFICAS_COHEN_SUTHERLAND_ALGORITHM_H

typedef enum {
    LEFT = 0,
    RIGHT = 1,
    BOTTOM = 2,
    TOP = 3
} edge;

typedef enum {
    TRUE,
    FALSE
} boolean;

typedef boolean outcode;

void line_cutout_with_cohen_sutherland(float x0, float y0, float x1, float y1, int valor);

boolean empty(outcode code[]);

boolean emptyIntersection(outcode code0[], outcode code1[]);

boolean equal(outcode code0[], outcode code1[]);

void calculateOutCode(float x, float y, outcode code[]);

#endif
