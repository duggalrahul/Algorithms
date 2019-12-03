output: main.o auxiliar_func.o Approx.o branch_and_bound.o
	g++ main.o auxiliar_func.o Approx.o branch_and_bound.o -o tsp_main

main.o: main.cpp
	g++ -c main.cpp

auxiliar_func.o: auxiliar_func.cpp auxiliar_func.h
	g++ -c auxiliar_func.cpp

Approx.o: Approx.cpp Approx.h
	g++ -c Approx.cpp

branch_and_bound.o: branch_and_bound.cpp branch_and_bound.h
	g++ -c branch_and_bound.cpp

clean:
	rm *.o tsp_main

