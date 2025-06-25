# Makefile para o Projeto TSP
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRCDIR = src
SOURCES = $(SRCDIR)/Graph.cpp $(SRCDIR)/TSPSolver.cpp $(SRCDIR)/PerformanceAnalyzer.cpp main.cpp
TARGET = tsp_solver

# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    RM = del /Q
    RM_DIR = rd /S /Q
    RUN_PREFIX = 
else
    RM = rm -f
    RM_DIR = rm -rf
    RUN_PREFIX = ./
endif

# Regra principal
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Compilação com debug
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Limpeza
clean:
	$(RM) $(TARGET) 

# Execução
run: $(TARGET)
	$(RUN_PREFIX)$(TARGET)

.PHONY: all debug clean run
