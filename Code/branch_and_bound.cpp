#include <stdio.h>
#include <vector>
#include <time.h>
#include <limits>
#include <math.h>
#include <stdlib.h> 
#include <fstream>

#include <string>
#include <tuple>

#include "auxiliar_func.h"

using std::fstream;
using std::string;

using namespace std; 


/*
**********************************************************************************************************************************
* DESCRIPTION:
* This function computes the lower bound for the travelling salesman problem considering the 2 shorstest edges of each node 
* strategy. To do this we first compute the minimum entry of each row and then subtract this minimum from each respective row.
* Then we compute the minimum entry of each column and subtract this minimum from each respective column. Finally, we return the 
* value of the lower bound which is them sum of the minimum of each row plus the minimum of each column.
**********************************************************************************************************************************
* INPUTS:
* vector<vector<int>> distances: This is the distance matrix that records the pairwise distance between each city. The entries
* of this matrix are updated according to the 2 shortest edge strategy for the travelling salesman problem.
**********************************************************************************************************************************
* OUTPUT:
* Return: the lower bound to the current sub-problem.
*/
double reduce(vector<vector<int>> &distances)
{
    int n=distances.size();// Current size of the sub-problem
    
	// Vectors to store the minimum of each row and the minimum of each column
    vector<int> min_row, min_col;
    min_row.resize(n,inf);
    min_col.resize(n,inf);
    
	// Find the minimum of each row
    for(int row = 0; row < n; ++row)
    {
		for (int col = 0; col < n; ++col)
        { 
            if( distances[row][col] < min_row[row])
            {
                min_row[row]=distances[row][col];
            } 
        }
    }

	// Subtract the minimum of each from its respective row
	for (int row = 0; row < n; ++row)
	{
		for (int col = 0; col < n; ++col)
		{
			if (min_row[row] < inf  && distances[row][col] < inf)
				distances[row][col] -= min_row[row];
		}
	}

	// Find the minimum of each column
    for(int row = 0; row < n; ++row)
    {
       for(int  col= 0; col < n; ++col)
        {   
            if( distances[row][col] < min_col[col])
            {
                min_col[col]=distances[row][col];
            }          
        }
    }

    double sum=0;
    
	// Subtract the minimum of each column from its respective column
    for(int row = 0; row < n; ++row)
    {
       for(int  col= 0; col < n; ++col)
        { 
		   if (min_col[col]<inf && distances[row][col]<inf)
				distances[row][col]-=min_col[col];        
        }
        sum+=min_row[row]; // Sums the minimum of each row
    }
    
	// Sums the minimum of each column
    for(int  col= 0; col < n; ++col)
    { 
        sum+=min_col[col];        
    }

    return sum;
}



/*
**********************************************************************************************************************************
* DESCRIPTION:
* This function deletes the row row_del and column col_del from the distance matrix.
**********************************************************************************************************************************
* INPUTS:
* vector<vector<int>> &distances: This is the distance matrix that records the pairwise distance between each city.
*
* int row_del: The row to be deleted.
*
* int col_del: Column to be deleted.
**********************************************************************************************************************************
* OUTPUT:
* Return: 0 ( no meaning )
*/
double left_choice(vector<vector<int>> &distances, int row_del, int col_del)
{
	int n = distances.size();// Current size of the sub-problem

	if (!distances.empty())// Check to see if the distance matrix is not empty
	{
		// Deletes column col_del from distance matrix
		for (int rows = 0; rows < n; ++rows)
		{
			distances[rows].erase(distances[rows].begin() + col_del);
		}
	}

	// Delete row row_del from distance matrix
	distances.erase(distances.begin() + row_del);

	return 0;

}


/*
**********************************************************************************************************************************
* DESCRIPTION:
* This function chooses the edge with the smallest weight in row row_choose of the distance matrix.
**********************************************************************************************************************************
* INPUTS:
* vector<vector<int>> &distances: This is the distance matrix that records the pairwise distance between each city.
*
* int &row_choose: The row in which to look for the smallest edge.
*
* int &col_choose: Returns the chosen column that represent the smallest edge of this row.
**********************************************************************************************************************************
* OUTPUT:
* Return: 0 ( no meaning )
*/
double choose_edge(vector<vector<int>> &distances, int &row_choose, int &col_choose)
{
    int n=distances.size(); // Current size of the sub-problem
    
    int min_edge=inf; // Value of the minimum edge initialized with infinity

    // Loop through the columns of the distance matrix  to find the minimum entry of row row_choose 
    for(int  col= 1; col < n; ++col) 
    { 
		if (distances[row_choose][col] < min_edge) 
        {
			min_edge = distances[row_choose][col]; 
            col_choose=col;
        }          
	}   

    return 0;  
}



