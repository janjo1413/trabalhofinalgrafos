#include "src/Graph.h"
#include "src/TSPSolver.h"
#include "src/PerformanceAnalyzer.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void showHeader() {
    clearScreen();
    std::cout << "==========================================================" << std::endl;
    std::cout << "         TRABALHO FINAL - TEORIA E APLICACOES EM GRAFOS" << std::endl;
    std::cout << "       Problema do Caixeiro Viajante Simetrico" << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Heuristicas Implementadas:" << std::endl;
    std::cout << "  - Vizinho Mais Proximo (Construtiva)" << std::endl;
    std::cout << "  - Insercao Mais Barata (Construtiva)" << std::endl;
    std::cout << "  - 2-opt (Busca Local)" << std::endl;
    std::cout << std::endl;
}

void demonstrateSmallExample() {
    showHeader();
    std::cout << "\n=== DEMONSTRACAO COM GRAFO PEQUENO ===" << std::endl;
    std::cout << "Gerando grafo completo com 6 vertices para visualizacao..." << std::endl;
    
    Graph graph(6);
    graph.gerarGrafoCompletoAleatorio(10.0, 50.0);
    
    std::cout << "\nMatriz de Distancias Gerada:" << std::endl;
    std::cout << "     ";
    for (int i = 0; i < 6; i++) {
        std::cout << std::setw(8) << i;
    }
    std::cout << std::endl;
    
    for (int i = 0; i < 6; i++) {
        std::cout << std::setw(3) << i << ": ";
        for (int j = 0; j < 6; j++) {
            if (i == j) {
                std::cout << std::setw(8) << "---";
            } else {
                std::cout << std::setw(8) << std::fixed << std::setprecision(1) 
                          << graph.obterDistancia(i, j);
            }
        }
        std::cout << std::endl;
    }
    
    TSPSolver solver(graph);
    
    std::cout << "\n=== APLICANDO HEURISTICAS ===" << std::endl;
    
    std::cout << "\n1. VIZINHO MAIS PROXIMO:" << std::endl;
    auto result1 = solver.resolverComVizinhoMaisProximo();
    std::cout << "   Tour: ";
    for (size_t i = 0; i < result1.tour.size(); i++) {
        std::cout << result1.tour[i];
        if (i < result1.tour.size() - 1) std::cout << " -> ";
    }
    std::cout << " -> " << result1.tour[0] << std::endl;
    std::cout << "   Distancia: " << std::fixed << std::setprecision(2) << result1.totalDistance << std::endl;
    std::cout << "   Tempo: " << std::setprecision(3) << result1.executionTime << " ms" << std::endl;
    
    std::cout << "\n2. VIZINHO MAIS PROXIMO + 2-OPT:" << std::endl;
    auto result2 = solver.resolverComVizinhoMaisProximoEDoisOpt();
    std::cout << "   Tour: ";
    for (size_t i = 0; i < result2.tour.size(); i++) {
        std::cout << result2.tour[i];
        if (i < result2.tour.size() - 1) std::cout << " -> ";
    }
    std::cout << " -> " << result2.tour[0] << std::endl;
    std::cout << "   Distancia: " << std::fixed << std::setprecision(2) << result2.totalDistance << std::endl;
    std::cout << "   Tempo: " << std::setprecision(3) << result2.executionTime << " ms" << std::endl;
    std::cout << "   Melhoria: " << std::setprecision(1) 
              << ((result1.totalDistance - result2.totalDistance) / result1.totalDistance * 100) 
              << "%" << std::endl;
    
    std::cout << "\n3. INSERCAO MAIS BARATA:" << std::endl;
    auto result3 = solver.resolverComInsercaoMaisBarata();
    std::cout << "   Tour: ";
    for (size_t i = 0; i < result3.tour.size(); i++) {
        std::cout << result3.tour[i];
        if (i < result3.tour.size() - 1) std::cout << " -> ";
    }
    std::cout << " -> " << result3.tour[0] << std::endl;
    std::cout << "   Distancia: " << std::fixed << std::setprecision(2) << result3.totalDistance << std::endl;
    std::cout << "   Tempo: " << std::setprecision(3) << result3.executionTime << " ms" << std::endl;
    
    std::cout << "\n4. INSERCAO MAIS BARATA + 2-OPT:" << std::endl;
    auto result4 = solver.resolverComInsercaoMaisBarataEDoisOpt();
    std::cout << "   Tour: ";
    for (size_t i = 0; i < result4.tour.size(); i++) {
        std::cout << result4.tour[i];
        if (i < result4.tour.size() - 1) std::cout << " -> ";
    }
    std::cout << " -> " << result4.tour[0] << std::endl;
    std::cout << "   Distancia: " << std::fixed << std::setprecision(2) << result4.totalDistance << std::endl;
    std::cout << "   Tempo: " << std::setprecision(3) << result4.executionTime << " ms" << std::endl;
    std::cout << "   Melhoria: " << std::setprecision(1) 
              << ((result3.totalDistance - result4.totalDistance) / result3.totalDistance * 100) 
              << "%" << std::endl;
    
    pauseScreen();
}

