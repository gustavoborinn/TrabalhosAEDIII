#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Estrutura de dados para o grafo
typedef struct {
    int num_vertices;
    int matriz_adj[MAX_VERTICES][MAX_VERTICES];
} Grafo;

// Inicialização do grafo
void inicializar_grafo(Grafo *grafo, int num_vertices) {
    grafo->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            grafo->matriz_adj[i][j] = 0;
        }
    }
}

// Adicionar aresta ao grafo
void adicionar_aresta(Grafo *grafo, int origem, int destino, int peso) {
    grafo->matriz_adj[origem][destino] = peso;
    grafo->matriz_adj[destino][origem] = peso; // Para grafos não direcionados
}

// Algoritmo de Dijkstra para encontrar o caminho mínimo
void dijkstra(const Grafo *grafo, int origem, int *distancias) {
    bool visitados[MAX_VERTICES] = {false};
    for (int i = 0; i < grafo->num_vertices; i++) {
        distancias[i] = INT_MAX;
    }
    distancias[origem] = 0;
    
    for (int i = 0; i < grafo->num_vertices; i++) {
        int u = -1;
        for (int j = 0; j < grafo->num_vertices; j++) {
            if (!visitados[j] && (u == -1 || distancias[j] < distancias[u])) {
                u = j;
            }
        }
        visitados[u] = true;
        
        for (int v = 0; v < grafo->num_vertices; v++) {
            if (grafo->matriz_adj[u][v] && !visitados[v] && distancias[v] > distancias[u] + grafo->matriz_adj[u][v]) {
                distancias[v] = distancias[u] + grafo->matriz_adj[u][v];
            }
        }
    }
}

// Cálculo de closeness
float closeness(const Grafo *grafo, int vertice) {
    int distancias[MAX_VERTICES];
    dijkstra(grafo, vertice, distancias);
    int soma_distancias = 0;
    for (int i = 0; i < grafo->num_vertices; i++) {
        soma_distancias += distancias[i];
    }
    return (float)soma_distancias / (grafo->num_vertices - 1);
}

// Função para desenhar o grafo
void desenhar_grafo(const int matriz_adj[][MAX_VERTICES], int num_vertices) {
    FILE *fp;
    fp = fopen("temp_grafo.py", "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        exit(1);
    }
    fprintf(fp, "from desenhar_grafo import desenhar_grafo\n\n");
    fprintf(fp, "matriz_adj = [\n");
    for (int i = 0; i < num_vertices; i++) {
        fprintf(fp, "    [");
        for (int j = 0; j < num_vertices; j++) {
            fprintf(fp, "%d", matriz_adj[i][j]);
            if (j != num_vertices - 1) {
                fprintf(fp, ", ");
            }
        }
        fprintf(fp, "]");
        if (i != num_vertices - 1) {
            fprintf(fp, ",");
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "]\n\n");
    fprintf(fp, "desenhar_grafo(matriz_adj)\n");
    fclose(fp);

    system("python temp_grafo.py");
}

int main() {
    Grafo grafo;
    inicializar_grafo(&grafo, 5);
    adicionar_aresta(&grafo, 0, 4, 20);
    adicionar_aresta(&grafo, 0, 1, 10);
    adicionar_aresta(&grafo, 0, 2, 5);
    adicionar_aresta(&grafo, 1, 3, 3);
    adicionar_aresta(&grafo, 2, 4, 7);

    // Teste do cálculo de closeness
    float closeness_value = closeness(&grafo, 2);
    printf("Closeness do vértice 0: %f\n", closeness_value);

    // Teste do desenho do grafo
    desenhar_grafo(grafo.matriz_adj, grafo.num_vertices);

    return 0;
}
