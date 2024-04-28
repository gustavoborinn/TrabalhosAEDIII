import networkx as nx
import matplotlib.pyplot as plt

def desenhar_grafo(matriz_adj):
    G = nx.Graph()  # Cria um objeto de grafo

    # Adiciona os vértices e arestas ao grafo
    for i in range(len(matriz_adj)):
        for j in range(len(matriz_adj[i])):
            if matriz_adj[i][j] != 0:
                G.add_edge(i, j, weight=matriz_adj[i][j])

    # Desenha o grafo
    pos = nx.spring_layout(G)  # Define a posição dos nós
    nx.draw(G, pos, with_labels=True)  # Desenha os nós
    labels = nx.get_edge_attributes(G, 'weight')  # Obtém os pesos das arestas
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)  # Desenha os pesos das arestas

    plt.show()  # Exibe o gráfico