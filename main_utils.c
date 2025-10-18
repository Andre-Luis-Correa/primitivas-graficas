#include "main_utils.h"
#include "sdl_utils.h"
#include "drawing_algorithms.h"

void show_menu() {
    printf("\n");
    printf("=====================================\n");
    printf("     PRIMITIVAS GRAFICAS - MENU      \n");
    printf("=====================================\n");
    printf("1. Desenhar Linha (Ponto Medio)\n");
    printf("2. Recorte de Linha (Cohen-Sutherland) [EM BREVE]\n");
    printf("3. Desenhar Poligono [EM BREVE]\n");
    printf("4. Preencher Poligono (Scanline) [EM BREVE]\n");
    printf("0. Sair\n");
    printf("=====================================\n");
    printf("Escolha uma opcao: ");
}

void menu_draw_line_with_midpoint_algorithm() {
    clear_screen();

    int color = rgb_to_color(0, 255, 0);
    draw_line_with_midpoint_algorithm(10, 100, 100, 10, color);
    draw_line_with_midpoint_algorithm(100, 10, 10, 100, color);
    draw_line_with_midpoint_algorithm(200, 100, 1, 1, color);
    draw_line_with_midpoint_algorithm(1, 1, 200, 100, color);
    draw_line_with_midpoint_algorithm(200, 100, 200, 10, color);
    draw_line_with_midpoint_algorithm(200, 10, 200, 100, color);
    draw_line_with_midpoint_algorithm(200, 100, 50, 100, color);

    //update_screen();
    update_and_wait();
}