cc := g++
flags := -lraylib -lm -lpthread

all: grid main gol run
grid: grid.cpp
	$(cc) -O2 grid.cpp -c grid.o $(flags)

gol: Simulation.cpp
	$(cc) -O2 Simulation.cpp -c Simulation.o $(flags)

main: main.cpp
	$(cc) -O2 main.cpp -c main.o $(flags)

run: main.o grid.o Simulation.o
	$(cc) -O2 main.o grid.o Simulation.o -o run $(flags) && ./run
