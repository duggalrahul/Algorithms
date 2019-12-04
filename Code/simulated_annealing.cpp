#include "simulated_annealing.h"


// cost1 is cost of existing_tour and cost2 is cost of neighbouring tour
// if fn returns 1 then we chose neighbour else chose existing
bool metropolis_criterion(double cost1, double cost2, double T){
	 if(cost2 < cost1){
	 	return true;
	 }
	 double probability = exp((cost1 - cost2) / T);

	 bool TrueFalse = (rand() % 100) < (int)(probability*100);

	 return TrueFalse;

}


// function returns a tuple of (instance tuple, cost of optimal tour and time taken)
tuple<vector<int>,double,double> simulated_annealing(vtup instance,double time,int seed, vector<tuple<int, double>> &trace){

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
			trace.push_back(make_tuple((int)best_tour_cost,double( clock () - begin_time ) /  CLOCKS_PER_SEC));
		}

		if(metropolis_criterion(existing_tour_cost,neighbour_tour_cost,T)){
			existing_tour = neighbouring_tour;
		}

		T = a*T;

	}

	// cout<<"Original cost was "<<get_tour_length(get_random_tour(instance,seed))<<" new cost is "<<get_tour_length(existing_tour)<<endl;
	// cout<<"Time taken (s) "<<time_in_seconds<<endl;

	vector<int> tour;
	int i;
	for(i=0;i<existing_tour.size()-1;i++){
		tour.push_back(get<0>(existing_tour[i])-1);
	}

	auto result = std::make_tuple(tour,best_tour_cost,time_in_seconds); 

	return result;
}