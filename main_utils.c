#include "main_utils.h"

void show_menu() {
    printf("\n");
    printf("=====================================\n");
    printf("     PRIMITIVAS GRAFICAS - MENU      \n");
    printf("=====================================\n");
    printf("1. Desenhar Linha (Ponto Medio)\n");
    printf("2. Recorte de Linha (Cohen-Sutherland)\n");
    printf("3. Desenhar Poligono [EM BREVE]\n");
    printf("4. Preencher Poligono (Scanline) [EM BREVE]\n");
    printf("0. Sair\n");
    printf("=====================================\n");
    printf("Escolha uma opcao: ");
}

void menu_draw_line_with_midpoint_algorithm() {
    clear_screen();

    int red = rgb_to_color(255, 0, 0);
    int green = rgb_to_color(0, 255, 0);
    int blue = rgb_to_color(0, 0, 255);
    int yellow = rgb_to_color(255, 255, 0);
    int cian = rgb_to_color(0, 255, 255);
    int pink = rgb_to_color(255, 0, 255);
    int white = rgb_to_color(255, 255, 255);
    int orange = rgb_to_color(255, 128, 0);

    // Ponto central da tela (supondo 800x600)
    int cx = 400;
    int cy = 300;

    // Comprimentos para linhas "rasas" (mais horizontal)
    int shallow_dx = 200;
    int shallow_dy = 75;

    // Comprimentos para linhas "íngremes" (mais vertical)
    int steep_dx = 75;
    int steep_dy = 200;

    // Desenhando 8 linhas (octantes) a partir do centro (400, 300)
    // Octante 1 (Leste-Sudeste)
    draw_line_with_midpoint_algorithm(cx, cy, cx + shallow_dx, cy + shallow_dy, red);
    // Octante 2 (Sul-Sudeste)
    draw_line_with_midpoint_algorithm(cx, cy, cx + steep_dx, cy + steep_dy, green);
    // Octante 3 (Sul-Sudoeste)
    draw_line_with_midpoint_algorithm(cx, cy, cx - steep_dx, cy + steep_dy, blue);
    // Octante 4 (Oeste-Sudoeste)
    draw_line_with_midpoint_algorithm(cx, cy, cx - shallow_dx, cy + shallow_dy, yellow);
    // Octante 5 (Oeste-Noroeste)
    draw_line_with_midpoint_algorithm(cx, cy, cx - shallow_dx, cy - shallow_dy, cian);
    // Octante 6 (Norte-Noroeste)
    draw_line_with_midpoint_algorithm(cx, cy, cx - steep_dx, cy - steep_dy, pink);
    // Octante 7 (Norte-Nordeste)
    draw_line_with_midpoint_algorithm(cx, cy, cx + steep_dx, cy - steep_dy, white);
    // Octante 8 (Leste-Nordeste)
    draw_line_with_midpoint_algorithm(cx, cy, cx + shallow_dx, cy - shallow_dy, orange);

    // Desenhando 4 linhas (cardeais) em branco
    // Horizontal (Leste)
    draw_line_with_midpoint_algorithm(cx, cy, cx + 250, cy, white);
    // Horizontal (Oeste)
    draw_line_with_midpoint_algorithm(cx, cy, cx - 250, cy, white);
    // Vertical (Sul)
    draw_line_with_midpoint_algorithm(cx, cy, cx, cy + 250, white);
    // Vertical (Norte)
    draw_line_with_midpoint_algorithm(cx, cy, cx, cy - 250, white);

    update_and_wait();
}

void menu_line_cutout_with_cohen_sutherland() {
    clear_screen();

    int rectColor = rgb_to_color(255, 255, 255);
    int lineColorIn = rgb_to_color(0, 255, 0);
    int lineColorOut = rgb_to_color(255, 0, 0);
    int lineColorClip = rgb_to_color(0, 255, 255);

    // Desenha a janela de recorte (XMIN, YMIN) a (XMAX, YMAX)
    draw_line_with_midpoint_algorithm((int) XMIN, (int) YMIN, (int) XMAX, (int) YMIN, rectColor);
    draw_line_with_midpoint_algorithm((int) XMAX, (int) YMIN, (int) XMAX, (int) YMAX, rectColor);
    draw_line_with_midpoint_algorithm((int) XMAX, (int) YMAX, (int) XMIN, (int) YMAX, rectColor);
    draw_line_with_midpoint_algorithm((int) XMIN, (int) YMAX, (int) XMIN, (int) YMIN, rectColor);

    // 1. Totalmente dentro
    // Desenha a linha original em vermelho
    draw_line_with_midpoint_algorithm(150, 150, 300, 300, lineColorOut);
    // Desenha a linha recortada (que é a linha inteira) em verde por cima
    line_cutout_with_cohen_sutherland(150, 150, 300, 300, lineColorIn);

    // 2. Totalmente fora - lado
    // Desenha a linha original em vermelho
    draw_line_with_midpoint_algorithm(50, 50, 80, 80, lineColorOut);
    // Função de recorte não desenhará nada (accepted = FALSE)
    line_cutout_with_cohen_sutherland(50, 50, 80, 80, lineColorOut);

    // 3. Totalmente fora - canto
    // Desenha a linha original em vermelho
    draw_line_with_midpoint_algorithm(550, 50, 600, 100, lineColorOut);
    // Função de recorte não desenhará nada
    line_cutout_with_cohen_sutherland(550, 50, 600, 100, lineColorOut);

    // 4. Cruzando 2 bordas
    // Desenha a linha original em vermelho
    draw_line_with_midpoint_algorithm(50, 250, 550, 250, lineColorOut);
    // Desenha o segmento recortado em ciano por cima
    line_cutout_with_cohen_sutherland(50, 250, 550, 250, lineColorClip);

    // 5. Cruzando 2 bordas
    // Desenha a linha original em vermelho
    draw_line_with_midpoint_algorithm(250, 50, 250, 550, lineColorOut);
    // Desenha o segmento recortado em ciano por cima
    line_cutout_with_cohen_sutherland(250, 50, 250, 550, lineColorClip);

    // 6. Cruzando 2 bordas diagonal
    // Desenha a linha original em vermelho
    draw_line_with_midpoint_algorithm(50, 50, 300, 350, lineColorOut);
    // Desenha o segmento recortado em ciano por cima
    line_cutout_with_cohen_sutherland(50, 50, 300, 350, lineColorClip);

    // 7. Cruzando 2 bordas diagonal
    // Desenha a linha original em vermelho
    draw_line_with_midpoint_algorithm(300, 50, 550, 300, lineColorOut);
    // Desenha o segmento recortado em ciano por cima
    line_cutout_with_cohen_sutherland(300, 50, 550, 300, lineColorClip);

    // 8. Cruzando 1 borda
    // Desenha a linha original em vermelho
    draw_line_with_midpoint_algorithm(150, 150, 150, 500, lineColorOut);
    // Desenha o segmento recortado em ciano por cima
    line_cutout_with_cohen_sutherland(150, 150, 150, 500, lineColorClip);

    // Exibe o resultado
    update_and_wait();
}