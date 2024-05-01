/*+-------------------------------------------------------------+
 | UNIFAL – Universidade Federal de Alfenas.                    |
 | BACHARELADO EM CIÊNCIA DA COMPUTAÇÃO.                        |
 | Trabalho..: Algoritmo em Grafos                              |
 | Disciplina: Algoritmos e Estrutura de Dados III              |
 | Professor.: Iago Augusto de Carvalho                                             |
 | Aluno(s)..: Gustavo Benfica Paulino                          |
 | Gustavo Borin Nascimento                                     |
 | Lucas Gabriel da Silva Batista                               |
 | Maria Luiza Alves Belarmino                                  |
 | Vinícius Gomes                                               |
 | Data......: 30/04/2024                                       |
 +-------------------------------------------------------------+*/


/*O objetivo do trabalho prático em é utilizar algoritmos 
em grafos para resolver um problema de centralidade em redes complexas. 
Mais especificamente, o trabalho envolve a implementação do cálculo de closeness 
em grafos, a análise da centralidade dos vértices e a visualização do grafo com base 
nesse cálculo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 75 //Quantidade máxima de vértices

// Estrutura de dados para o grafo
typedef struct {
    int num_vertices; //armazena o número de vértices
    int matriz_adj[MAX_VERTICES][MAX_VERTICES];
} Grafo;

/* Inicialização do grafo, definindo o número de vértices e configurando 
a matriz de adjacência para indicar que inicialmente não há conexões entre 
os vértices*/
void inicializar_grafo(Grafo *grafo, int num_vertices) {
    grafo->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            grafo->matriz_adj[i][j] = 0;
        }
    }
}

/*Permite incluir uma aresta com um determinado peso entre dois vértices
 no grafo, sendo essa operação válida para grafos não direcionados.*/
void adicionar_aresta(Grafo *grafo, int origem, int destino, int peso) {
    grafo->matriz_adj[origem][destino] = peso;
    grafo->matriz_adj[destino][origem] = peso;
}

/*Carrega a estrutura de um grafo a partir de um arquivo externo, permitindo 
a representação de grafos com diferentes configurações e tamanhos.*/
void carregar_grafo(Grafo *grafo, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int origem, destino, peso;
    int max_vertice = -1;
    while (fscanf(arquivo, "%d %d %d", &origem, &destino, &peso) == 3) {
        if (origem > max_vertice) max_vertice = origem;
        if (destino > max_vertice) max_vertice = destino;
    }

    // Agora que sabemos o número de vértices, podemos inicializar o grafo
    inicializar_grafo(grafo, max_vertice + 1);

    // Voltar ao início do arquivo para ler os dados novamente
    rewind(arquivo);

    while (fscanf(arquivo, "%d %d %d", &origem, &destino, &peso) == 3) {
        adicionar_aresta(grafo, origem, destino, peso);
    }

    fclose(arquivo);
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

/*Essa função analisa a centralidade em grafos, 
permitindo avaliar quais vértices são mais centrais e influentes na rede.*/
void calcular_closeness(const Grafo *grafo) {
    FILE *fp;
    fp = fopen("centralidade.txt", "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    for (int v = 0; v < grafo->num_vertices; v++) {
        int distancias[MAX_VERTICES];
        dijkstra(grafo, v, distancias);
        int soma_distancias = 0;
        for (int i = 0; i < grafo->num_vertices; i++) {
            soma_distancias += distancias[i];
        }
        float closeness = (float)soma_distancias / (grafo->num_vertices - 1);
        fprintf(fp, "%f\n", closeness);
    }

    fclose(fp);
}


// Função para desenhar o grafo a partir de sua matriz de adjacência
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
    char nome_arquivo[256];
    char caminho_completo[512];

    printf("Escolha um dos grafos dentro da pasta 'exemplosGrafos': ");
    printf("\nExemplo: grafo27Vertices.txt\n");
    printf("Variacoes de Vertices possiveis: 27,33,38,41,47,50,54,60,64,73.\n");
    printf("Digite o Grafo: ");
    scanf("%s", nome_arquivo);

    // Adiciona o nome da pasta antes do nome do arquivo
    sprintf(caminho_completo, "grafosExemplos/%s", nome_arquivo);

    inicializar_grafo(&grafo, MAX_VERTICES); // Inicializa o grafo com o número máximo de vértices
    carregar_grafo(&grafo, caminho_completo); // Carrega o grafo a partir do arquivo

    // Agora você pode chamar as outras funções com o grafo carregado
    calcular_closeness(&grafo);
    desenhar_grafo(grafo.matriz_adj, grafo.num_vertices);

    return 0;
}
