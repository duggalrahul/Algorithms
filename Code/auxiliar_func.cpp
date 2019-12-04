#include "auxiliar_func.h"


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