#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Definições de parâmetros
#define MAX_VARS 25
#define MAX_CLAUSES 100
#define POP_SIZE 50
#define GENERATIONS 50
#define MUTATION_RATE 0.01

// Estrutura para representar uma cláusula
typedef struct {
    int literais[MAX_VARS];
    int tamanho;
} Clausula;

// Estrutura para representar um indivíduo (solução)
typedef struct {
    bool genes[MAX_VARS];
    int fitness;
} Individuo;

// Função para avaliar uma solução
int avaliar_solucao(bool solucao[], Clausula clausulas[], int num_clausulas) {
    int clausulas_satisfeitas = 0;
    for (int i = 0; i < num_clausulas; i++) {
        bool clausula_satisfeita = false;
        for (int j = 0; j < clausulas[i].tamanho; j++) {
            int var = abs(clausulas[i].literais[j]) - 1;
            bool eh_verdadeiro = clausulas[i].literais[j] > 0;
            if (solucao[var] == eh_verdadeiro) {
                clausula_satisfeita = true;
                break;
            }
        }
        if (clausula_satisfeita) {
            clausulas_satisfeitas++;
        }
    }
    return clausulas_satisfeitas;
}

// Algoritmo Hill Climbing
void busca_local(Clausula clausulas[], int num_vars, int num_clausulas, bool melhor_solucao[], int *melhor_score) {
    bool solucao[MAX_VARS];
    for (int i = 0; i < num_vars; i++) {
        solucao[i] = rand() % 2;
    }
    
    *melhor_score = avaliar_solucao(solucao, clausulas, num_clausulas);
    for (int i = 0; i < num_vars; i++) {
        melhor_solucao[i] = solucao[i];
    }

    bool melhorando = true;
    while (melhorando) {
        melhorando = false;
        for (int i = 0; i < num_vars; i++) {
            solucao[i] = !solucao[i];
            int score = avaliar_solucao(solucao, clausulas, num_clausulas);
            if (score > *melhor_score) {
                *melhor_score = score;
                for (int j = 0; j < num_vars; j++) {
                    melhor_solucao[j] = solucao[j];
                }
                melhorando = true;
            } else {
                solucao[i] = !solucao[i];
            }
        }
    }
}

// Função para inicializar a população no algoritmo genético
void inicializar_populacao(Individuo populacao[], int num_vars) {
    for (int i = 0; i < POP_SIZE; i++) {
        for (int j = 0; j < num_vars; j++) {
            populacao[i].genes[j] = rand() % 2;
        }
    }
}

// Função para avaliar a população no algoritmo genético
void avaliar_populacao(Individuo populacao[], Clausula clausulas[], int num_clausulas) {
    for (int i = 0; i < POP_SIZE; i++) {
        populacao[i].fitness = avaliar_solucao(populacao[i].genes, clausulas, num_clausulas);
    }
}

// Função para selecionar os pais no algoritmo genético
void selecionar_pais(Individuo populacao[], Individuo *pai1, Individuo *pai2) {
    *pai1 = populacao[rand() % POP_SIZE];
    *pai2 = populacao[rand() % POP_SIZE];
}

// Função de crossover no algoritmo genético
void crossover(Individuo pai1, Individuo pai2, Individuo *filho1, Individuo *filho2, int num_vars) {
    int ponto_corte = rand() % num_vars;
    for (int i = 0; i < ponto_corte; i++) {
        filho1->genes[i] = pai1.genes[i];
        filho2->genes[i] = pai2.genes[i];
    }
    for (int i = ponto_corte; i < num_vars; i++) {
        filho1->genes[i] = pai2.genes[i];
        filho2->genes[i] = pai1.genes[i];
    }
}

// Função de mutação no algoritmo genético
void mutar(Individuo *individuo, int num_vars) {
    for (int i = 0; i < num_vars; i++) {
        if ((rand() % 100) < (MUTATION_RATE * 100)) {
            individuo->genes[i] = !individuo->genes[i];
        }
    }
}

// Algoritmo Genético
void algoritmo_genetico(Clausula clausulas[], int num_vars, int num_clausulas, bool melhor_solucao[], int *melhor_score) {
    Individuo populacao[POP_SIZE];
    Individuo nova_populacao[POP_SIZE];

    inicializar_populacao(populacao, num_vars);
    avaliar_populacao(populacao, clausulas, num_clausulas);

    *melhor_score = 0;

    for (int geracao = 0; geracao < GENERATIONS; geracao++) {
        for (int i = 0; i < POP_SIZE; i += 2) {
            Individuo pai1, pai2, filho1, filho2;
            selecionar_pais(populacao, &pai1, &pai2);
            crossover(pai1, pai2, &filho1, &filho2, num_vars);
            mutar(&filho1, num_vars);
            mutar(&filho2, num_vars);
            nova_populacao[i] = filho1;
            nova_populacao[i + 1] = filho2;
        }

        for (int i = 0; i < POP_SIZE; i++) {
            populacao[i] = nova_populacao[i];
        }

        avaliar_populacao(populacao, clausulas, num_clausulas);

        for (int i = 0; i < POP_SIZE; i++) {
            if (populacao[i].fitness > *melhor_score) {
                *melhor_score = populacao[i].fitness;
                for (int j = 0; j < num_vars; j++) {
                    melhor_solucao[j] = populacao[i].genes[j];
                }
            }
        }
    }
}

