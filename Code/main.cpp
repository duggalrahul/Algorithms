// compile : g++ -Wall -o main main.cpp
// execute : ./main -inst "../DATA/Atlanta.tsp" -alg "BnB" -time 10 -seed 0


#include <iostream>
#include <fstream>
// #include <bits/stdc++.h> 
# include "/Users/rahul/Projects/headers/stdc++.h" // For rahul's macbook
#include <stdlib.h> 
#include <sstream>
#include <iterator>
#include "branch_and_bound.h"
#include "Approx.h"
#include "hill_climbing.h"
#include "simulated_annealing.h"

using namespace std;

string INPUT_FORMAT = "./main.cpp -inst <filename> -alg [BnB | Approx | hill_climbing | simulated_annealing] -time <cutoff_in_seconds> [-seed <random_seed>]";


void throw_input_parse_error(){
	cout<<"Please follow the specified input format"<<endl<<INPUT_FORMAT<<endl;
}

tuple<string,string,double,int> parse_input(int argc, char** argv){
	string filename;
	string algorithm;
	double time;
	int seed;

	if (argc != 9) {
        // we assume there are 8 input args
        throw_input_parse_error();
        // return 0;
    }
    else{

    	if ((string)"-inst" == (string)argv[1]) {
    		filename = argv[2];
    	}
    	else{
    		throw_input_parse_error();
    	}

    	if ((string)"-alg" == (string)argv[3]) {
    		algorithm = argv[4];
    	}
    	else{
    		throw_input_parse_error();
    	}

    	if ((string)"-time" == (string)argv[5]) {
    		time = atof(argv[6]);
    	}
    	else{
    		throw_input_parse_error();
    	}

    	if ((string)"-seed" == (string)argv[7]) {
    		seed = atoi(argv[8]);
    	}
    	else{
    		throw_input_parse_error();
    	}
    }

    auto input = std::make_tuple(filename,algorithm,time,seed); 

    return input;

}

vector<tuple<int,double,double>> read_tsp_file(string filename){
	vector<tuple<int, double, double>> instance;
	ifstream tspfile(filename);
	string line;
	int skip_flag = 1;
	double x_coordinate,y_coordinate;

	
	
	string label;
	int n, index, idummy;
	double ddummy;

	if (!tspfile.is_open())
	{
		printf("File could not be open.\n");
		return instance;
	}

	while (tspfile >> label && label != "EOF")
	{

		if (label == "DIMENSION:")
		{
			tspfile >> n;

		}
		else if (label == "NODE_COORD_SECTION")
		{
			for (int i = 0; i < n; ++i)
			{
				tspfile >> index;
				tspfile >> x_coordinate;
				tspfile >> y_coordinate;

				auto city = make_tuple(index, x_coordinate, y_coordinate);

				instance.push_back(city);

				
			}
			
		}
	}

	tspfile.close();

    return instance;


}

int main(int argc, char** argv){
	
	std::tuple<string,string,double,int> input;

	input = parse_input(argc, argv);

	// parse input parameters
	string filename = get<0>(input);
	string algorithm = get<1>(input);
	double time = get<2>(input);
	int seed = get<3>(input);

	// read .tsp file specified by -inst
	vector<tuple<int, double, double>> instance;

	printf("%s \n", filename.c_str());
	instance = read_tsp_file(filename);

	int n = instance.size();

	vector<vector<int>> distance_matrix = compute_dist_matrix( instance );

	if(algorithm == (string)"BnB"){
		vector<int>  best_sol;
		best_sol.resize(n, 0);
		int best = inf;
		vector<tuple<int, double>> trace;
		double start_time = double(clock());
		branch_and_bound(distance_matrix, double (time), best, best_sol, trace);

		printf("Best Solution:  %d \n", best);	


		int sum = 0;
		for (int row = 0; row < n; row++)
		{
			//printf(" %d --->  %d \n", row, best_sol[row]);

			sum += distance_matrix[row][best_sol[row]];
		}

		printf("Best Solution (sum):  %d  \n", sum);

		double runtime = double(clock() - start_time) / double(CLOCKS_PER_SEC);

		printf("Total time:  %f s \n", runtime);

		for (int row = 0; row < trace.size(); row++)
		{
			printf(" Solution %d  time %f \n", std::get<0>(trace[row]), std::get<1>(trace[row]));

		}

		output_solution(filename, algorithm, time,  best,  best_sol);
		output_trace(filename, algorithm, time, trace);

		printf("Finished!!\n");
	}
	else if(algorithm == (string)"Approx"){
		vector<vector<int>> distance_matrix = compute_dist_matrix( instance );
		double start_time = double(clock());
		tuple<int,vector<int>> solution = Approx(distance_matrix, time, seed);
		output_solution(filename, algorithm, time,  std::get<0>(solution),  std::get<1>(solution));
		double runtime = double(clock() - start_time) / double(CLOCKS_PER_SEC);
		printf("Best Solution (sum):  %d  \n", std::get<0>(solution));
		printf("Total time:  %f s \n", runtime);
	}
	else if(algorithm == (string)"hill_climbing"){
		cout<<"Solving using Hill Climbing"<<endl;
		tuple<vector<int>,double,double> result;
		int run = 0, n_runs=10;
		double average_time = 0, average_cost = 0;
		for(run=1;run<=n_runs;run++){
			srand(run+seed);
			vector<tuple<int, double>> trace;
			result = hill_climbing(instance,time,seed,trace);
			average_cost += get<1>(result) / n_runs;
			average_time += get<2>(result) / n_runs;

			if(run == 1){
				// string filename, string method, float cutoff, int random_seed,  int best, vector<int> best_sol
				output_solution(filename, algorithm, time,  run+seed, get<1>(result),  std::get<0>(result));
				output_trace(filename, algorithm, time, run+seed, trace);
			}
		}
		
		cout<<fixed<<" City "<<filename<<" algorithm "<<algorithm<<" average time "<<average_time<<" average cost "<<average_cost<<endl;
		
	}
	else if(algorithm == (string)"simulated_annealing"){
		cout<<"Solving using Simulated Annealing"<<endl;
		tuple<vector<int>,double,double> result;
		int run = 0, n_runs=10;
		double average_time = 0, average_cost = 0;
		for(run=1;run<=n_runs;run++){
			srand(run+seed);
			vector<tuple<int, double>> trace;
			result = simulated_annealing(instance,time,seed,trace);
			average_cost += get<1>(result) / n_runs;
			average_time += get<2>(result) / n_runs;

			if(run == 1){
				output_solution(filename, algorithm, time, run+seed,  get<1>(result),  std::get<0>(result));
				output_trace(filename, algorithm, time, run+seed, trace);
			}
		}
		cout<<fixed<<" City "<<filename<<" algorithm "<<algorithm<<" average time "<<average_time<<" average cost "<<average_cost<<endl;
		
	}
  
    return 0; 
}