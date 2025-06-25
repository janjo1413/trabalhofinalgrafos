#include "TSPSolver.h"
#include <chrono>
#include <algorithm>
#include <cfloat>
#include <functional>
#include <set>
#include <stdexcept>

using namespace std::chrono;
using std::invalid_argument;

TSPSolver::TSPSolver(const Graph& g) : graph(g) {
    if (g.obterNumeroVertices() < 3) {
        throw std::invalid_argument("TSP requer pelo menos 3 vertices");
    }
}

std::vector<int> TSPSolver::heuristicaVizinhoMaisProximo(int verticeInicial) const {
    int n = graph.obterNumeroVertices();
    std::vector<int> tour;
    std::vector<bool> visited(n, false);
    
    int current = verticeInicial;
    tour.push_back(current);
    visited[current] = true;
    
    for (int i = 1; i < n; i++) {
        double minDistance = DBL_MAX;
        int nextVertex = -1;
        
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph.obterDistancia(current, j) < minDistance) {
                minDistance = graph.obterDistancia(current, j);
                nextVertex = j;
            }
        }
        
        tour.push_back(nextVertex);
        visited[nextVertex] = true;
        current = nextVertex;
    }
    
    return tour;
}

std::vector<int> TSPSolver::heuristicaInsercaoMaisBarata() const {
    int n = graph.obterNumeroVertices();
    
    // Encontra a aresta mais barata
    double minDist = DBL_MAX;
    int u = 0, v = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph.obterDistancia(i, j) < minDist) {
                minDist = graph.obterDistancia(i, j);
                u = i;
                v = j;
            }
        }
    }
    
    std::vector<int> tour = {u, v};
    std::set<int> inTour = {u, v};
    
    // Insere os vértices restantes
    while (tour.size() < static_cast<size_t>(n)) {
        double minInsertionCost = DBL_MAX;
        int bestVertex = -1;
        int bestPosition = -1;
        
        // Para cada vertice nao no tour
        for (int k = 0; k < n; k++) {
            if (inTour.find(k) != inTour.end()) continue;
            
            // Para cada posicao possivel no tour
            for (size_t pos = 0; pos < tour.size(); pos++) {
                int i = tour[pos];
                int j = tour[(pos + 1) % tour.size()];
                
                double insertionCost = graph.obterDistancia(i, k) + 
                                     graph.obterDistancia(k, j) - 
                                     graph.obterDistancia(i, j);
                
                if (insertionCost < minInsertionCost) {
                    minInsertionCost = insertionCost;
                    bestVertex = k;
                    bestPosition = pos + 1;
                }
            }
        }
        
        tour.insert(tour.begin() + bestPosition, bestVertex);
        inTour.insert(bestVertex);
    }
    
    return tour;
}

std::vector<int> TSPSolver::melhoramentoDoisOpt(std::vector<int> tour) const {
    bool improved = true;
    int iterations = 0;
    const int maxIterations = 100; // Reduzido para melhor performance
    
    while (improved && iterations < maxIterations) {
        improved = false;
        iterations++;
        
        for (size_t i = 1; i < tour.size() - 2; i++) {
            for (size_t j = i + 1; j < tour.size(); j++) {
                if (j - i == 1) continue; // Arestas adjacentes
                
                // Calcula o custo atual
                double currentCost = graph.obterDistancia(tour[i-1], tour[i]) + 
                                   graph.obterDistancia(tour[j], tour[(j+1) % tour.size()]);
                
                // Calcula o custo apos 2-opt
                double newCost = graph.obterDistancia(tour[i-1], tour[j]) + 
                               graph.obterDistancia(tour[i], tour[(j+1) % tour.size()]);
                
                if (newCost < currentCost - 1e-9) { // Adiciona tolerância
                    std::reverse(tour.begin() + i, tour.begin() + j + 1);
                    improved = true;
                    break; // Sai do loop interno quando encontra melhoria
                }
            }
            if (improved) break; // Sai do loop externo também
        }
    }
    
    return tour;
}

TSPResult TSPSolver::resolverComVizinhoMaisProximo() const {
    std::vector<int> tour;
    double time = medirTempoExecucao([&]() {
        tour = heuristicaVizinhoMaisProximo();
    });
    
    double distance = calcularDistanciaDoTour(tour);
    return TSPResult(tour, distance, time);
}

TSPResult TSPSolver::resolverComVizinhoMaisProximoEDoisOpt() const {
    std::vector<int> tour;
    double time = medirTempoExecucao([&]() {
        tour = heuristicaVizinhoMaisProximo();
        tour = melhoramentoDoisOpt(tour);
    });
    
    double distance = calcularDistanciaDoTour(tour);
    return TSPResult(tour, distance, time);
}

TSPResult TSPSolver::resolverComInsercaoMaisBarata() const {
    std::vector<int> tour;
    double time = medirTempoExecucao([&]() {
        tour = heuristicaInsercaoMaisBarata();
    });
    
    double distance = calcularDistanciaDoTour(tour);
    return TSPResult(tour, distance, time);
}

TSPResult TSPSolver::resolverComInsercaoMaisBarataEDoisOpt() const {
    std::vector<int> tour;
    double time = medirTempoExecucao([&]() {
        tour = heuristicaInsercaoMaisBarata();
        tour = melhoramentoDoisOpt(tour);
    });
    
    double distance = calcularDistanciaDoTour(tour);
    return TSPResult(tour, distance, time);
}

double TSPSolver::calcularDistanciaDoTour(const std::vector<int>& tour) const {
    if (tour.empty()) return 0.0;
    
    double totalDistance = 0.0;
    for (size_t i = 0; i < tour.size(); i++) {
        int from = tour[i];
        int to = tour[(i + 1) % tour.size()];
        totalDistance += graph.obterDistancia(from, to);
    }
    return totalDistance;
}

double TSPSolver::medirTempoExecucao(std::function<void()> func) const {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    return duration.count() / 1000.0; // Retorna em milissegundos
}
