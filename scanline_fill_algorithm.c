#include "scanline_fill_algorithm.h"


// Insere uma aresta em uma lista (ET ou AET), mantendo-a ordenada pela coordenada x_atual
void insert_edge(EdgeNode** list_head, EdgeNode* edge) {
    if (*list_head == NULL) {
        *list_head = edge;
    } else {
        EdgeNode* p = *list_head;
        EdgeNode* prev = NULL;
        while (p != NULL && p->x_atual < edge->x_atual) {
            prev = p;
            p = p->next;
        }
        if (prev == NULL) {
            // Insere no início
            edge->next = *list_head;
            *list_head = edge;
        } else {
            // Insere no meio ou fim
            edge->next = p;
            prev->next = edge;
        }
    }
}

// Constrói a Tabela de Arestas Globais (ET) a partir dos vértices do polígono
void build_ET(int* vx, int* vy, int n, EdgeNode* ET[]) {
    for (int i = 0; i < n; i++) {
        int i_next = (i + 1) % n;

        int y1 = vy[i];
        int x1 = vx[i];
        int y2 = vy[i_next];
        int x2 = vx[i_next];

        // Ignora arestas horizontais
        if (y1 == y2) continue;

        // Garante que (x1, y1) seja o ponto com menor y
        int ymin = y1 < y2 ? y1 : y2;
        int ymax = y1 > y2 ? y1 : y2;
        float x_of_ymin = (float)(y1 < y2 ? x1 : x2);

        // Calcula o incremento x (1/m)
        float inv_m = (float)(x2 - x1) / (float)(y2 - y1);

        // Cria o nó da aresta
        EdgeNode* new_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
        if (new_edge == NULL) return; // Falha de alocação

        new_edge->ymax = ymax;
        new_edge->x_atual = x_of_ymin;
        new_edge->inv_m = inv_m;
        new_edge->next = NULL;

        // Insere na ET no bucket 'ymin', ordenado por x
        insert_edge(&ET[ymin], new_edge);
    }
}

// Desenha os spans (segmentos horizontais) entre pares de 'x' na AET
void draw_scanline_spans(EdgeNode* AET, int y, int color) {
    EdgeNode* p = AET;
    while (p != NULL && p->next != NULL) {
        // Pega o par de coordenadas x
        int x_start = (int)ceil(p->x_atual);
        int x_end = (int)floor(p->next->x_atual);

        // Desenha a linha horizontal
        for (int x = x_start; x <= x_end; x++) {
            write_pixel(x, y, color); //
        }

        // Pula para o próximo par
        p = p->next->next;
    }
}

// Remove da AET as arestas que terminam na scanline atual (y == ymax)
void remove_edges_at_y(EdgeNode** AET, int y) {
    EdgeNode* p = *AET;
    EdgeNode* prev = NULL;
    while (p != NULL) {
        if (p->ymax == y) {
            EdgeNode* to_free = p;
            if (prev == NULL) {
                // Remove do início
                *AET = p->next;
                p = *AET;
            } else {
                // Remove do meio ou fim
                prev->next = p->next;
                p = p->next;
            }
            free(to_free);
        } else {
            prev = p;
            p = p->next;
        }
    }
}

/*
Atualiza a coordenada 'x' de cada aresta na AET.
x = x + 1/m
*/
void update_aet(EdgeNode* AET) {
    for (EdgeNode* p = AET; p != NULL; p = p->next) {
        p->x_atual += p->inv_m;
    }
}

// Reordena a AET com base nos novos valores de 'x'
void resort_aet(EdgeNode** AET) {
    if (*AET == NULL || (*AET)->next == NULL) return;

    EdgeNode* sorted_list = NULL;
    EdgeNode* current = *AET;

    while (current != NULL) {
        EdgeNode* next_node = current->next;
        // Desconecta o nó
        current->next = NULL;
        // Insere na lista ordenada
        insert_edge(&sorted_list, current);
        current = next_node;
    }

    *AET = sorted_list;
}

// Move as arestas da ET[y] para a AET, mantendo a AET ordenada
void move_edges_from_et_to_aet(EdgeNode* ET[], EdgeNode** AET, int y) {
    EdgeNode* et_bucket = ET[y];
    EdgeNode* p_aet = *AET;
    EdgeNode* p_et = et_bucket;

    EdgeNode* new_aet_head = NULL;
    EdgeNode* new_aet_tail = NULL;

    // Mescla (merge) as duas listas ordenadas (AET e ET[y])
    while (p_aet != NULL && p_et != NULL) {
        EdgeNode* smaller;
        if (p_aet->x_atual < p_et->x_atual) {
            smaller = p_aet;
            p_aet = p_aet->next;
        } else {
            smaller = p_et;
            p_et = p_et->next;
        }

        if (new_aet_head == NULL) {
            new_aet_head = smaller;
            new_aet_tail = smaller;
        } else {
            new_aet_tail->next = smaller;
            new_aet_tail = smaller;
        }
    }

    // Adiciona o restante de qualquer lista
    if (p_aet != NULL) {
        if (new_aet_head == NULL) *AET = p_aet;
        else new_aet_tail->next = p_aet;
    } else if (p_et != NULL) {
        if (new_aet_head == NULL) *AET = p_et;
        else new_aet_tail->next = p_et;
    } else {
        *AET = new_aet_head;
    }

    if (new_aet_head != NULL) *AET = new_aet_head;

    // Esvazia o bucket da ET
    ET[y] = NULL;
}

void fill_polygon_with_scanline(int* vx, int* vy, int num_vertices, int color) {
    // Aloca a ET. É um array de ponteiros para EdgeNode
    EdgeNode* ET[SCREEN_HEIGHT];
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        ET[i] = NULL;
    }

    // Aloca a AET (inicia vazia)
    EdgeNode* AET = NULL;

    // 1. Constrói a ET
    build_ET(vx, vy, num_vertices, ET);

    // 2. Encontra a primeira scanline (ymin)
    int y = 0;
    while (y < SCREEN_HEIGHT && ET[y] == NULL) {
        y++;
    }

    // 3. Loop principal
    while (y < SCREEN_HEIGHT) {
        // Passo 5: Retira arestas (y == ymax)
        remove_edges_at_y(&AET, y);

        // Passo 4: Transfere de ET[y] para AET
        move_edges_from_et_to_aet(ET, &AET, y);

        // Passo 6: Desenha os pixels
        draw_scanline_spans(AET, y, color);

        // Passo 7: Incrementa y
        y++;

        // Passo 8: Atualiza x (x = x + 1/m)
        update_aet(AET);

        // Passo 9: Reordena AET
        resort_aet(&AET);

        // Se AET e ET (restante) estão vazias, pode parar.
        if (AET == NULL) {
            // Avança y para a próxima entrada da ET
            while (y < SCREEN_HEIGHT && ET[y] == NULL) {
                y++;
            }
            if (y == SCREEN_HEIGHT) {
                // Sai do loop principal
                break;
            }
        }
    }
}