#!/bin/bash

echo "============================================"
echo "  TRABALHO FINAL - TEORIA DOS GRAFOS"
echo "  Problema do Caixeiro Viajante Simetrico"
echo "============================================"
echo
echo "Escolha uma opcao:"
echo
echo "1. Executar programa TSP"
echo "2. Ver resultados (CSV)"
echo "3. Abrir documentacao"
echo "0. Sair"
echo

read -p "Sua escolha: " opcao

if [ "$opcao" = "1" ]; then
    if [ -f "tsp_solver" ]; then
        echo "Executando programa..."
        ./tsp_solver
    else
        echo "Compilando..."
        g++ -std=c++17 -O2 src/Graph.cpp src/TSPSolver.cpp src/PerformanceAnalyzer.cpp main.cpp -o tsp_solver
        if [ -f "tsp_solver" ]; then
            ./tsp_solver
        else
            echo "ERRO: Falha na compilacao!"
            read -p "Pressione ENTER para continuar..."
        fi
    fi
elif [ "$opcao" = "2" ]; then
    if [ -f "resultados_tsp.csv" ]; then
        if command -v xdg-open > /dev/null; then
            xdg-open resultados_tsp.csv
        elif command -v open > /dev/null; then
            open resultados_tsp.csv
        else
            echo "Não foi possível abrir o arquivo automaticamente."
            echo "O arquivo está em: $(pwd)/resultados_tsp.csv"
        fi
    else
        echo "Arquivo nao encontrado. Execute o programa primeiro."
        read -p "Pressione ENTER para continuar..."
    fi
elif [ "$opcao" = "3" ]; then
    if command -v xdg-open > /dev/null; then
        xdg-open apresentacao.html
    elif command -v open > /dev/null; then
        open apresentacao.html
    else
        echo "Não foi possível abrir o arquivo automaticamente."
        echo "O arquivo está em: $(pwd)/apresentacao.html"
    fi
elif [ "$opcao" = "0" ]; then
    exit 0
else
    echo "Opcao invalida!"
    read -p "Pressione ENTER para continuar..."
    exec $0
fi

echo
read -p "Pressione ENTER para continuar..."
