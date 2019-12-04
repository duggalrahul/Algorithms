#include "auxiliar_func.h"
using namespace std;

int inf= 100000000;

/*
**********************************************************************************************************************************
* DESCRIPTION:
* Computes the distance matrix for the instance of the problem.
**********************************************************************************************************************************
* INPUTS:
* vector<tuple<int, double, double>>: Each tuple represents one city of the instance, 
 the tuple has the form: <index, x coordinate, y coordinate>
**********************************************************************************************************************************
* OUTPUT:
* Return: The distance matrix, entry (i,j) of matrix represents the distance between cities i and j.
*/
vector<vector<int>> compute_dist_matrix(vector<tuple<int, double, double>> instance)
{
    // Get instance size
	int n = instance.size();
    
    // Initialize distance matrix
	vector<vector<int>> distances;
	distances.resize(n);	

	int max_dist = 0;
    
    // Run through the cities and compute pairwise distance
	for (int row = 0; row<n; row++)
	{
		for (int col = 0; col < n; col++)
		{
            // Computes Euclidean distance rounded to the nearest int.
			distances[row].push_back(int(sqrt(pow(std::get<1>(instance[row]) - std::get<1>(instance[col]), 2)
				+ pow(std::get<2>(instance[row]) - std::get<2>(instance[col]), 2)) + 0.50000000001));

            // Compute the largest distance
			if (distances[row][col]>max_dist)
				max_dist = distances[row][col] + 1;
		}

	}
	
    // Update the inf value
	max_dist *= n;
	inf = max_dist;

    // Set diagonal of distance matrix to inf
	for (int row = 0; row < n; row++)
	{
		distances[row][row] = max_dist;
	}
	

	return distances;
}

/*
**********************************************************************************************************************************
* DESCRIPTION:
* Creates the solution file.
**********************************************************************************************************************************
* INPUTS:
* string filename: filename with path of the input instance
*
* string method: Algorithm used for the solution.
*
* float cutoff: Cutoff time used with the algorithm.
*
* int random_seed: Random seed used for the algorithm.
*
* int best: Best solution found.
*
* vector<int> best_sol: Best solution found
**********************************************************************************************************************************
* OUTPUT:
* Return: 0 ( no meaning )
*/
int output_solution(string filename, string method, float cutoff, int random_seed, int best, vector<int> best_sol)
{
	
	// Remove extension if present.
	const size_t period_idx = filename.rfind('.');
	if (std::string::npos != period_idx)
	{
		filename.erase(period_idx);
	}
	filename = filename + "_" + method + "_" + to_string( int (cutoff)) + "_" + to_string(random_seed) + ".sol";

	ofstream sol_file(filename);

	if (sol_file.is_open())
	{
		sol_file << best << endl << best_sol[0];

		for (int i = 1; i < best_sol.size(); i++)
		{
			sol_file << "," << best_sol[i];
		}
		
		sol_file.close();
	}
	else 
		printf( "File could not be open\n");

	return 0;
}

/*
**********************************************************************************************************************************
* DESCRIPTION:
* Creates the solution file.
**********************************************************************************************************************************
* INPUTS:
* string filename: filename with path of the input instance
*
* string method: Algorithm used for the solution.
*
* float cutoff: Cutoff time used with the algorithm.
*
* int best: Best solution found.
*
* vector<int> best_sol: Best solution found
**********************************************************************************************************************************
* OUTPUT:
* Return: 0 ( no meaning )
*/
int output_solution(string filename, string method, float cutoff, int best, vector<int> best_sol)
{
	

	// Remove extension if present.
	const size_t period_idx = filename.rfind('.');
	if (std::string::npos != period_idx)
	{
		filename.erase(period_idx);
	}
	filename = filename + "_" + method + "_" + to_string(int(cutoff)) + ".sol";

	ofstream sol_file(filename);

	if (sol_file.is_open())
	{
		sol_file << best << endl << best_sol[0];

		for (int i = 1; i < best_sol.size(); i++)
		{
			sol_file << "," << best_sol[i];
		}

		sol_file.close();
	}
	else
		printf("File could not be open\n");

	return 0;
}


/*
**********************************************************************************************************************************
* DESCRIPTION:
* Creates the trace file.
**********************************************************************************************************************************
* INPUTS:
* string filename: filename with path of the input instance
*
* string method: Algorithm used for the solution.
*
* float cutoff: Cutoff time used with the algorithm.
*
* int random_seed: Random seed used for the algorithm.
*
* vector<tuple<int, double>> trace: Trace of the algorithm. Tuple of the form <solution value, time> 
**********************************************************************************************************************************
* OUTPUT:
* Return: 0 ( no meaning )
*/
int output_trace(string filename, string method, float cutoff, int random_seed, vector<tuple<int, double>> trace)
{

	// Remove extension if present.
	const size_t period_idx = filename.rfind('.');
	if (std::string::npos != period_idx)
	{
		filename.erase(period_idx);
	}
	filename = filename + "_" + method + "_" + to_string(int(cutoff)) + "_" + to_string(random_seed) + ".trace";

	ofstream sol_file(filename);

	if (sol_file.is_open())
	{
		
		for (int i = 0; i < trace.size(); i++)
		{
			sol_file << std::fixed << std::setprecision(2) << std::get<1>(trace[i]) << ", " << std::get<0>(trace[i]);
            if (i < (trace.size()-1) )
            {
                sol_file << endl;
            }
		}

		sol_file.close();
	}
	else
		printf("File could not be open\n");

	return 0;
}

/*
**********************************************************************************************************************************
* DESCRIPTION:
* Creates the trace file.
**********************************************************************************************************************************
* INPUTS:
* string filename: filename with path of the input instance
*
* string method: Algorithm used for the solution.
*
* float cutoff: Cutoff time used with the algorithm.
*
* vector<tuple<int, double>> trace: Trace of the algorithm. Tuple of the form <solution value, time> 
**********************************************************************************************************************************
* OUTPUT:
* Return: 0 ( no meaning )
*/
int output_trace(string filename, string method, float cutoff, vector<tuple<int, double>> trace)
{


	// Remove extension if present.
	const size_t period_idx = filename.rfind('.');
	if (std::string::npos != period_idx)
	{
		filename.erase(period_idx);
	}
	filename = filename + "_" + method + "_" + to_string(int(cutoff)) + ".trace";

	ofstream sol_file(filename);

	if (sol_file.is_open())
	{
		
		for (int i = 0; i < trace.size(); i++)
		{
			sol_file << std::fixed << std::setprecision(2) << std::get<1>(trace[i]) << ", " << std::get<0>(trace[i]);
            
            if (i < (trace.size()-1) )
            {
                sol_file << endl;
            }
		}

		sol_file.close();
	}
	else
		printf("File could not be open\n");

	return 0;
}



double get_distance(tup city1, tup city2){
	double city1_x = get<1>(city1);
	double city2_x = get<1>(city2);
	double city1_y = get<2>(city1);
	double city2_y = get<2>(city2);

	return sqrt((city1_x-city2_x)*(city1_x-city2_x) + (city1_y-city2_y)*(city1_y-city2_y));
}


bool check_tour_validness(vtup tour){
	if(get<0>(tour[0]) != get<0>(tour[tour.size()-1])){
		std::cout<<"Error: The tour should return back to the original location"<<std::endl;
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
	
	random_shuffle(begin(instance),end(instance));

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