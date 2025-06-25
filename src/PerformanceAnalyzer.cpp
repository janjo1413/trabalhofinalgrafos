#include "PerformanceAnalyzer.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>

PerformanceResult PerformanceAnalyzer::analisarAlgoritmo(
    int tamanhoGrafo, 
    const std::string& nomeAlgoritmo,
    std::function<TSPResult(const Graph&)> algoritmo,
    int numeroInstancias) {
    
    std::vector<double> times;
    std::vector<double> distances;
    
    for (int i = 0; i < numeroInstancias; i++) {
        Graph graph(tamanhoGrafo);
        graph.gerarGrafoCompletoAleatorio();
        
        TSPResult result = algoritmo(graph);
        times.push_back(result.executionTime);
        distances.push_back(result.totalDistance);
    }
    
    // Calcula médias
    double avgTime = 0, avgDistance = 0;
    for (int i = 0; i < numeroInstancias; i++) {
        avgTime += times[i];
        avgDistance += distances[i];
    }
    avgTime /= numeroInstancias;
    avgDistance /= numeroInstancias;
    
    // Calcula desvios padrao
    double timeStdDev = calcularDesvioPadrao(times, avgTime);
    double distanceStdDev = calcularDesvioPadrao(distances, avgDistance);
    
    return PerformanceResult(tamanhoGrafo, avgTime, avgDistance, timeStdDev, distanceStdDev, nomeAlgoritmo);
}

std::vector<PerformanceResult> PerformanceAnalyzer::analisarTodosAlgoritmos(
    const std::vector<int>& tamanhosGrafos,
    int numeroInstancias) {
    
    std::vector<PerformanceResult> results;
    
    // Define os algoritmos a serem testados
    std::map<std::string, std::function<TSPResult(const Graph&)>> algorithms = {
        {"Vizinho Mais Proximo", [](const Graph& g) {
            TSPSolver solver(g);
            return solver.resolverComVizinhoMaisProximo();
        }},
        {"VMP + 2-opt", [](const Graph& g) {
            TSPSolver solver(g);
            return solver.resolverComVizinhoMaisProximoEDoisOpt();
        }},
        {"Insercao Mais Barata", [](const Graph& g) {
            TSPSolver solver(g);
            return solver.resolverComInsercaoMaisBarata();
        }},
        {"IMB + 2-opt", [](const Graph& g) {
            TSPSolver solver(g);
            return solver.resolverComInsercaoMaisBarataEDoisOpt();
        }}
    };
    
    std::cout << "Executando analise de desempenho..." << std::endl;
    std::cout << "Tamanhos de grafo: ";
    for (int size : tamanhosGrafos) std::cout << size << " ";
    std::cout << std::endl;
    std::cout << "Instancias por tamanho: " << numeroInstancias << std::endl << std::endl;
    
    int totalTests = tamanhosGrafos.size() * algorithms.size();
    int currentTest = 0;
    
    for (int size : tamanhosGrafos) {
        for (const auto& [name, algorithm] : algorithms) {
            currentTest++;
            std::cout << "Progresso: " << currentTest << "/" << totalTests 
                     << " - Testando " << name << " (n=" << size << ")..." << std::endl;
            
            PerformanceResult result = analisarAlgoritmo(size, name, algorithm, numeroInstancias);
            results.push_back(result);
        }
    }
    
    return results;
}

void PerformanceAnalyzer::salvarResultadosEmArquivo(
    const std::vector<PerformanceResult>& results, 
    const std::string& nomeArquivo) {
    
    std::ofstream file(nomeArquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo: " << nomeArquivo << std::endl;
        return;
    }
    
    // Cabecalho CSV
    file << "Algoritmo,Tamanho,Tempo_Medio(ms),Distancia_Media,Desvio_Tempo,Desvio_Distancia\n";
    
    for (const auto& result : results) {
        file << result.algorithm << ","
             << result.graphSize << ","
             << std::fixed << std::setprecision(3) << result.avgTime << ","
             << std::setprecision(2) << result.avgDistance << ","
             << std::setprecision(3) << result.timeStdDev << ","
             << std::setprecision(2) << result.distanceStdDev << "\n";
    }
    
    file.close();
    std::cout << "Resultados salvos em: " << nomeArquivo << std::endl;
}

void PerformanceAnalyzer::imprimirResultados(const std::vector<PerformanceResult>& results) {
    imprimirCabecalho();
    
    for (const auto& result : results) {
        std::cout << std::setw(20) << result.algorithm
                  << std::setw(8) << result.graphSize
                  << std::setw(12) << std::fixed << std::setprecision(2) << result.avgTime
                  << std::setw(15) << std::setprecision(1) << result.avgDistance
                  << std::setw(12) << std::setprecision(2) << result.timeStdDev
                  << std::setw(15) << std::setprecision(1) << result.distanceStdDev
                  << std::endl;
    }
    
    imprimirSeparador();
}

void PerformanceAnalyzer::gerarRelatorioComparativo(const std::vector<PerformanceResult>& results) {
    std::cout << "\n=== RELATORIO COMPARATIVO ===" << std::endl;
    
    // Agrupa resultados por tamanho
    std::map<int, std::vector<PerformanceResult>> resultsBySize;
    for (const auto& result : results) {
        resultsBySize[result.graphSize].push_back(result);
    }
    
    for (const auto& [size, sizeResults] : resultsBySize) {
        std::cout << "\nTamanho do grafo: " << size << " vertices" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        
        // Encontra melhor tempo e melhor distancia
        auto bestTime = *std::min_element(sizeResults.begin(), sizeResults.end(),
            [](const PerformanceResult& a, const PerformanceResult& b) {
                return a.avgTime < b.avgTime;
            });
            
        auto bestDistance = *std::min_element(sizeResults.begin(), sizeResults.end(),
            [](const PerformanceResult& a, const PerformanceResult& b) {
                return a.avgDistance < b.avgDistance;
            });
        
        for (const auto& result : sizeResults) {
            std::cout << std::setw(20) << result.algorithm << ": ";
            
            if (result.algorithm == bestTime.algorithm) {
                std::cout << "(MELHOR TEMPO) ";
            }
            if (result.algorithm == bestDistance.algorithm) {
                std::cout << "(MELHOR DISTANCIA) ";
            }
            
            std::cout << "Tempo: " << std::fixed << std::setprecision(2) << result.avgTime << "ms, "
                     << "Distancia: " << std::setprecision(1) << result.avgDistance << std::endl;
        }
    }
}

double PerformanceAnalyzer::calcularDesvioPadrao(const std::vector<double>& valores, double media) {
    if (valores.empty()) return 0.0;
    
    double variance = 0.0;
    for (double value : valores) {
        variance += (value - media) * (value - media);
    }
    variance /= valores.size();
    return std::sqrt(variance);
}

void PerformanceAnalyzer::imprimirCabecalho() {
    std::cout << "\n=== RESULTADOS DA ANALISE DE DESEMPENHO ===" << std::endl;
    imprimirSeparador();
    std::cout << std::setw(20) << "Algoritmo"
              << std::setw(8) << "Tamanho"
              << std::setw(12) << "Tempo(ms)"
              << std::setw(15) << "Distancia"
              << std::setw(12) << "Desv.Tempo"
              << std::setw(15) << "Desv.Dist"
              << std::endl;
    imprimirSeparador();
}

void PerformanceAnalyzer::imprimirSeparador() {
    std::cout << std::string(82, '-') << std::endl;
}
