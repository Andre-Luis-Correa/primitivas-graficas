#include "cohen_sutherland_algorithm.h"

boolean empty(outcode code[]) {
    for (int i = LEFT; i <= TOP; i++) {
        if (code[i] == TRUE) {
            return FALSE;
        }
    }
    return TRUE;
}

boolean emptyIntersection(outcode code0[], outcode code1[]) {
    for (int i = LEFT; i <= TOP; i++) {
        if (code0[i] == TRUE && code1[i] == TRUE) return TRUE;
    }
    return FALSE;
}

void calculateOutCode(float x, float y, outcode code[]) {
    int i;
    for (i = LEFT; i <= TOP; i++)
        code[i] = FALSE;

    if (y > YMAX)
        code[TOP] = TRUE;
    else if (y < YMIN)
        code[BOTTOM] = TRUE;

    if (x > XMAX)
        code[RIGHT] = TRUE;
    else if (x < XMIN)
        code[LEFT] = TRUE;
}

void line_cutout_with_cohen_sutherland(float x0, float y0, float x1, float y1, int color) {
    boolean accepted, ready;
    outcode outcode0[4], outcode1[4], *outcodeOut;

    float x, y;
    accepted = FALSE;
    ready = FALSE;

    calculateOutCode(x0, y0, outcode0);
    calculateOutCode(x1, y1, outcode1);

    do {
        if (empty(outcode0) && empty(outcode1)) {
            accepted = TRUE;
            ready = TRUE;
        } else if (emptyIntersection(outcode0, outcode1)) {
            ready = TRUE;
        } else {
            outcodeOut = empty(outcode0) ? outcode1 : outcode0;

            if (outcodeOut[TOP]) {
                x = x0 + (x1 - x0) * (YMAX - y0) / (y1 - y0);
                y = YMAX;
            } else if (outcodeOut[BOTTOM]) {
                x = x0 + (x1 - x0) * (YMIN - y0) / (y1 - y0);
                y = YMIN;
            } else if (outcodeOut[RIGHT]) {
                y = y0 + (y1 - y0) * (XMAX - x0) / (x1 - x0);
                x = XMAX;
            } else if (outcodeOut[LEFT]) {
                y = y0 + (y1 - y0) * (XMIN - x0) / (x1 - x0);
                x = XMIN;
            }

            if (outcodeOut == outcode0) {
                x0 = x;
                y0 = y;
                calculateOutCode(x0, y0, outcode0);
            } else {
                x1 = x;
                y1 = y;
                calculateOutCode(x1, y1, outcode1);
            }
        }
    } while (!ready);

    if (accepted) {
        draw_line_with_midpoint_algorithm(
                (int) (x0 + 0.5f), (int) (y0 + 0.5f),
                (int) (x1 + 0.5f), (int) (y1 + 0.5f),
                color
        );
    }
}