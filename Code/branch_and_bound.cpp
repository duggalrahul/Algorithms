#include <stdio.h>
#include <vector>
#include <time.h>
#include <limits>
#include <math.h>

#include <fstream>

#include <string>

#include "auxiliar_func.h"

using std::fstream;
using std::string;

using namespace std; 

// std::numeric_limits<int>::max();

double reduce(vector<vector<int>> &distances)
{
    int n=distances.size();
    
    vector<int> min_row, min_col;
    min_row.resize(n,inf);
    min_col.resize(n,inf);
    
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

	for (int row = 0; row < n; ++row)
	{
		for (int col = 0; col < n; ++col)
		{
			if (min_row[row] < inf  && distances[row][col] < inf)// && col>=1)
				distances[row][col] -= min_row[row];
		}
	}

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
    
    for(int row = 0; row < n; ++row)
    {
       for(int  col= 0; col < n; ++col)
        { 
		   if (min_col[col]<inf && distances[row][col]<inf)
				distances[row][col]-=min_col[col];        
        }
        sum+=min_row[row];
    }
    
    for(int  col= 0; col < n; ++col)
    { 
        sum+=min_col[col];        
    }
    return sum;
}




double left_choice(vector<vector<int>> &distances, int row_del, int col_del, vector<int> indexes_row, vector<int> indexes_col)
{
	int n = distances.size();
	//distances[col_del][row_del] = inf;
	int row,col;
	

	if (!distances.empty())
	{
		for (int rows = 0; rows < n; ++rows)
		{
			distances[rows].erase(distances[rows].begin() + col_del);
		}
	}

	distances.erase(distances.begin() + row_del);

	return 0;

}

double choose_edge(vector<vector<int>> &distances, int &row_choose, int &col_choose)
{
    int n=distances.size();
    
    int min_edge=inf;
    
    
    //for(int row = 0; row < n; ++row)
    {
       for(int  col= 1; col < n; ++col)
        { 
		   if (distances[row_choose][col] < min_edge)
            {
			   min_edge = distances[row_choose][col];
                //row_choose=row;
                col_choose=col;
            }
           
        }
    }

	/*if (min_edge == inf)
	{
		row_choose = -1;
	}*/
    return 0;
    
}

int branch_and_bound_2(vector<vector<int>> distances, vector<int> indexes_row,vector<int> indexes_col,
	int &best, vector<int> &best_sol, vector<int> current_solution, int lower_bound, int row_choose, int col_choose, bool left, clock_t start_time)
{
    
	double current_time = double(clock() - start_time) / double(CLOCKS_PER_SEC);

	if (current_time > 6000)
	{
		printf("overtime\n");
		return 0;
	}
		

	int lower_plus=0;


	int n = distances.size();

	/*for(int row = 0; row < n; ++row)
	{
		for (int col = 0; col < n; ++col)
		{
			printf("%d ", distances[row][col]);

		}
		printf("\n");
	}*/

    if(row_choose>-1)
    {

        if(left)
        {
			
			left_choice(distances, row_choose, col_choose, indexes_row, indexes_col);
			
            current_solution[indexes_row[row_choose]]=indexes_col[col_choose];
			indexes_row.erase(indexes_row.begin()+row_choose);
			
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
			if (indexes_row[row] != indexes_col[col_choose])
				printf("warning_________________________________________________________________________________\n");


			indexes_col.erase(indexes_col.begin() + col_choose);
            lower_plus=reduce(distances);
            lower_bound += lower_plus;
			
            if(distances.size()<=2)
            {
				current_solution[indexes_row[row_choose]] = indexes_col[1];

				lower_bound += distances[(row_choose + 1) % 2][0] + distances[row_choose][1];
                if(lower_bound<best)
                {
					
                    best=lower_bound;
                    best_sol=current_solution;
					printf("best so far %d\n", best);	


					int sum = 0;
					for (int row = 0; row < current_solution.size(); row++)
					{
						

						//sum += distances[row][best_sol[row]];
					}

                }
                return 0;
            }
			
        }
        else
        {
			
            distances[row_choose][col_choose]=inf;
			
            lower_plus=reduce(distances);
			
            lower_bound+=lower_plus;
			
        }
    }
    else
    {
        lower_bound=reduce(distances);
		row_choose = col_choose = 0;
    }
    
	
	if (lower_bound>=best )
    {
        return 0;
    }

	
    choose_edge(distances,  row_choose, col_choose); 

	if (distances[row_choose][col_choose] >= inf)
		return 0;
	

	branch_and_bound_2(distances, indexes_row, indexes_col, best, best_sol, current_solution, lower_bound + distances[row_choose][col_choose], row_choose, col_choose, true, start_time);
	
	branch_and_bound_2(distances, indexes_row, indexes_col, best, best_sol, current_solution, lower_bound, row_choose, col_choose, false, start_time);
  
      
    
    return 0;
}



int main() 
{ 
  
	string filepath="C:\\Users\\fsenhora3\\Dropbox\\PhD\\classes\\algorithms\\project\\DATA\\DATA\\UKansasState.tsp";

	fstream file;
	file.open((char*) filepath.c_str(), fstream::in);

if(!file.is_open())
  {
    printf( "File could not be open.\n");

	system("pause");
    return false;
  }

  string label;
  int n, id, idummy;
  double ddummy;

  
  vector<double> coord_x,coord_y;

  while (file>>label && label != "EOF")
  {

    if(label == "DIMENSION:")
    {
      file >> n;
      
      printf("Locations: %d \n", n);
      coord_x.resize(n,0);
      coord_y.resize(n,0);      
    }
	else if (label == "NODE_COORD_SECTION")
	{
		for (int i = 0; i < n; ++i)
		{
			file >> idummy;
			file >> coord_x[i];
			file >> coord_y[i];


			printf("Location %d: ( %f , %f ) \n", idummy, coord_x[i], coord_y[i]);
		}
		printf("Node coordinates Loaded\n");
	}
  }      

  
  vector<int> indexes_row, indexes_col, best_sol, current_solution;
  
  best_sol.resize(n,0);
  current_solution.resize(n,0);
  
	vector<vector<int>> distances;
	distances = compute_dist_matrix( coord_x, coord_y );
  
  for(int row=0; row<n;row++)
  {
	  
        indexes_row.push_back(row);
        indexes_col.push_back(row);
  }
  

 int best=inf, lower_bound=0;
 int row_choose=-1, col_choose=-1;


 printf("Start! \n");

 clock_t start_time;

 start_time = clock();


  branch_and_bound_2( distances,  indexes_row, indexes_col, best, best_sol,  current_solution,
	  lower_bound, row_choose, col_choose, true, start_time);
  
  printf("Best Solution:  %d \n", best);
  
  int sum = 0;
  for (int row = 0; row < n; row++)
  {
	  printf(" %d --->  %d \n", row, best_sol[row]);

	  sum += distances[row][best_sol[row]];
  }

  printf("Best Solution:  %d  \n", sum);

  double runtime = double(clock() - start_time) / double(CLOCKS_PER_SEC);

  printf("Total time:  %f s \n", runtime);

  printf("Finished!!\n");

  system("pause");

    return 0; 
} 