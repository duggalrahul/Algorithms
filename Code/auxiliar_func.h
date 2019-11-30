#ifndef _AUXILIAR_
#define _AUXILIAR_

#include <stdio.h>
#include <vector>
#include <tuple>
#include <math.h>

#include <fstream>
#include <string>
#include <stdlib.h> 




using std::fstream;
using std::string;

using namespace std;

extern int inf ;

vector<vector<int>> compute_dist_matrix(vector<double> coord_x, vector<double> coord_y);

vector<vector<int>> compute_dist_matrix(vector<float> coord_x, vector<float> coord_y);

vector<vector<int>> compute_dist_matrix(vector<tuple<int, double, double>> instance);

#endif