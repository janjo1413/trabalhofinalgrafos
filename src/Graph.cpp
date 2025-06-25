#include "Graph.h"
#include <stdexcept>

Graph::Graph(int vertices) : numVertices(vertices) {
    if (vertices <= 0) {
        throw std::invalid_argument("Número de vértices deve ser positivo");
    }
    adjacencyMatrix.resize(vertices, std::vector<double>(vertices, 0.0));
}

void Graph::gerarGrafoCompletoAleatorio(double pesoMinimo, double pesoMaximo) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(pesoMinimo, pesoMaximo);
    
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i == j) {
                adjacencyMatrix[i][j] = 0.0;
            } else if (i < j) {
                double weight = dis(gen);
                adjacencyMatrix[i][j] = weight;
                adjacencyMatrix[j][i] = weight; // Grafo simétrico
            }
        }
    }
}

double Graph::obterDistancia(int de, int para) const {
    if (de < 0 || de >= numVertices || para < 0 || para >= numVertices) {
        throw std::out_of_range("Indices de vertices invalidos");
    }
    return adjacencyMatrix[de][para];
}
