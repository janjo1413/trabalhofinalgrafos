# Makefile para o Projeto TSP
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRCDIR = src
SOURCES = $(SRCDIR)/Graph.cpp $(SRCDIR)/TSPSolver.cpp $(SRCDIR)/PerformanceAnalyzer.cpp main.cpp
TARGET = tsp_solver.exe

# Regra principal
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Compilação com debug
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Limpeza
clean:
	del /Q $(TARGET) 2>nul || exit 0

# Execução
run: $(TARGET)
	./$(TARGET)

.PHONY: all debug clean run
