#include "sdl_utils.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("Primitivas Gráficas",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("Erro ao criar renderer: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

void close_sdl() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void clear_screen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void update_and_wait() {
    SDL_RenderPresent(renderer);

    printf("\nJanela aberta. Pressione ESC ou feche a janela para continuar.\n");

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = 1;
            }
        }
        SDL_Delay(16); // ~60 FPS
    }
}

int rgb_to_color(int r, int g, int b) {
    return (r << 16) | (g << 8) | b;
}
