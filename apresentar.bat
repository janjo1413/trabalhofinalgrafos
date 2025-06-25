@echo off
echo.
echo ============================================
echo   TRABALHO FINAL - TEORIA DOS GRAFOS
echo   Problema do Caixeiro Viajante Simetrico
echo ============================================
echo.
echo Escolha uma opcao:
echo.
echo 1. Executar programa TSP
echo 2. Ver resultados (CSV)
echo 3. Abrir documentacao
echo 0. Sair
echo.
set /p opcao="Sua escolha: "

if "%opcao%"=="1" (
    if exist tsp_solver.exe (
        echo Executando programa...
        tsp_solver.exe
    ) else (
        echo Compilando...
        g++ -std=c++17 -O2 src/Graph.cpp src/TSPSolver.cpp src/PerformanceAnalyzer.cpp main.cpp -o tsp_solver.exe
        if exist tsp_solver.exe (
            tsp_solver.exe
        ) else (
            echo ERRO: Falha na compilacao!
            pause
        )
    )
) else if "%opcao%"=="2" (
    if exist resultados_tsp.csv (
        start resultados_tsp.csv
    ) else (
        echo Arquivo nao encontrado. Execute o programa primeiro.
        pause
    )
) else if "%opcao%"=="3" (
    start apresentacao.html
) else if "%opcao%"=="0" (
    exit
) else (
    echo Opcao invalida!
    pause
    apresentar.bat
)

echo.
pause
