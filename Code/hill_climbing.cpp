#include "hill_climbing.h"

// function returns a tuple of (optimal tour order, cost of optimal tour and time taken)
tuple<vector<int>,int,double> hill_climbing(vtup instance,double time,int seed, vector<tuple<int, double>> &trace){

	const clock_t begin_time = clock();
	vtup existing_tour = get_random_tour(instance,seed);
	vtup best_neighbouring_tour;
	int global_best_cost;
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
		int neighbour_best_cost = get_tour_length(existing_tour);
		int cost;

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
			trace.push_back(make_tuple(global_best_cost,double( clock () - begin_time ) /  CLOCKS_PER_SEC));
		}
		else{
			break;
		}

	}

	vector<int> tour;
	for(i=0;i<existing_tour.size()-1;i++){
		tour.push_back(get<0>(existing_tour[i])-1);
	}

	auto result = std::make_tuple(tour,global_best_cost,time_in_seconds); 

	return result;
}