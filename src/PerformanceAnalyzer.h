#ifndef PERFORMANCE_ANALYZER_H
#define PERFORMANCE_ANALYZER_H

#include "TSPSolver.h"
#include <vector>
#include <string>
#include <functional>

struct PerformanceResult {
    int graphSize;
    double avgTime;
    double avgDistance;
    double timeStdDev;
    double distanceStdDev;
    std::string algorithm;
    
    PerformanceResult(int size, double time, double dist, double timeStd, double distStd, const std::string& alg)
        : graphSize(size), avgTime(time), avgDistance(dist), timeStdDev(timeStd), distanceStdDev(distStd), algorithm(alg) {}
};

class PerformanceAnalyzer {
private:
    static const int DEFAULT_INSTANCES = 10;
    
public:
    // Testa desempenho de um algoritmo específico
    static PerformanceResult analisarAlgoritmo(
        int tamanhoGrafo, 
        const std::string& nomeAlgoritmo,
        std::function<TSPResult(const Graph&)> algoritmo,
        int numeroInstancias = DEFAULT_INSTANCES
    );
    
    // Testa todos os algoritmos implementados
    static std::vector<PerformanceResult> analisarTodosAlgoritmos(
        const std::vector<int>& tamanhosGrafos,
        int numeroInstancias = DEFAULT_INSTANCES
    );
    
    // Salva resultados em arquivo
    static void salvarResultadosEmArquivo(
        const std::vector<PerformanceResult>& results, 
        const std::string& nomeArquivo = "performance_results.csv"
    );
    
    // Imprime resultados formatados
    static void imprimirResultados(const std::vector<PerformanceResult>& results);
    
    // Gera relatorio comparativo
    static void gerarRelatorioComparativo(const std::vector<PerformanceResult>& results);
    
private:
    static double calcularDesvioPadrao(const std::vector<double>& valores, double media);
    static void imprimirCabecalho();
    static void imprimirSeparador();
};

#endif
