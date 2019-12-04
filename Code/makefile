output: main.o auxiliar_func.o Approx.o branch_and_bound.o simulated_annealing.o hill_climbing.o
	g++ -std=c++11 main.o auxiliar_func.o Approx.o branch_and_bound.o hill_climbing.o  simulated_annealing.o -o output

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

auxiliar_func.o: auxiliar_func.cpp auxiliar_func.h
	g++ -std=c++11 -c auxiliar_func.cpp

Approx.o: Approx.cpp Approx.h
	g++ -std=c++11 -c Approx.cpp

simulated_annealing.o: simulated_annealing.cpp simulated_annealing.h
	g++ -std=c++11 -c simulated_annealing.cpp

hill_climbing.o: hill_climbing.cpp hill_climbing.h
	g++ -std=c++11 -c hill_climbing.cpp

branch_and_bound.o: branch_and_bound.cpp branch_and_bound.h
	g++ -std=c++11 -c branch_and_bound.cpp

clean:
	rm *.o output

