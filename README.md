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
├── main.cpp                       # Ponto de entrada do programa
├── src/                          # Código fonte organizado
│   ├── Graph.h/cpp               # Classe do grafo
│   ├── TSPSolver.h/cpp           # Algoritmos TSP
│   └── PerformanceAnalyzer.h/cpp # Análise e métricas
├── .vscode/                      # Configurações VS Code
├── resultados_tsp.csv            # Dados experimentais
├── apresentacao.html             # Documentação visual
├── apresentar.bat               # Script Windows
├── Makefile                     # Build system
├── .gitignore                   # Arquivos ignorados
├── LICENSE                      # Licença MIT
└── README.md                    # Este arquivo
```

### 📄 Descrição Detalhada dos Arquivos

#### 🚀 **Arquivos Principais**
- **`main.cpp`**: Ponto de entrada do programa com menu interativo em português. Permite escolher entre demonstração, teste rápido ou análise completa. Centraliza toda a interface do usuário.

#### 🧩 **Código Fonte (`src/`)**
- **`Graph.h/cpp`**: Implementa a representação do grafo completo simétrico. Contém matriz de adjacência, geração de pesos aleatórios e funções auxiliares para manipulação do grafo.

- **`TSPSolver.h/cpp`**: Coração do projeto - implementa todas as heurísticas TSP:
  - Vizinho Mais Próximo (construção gulosa)
  - Inserção Mais Barata (construção por inserção)
  - 2-opt (busca local para otimização)
  - Combinações das heurísticas para melhor qualidade

- **`PerformanceAnalyzer.h/cpp`**: Responsável pela análise experimental:
  - Execução de múltiplas instâncias
  - Medição precisa de tempo (microsegundos)
  - Cálculo de estatísticas (média, desvio padrão)
  - Exportação para CSV

#### 🔧 **Configuração e Build**
- **`Makefile`**: Sistema de build multiplataforma. Facilita compilação com flags otimizadas (-O2) e limpeza de arquivos temporários.

- **`.vscode/tasks.json`**: Tarefas pré-configuradas para VS Code (compilação otimizada, debug, execução). Melhora produtividade no desenvolvimento.

- **`.gitignore`**: Define arquivos que não devem ser versionados (executáveis .exe, objetos .o, temporários). Mantém repositório limpo.

#### 📊 **Resultados e Documentação**
- **`resultados_tsp.csv`**: Arquivo de saída com dados experimentais. Contém tempos, custos e estatísticas de todas as execuções para análise posterior.

- **`apresentacao.html`**: Documentação visual completa do projeto. Explica algoritmos, mostra resultados e serve como material de apresentação.

- **`apresentar.bat`**: Script Windows para facilitar apresentação. Abre automaticamente o HTML e executa o programa.

#### 📜 **Licenciamento**
- **`LICENSE`**: Licença MIT para uso acadêmico e comercial. Permite distribuição e modificação do código.

- **`README.md`**: Este arquivo - documentação principal do projeto com instruções de uso, exemplos e informações acadêmicas.

## 🚀 Quick Start

```bash
# Clone o repositório
git clone https://github.com/janjo1413/trabalhofinalgrafos.git
cd trabalhofinalgrafos

# Compile e execute
g++ -std=c++17 -O2 src/Graph.cpp src/TSPSolver.cpp src/PerformanceAnalyzer.cpp main.cpp -o tsp_solver.exe
./tsp_solver.exe
```

## � Quick Start

### Windows

```powershell
# Clone o repositório
git clone https://github.com/janjo1413/trabalhofinalgrafos.git
cd trabalhofinalgrafos

# Método 1: Usando o script de apresentação
apresentar.bat

# Método 2: Compilar e executar manualmente
g++ -std=c++17 -O2 src/Graph.cpp src/TSPSolver.cpp src/PerformanceAnalyzer.cpp main.cpp -o tsp_solver.exe
.\tsp_solver.exe

# Método 3: Usando Makefile
make all
.\tsp_solver.exe
```

### Linux/macOS

```bash
# Clone o repositório
git clone https://github.com/janjo1413/trabalhofinalgrafos.git
cd trabalhofinalgrafos

# Método 1: Usando o script de apresentação
chmod +x apresentar.sh
./apresentar.sh

# Método 2: Compilar e executar manualmente
g++ -std=c++17 -O2 src/Graph.cpp src/TSPSolver.cpp src/PerformanceAnalyzer.cpp main.cpp -o tsp_solver
./tsp_solver

# Método 3: Usando Makefile
make all
./tsp_solver
```

### Requisitos
- Compilador compatível com C++17 (GCC 7+, Clang 5+, MSVC 2017+)
- 2GB de RAM (para instâncias grandes)
- Make (opcional, para usar o Makefile)

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
