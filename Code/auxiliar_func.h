#pragma once

#include <stdio.h>
#include <vector>
#include <tuple>
#include <math.h>
//#include "/Users/rahul/Projects/headers/stdc++.h" // For rahul's macbook
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <iomanip>
#include <limits>



using std::fstream;
using std::string;

using namespace std;

extern int inf ;

vector<vector<int>> compute_dist_matrix(vector<double> coord_x, vector<double> coord_y);

vector<vector<int>> compute_dist_matrix(vector<float> coord_x, vector<float> coord_y);

vector<vector<int>> compute_dist_matrix(vector<tuple<int, double, double>> instance);

int output_solution(string filename, string method, float cutoff, int random_seed, int best, vector<int> best_sol);

int output_solution(string filename, string method, float cutoff, int best, vector<int> best_sol);

int output_trace(string filename, string method, float cutoff, int random_seed, vector<tuple<int, double>> trace);

int output_trace(string filename, string method, float cutoff, vector<tuple<int, double>> trace);


// added by rahul

typedef tuple<int,double,double> tup;
typedef vector<tup> vtup;

/*struct Gen {
  mt19937 g;
  Gen()
   : g(static_cast<uint32_t>(time(0)))
  {
  }
  size_t operator()(size_t n)
  {
    std::uniform_int_distribution<size_t> d(0, n ? n-1 : 0);
    return d(g);
  }
};*/

double get_distance(tup city1, tup city2);
bool check_tour_validness(vtup tour);
double get_tour_length(vtup tour);
vtup get_random_tour(vtup instance,int seed);
vtup two_opt_swap(vtup tour,int i,int k);
void  print_tour(vtup tour);
vtup get_random_neighbour(vtup tour);
vector<vtup> get_neighbours(vtup tour);
