// compile : g++ -Wall -o main main.cpp
// execute : ./main -inst "../DATA/Atlanta.tsp" -alg "BnB" -time 10 -seed 0


#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <sstream>
#include <iterator>
  

using namespace std;

string INPUT_FORMAT = "./main.cpp -inst <filename> -alg [BnB | Approx | LS1 | LS2] -time <cutoff_in_seconds> [-seed <random_seed>]";


void throw_input_parse_error(){
	cout<<"Please follow the specified input format"<<endl<<INPUT_FORMAT<<endl;
}

tuple<string,string,float,int> parse_input(int argc, char** argv){
	string filename;
	string algorithm;
	float time;
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

vector<tuple<int,float,float>> read_tsp_file(string filename){
	vector<tuple<int,float,float>> instance;
	ifstream tspfile(filename);
	string line;
	int skip_flag = 1;

	if(tspfile.is_open()){
		while ( getline (tspfile,line) )
	    {
	    	// skip until you encounter a line saying "NODE_COORD_SECTION"
			if((string)"NODE_COORD_SECTION" == line){
	    		skip_flag = 0;
	    		continue;
	    	} 
	    	if(skip_flag){
	    		continue;
	    	}

	      	int index;
	      	float x_coordinate,y_coordinate;

	      	if((string)"EOF" != line){
	      		std::istringstream buf(line);
    			std::istream_iterator<std::string> beg(buf), end;

    			std::vector<std::string> tokens(beg, end); // done!

			    index = stoi(tokens[0]);
			    x_coordinate = stof(tokens[1]);
			    y_coordinate = stof(tokens[2]);

			    auto city = make_tuple(index,x_coordinate,y_coordinate);

			    instance.push_back(city);
	      	}
	      	else{
	      		break;
	      	}	      	
	    }

	    tspfile.close();
	}


	

    return instance;


}

typedef tuple<int,float,float> tup;
typedef vector<tup> vtup;

float get_distance(tup city1, tup city2){
	float city1_x = get<1>(city1);
	float city2_x = get<1>(city2);
	float city1_y = get<2>(city1);
	float city2_y = get<2>(city2);

	return sqrt((city1_x-city2_x)*(city1_x-city2_x) + (city1_y-city2_y)*(city1_y-city2_y));
}


bool check_tour_validness(vtup tour){
	if(get<0>(tour[0]) != get<0>(tour[tour.size()-1])){
		cout<<"Error: The tour should return back to the original location"<<endl;
		return false;
	}
	return true;
}

float get_tour_length(vtup tour){
	uint i;
	float tour_length = 0;

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
	vector<tuple<int,float,float>> new_tour;
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

vtup hill_climbing(vtup instance,float time,int seed){

	vtup existing_tour = get_random_tour(instance,seed);
	vtup best_neighbouring_tour;
	double global_best_cost;
	int i;
	int iter = 0;

	global_best_cost = get_tour_length(existing_tour);

	while(1){			
		iter++;

		// generate neighbours of current tour using 2-opt
		vector<vtup> neighbours = get_neighbours(existing_tour);
		double neighbour_best_cost = get_tour_length(existing_tour);
		long long cost;

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

		cout<<"iter "<<iter<<" best cost "<<global_best_cost<<endl;

	}

	cout<<"Original cost was "<<get_tour_length(get_random_tour(instance,seed))<<" new cost is "<<get_tour_length(existing_tour)<<endl;
	


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


float simulated_annealing(vtup instance,float time,int seed){

	
	vtup existing_tour = get_random_tour(instance,seed);
	vtup neighbouring_tour = get_random_neighbour(existing_tour);
	vtup best_tour;

	// cout<<"Actual tour"<<endl;
	// print_tour(existing_tour);
	// cout<<"Neighbour tour"<<endl;
	// print_tour(neighbouring_tour);

	// Define annealing parameters
	int t,max_t = 20000;
	float T = 10;
	float a = 0.95; // geometric schedule
	double best_tour_cost = get_tour_length(existing_tour);
	double existing_tour_cost = get_tour_length(existing_tour);
	double neighbour_tour_cost = get_tour_length(existing_tour);

	for(t=1;t<max_t;t++){
		

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

		cout<<"best cost "<<best_tour_cost<<endl;


	}



	return 0;
}



int main(int argc, char** argv){
	
	std::tuple<string,string,float,int> input;

	input = parse_input(argc, argv);

	// parse input parameters
	string filename = get<0>(input);
	string algorithm = get<1>(input);
	float time = get<2>(input);
	int seed = get<3>(input);

	// read .tsp file specified by -inst
	vector<tuple<int,float,float>> instance;
	instance = read_tsp_file(filename);

	if(algorithm == (string)"BnB"){
		// add call to branch and bound algorithm here
		// solution = BnB(instance,time,seed);
	}
	else if(algorithm == (string)"Approx"){
		// add call to Approx algorithm here
		// solution = Approx(instance,time,seed);
	}
	else if(algorithm == (string)"LS1"){
		// add call to LS1 algorithm here
		// solution = LS1(instance,time,seed);
		srand(seed);		
		simulated_annealing(instance,time,seed);
		
	}
	else if(algorithm == (string)"LS2"){
		// add call to LS2 algorithm here
		srand(seed);
		hill_climbing(instance,time,seed);
	}
   
  
    return 0; 
}