/*
**********************************************************************************************************************************
* DESCRIPTION:
* This function uses the branch and bound algorithm to compute the optimal solution to the travelling salesman problem.
* It uses the 2 shorstest edges of each node strategy as a lower bound to the optimal solution. The branch and bound algorithm
* is implemented recursively.
**********************************************************************************************************************************
* INPUTS:
* vector<vector<int>> distances: This is the distance matrix that records the pairwise distance between each city.
*
* clock_t start_time: This is the time at which we started the algorithm, and it is used to limit the running of the algorithm by
the max specified time.
*
* double max_time: Specifys the maximum time, in seconds, for the algorithm.
*
* int &best: Return the value of the best solution found.
*
* vector<int> &best_sol: Returns the best solution found in a vector, such that best_sol[i]=j indicates that the edge (i,j) is 
part of the path found for the solution.
*
* vector<tuple<int, double>> &trace: Return the trace of the algorithm storing the pairs <solution, time stamp>.
*
* vector<int> current_solution: Variable used in the recursion used to store the current solution. When calling this function
just use the default value.
*
* vector<int> indexes_row: Variable used in the recursion to store the rows of the distance matrix which are still available.
When calling this function just use the default value.
*
* vector<int> indexes_col: Variable used in the recursion to store the columns of the distance matrix which are still available.
When calling this function just use the default value.
*
* int lower_bound: Variable used in the recursion to store the current lower bound to the optimal solution. When calling this
function just use the default value.
*
* int row_choose: Variable used in the recursion to determine the next row to chose of the distance matrix. When calling this
function just use the default value.
*
* int col_choose: Variable used in the recursion to determine the next column to chose of the distance matrix. When calling this
function just use the default value.
*
*  bool left: Variable used in the recursion to determine if we include the edge (row_choose, col_choose) in the solution 
(left=TRUE), or if we exclude the edge (row_choose, col_choose) from the solution (left=FALSE). When calling this function just 
use the default value.
**********************************************************************************************************************************
* OUTPUT:
* Return: 0 ( no meaning )
*/
int branch_and_bound_2(vector<vector<int>> distances,  clock_t start_time, double max_time,
	int &best, vector<int> &best_sol, vector<tuple<int, double>> &trace, vector<int> current_solution = vector<int>(), 
	vector<int> indexes_row = vector<int>(), vector<int> indexes_col = vector<int>(), int lower_bound = inf,
	int row_choose=-1, int col_choose=-1, bool left=true)
{
    
	// Check how much time has elapsed since the beginning of the algorithm.
	double current_time = double(clock() - start_time) / double(CLOCKS_PER_SEC);

	// If the elapsed time is greater than the time limit stops the algorithm.
	if (current_time > max_time)
	{
		return 0;
	}		

	// Current size of the sub-problem
	int n = distances.size();

	// If it receives a valid choice for row, otherwise interprets this as the initial call to the algorithm
    if(row_choose>-1)
    {

		// If we should include edge (row_choose, col_choose) to the current solution
        if(left)
        {
			
			// Eliminates the row_choose and the col_choose from the distance matrix because this row and
			// this column do not have any valid choice anymore.
			left_choice(distances, row_choose, col_choose);
			
			// Add edge (row_choose, col_choose) to the current solution
            current_solution[indexes_row[row_choose]]=indexes_col[col_choose];

			// Update the vector that keeps track of the city index of each row
			indexes_row.erase(indexes_row.begin()+row_choose);
			

			// Perform a binary search on the indexes_row vector to find the row corresponding to the 
			// city of index indexes_col[col_choose]. We do this because the next edge that we choose 
			// will come from the last node that we got into.
			int top = n-1, bot = 0, row;
			while (top >= bot)
			{
				row = (top + bot) / 2;
				if (indexes_row[row] > indexes_col[col_choose])
					top = row - 1;
				else if (indexes_row[row] < indexes_col[col_choose])
					bot = row + 1;
				else
					bot = top + 1;
			}
			row_choose = row;
			
			// Update the vector that keeps track of the city index of each column
			indexes_col.erase(indexes_col.begin() + col_choose);
            
			// Updates the lower bound by reducing each row and each column, which means, subtracting
			// the minimum of each row and each column from each entry
            lower_bound += reduce(distances);
			
			// If the size of the distance matrix is less than two then there is only one possible choice left
			// for the remaining edges.
            if(distances.size()<=2)
            {
				// Add the edge to the last remaining node and the last node to the initial node
				current_solution[indexes_row[row_choose]] = indexes_col[1];

				// Add the weight of the edges added this way 
				lower_bound += distances[(row_choose + 1) % 2][0] + distances[row_choose][1];

				// Check if the current solution is better than the best solution found so far
                if(lower_bound<best)
                {
					
					// Update the best solution
                    best=lower_bound;
                    best_sol=current_solution;

					// Update the trace variable
					trace.push_back(make_tuple(best, double(clock() - start_time) / double(CLOCKS_PER_SEC)));
                }
                return 0;
            }
			
        }
        else // If we should exclude edge (row_choose, col_choose) from the current solution
        {			

			// Set the weight of the edge (row_choose, col_choose) to infinity so it wont be chosen
            distances[row_choose][col_choose]=inf;

			// Updates the lower bound by reducing each row and each column, which means, subtracting
			// the minimum of each row and each column from each entry
            lower_bound+=reduce(distances);			
        }
    }
    else // Initial call to this algorithm, initalization of the recursive variables
    {
		
		// Initialization of recursive variables
		current_solution.resize(n, 0);
		for (int row = 0; row < n; row++)
		{
			indexes_row.push_back(row);
			indexes_col.push_back(row);
		}

        lower_bound=reduce(distances);
		row_choose = col_choose = 0;
    }
    
	
	// If the lower bound solution is worst than the best solution found so far terminate this branch
	// of sub-problems
	if (lower_bound>=best )
    {
        return 0;
    }

	// Choose the edge with the minimum weigh leaving the current node
    choose_edge(distances,  row_choose, col_choose); 

	// If the chosen edge weight is infinity means that there is no more valid edges to choose and we
	// terminate this branch of sub-problems
	if (distances[row_choose][col_choose] >= inf)
		return 0;
	
	// Add the edge (row_choose, col_choose) to the solution and solve the branch considering this sub-problem
	branch_and_bound_2(distances, start_time, max_time, best, best_sol, trace, current_solution, indexes_row, indexes_col,
		lower_bound + distances[row_choose][col_choose], row_choose, col_choose, true);
	
	// Exclude the edge (row_choose, col_choose) from the solution and solve the branch considering this sub-problem
	branch_and_bound_2(distances, start_time, max_time, best, best_sol, trace, current_solution, indexes_row, indexes_col,
		lower_bound, row_choose, col_choose, false);
     
    return 0;
}



