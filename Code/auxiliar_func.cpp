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


vector<vector<int>> compute_dist_matrix(vector<tuple<int, float, float>> instance)
{

	int n = instance.size();
	vector<vector<int>> distances;


	distances.resize(n);


	int max_dist = 0;
	for (int row = 0; row<n; row++)
	{
		for (int col = 0; col < n; col++)
		{

			distances[row].push_back(int(sqrt(pow(std::get<1>(instance[row]) - std::get<1>(coord_x[col]), 2) 
				+ pow(std::get<2>(coord_y[row]) - std::get<2>(coord_y[col]), 2)) + 0.50000000001));

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