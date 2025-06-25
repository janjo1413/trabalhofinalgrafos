#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "Graph.h"
#include <vector>
#include <utility>
#include <functional>

struct TSPResult {
    std::vector<int> tour;
    double totalDistance;
    double executionTime; // em milissegundos
    
    TSPResult(const std::vector<int>& t, double dist, double time) 
        : tour(t), totalDistance(dist), executionTime(time) {}
};

class TSPSolver {
private:
    const Graph& graph;
    
public:
    explicit TSPSolver(const Graph& g);
    
    // Heurísticas construtivas
    std::vector<int> heuristicaVizinhoMaisProximo(int verticeInicial = 0) const;
    std::vector<int> heuristicaInsercaoMaisBarata() const;
    
    // Heurísticas de busca local
    std::vector<int> melhoramentoDoisOpt(std::vector<int> tour) const;
    
    // Métodos principais
    TSPResult resolverComVizinhoMaisProximo() const;
    TSPResult resolverComVizinhoMaisProximoEDoisOpt() const;
    TSPResult resolverComInsercaoMaisBarata() const;
    TSPResult resolverComInsercaoMaisBarataEDoisOpt() const;
    
    // Utilitarios
    double calcularDistanciaDoTour(const std::vector<int>& tour) const;
    
private:
    double medirTempoExecucao(std::function<void()> func) const;
};

#endif
