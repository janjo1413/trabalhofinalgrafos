# 🚀 Problema do Caixeiro Viajante Simétrico
**Trabalho Final - TEORIA E APLICAÇÕES EM GRAFOS (2025.1)**

> Implementação completa de heurísticas para TSP em C++17 com análise experimental

## 📋 Sobre o Projeto

Implementação de heurísticas para o **Traveling Salesman Problem (TSP) Simétrico** em C++17, com análise de performance e funções em português para facilitar compreensão acadêmica.

### 🎯 Objetivos

- ✅ Implementar heurísticas construtivas (Vizinho Mais Próximo, Inserção Mais Barata)
- ✅ Aplicar busca local (2-opt) para otimização
- ✅ Executar 10 instâncias por dimensão (50, 100, 200, 300, 500, 750, 1000, 2000 vértices)
- ✅ Exportar resultados em formato CSV
- ✅ Interface didática em português

## 🔧 Algoritmos Implementados

### Heurísticas Construtivas
- **Vizinho Mais Próximo**: Constrói tour escolhendo sempre a cidade mais próxima
- **Inserção Mais Barata**: Insere cada cidade na posição de menor custo

### Busca Local
- **2-opt**: Otimização que reconecta arestas para reduzir custo do tour

## 📁 Estrutura do Projeto

```
projeto/
├── main.cpp                       # Menu interativo
├── src/
│   ├── Graph.h/cpp               # Representação do grafo
│   ├── TSPSolver.h/cpp           # Implementação das heurísticas
│   └── PerformanceAnalyzer.h/cpp # Análise estatística e CSV
├── resultados_tsp.csv            # Arquivo de saída
├── apresentacao.html             # Documentação visual
├── apresentar.bat               # Script de apresentação
└── README.md                    # Este arquivo
```

## 🚀 Quick Start

```bash
# Clone o repositório
git clone https://github.com/janjo1413/trabalhofinalgrafos.git
cd trabalhofinalgrafos

# Compile e execute
g++ -std=c++17 -O2 src/Graph.cpp src/TSPSolver.cpp src/PerformanceAnalyzer.cpp main.cpp -o tsp_solver.exe
./tsp_solver.exe
```

### 🖥️ Método Alternativo
```bash
# Usando Makefile
make all
./tsp_solver.exe

# Para apresentação
./apresentar.bat  # Windows
```

## 📊 Demo dos Resultados

![TSP Demo](https://img.shields.io/badge/TSP-Demo-blue) ![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C) ![License](https://img.shields.io/badge/License-MIT-green)

### Menu Interativo
```
=== MENU PRINCIPAL ===
  1. Demonstracao com Grafo Pequeno
  2. Teste Rapido  
  3. Analise Completa
  0. Sair
```

### 📈 Exemplo de Resultados

| Algoritmo | Tamanho | Tempo(ms) | Distância | Qualidade |
|-----------|---------|-----------|-----------|-----------|
| VMP + 2-opt | 100 | 0.23 | 408.1 | ⭐⭐⭐⭐⭐ |
| IMB + 2-opt | 100 | 1.53 | 472.4 | ⭐⭐⭐⭐ |
| Vizinho Mais Próximo | 100 | 0.02 | 557.1 | ⭐⭐⭐ |
| Inserção Mais Barata | 100 | 1.02 | 694.4 | ⭐⭐ |

## 📈 Resultados

O programa gera `resultados_tsp.csv` com:
- Dimensão do grafo (50 a 2000 vértices)
- Algoritmo utilizado (4 variações)
- Tempo médio de execução (ms)
- Custo médio, desvio padrão
- Dados de 10 instâncias por dimensão

## 🏆 Características do Projeto

- **Linguagem**: C++17 com funções em português
- **Compilador**: g++ com otimizações -O2
- **Precisão**: Medição em microsegundos
- **Grafos**: Completos não-orientados simétricos com pesos aleatórios
- **Escalabilidade**: Testado até 2000 vértices

## 📖 Documentação

- **[Documentação Visual](apresentacao.html)**: Abra no navegador para ver a documentação completa
- **[Resultados CSV](resultados_tsp.csv)**: Dados experimentais gerados
- **[Código Fonte](src/)**: Implementação das heurísticas

## 🤝 Como Contribuir

1. Fork o projeto
2. Crie sua feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit suas mudanças (`git commit -m 'Add some AmazingFeature'`)
4. Push para a branch (`git push origin feature/AmazingFeature`)
5. Abra um Pull Request

## ⚙️ Requisitos

- Compilador C++17 (g++, clang++, MSVC)
- Sistema: Windows, Linux, macOS

---
**👥 Integrantes**: João Gabriel, Maria Eduarda, Enrico Teixeira, Otavio França  
**🎓 Projeto desenvolvido para demonstrar implementação eficiente de algoritmos clássicos e análise experimental.**

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.
