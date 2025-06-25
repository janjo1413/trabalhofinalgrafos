#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <random>

class Graph {
private:
    std::vector<std::vector<double>> adjacencyMatrix;
    int numVertices;

public:
    Graph(int vertices);
    
    // Metodos de geracao de grafos
    void gerarGrafoCompletoAleatorio(double pesoMinimo = 1.0, double pesoMaximo = 100.0);
    
    // Getters
    int obterNumeroVertices() const { return numVertices; }
    double obterDistancia(int de, int para) const;
    const std::vector<std::vector<double>>& obterMatriz() const { return adjacencyMatrix; }
};

#endif
