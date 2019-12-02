// compile : g++ -Wall -o main main.cpp
// execute : ./main -inst "../DATA/Atlanta.tsp" -alg "BnB" -time 10 -seed 0


#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <sstream>
#include <iterator>
#include "branch_and_bound.h"
#include "Approx.h"

using namespace std;

string INPUT_FORMAT = "./main.cpp -inst <filename> -alg [BnB | Approx | LS1 | LS2] -time <cutoff_in_seconds> [-seed <random_seed>]";


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

typedef tuple<int,double,double> tup;
typedef vector<tup> vtup;

double get_distance(tup city1, tup city2){
	double city1_x = get<1>(city1);
	double city2_x = get<1>(city2);
	double city1_y = get<2>(city1);
	double city2_y = get<2>(city2);

	return sqrt((city1_x-city2_x)*(city1_x-city2_x) + (city1_y-city2_y)*(city1_y-city2_y));
}


bool check_tour_validness(vtup tour){
	if(get<0>(tour[0]) != get<0>(tour[tour.size()-1])){
		cout<<"Error: The tour should return back to the original location"<<endl;
		return false;
	}
	return true;
}

double get_tour_length(vtup tour){
	uint i;
	double tour_length = 0;

	check_tour_validness(tour);
	

	for(i=1;i<tour.size();i++){
		tour_length += get_distance(tour[i],tour[i-1]);
	}

	return tour_length;
}


// This fucntion generates a random tour which is used to initialize our local search.
vtup get_random_tour(vtup instance,int seed){
	
	random_shuffle(instance.begin(),instance.end());

	// last city should be same as the first
	instance.push_back(instance[0]);

	return instance;
}

// This function implements the 2 opt swap outlined at https://en.wikipedia.org/wiki/2-opt
vtup two_opt_swap(vtup tour,int i,int k){
	vector<tuple<int,double,double>> new_tour;
	int j;

	// step 1 in wiki
	for(j=0;j<i;j++){
		new_tour.push_back(tour[j]);
	}
	// step 2 in wiki
	for(j=k;j>=i;j--){
		new_tour.push_back(tour[j]);
	}
	// step 3 in wiki
	for(j=k+1;j<tour.size();j++){
		new_tour.push_back(tour[j]);
	}

	return new_tour;
}


void  print_tour(vtup tour){
	int i;

	check_tour_validness(tour);

	cout<<"Tour ordrering is as below"<<endl;
	for(i=0;i<tour.size();i++){
		cout<<get<0>(tour[i])<<endl;
	}
}

vector<vtup> get_neighbours(vtup tour){

	check_tour_validness(tour);

	vector<vtup> neighbours;
	int i,k;

	for(i=1;i<tour.size()-1;i++){
		for(k=i+1;k<tour.size()-1;k++){
			
			vtup neighbour = two_opt_swap(tour,i,k);
			// cout<<"i "<<i<<" k "<<k<<" cost "<<get_tour_length(neighbour)<<endl;
			neighbours.push_back(neighbour);
		}
	}

	return neighbours;	
}

// this function constructs a random neighbouring tour using 2-opt
vtup get_random_neighbour(vtup tour){
	check_tour_validness(tour);

	// we need two random numbers in [min,max] for call to 2-opt
	int min = 1;
	int max = tour.size()-1 - min;

	// get two distinct numbers r1 and r2
	int r1 = rand() % max + min;
	int r2 = r1;
	while(r1 == r2){
		r2 = rand() % max + min;
	} 

	// we need to have i<k
	int i = std::min(r1,r2);
	int k = std::max(r1,r2);

	// cout<<"random i and k are "<<i<<" "<<k<<endl;

	return two_opt_swap(tour,i,k);
}

