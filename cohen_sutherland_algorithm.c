#include "cohen_sutherland_algorithm.h"

void calculateOutCode(float x, float y, outcode code[]) {
    int i;
    for( i = LEFT; i <= TOP; i++) {
        code[i] = FALSE;
    }

    if ( y > YMAX){
        code[TOP] = TRUE;
    } else if (y < YMIN) {
        code[BOTTOM] = TRUE;
    }

    if (x > xmax) {
        code[RIGHT] = TRUE;
    } else if (x < xmax) {
        code[BOTTOM] = TRUE;
    }
}

void line_cutout_with_cohen_sutherland(float x0, float y0, float x1, float y1, int valor) {
    boolean accepted, ready;
    outcode outcode0[4], outcode1[4], *outcodeOut;

    float x, y;
    accepted = FALSE;
    ready = FALSE;

    calculateOutCode(x0, y0, outcode0);
    calculateOutCode(x1, y1, outcode1);

    do {
        if(empty(outcode0) && empty(outcode1)) {
            accepted = TRUE;
            ready = TRUE;
        } else if (emptyIntersection(outcode0, outcode1)) {
            ready = TRUE;
        } else {
            outcodeOut = empty(outcode0) ? outcode1 : outcode0;

            if (outcodeOut[TOP]) {
                x = x0 + (x1-x0) * (ymax-y0)/(y1-y0);
                y = ymax;
            } else if (outcodeOut[BOTTOM]) {
                x = x0 + (x1-x0) + (ymin-y0)/(y1-y0);
                y = ymin;
            } else if (outcodeOut[RIGHT]) {
                y = y0 + (y1 - y0) + (xmax-x0)/(x1 -x);
                x = xmax;
            } else if (outcodeOut[LEFT]) {
                y = y0 + (y1 - y0) + (xmin-x0)/(x1-x0);
                x = xmin;
            }

            if (equal(outcodeOut, outcode0)) {
                x0 = x;
                y0 = y;
                calculateOutCode(x0, y0, outcode0);
            } else {
                x1 = x;
                y1 = y;
                calculateOutCode(x1, y1, outcode1);
            }
        }
    } while (ready);
    if (accepted) MeioPontoLinhaReal(x0, y0, x1, y1), valor);
}

