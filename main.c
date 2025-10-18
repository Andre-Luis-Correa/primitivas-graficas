#include <stdio.h>
#include "main_utils.h"

/*

1. Implemente o algoritmo do ponto médio para desenhar retas em C.
2. Implemente o algorítmo de recorte de primitivas (Cohen Sutherland) em C.
3. Implemente o algoritmo para desenhar um poligono. em C
4. Implemente o algoritmo para preenchimento de um poligono (scanline) em C.

*/

int main(int argc, char* argv[]) {
    int opcao;

    do {
        show_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (init_sdl()) {
                    menu_draw_line_with_midpoint_algorithm();
                    close_sdl();
                } else {
                    printf("Falha na inicializacao do SDL!\n");
                }
                break;

            case 2:
                if (init_sdl()) {
                    menu_line_cutout_with_cohen_sutherland();
                    close_sdl();
                } else {
                    printf("Falha na inicializacao do SDL!\n");
                }
                break;

            case 3: {
                int num_vertices;
                printf("\nDigite o numero de vertices (minimo 3): ");
                scanf("%d", &num_vertices);

                if (num_vertices < 3) {
                    printf("Numero de vertices invalido! Retornando ao menu.\n");
                } else {
                    if (init_sdl()) {
                        menu_draw_polygon(num_vertices);
                        close_sdl();
                    } else {
                        printf("Falha na inicializacao do SDL!\n");
                    }
                }
                break;
            }

            case 4:
                printf("\n[TODO] Preenchimento Scanline ainda nao implementado.\n");
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}