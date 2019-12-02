#include "auxiliar_func.h"


int inf = 100000000000;

vector<vector<int>> compute_dist_matrix(vector<double> coord_x, vector<double> coord_y)
{

	int n = coord_x.size();
	vector<vector<int>> distances;


	distances.resize(n);


	int max_dist = 0;
	for (int row = 0; row<n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			
			distances[row].push_back(int(sqrt(pow(coord_x[row] - coord_x[col], 2) + pow(coord_y[row] - coord_y[col], 2)) + 0.50000000001));
			
			if (distances[row][col]>max_dist)
				max_dist = distances[row][col] + 1;
		}
		
	}
	printf("max distanace %d\n", max_dist);
	max_dist *= n;
	inf = max_dist;

	for (int row = 0; row < n; row++)
	{
		distances[row][row] = max_dist;
	}
	printf("inf distanace %d\n", inf);

	return distances;
}


vector<vector<int>> compute_dist_matrix(vector<float> coord_x, vector<float> coord_y)
{

	int n = coord_x.size();
	vector<vector<int>> distances;


	distances.resize(n);


	int max_dist = 0;
	for (int row = 0; row<n; row++)
	{
		for (int col = 0; col < n; col++)
		{

			distances[row].push_back(int(sqrt(pow(coord_x[row] - coord_x[col], 2) + pow(coord_y[row] - coord_y[col], 2)) + 0.50000000001));

			if (distances[row][col]>max_dist)
				max_dist = distances[row][col] + 1;
		}

	}
	printf("max distanace %d\n", max_dist);
	max_dist *= n;
	inf = max_dist;

	for (int row = 0; row < n; row++)
	{
		distances[row][row] = max_dist;
	}
	printf("inf distanace %d\n", inf);

	return distances;
}


vector<vector<int>> compute_dist_matrix(vector<tuple<int, double, double>> instance)
{

	int n = instance.size();
	vector<vector<int>> distances;

	distances.resize(n);
	

	int max_dist = 0;
	for (int row = 0; row<n; row++)
	{
		for (int col = 0; col < n; col++)
		{

			distances[row].push_back(int(sqrt(pow(std::get<1>(instance[row]) - std::get<1>(instance[col]), 2)
				+ pow(std::get<2>(instance[row]) - std::get<2>(instance[col]), 2)) + 0.50000000001));

			if (distances[row][col]>max_dist)
				max_dist = distances[row][col] + 1;
		}

	}
	printf("max distanace %d\n", max_dist);
	max_dist *= n;
	inf = max_dist;

	for (int row = 0; row < n; row++)
	{
		distances[row][row] = max_dist;
	}
	printf("inf distanace %d\n", inf);

	return distances;
}


int output_solution(string filename, string method, float cutoff, int random_seed,  int best, vector<int> best_sol)
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
			sol_file << std::fixed << std::setprecision(2) << std::get<1>(trace[i]) << ", " << std::get<0>(trace[i]) << endl;
		}

		sol_file.close();
	}
	else
		printf("File could not be open\n");

	return 0;
}


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
			sol_file << std::fixed << std::setprecision(2) << std::get<1>(trace[i]) << ", " << std::get<0>(trace[i]) << endl;
		}

		sol_file.close();
	}
	else
		printf("File could not be open\n");

	return 0;
}