void runQuickAnalysis() {
    showHeader();
    std::cout << "\n=== TESTE RAPIDO ===" << std::endl;
    std::cout << "Executando teste com 5 instancias por tamanho..." << std::endl;
    
    std::vector<int> sizes = {20, 50, 100, 150};
    const int instances = 5;
    
    std::cout << "Tamanhos de grafos: ";
    for (int size : sizes) {
        std::cout << size << " ";
    }
    std::cout << std::endl << std::endl;
    
    auto results = PerformanceAnalyzer::analisarTodosAlgoritmos(sizes, instances);
    
    PerformanceAnalyzer::imprimirResultados(results);
    PerformanceAnalyzer::gerarRelatorioComparativo(results);
    
    pauseScreen();
}

void runFullAnalysis() {
    showHeader();
    std::cout << "\n=== ANALISE COMPLETA ===" << std::endl;
    std::cout << "Executando analise com 10 instancias por dimensao..." << std::endl;
    
    std::vector<int> sizes = {50, 100, 200, 300, 500, 750, 1000, 2000};
    const int instances = 10;
    
    std::cout << "Tamanhos de grafos: ";
    for (int size : sizes) {
        std::cout << size << " ";
    }
    std::cout << std::endl << std::endl;
    
    std::cout << "AVISO: Esta analise pode levar varios minutos para completar." << std::endl;
    std::cout << "Continuar? (s/n): ";
    
    char choice;
    std::cin >> choice;
    
    if (choice == 's' || choice == 'S') {
        auto results = PerformanceAnalyzer::analisarTodosAlgoritmos(sizes, instances);
        
        PerformanceAnalyzer::imprimirResultados(results);
        PerformanceAnalyzer::gerarRelatorioComparativo(results);
        PerformanceAnalyzer::salvarResultadosEmArquivo(results, "resultados_tsp.csv");
        
        std::cout << "\nAnalise concluida. Resultados salvos em 'resultados_tsp.csv'" << std::endl;
    } else {
        std::cout << "Analise cancelada." << std::endl;
    }
    
    pauseScreen();
}

int main() {
    int option;
    
    do {
        showHeader();
        std::cout << "\n=== MENU PRINCIPAL ===" << std::endl;
        std::cout << "  1. Demonstracao com Grafo Pequeno" << std::endl;
        std::cout << "  2. Teste Rapido" << std::endl;
        std::cout << "  3. Analise Completa" << std::endl;
        std::cout << "  0. Sair" << std::endl;
        std::cout << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> option;
        
        try {
            switch(option) {
                case 1:
                    demonstrateSmallExample();
                    break;
                case 2:
                    runQuickAnalysis();
                    break;
                case 3:
                    runFullAnalysis();
                    break;
                case 0:
                    clearScreen();
                    std::cout << "Programa finalizado." << std::endl;
                    break;
                default:
                    std::cout << "ERRO: Opcao invalida! Pressione ENTER para tentar novamente...";
                    std::cin.ignore();
                    std::cin.get();
            }
        } catch (const std::exception& e) {
            std::cout << "ERRO: Erro durante a execucao: " << e.what() << std::endl;
            pauseScreen();
        }
        
    } while(option != 0);
    
    return 0;
}
