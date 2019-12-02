#pragma once

#include <stdio.h>
#include <vector>
#include <tuple>
#include <math.h>

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