// Função para imprimir uma solução
void imprimir_solucao(bool solucao[], int num_vars) {
    for (int i = 0; i < num_vars; i++) {
        printf("%d ", solucao[i]);
    }
    printf("\n");
}

// Função para executar uma instância de teste
void executar_instancia(Clausula clausulas[], int num_vars, int num_clausulas) {
    bool melhor_solucao_bl[MAX_VARS];
    int melhor_score_bl;
    clock_t inicio_bl = clock();
    busca_local(clausulas, num_vars, num_clausulas, melhor_solucao_bl, &melhor_score_bl);
    clock_t fim_bl = clock();
    double tempo_bl = (double)(fim_bl - inicio_bl) / CLOCKS_PER_SEC;

    bool melhor_solucao_ag[MAX_VARS];
    int melhor_score_ag;
    clock_t inicio_ag = clock();
    algoritmo_genetico(clausulas, num_vars, num_clausulas, melhor_solucao_ag, &melhor_score_ag);
    clock_t fim_ag = clock();
    double tempo_ag = (double)(fim_ag - inicio_ag) / CLOCKS_PER_SEC;

    printf("%-20s %-20s %-20s\n", "Algoritmo", "Melhor Pontuação", "Tempo (segundos)");
    printf("------------------------------------------------------------\n");
    printf("%-20s %-20d %-20.4f\n", "[Busca Local]", melhor_score_bl, tempo_bl);
    printf("%-20s", "Melhor Solução: ");
    imprimir_solucao(melhor_solucao_bl, num_vars);

    printf("\n%-20s %-20d %-20.4f\n", "[Algoritmo Genético]", melhor_score_ag, tempo_ag);
    printf("%-20s", "Melhor Solução: ");
    imprimir_solucao(melhor_solucao_ag, num_vars);
}

