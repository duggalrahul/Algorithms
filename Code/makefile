output: main.o auxiliar_func.o Approx.o branch_and_bound.o hill_climbing.o simulated_annealing.o 
	g++ main.o auxiliar_func.o Approx.o branch_and_bound.o hill_climbing.o simulated_annealing.o -o tsp_main

main.o: main.cpp
	g++ -c main.cpp

auxiliar_func.o: auxiliar_func.cpp auxiliar_func.h
	g++ -c auxiliar_func.cpp

Approx.o: Approx.cpp Approx.h
	g++ -c Approx.cpp

simulated_annealing.o: simulated_annealing.cpp simulated_annealing.h
	g++ -c simulated_annealing.cpp

hill_climbing.o: hill_climbing.cpp hill_climbing.h
	g++ -c hill_climbing.cpp

branch_and_bound.o: branch_and_bound.cpp branch_and_bound.h
	g++ -c branch_and_bound.cpp

clean:
	rm *.o tsp_main

