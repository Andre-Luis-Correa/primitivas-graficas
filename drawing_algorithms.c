#include "drawing_algorithms.h"

// Octante 1: 0° <= ângulo < 45° (dx >= dy, ambos positivos)
static void draw_line_octant_1(int x1, int y1, int x2, int y2, int color) {
    int dx, dy, incE, incNE, d, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * dy - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);
    x = x1;
    y = y1;

    write_pixel(x, y, color);

    while (x < x2) {
        if(d <= 0) {
            d = d + incE;
            x = x + 1;
        } else {
            d = d + incNE;
            x = x + 1;
            y = y + 1;
        }
        write_pixel(x, y, color);
    }
}

// Octante 2: 45° <= ângulo < 90° (dy > dx, ambos positivos)
static void draw_line_octant_2(int x1, int y1, int x2, int y2, int color) {
    int dx, dy, incE, incNE, d, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * dx - dy;
    incE = 2 * dx;
    incNE = 2 * (dx - dy);
    x = x1;
    y = y1;

    write_pixel(x, y, color);

    while (y < y2) { // Loop simples
        if(d <= 0) {
            d = d + incE;
            y = y + 1;
        } else {
            d = d + incNE;
            x = x + 1;
            y = y + 1;
        }
        write_pixel(x, y, color);
    }
}

// Octante 3: 90° <= ângulo < 135° (dy > -dx, dy > 0, dx < 0)
static void draw_line_octant_3(int x1, int y1, int x2, int y2, int color) {
    int dx, dy, incE, incNE, d, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * (-dx) - dy;
    incE = 2 * (-dx);
    incNE = 2 * ((-dx) - dy);
    x = x1;
    y = y1;

    write_pixel(x, y, color);

    while (y < y2) { // Loop simples
        if(d <= 0) {
            d = d + incE;
            y = y + 1;
        } else {
            d = d + incNE;
            x = x - 1;
            y = y + 1;
        }
        write_pixel(x, y, color);
    }
}

// Octante 4: 135° <= ângulo < 180° (-dx >= dy, dy > 0, dx < 0)
static void draw_line_octant_4(int x1, int y1, int x2, int y2, int color) {
    int dx, dy, incE, incNE, d, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * dy - (-dx);
    incE = 2 * dy;
    incNE = 2 * (dy - (-dx));
    x = x1;
    y = y1;

    write_pixel(x, y, color);

    while (x > x2) { // Loop simples
        if(d <= 0) {
            d = d + incE;
            x = x - 1;
        } else {
            d = d + incNE;
            x = x - 1;
            y = y + 1;
        }
        write_pixel(x, y, color);
    }
}

// Octante 5: 180° <= ângulo < 225° (-dx >= -dy, ambos negativos)
static void draw_line_octant_5(int x1, int y1, int x2, int y2, int color) {
    int dx, dy, incE, incNE, d, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * (-dy) - (-dx);
    incE = 2 * (-dy);
    incNE = 2 * ((-dy) - (-dx));
    x = x1;
    y = y1;

    write_pixel(x, y, color);

    while (x > x2) { // Loop simples
        if(d <= 0) {
            d = d + incE;
            x = x - 1;
        } else {
            d = d + incNE;
            x = x - 1;
            y = y - 1;
        }
        write_pixel(x, y, color);
    }
}

// Octante 6: 225° <= ângulo < 270° (-dy > -dx, ambos negativos)
static void draw_line_octant_6(int x1, int y1, int x2, int y2, int color) {
    int dx, dy, incE, incNE, d, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * (-dx) - (-dy);
    incE = 2 * (-dx);
    incNE = 2 * ((-dx) - (-dy));
    x = x1;
    y = y1;

    write_pixel(x, y, color);

    while (y > y2) { // Loop simples
        if(d <= 0) {
            d = d + incE;
            y = y - 1;
        } else {
            d = d + incNE;
            x = x - 1;
            y = y - 1;
        }
        write_pixel(x, y, color);
    }
}

// Octante 7: 270° <= ângulo < 315° (-dy > dx, dy < 0, dx > 0)
static void draw_line_octant_7(int x1, int y1, int x2, int y2, int color) {
    int dx, dy, incE, incNE, d, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * dx - (-dy);
    incE = 2 * dx;
    incNE = 2 * (dx - (-dy));
    x = x1;
    y = y1;

    write_pixel(x, y, color);

    while (y > y2) { // Loop simples
        if(d <= 0) {
            d = d + incE;
            y = y - 1;
        } else {
            d = d + incNE;
            x = x + 1;
            y = y - 1;
        }
        write_pixel(x, y, color);
    }
}

// Octante 8: 315° <= ângulo < 360° (dx >= -dy, dx > 0, dy < 0)
static void draw_line_octant_8(int x1, int y1, int x2, int y2, int color) {
    int dx, dy, incE, incNE, d, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * (-dy) - dx;
    incE = 2 * (-dy);
    incNE = 2 * ((-dy) - dx);
    x = x1;
    y = y1;

    write_pixel(x, y, color);

    while (x < x2) { // Loop simples
        if(d <= 0) {
            d = d + incE;
            x = x + 1;
        } else {
            d = d + incNE;
            x = x + 1;
            y = y - 1;
        }
        write_pixel(x, y, color);
    }
}

void draw_line_with_midpoint_algorithm(int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int absdx = abs(dx);
    int absdy = abs(dy);

    // Determina qual octante e chama a função correspondente
    if (absdx >= absdy) {
        // Inclinação <= 45 graus
        if (dx >= 0) {
            if (dy >= 0) {
                // Octante 1
                printf("Octante 1\n");
                draw_line_octant_1(x1, y1, x2, y2, color);
            } else {
                // Octante 8
                printf("Octante 8\n");
                draw_line_octant_8(x1, y1, x2, y2, color);
            }
        } else {
            if (dy >= 0) {
                // Octante 4
                printf("Octante 4\n");
                draw_line_octant_4(x1, y1, x2, y2, color);
            } else {
                // Octante 5
                printf("Octante 5\n");
                draw_line_octant_5(x1, y1, x2, y2, color);
            }
        }
    } else {
        // Inclinação > 45 graus
        if (dy >= 0) {
            if (dx >= 0) {
                // Octante 2
                printf("Octante 2\n");
                draw_line_octant_2(x1, y1, x2, y2, color);
            } else {
                // Octante 3
                printf("Octante 3\n");
                draw_line_octant_3(x1, y1, x2, y2, color);
            }
        } else {
            if (dx >= 0) {
                // Octante 7
                printf("Octante 7\n");
                draw_line_octant_7(x1, y1, x2, y2, color);
            } else {
                // Octante 6
                printf("Octante 6\n");
                draw_line_octant_6(x1, y1, x2, y2, color);
            }
        }
    }
}