#pragma once

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

double reduce(vector<vector<int>> &distances);

double left_choice(vector<vector<int>> &distances, int row_del, int col_del);

double choose_edge(vector<vector<int>> &distances, int &row_choose, int &col_choose);

int branch_and_bound(vector<vector<int>> distances, double max_time,
	int &best, vector<int> &best_sol, vector<tuple<int, double>> &trace, vector<int> current_solution = vector<int>(),
	vector<int> indexes_row = vector<int>(), vector<int> indexes_col = vector<int>(), int lower_bound = inf,
	int row_choose = -1, int col_choose = -1, bool left = true, clock_t start_time = clock());