int main() {
    srand(time(NULL));

    // Definir 10 diferentes instâncias
    Clausula instancias[10][MAX_CLAUSES] = {
        // Instância 1: 5 variáveis, 3 cláusulas
        {
            {{1, -2, 3}, 3},
            {{-1, 4, -5}, 3},
            {{2, 3, -4}, 3}
        },
        // Instância 2: 5 variáveis, 5 cláusulas
        {
            {{1, -2, 3}, 3},
            {{-1, 4, -5}, 3},
            {{2, 3, -4}, 3},
            {{1, 2, 3}, 3},
            {{-1, -3, 5}, 3}
        },
        // Instância 3: 10 variáveis, 8 cláusulas
        {
            {{1, -2, 3}, 3},
            {{-1, 4, -5}, 3},
            {{2, 3, -4}, 3},
            {{1, 2, 3}, 3},
            {{-1, -3, 5}, 3},
            {{6, 7, -8}, 3},
            {{-6, 8, 9}, 3},
            {{-7, -9, 10}, 3}
        },
        // Instância 4: 10 variáveis, 10 cláusulas
        {
            {{1, -2, 3}, 3},
            {{-1, 4, -5}, 3},
            {{2, 3, -4}, 3},
            {{1, 2, 3}, 3},
            {{-1, -3, 5}, 3},
            {{6, 7, -8}, 3},
            {{-6, 8, 9}, 3},
            {{-7, -9, 10}, 3},
            {{1, 4, -7}, 3},
            {{-3, 6, -10}, 3}
        },
        // Instância 5: 15 variáveis, 12 cláusulas
        {
            {{1, -2, 3}, 3},
            {{-1, 4, -5}, 3},
            {{2, 3, -4}, 3},
            {{1, 2, 3}, 3},
            {{-1, -3, 5}, 3},
            {{6, 7, -8}, 3},
            {{-6, 8, 9}, 3},
            {{-7, -9, 10}, 3},
            {{1, 4, -7}, 3},
            {{-3, 6, -10}, 3},
            {{11, -12, 13}, 3},
            {{-11, 14, -15}, 3}
        },
        // Instância 6: 15 variáveis, 15 cláusulas
        {
            {{1, -2, 3}, 3},
            {{-1, 4, -5}, 3},
            {{2, 3, -4}, 3},
            {{1, 2, 3}, 3},
            {{-1, -3, 5}, 3},
            {{6, 7, -8}, 3},
            {{-6, 8, 9}, 3},
            {{-7, -9, 10}, 3},
            {{1, 4, -7}, 3},
            {{-3, 6, -10}, 3},
            {{11, -12, 13}, 3},
            {{-11, 14, -15}, 3},
            {{5, 8, -13}, 3},
            {{-2, 6, 12}, 3},
            {{3, -7, 9}, 3}
        },
        // Instância 7: 20 variáveis, 18 cláusulas
        {
            {{1, -2, 3}, 3},
            {{-1, 4, -5}, 3},
            {{2, 3, -4}, 3},
            {{1, 2, 3}, 3},
            {{-1, -3, 5}, 3},
            {{6, 7, -8}, 3},
            {{-6, 8, 9}, 3},
            {{-7, -9, 10}, 3},
            {{1, 4, -7}, 3},
            {{-3, 6, -10}, 3},
            {{11, -12, 13}, 3},
            {{-11, 14, -15}, 3},
            {{5, 8, -13}, 3},
            {{-2, 6, 12}, 3},
            {{3, -7, 9}, 3},
            {{16, -17, 18}, 3},
            {{-16, 19, -20}, 3},
            {{4, 10, -12}, 3}
        },
        // Instância 8: 20 variáveis, 20 cláusulas
        {
            {{1, -2, 3}, 3},
            {{-1, 4, -5}, 3},
            {{2, 3, -4}, 3},
            {{1, 2, 3}, 3},
            {{-1, -3, 5}, 3},
            {{6, 7, -8}, 3},
            {{-6, 8, 9}, 3},
            {{-7, -9, 10}, 3},
            {{1, 4, -7}, 3},
            {{-3, 6, -10}, 3},
            {{11, -12, 13}, 3},
            {{-11, 14, -15}, 3},
            {{5, 8, -13}, 3},
            {{-2, 6, 12}, 3},
            {{3, -7, 9}, 3},
            {{16, -17, 18}, 3},
            {{-16, 19, -20}, 3},
            {{4, 10, -12}, 3},
            {{8, -15, 17}, 3},
            {{7, -9, 20}, 3}
        },
        // Instância 9: 25 variáveis, 22 cláusulas
        {
            {{1, -2, 3}, 3},
            {{-1, 4, -5}, 3},
            {{2, 3, -4}, 3},
            {{1, 2, 3}, 3},
            {{-1, -3, 5}, 3},
            {{6, 7, -8}, 3},
            {{-6, 8, 9}, 3},
            {{-7, -9, 10}, 3},
            {{1, 4, -7}, 3},
            {{-3, 6, -10}, 3},
            {{11, -12, 13}, 3},
            {{-11, 14, -15}, 3},
            {{5, 8, -13}, 3},
            {{-2, 6, 12}, 3},
            {{3, -7, 9}, 3},
            {{16, -17, 18}, 3},
            {{-16, 19, -20}, 3},
            {{4, 10, -12}, 3},
            {{8, -15, 17}, 3},
            {{7, -9, 20}, 3},
            {{21, -22, 23}, 3},
            {{-21, 24, -25}, 3}
        },
        // Instância 10: 25 variáveis, 25 cláusulas
        {
            {{1, -2, 3}, 3},
            {{-1, 4, -5}, 3},
            {{2, 3, -4}, 3},
            {{1, 2, 3}, 3},
            {{-1, -3, 5}, 3},
            {{6, 7, -8}, 3},
            {{-6, 8, 9}, 3},
            {{-7, -9, 10}, 3},
            {{1, 4, -7}, 3},
            {{-3, 6, -10}, 3},
            {{11, -12, 13}, 3},
            {{-11, 14, -15}, 3},
            {{5, 8, -13}, 3},
            {{-2, 6, 12}, 3},
            {{3, -7, 9}, 3},
            {{16, -17, 18}, 3},
            {{-16, 19, -20}, 3},
            {{4, 10, -12}, 3},
            {{8, -15, 17}, 3},
            {{7, -9, 20}, 3},
            {{21, -22, 23}, 3},
            {{-21, 24, -25}, 3},
            {{3, 14, -16}, 3},
            {{5, 18, 20}, 3},
            {{-4, 13, -19}, 3}
        }
    };

    int num_vars[10] = {5, 5, 10, 10, 15, 15, 20, 20, 25, 25};
    int num_clauses[10] = {3, 5, 8, 10, 12, 15, 18, 20, 22, 25};

    for (int i = 0; i < 10; i++) {
        printf("_____________________________________________________________________________\n");
        printf("Instância %d:\n", i + 1);
        executar_instancia(instancias[i], num_vars[i], num_clauses[i]);
        printf("\n");
    }

    return 0;
}