vtup hill_climbing(vtup instance,double time,int seed){

	const clock_t begin_time = clock();
	vtup existing_tour = get_random_tour(instance,seed);
	vtup best_neighbouring_tour;
	double global_best_cost;
	int i;
	int iter = 0;
	double time_in_seconds;

	global_best_cost = get_tour_length(existing_tour);

	while(1){			
		iter++;

		time_in_seconds = double( clock () - begin_time ) /  CLOCKS_PER_SEC;


		if(time_in_seconds > time*60){
			break;
		}

		// generate neighbours of current tour using 2-opt
		vector<vtup> neighbours = get_neighbours(existing_tour);
		double neighbour_best_cost = get_tour_length(existing_tour);
		long long cost;

		cout<<"time (s) "<<time_in_seconds<< "num neighbours "<<neighbours.size()<<endl;

		// iterate through neighbours to find neighbour with lowest cost
		for(i=0;i<neighbours.size();i++){
			cost = get_tour_length(neighbours[i]);

			if(cost < neighbour_best_cost){
				best_neighbouring_tour = neighbours[i];
				neighbour_best_cost = cost;
			}
		}

		// if the neighbours optimize global cost, then chose best neighbour else quit
		if(neighbour_best_cost < global_best_cost){
			global_best_cost = neighbour_best_cost;
			existing_tour = best_neighbouring_tour;
		}
		else{
			break;
		}

		// cout<<"iter "<<iter<<" best cost "<<global_best_cost<<endl;

	}

	cout<<"Original cost was "<<get_tour_length(get_random_tour(instance,seed))<<" new cost is "<<get_tour_length(existing_tour)<<endl;
	cout<<"Time taken (s) "<<time_in_seconds<<endl;

	return existing_tour;
}

// cost1 is cost of existing_tour and cost2 is cost of neighbouring tour
// if fn returns 1 then we chose neighbour else chose existing
bool metropolis_criterion(double cost1, double cost2, double T){
	 if(cost2 < cost1){
	 	return true;
	 }
	 double probability = exp((cost1 - cost2) / T);

	 bool TrueFalse = (rand() % 100) < (int)(probability*100);

	 // cout<<" probability "<<probability<<" "<<TrueFalse<<endl;

	 return TrueFalse;

}


double simulated_annealing(vtup instance,double time,int seed){

	const clock_t begin_time = clock();
	vtup existing_tour = get_random_tour(instance,seed);
	vtup neighbouring_tour = get_random_neighbour(existing_tour);
	vtup best_tour;

	// Define annealing parameters
	int t,max_t = 20000;
	double T = 10;
	double a = 0.95; // geometric schedule
	double best_tour_cost = get_tour_length(existing_tour);
	double existing_tour_cost = get_tour_length(existing_tour);
	double neighbour_tour_cost = get_tour_length(existing_tour);
	double time_in_seconds;

	for(t=1;t<max_t;t++){

		time_in_seconds = double( clock () - begin_time ) /  CLOCKS_PER_SEC;

		// cout<<"time (s) "<<time_in_seconds<<endl;

		if(time_in_seconds > time*60){
			break;
		}

		// generate random neighbour from current tour
		vtup neighbouring_tour = get_random_neighbour(existing_tour);

		existing_tour_cost = get_tour_length(existing_tour);
		neighbour_tour_cost = get_tour_length(neighbouring_tour);

		if(existing_tour_cost < best_tour_cost){
			best_tour_cost = existing_tour_cost;
			best_tour = existing_tour;
		}

		if(metropolis_criterion(existing_tour_cost,neighbour_tour_cost,T)){
			existing_tour = neighbouring_tour;
		}

		T = a*T;

		// cout<<"best cost "<<best_tour_cost<<endl;


	}

	cout<<"Original cost was "<<get_tour_length(get_random_tour(instance,seed))<<" new cost is "<<get_tour_length(existing_tour)<<endl;
	cout<<"Time taken (s) "<<time_in_seconds<<endl;

	return 0;
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
	else if(algorithm == (string)"LS1"){
		cout<<"Solving using Hill Climbing"<<endl;
		srand(seed);
		hill_climbing(instance,time,seed);
	}
	else if(algorithm == (string)"LS2"){
		cout<<"Solving using Simulated Annealing"<<endl;
		srand(seed);		
		simulated_annealing(instance,time,seed);
	}
   
  
    return 0; 
}