int main() 
{ 
  
	string filepath="C:\\Users\\fsenhora3\\Dropbox\\PhD\\classes\\algorithms\\project\\DATA\\DATA\\";
	
	string locations[13] = { "Cincinnati.tsp",
		"UKansasState.tsp",
		"Atlanta.tsp",
		"Philadelphia.tsp",
		"Boston.tsp",
		"Berlin.tsp",
		"Champaign.tsp",
		"NYC.tsp",
		"Denver.tsp",
		"SanFrancisco.tsp",
		"UMissouri.tsp",
		"Toronto.tsp",
		"Roanoke.tsp"
	};

	for (int i = 0; i < 14; i++)
	{

		printf("%s \n", locations[i]);
		fstream file;
		string file_full_name = filepath + locations[i];
		file.open((char*)file_full_name.c_str(), fstream::in);

		if (!file.is_open())
		{
			printf("File could not be open.\n");

			system("pause");
			return false;
		}

		string label;
		int n, id, idummy;
		double ddummy;


		vector<double> coord_x, coord_y;

		while (file >> label && label != "EOF")
		{

			if (label == "DIMENSION:")
			{
				file >> n;

				//printf("Locations: %d \n", n);
				coord_x.resize(n, 0);
				coord_y.resize(n, 0);


			}
			else if (label == "NODE_COORD_SECTION")
			{
				for (int i = 0; i < n; ++i)
				{
					file >> idummy;
					file >> coord_x[i];
					file >> coord_y[i];


					//printf("Location %d: ( %f , %f ) \n", idummy, coord_x[i], coord_y[i]);
				}
				//printf("Node coordinates Loaded\n");
			}
		}


		vector<int>  best_sol;
		best_sol.resize(n, 0);
		

		vector<vector<int>> distances;
		distances = compute_dist_matrix(coord_x, coord_y);

		
		int best = inf, lower_bound = 0;
		int row_choose = -1, col_choose = -1;


		printf("Start! \n");

		clock_t start_time;

		start_time = clock();

		vector<tuple<int, double>> trace;
		double max_time = 60 * 1;

		branch_and_bound_2(distances, start_time, max_time, best, best_sol, trace);



		printf("Best Solution:  %d \n", best);

		int sum = 0;
		for (int row = 0; row < n; row++)
		{
			//printf(" %d --->  %d \n", row, best_sol[row]);

			sum += distances[row][best_sol[row]];
		}

		printf("Best Solution:  %d  \n", sum);

		double runtime = double(clock() - start_time) / double(CLOCKS_PER_SEC);

		printf("Total time:  %f s \n", runtime);

		for (int row = 0; row < trace.size(); row++)
		{
			printf(" Solution %d  time %f \n", std::get<0>(trace[row]), std::get<1>(trace[row]));

		}

		printf("Finished!!\n");
		printf("_______________________________________________________________");
	}
  system("pause");

    return 0; 
} 