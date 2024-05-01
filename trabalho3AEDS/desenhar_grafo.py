import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

def desenhar_grafo(matriz_adj):
    G = nx.Graph()  # Cria um objeto de grafo

    # Adiciona os vértices e arestas ao grafo
    for i in range(len(matriz_adj)):
        for j in range(len(matriz_adj[i])):
            if matriz_adj[i][j] != 0:
                G.add_edge(i, j, weight=matriz_adj[i][j])

    # Lê os valores de centralidade do arquivo
    with open('centralidade.txt', 'r') as f:
        centralidade = [float(line.strip()) for line in f]

    # Mapeia os valores de centralidade para uma escala de cores
    min_centrality = min(centralidade)
    max_centrality = max(centralidade)
    cores = [(c - min_centrality) / (max_centrality - min_centrality) for c in centralidade]

    # Cria um mapa de cores de vermelho para azul
    cmap = mcolors.LinearSegmentedColormap.from_list("mycmap", ['red', 'blue'])

    # Desenha o grafo
    pos = nx.spring_layout(G, k=3)  # Define a posição dos nós com um valor maior de k
    nx.draw(G, pos, node_color=cores, cmap=cmap, with_labels=True)  # Desenha os nós com a cor correspondente
    labels = nx.get_edge_attributes(G, 'weight')  # Obtém os pesos das arestas
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)  # Desenha os pesos das arestas

    plt.show()  # Exibe o gráfico