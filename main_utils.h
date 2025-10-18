#ifndef PRIMITIVASGRAFICAS_MAIN_UTILS_H
#define PRIMITIVASGRAFICAS_MAIN_UTILS_H

#include <stdio.h>
#include <math.h>
#include "sdl_utils.h"
#include "midpoint_line_algorithm.h"
#include "cohen_sutherland_algorithm.h"

void show_menu();
void menu_draw_line_with_midpoint_algorithm();
void menu_line_cutout_with_cohen_sutherland();
void menu_draw_polygon(int num_vertices);

#endif